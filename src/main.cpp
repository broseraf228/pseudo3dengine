#include "console_draw_utils.hpp"
#include "math/vec2.hpp"
#include "math/mtrx.hpp"
#include <iostream>
#include <chrono>
#include <thread>
#include <Windows.h>
#include <cmath>

#define PM(x, y) map_x*y + x 
#define PI 3.1415
#define SCEPROJLEN 2.0
#define SCRS 20.0

char grad[] = "$H80Oo+*;:,.";

struct Map {

    int const map_x, map_y;
    char *map;

    Map() : map_x{ 10 }, map_y{ 10 } {
        map = new char[map_x * map_y]
        {
            '#','#','#','#','#','#','#','#','#','#',
            '#','#','.','.','.','.','.','.','.','#',
            '#','.','.','.','.','.','.','.','.','#',
            '#','.','.','.','.','.','.','.','.','#',
            '#','.','.','.','.','#','.','.','.','#',
            '#','.','.','.','.','#','.','.','.','#',
            '#','.','.','.','#','#','.','.','.','#',
            '#','.','#','.','.','.','.','.','.','#',
            '#','.','.','.','.','.','.','.','.','#',
            '#','#','#','#','#','#','#','#','#','#'
        };
    }
    
    char get(int x, int y) const
    {
        if (x < 0 || x >= map_x || y < 0 || y >= map_y)
            return '?';

        return map[PM(x, y)];
    }
};

struct Camera {

    float FOW = PI/2; // FOV setings
    int ray_count;
    mtrx2* FOVRotators;
    float* FOCRayCos;

    ConsolePrimDrawer* drawer;

    float* lenghts; // for store rays distance

    Camera(ConsolePrimDrawer* drawer, int ray_density) : ray_count{ ray_density }, drawer{ drawer }
    {
        FOVRotators = new mtrx2[ray_count]; // create rotation matrix for create rays
        FOCRayCos = new float[ray_count];
        for (int i = 0; i < ray_count; i++) {
            FOVRotators[i] = mtrx2::mtrx_rotation(FOW / ray_count * i - FOW * 0.5);
            FOCRayCos[i] = 1.0 / cos(FOW / ray_count * i - FOW * 0.5);
            FOVRotators[i].ceil();
        }

        lenghts = new float[ray_count];
    }

    float raycoast(vec2 const& position, vec2 const& direction, Map const& map)
    {
        float step_lenght = 0.02; // lenght of reycoast lenght
        vec2 step_move = direction * step_lenght;

        vec2 pos = position;

        for (int i = 0; i < 1000; i++) {

            if (map.get(pos.x, pos.y) != '.')
                return i * step_lenght;   // if pos == solid block

            pos += step_move;

        }
        
    }

    void multiray_reycoast(vec2 const& position, vec2 const& direction, Map const& map)
    {
        for (int i = 0; i < ray_count; i++) {
            lenghts[i] = raycoast(position, FOVRotators[i] * direction, map);
        }
    }

    void draw_raycoast_result_on_screen()
    {
        float ray_width = float(drawer->get_sx()) / ray_count;

        for(int i = 0; i < ray_count; i++)
        {
            float ray_height = 4 * 0.25 / lenghts[i] * drawer->get_sy(); // barier height * screen distance / lenght to barrier * screen size
            ray_height *= FOCRayCos[i];
            float yoffset = (drawer->get_sy() - ray_height) * 0.5;
            drawer->rectangle(
                ray_width * i, yoffset,
                ray_width * (i+1), ray_height + yoffset,
                'H');
        }
        
    }
};

struct Player {
    vec2 player_position;
    vec2 direction;

    Player(int px, int py) : player_position{ float(px), float(py) }, direction{ 0, 1 } {}

};

int main(int argc, char* argv[])
{
    // init screen
    int screen_x = 120, screen_y = 29;
    ConsolePrimDrawer drawer(screen_x, screen_y);

    //init camera
    Camera camera{&drawer, 240};

    // init map
    Map map{};

    // init player
    Player player{ 4, 2 };


    // test raycoast
    
    mtrx2 rrot = mtrx2::mtrx_rotation(PI / 64);
    rrot.ceil();

    mtrx2 lrot = mtrx2::mtrx_rotation(-PI / 64);
    lrot.ceil();

    mtrx2 rot90 = mtrx2::mtrx_rotation(PI / 2);
    rot90.ceil();

    float speed = 1;

    while(true)
    {
        printf("\r");
        drawer.clear(); 
        camera.multiray_reycoast(player.player_position, player.direction, map);
        camera.draw_raycoast_result_on_screen();
        drawer.display();


        speed = 3;
        if (GetKeyState(VK_LSHIFT) & 0x8000/*Check if high-order bit is set (1 << 15)*/)
        {
            speed = 7;
        }

        if (GetKeyState('N') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
        {
            player.direction = lrot * player.direction;
        }
        if (GetKeyState('M') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
        {
            player.direction = rrot * player.direction;
        }

        if (GetKeyState('A') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
        {
            player.player_position -= rot90 * player.direction * 0.05;
        }
        if (GetKeyState('D') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
        {
            player.player_position += rot90 * player.direction * 0.05;
        }

        if (GetKeyState('W') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
        {
            player.player_position += player.direction * 0.02 * speed;
        }
        if (GetKeyState('S') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
        {
            player.player_position -= player.direction * 0.015 * speed;
        }

        drawer.update_cons_par();

        std::this_thread::sleep_for(std::chrono::milliseconds(int(1.0/60 * 1000)));
    }
    return 0;
}