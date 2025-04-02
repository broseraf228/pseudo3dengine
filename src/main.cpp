#include <iostream>
#include <Windows.h>
#include <cmath>

#include <time.h>
#include <chrono>
#include <thread>

#include "console_draw_utils.hpp"
#include "3d/renderer.hpp"
#include "3d/mesh.hpp"
#include "math/include_all.hpp"

#include<SFML/Graphics.hpp>

/* TODO:
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
    mtrx4 j = mtrx4( vec4(0,1,2,3), vec4(4,5,6,7), vec4(8,9,10,11), vec4(12,13,14,15) );
    mtrx4 g = mtrx4(vec4(16, 17, 18, 19), vec4(20, 21, 22, 23), vec4(24, 25, 26, 27), vec4(28, 29, 30, 31));

    mtrx4 r = j * g;

    vec4 vertices[6]
    {
        vec4(-1, 0, 1, 0),
        vec4(1, 0, 1, 0),
        vec4(1, 0, -1, 0),
        vec4(-1, 0, -1, 0),

        vec4(0, 1.4, 0, 0),
        vec4(0, -1.4, 0, 0),
    };

    face faces[8]{ 
        face(4, 0, 3, 0), 
        face(4, 0, 1, 0), 
        face(4, 2, 3, 0), 
        face(4, 2, 1, 0),

        face(5, 0, 3, 0),
        face(5, 0, 1, 0),
        face(5, 2, 3, 0),
        face(5, 2, 1, 0) };

    Mesh mesh(6, vertices, 8, faces);

    Model model(mesh, vec4(0, 0, 7, 0), mtrx4::mtrx_scale(vec4(1)));

    // init screen
    sf::RenderWindow window(sf::VideoMode(640, 640), "Game");

    PrimDrawer drawer(&window);

    //init camera
    MeshRanderer camera{&drawer};

    // GAME LOOP
    unsigned int frame_number = 0;
    clock_t tStart = clock();
    char title[5];

    bool run = true;
    while(run)
    {
        frame_number++;

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
        camera.addModel(model);
        camera.render();
        camera.clear();

        drawer.draw();
        drawer.display();
        drawer.clear();

        // upd model
        model.transform = mtrx4::mtrx_rotation_x(sin((float)frame_number / 90));
        model.position.x = sin((float)frame_number / 50) / 2 + sin((float)frame_number / 100);

        // wait
        if (1000 / 120 - mimiseck_delay > 0)
            Sleep(1000 / 120 - mimiseck_delay);
    }
    return 0;
}