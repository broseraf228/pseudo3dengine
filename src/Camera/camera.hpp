#pragma once

#include "../math/include_all.hpp"

#define PI 3.1415


struct PrimDrawer;
struct Map;

struct Camera {

    static int grad_lenght;
    static float rev_grad_lenght;
    static char* grad;

    float FOW = PI / 2; // FOV setings
    int ray_count;
    mtrx2* FOVRotators;
    float* FOCRayCos;

    PrimDrawer* drawer;

    float* lenghts; // for store rays distance
    short* lights; // for store rays color (fow block light)

    Camera(PrimDrawer* drawer, int ray_density);

    // start ray 
    static float raycoast(vec2 const& position, vec2 const& direction, Map const& map);
    // save ray lenght, light, and etc.
    float saveing_raycoast(vec2 const& position, vec2 const& direction, Map const& map, int ray_number);

    // start any rays and save his lenghts
    void multiray_reycoast(vec2 const& position, vec2 const& direction, Map const& map);

    // speking name
    void draw_raycoast_result_on_screen();
};