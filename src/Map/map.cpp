#include "map.hpp"
#include <cmath>
#include "../math/mtrx.hpp"

#define PI 3.1415

light_source::light_source(vec2 const& pos, short light_level) : position{ pos }, light_level{ light_level } {}
char light_source::count = 0;

Map::Map() : map_x{ 20 }, map_y{ 14 } {
    map = new char[map_x * map_y]
        {
                '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#',
                '#', '.', '#', '.', '.', '.', '#', '.', '.', '.', '.', '.', '.', '.', '#', '.', '.', '.', '.', '#',
                '#', '.', '#', '.', '.', '.', '#', '.', '.', '.', '.', '.', '.', '.', '#', '.', '.', '.', '.', '#',
                '#', '.', '.', '.', '.', '.', 'P', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#',
                '#', '.', '.', '.', '.', '.', '#', '.', '.', '.', '#', '.', '.', '.', '.', '.', '.', '.', '.', '#',
                '#', '.', '.', '.', '.', '.', '#', '.', '.', '.', '.', '.', '.', '.', '#', '.', '.', '.', '.', '#',
                '#', '.', '.', '.', '.', '.', '#', '.', '.', '.', '#', '.', '.', '.', '#', '.', '.', '.', '.', '#',
                '#', '.', '.', '.', '.', '.', '#', '.', '.', '.', '.', '.', '.', '.', '#', '.', '.', '#', '#', '#',
                '#', '.', '.', '.', '.', '.', '#', '.', '.', '.', '#', '.', '.', '.', '#', '.', '.', '#', '#', '#',
                '#', '.', '.', '.', '.', '.', '#', '.', '.', '.', '.', '.', '.', '.', 'P', '.', '.', '#', '#', '#',
                '#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#', '.', '.', '.', '#', '.', '.', '.', '.', '#',
                '#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#', '.', '.', '.', '.', '#',
                '#', '.', '.', '.', '.', '.', '#', '.', '.', '.', '.', '.', '.', '.', '#', '.', '.', '.', '.', '#',
                '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'
        };

    light_sources = new light_source[light_source::max_count];
    light_source::count = 0;

    add_light_source(vec2(1, 1), 64);

    objects_map = new char[map_x * map_y];

    // light maps
    light_level_map = new short[map_x * map_y] {0};

    base_light_level_map = new short[map_x * map_y];
    for (int i = 0; i < map_x * map_y; i++)
        base_light_level_map[i] = 132;

    dinamyc_light_level_map = new short[map_x * map_y] {0};

    tmp_light_level_map = new float[map_x * map_y] {0};
}

void Map::light_the_map() {
    for (int i = 0; i < map_x * map_y; i++) // clear ligmap
        light_level_map[i] = 0;

    for (int i = 0; i < map_x * map_y; i++) {
        if (base_light_level_map[i] + dinamyc_light_level_map[i] > 255)
            light_level_map[i] = 255;
        else
            light_level_map[i] = base_light_level_map[i] + dinamyc_light_level_map[i];
    }
}
void Map::add_light_source(vec2 const& position, short light_power)
{
    light_sources[light_source::count++] = light_source(position, light_power);
}
void Map::bake_all_lights()
{
    for (int i = 0; i < map_x * map_y; i++) // clear dinligmap
        dinamyc_light_level_map[i] = 0;

    for (int i = 0; i < light_source::count; i++)
        bake_light(light_sources[i]);
}
void Map::bake_light(light_source const& source)
{
    for (int i = 0; i < map_x * map_y; i++) // clear tmp map
        tmp_light_level_map[i] = 0;

    // raycoast light rays
    for (int angle = 0; angle < 200; angle++) {
        bake_ray_of_light(source.position,
            mtrx2::mtrx_rotation((2.0 * PI) / 200.0 * angle) * vec2(0, 1),
            source.light_level);
    }

    // modify light map
    for (int i = 0; i < map_x * map_y; i++) {
        if (dinamyc_light_level_map[i] + tmp_light_level_map[i] > 255)
            dinamyc_light_level_map[i] = 255;
        else
            dinamyc_light_level_map[i] += tmp_light_level_map[i];
    }
}
void Map::bake_ray_of_light(vec2 const& position, vec2 const& direction, short light_power) {
    float step_lenght = 0.1;
    vec2 pos = position;
    
    int md = 100;
    int res = 10;
    for (int i = 0; i < md * res; i++) {
        if (get(pos.x, pos.y) != '.') {
            float current_light_power = (light_power / pow((float)i / res, 1)); // current power of light ray
            
            if (tmp_light_level_map[PM((int)round(pos.x * 4), (int)round(pos.y * 4))] > current_light_power)
                return;

            tmp_light_level_map[PM((int)round(pos.x * 4), (int)round(pos.y * 4))] = current_light_power;
            return;
        }
        pos += direction * step_lenght;
    }
    return;
}


char Map::get(float x, float y) const
{
    x = round(x*4);
    y = round(y*4);

    if (x < 0 || x >= map_x || y < 0 || y >= map_y)
        return '.';

    char* el = map + PM((int)x, (int)y);

    if (*el == '.')
        return '.';
    else
        return '#';

    return map[PM((int)x, (int)y)];
}
short Map::get_light_level(float x, float y) const
{
    x = round(x * 4);
    y = round(y * 4);

    if (x < 0 || x >= map_x || y < 0 || y >= map_y)
        return 0;

    return light_level_map[PM((int)x, (int)y)];
}

void Map::update()
{
    return;
    for (int x = 0; x < map_x; x++)
        for (int y = 0; y < map_y; y++)
            objects_map[PM(x, y)] = map[PM(x, y)];
}

char Map::take(float x, float y)
{
    x = round(x*3);
    y = round(y*3);

    if (x < 0 || x >= map_x || y < 0 || y >= map_y)
        return '.';

    map[PM((int)x, (int)y)] = '.';

    return map[PM((int)x, (int)y)];
}