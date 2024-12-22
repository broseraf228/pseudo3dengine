#pragma once

#include "../math/mtrx.hpp"
#include "../math/vec2.hpp"

#define PI 3.1415


struct ConsolePrimDrawer;
struct Map;

struct Camera {

    float FOW = PI / 2; // FOV setings
    int ray_count;
    mtrx2* FOVRotators;
    float* FOCRayCos;

    ConsolePrimDrawer* drawer;

    float* lenghts; // for store rays distance

    Camera(ConsolePrimDrawer* drawer, int ray_density);

    // start ray 
    float raycoast(vec2 const& position, vec2 const& direction, Map const& map) const;

    // start any rays and save his lenghts
    void multiray_reycoast(vec2 const& position, vec2 const& direction, Map const& map);

    // speking name
    void draw_raycoast_result_on_screen();
};