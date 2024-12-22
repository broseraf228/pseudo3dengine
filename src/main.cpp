#include <iostream>
#include <Windows.h>
#include <cmath>

#include <time.h>
#include <chrono>
#include <thread>

#include "math/vec2.hpp"
#include "math/mtrx.hpp"

#include "Map/map.hpp"
#include "console_draw_utils.hpp"
#include "Camera/camera.hpp"

#define PI 3.1415
#define SCEPROJLEN 2.0
#define SCRS 20.0

char grad[] = "$H80Oo+*;:,.";

struct Player {
    vec2 position;
    vec2 direction;

    Camera const& cam;
    Map& map;

    Player(int px, int py, Map& map, Camera const& cam) : position{ float(px), float(py) }, direction{ 0, 1 }, map{map}, cam { cam } {}
    
    float take_timer = 1000;

    void update(float delta)
    {
        take_timer -= delta * 1000;
        if (take_timer < 0)
            take_timer = 0;
        mtrx2 rrot = mtrx2::mtrx_rotation(PI);
        rrot.ceil();

        mtrx2 lrot = mtrx2::mtrx_rotation(-PI);
        lrot.ceil();

        mtrx2 rot90 = mtrx2::mtrx_rotation(PI / 2);
        rot90.ceil();

        float speed = 1;
        // control
        speed = 100;
        if (GetKeyState(VK_LSHIFT) & 0x8000/*Check if high-order bit is set (1 << 15)*/)
        {
            speed = 200;
        }

        // take block
        if (GetKeyState('Q') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
        {
            take();
        }

        // rorate camera
        if (GetKeyState('N') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
        {
            direction = mtrx2::mtrx_rotation(-PI * delta) * direction;
        }
        if (GetKeyState('M') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
        {
            direction = mtrx2::mtrx_rotation(PI * delta) * direction;
        }

        // move player
        if (GetKeyState('A') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
        {
            position -= rot90 * direction * 0.017 * delta * speed;
        }
        if (GetKeyState('D') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
        {
            position += rot90 * direction * 0.017 * delta * speed;
        }
        if (GetKeyState('W') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
        {
            position += direction * 0.02 * speed * delta;
        }
        if (GetKeyState('S') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
        {
            position -= direction * 0.015 * speed * delta;
        }
    }
    void take()
    {
        if (take_timer > 0)
            return;
        float range = cam.raycoast(position, direction, map) + 0.25;
        vec2 ndir = position + direction * range;
        map.take(ndir.x, ndir.y);
        take_timer = 2000;
    }

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
    Player player{4, 2, map, camera};


    // GAME LOOP
    clock_t tStart = clock();
    char title[5];
    while(true)
    {

        // calac delay of runnung (AKA FPS)
        int mimiseck_delay = clock() - tStart;
        float delta = mimiseck_delay * 0.001;
        itoa(player.position.x, title, 10);
        SetConsoleTitle(title);

        tStart = clock();

        // update map
        map.update();

        // draw 
        drawer.update_cons_par();
        //printf("\r");
        drawer.clear();
        camera.multiray_reycoast(player.position, player.direction, map);
        camera.draw_raycoast_result_on_screen();
        drawer.display();

        // update player
        player.update(delta);

        // wait
        if (1000 / 60 - mimiseck_delay > 0)
            Sleep(1000 / 60 - mimiseck_delay);
    }
    return 0;
}