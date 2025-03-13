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

#include<SFML/Graphics.hpp>

/* TODO:
*/

#define PI 3.1415
#define SCEPROJLEN 2.0
#define SCRS 20.0

struct Player {
    vec2 position;
    vec2 direction;

    Camera const& cam;
    Map& map;

    Player(float px, float py, Map& map, Camera const& cam) : position{ float(px), float(py) }, direction{ 0, 1 }, map{map}, cam { cam } {}
    
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
        speed = 40;
        if (GetKeyState(VK_LSHIFT) & 0x8000/*Check if high-order bit is set (1 << 15)*/)
        {
            speed = 60;
        }

        // take block
        if (GetKeyState('Q') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
        {
            take();
        }

        // add light source
        if (GetKeyState('L') & 0x8000) {
            if (take_timer > 0)
                return;
            take_timer = 2000;
            map.add_light_source(position, 16);
            map.bake_all_lights();
            map.light_the_map();
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
    sf::RenderWindow window(sf::VideoMode(1200, 860), "Game");

    PrimDrawer drawer(&window);

    //init camera
    Camera camera{&drawer, 500};

    // init map
    Map map{};
    map.bake_all_lights();
    map.light_the_map();

    // init player
    Player player{0.25, 0.25, map, camera};


    // GAME LOOP
    clock_t tStart = clock();
    char title[5];

    bool run = true;
    while(run)
    {

        // calac delay of runnung (AKA FPS)
        int mimiseck_delay = clock() - tStart;
        float delta = mimiseck_delay * 0.001;
        itoa(mimiseck_delay, title, 10);
        SetConsoleTitle(title);

        tStart = clock();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                run = false;
                window.close();
            }
        }

        // update map
        map.update();

        // draw 
        drawer.update_cons_par();
        //printf("\r");
        drawer.clear();
        camera.multiray_reycoast(player.position, player.direction, map);
        camera.draw_raycoast_result_on_screen();
        drawer.draw();
        drawer.display();

        // update player
        player.update(delta);

        // wait
        if (1000 / 60 - mimiseck_delay > 0)
            Sleep(1000 / 60 - mimiseck_delay);
    }
    return 0;
}