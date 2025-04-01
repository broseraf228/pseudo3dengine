#include <iostream>
#include <Windows.h>
#include <cmath>

#include <time.h>
#include <chrono>
#include <thread>

#include "console_draw_utils.hpp"
#include "Camera/camera.hpp"
#include "mesh.hpp"

#include<SFML/Graphics.hpp>

/* TODO:
* fix memory leak in mesh destructor
* add rotation / scale matrix generator
* add load model from file function (отдельный класс)
*/

/*
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
        if (GetKeyState(VK_LSHIFT) & 0x8000)
        {
            speed = 60;
        }

        // take block
        if (GetKeyState('Q') & 0x8000)
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
        if (GetKeyState('N') & 0x8000)
        {
            direction = mtrx2::mtrx_rotation(-PI * delta) * direction;
        }
        if (GetKeyState('M') & 0x8000)
        {
            direction = mtrx2::mtrx_rotation(PI * delta) * direction;
        }

        // move player
        if (GetKeyState('A') & 0x8000)
        {
            position -= rot90 * direction * 0.017 * delta * speed;
        }
        if (GetKeyState('D') & 0x8000)
        {
            position += rot90 * direction * 0.017 * delta * speed;
        }
        if (GetKeyState('W') & 0x8000)
        {
            position += direction * 0.02 * speed * delta;
        }
        if (GetKeyState('S') & 0x8000)
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
*/

int main(int argc, char* argv[])
{
    vec4 vertices[4]
    {
        vec4(-3, 3, 10, 0),
        vec4(3, 3, 10, 0),
        vec4(3, -3, 10, 0),
        vec4(-3, -3, 10, 0)
    };

    face faces[2]{ face(0, 1, 2, 0), face(0, 3, 2, 0) };

    Mesh mesh(4, vertices, 2, faces);



    // init screen
    sf::RenderWindow window(sf::VideoMode(640, 640), "Game");

    PrimDrawer drawer(&window);

    //init camera
    Camera camera{&drawer};

    camera.addMesh(mesh);

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

        // draw 
        drawer.clear();

        camera.render();

        drawer.draw();
        drawer.display();

        // wait
        if (1000 / 60 - mimiseck_delay > 0)
            Sleep(1000 / 60 - mimiseck_delay);
    }
    return 0;
}