#pragma once

#define PM(x, y) map_x*y + x 

struct Map {

    int const map_x, map_y;
    char* map;

    char* objects_map;

    Map();

    char get(float x, float y) const;

    char take(float x, float y);

    void update();
};