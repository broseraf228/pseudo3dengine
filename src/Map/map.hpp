#pragma once

#include "../math/vec2.hpp"

#define PM(x, y) map_x*y + x 

struct light_source {
    light_source(vec2 const& pos = 0, short light_level = 0);
    vec2 position;
    short light_level;

    static char const max_count{ 64 };
    static char count;
};

struct Map {

    int const map_x, map_y;
    char* map;

    char* objects_map;

    // light level can be 0-255
    short* base_light_level_map;
    short* dinamyc_light_level_map;
    light_source* light_sources;
    short* light_level_map;

    Map();

    // summ the base_light_level_map and dinamic_light_level_map; generate light_level_map
    void light_the_map();

    void add_light_source(vec2 const& position, short light_level = 64);
    float* tmp_light_level_map;
    void bake_all_lights();
    void bake_light(light_source const &);
    void bake_ray_of_light(vec2 const& position, vec2 const & direction, short light_power);

    char get(float x, float y) const;
    short get_light_level(float x, float y) const;

    char take(float x, float y);

    void update();
};