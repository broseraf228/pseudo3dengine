#include "camera.hpp"

#include <cmath>

#include "../Map/map.hpp"
#include "../console_draw_utils.hpp"

#include<SFML/Graphics.hpp>

int Camera::grad_lenght = 8;
float Camera::rev_grad_lenght = 1 / (256.0 / grad_lenght);
char* Camera::grad = new char[grad_lenght] {' ', '.', '\'', ':', '"', 'o', '8', '$'};

Camera::Camera(PrimDrawer* drawer, int ray_density) : ray_count{ ray_density }, drawer{ drawer }
{
    FOVRotators = new mtrx2[ray_count]; // create rotation matrix for create rays
    FOCRayCos = new float[ray_count];
    for (int i = 0; i < ray_count; i++) {
        float angle_by_direction = FOW / ray_count * i - FOW * 0.5;
        FOVRotators[i] = mtrx2::mtrx_rotation(angle_by_direction);
        FOCRayCos[i] = 1.0 / cos(angle_by_direction);
        //FOVRotators[i].ceil();
    }

    lenghts = new float[ray_count];
    lights = new short[ray_count];
}

float Camera::raycoast(vec2 const& position, vec2 const& direction, Map const& map)
{
    float step_lenght = 0.01; // lenght of reycoast lenght
    vec2 step_move = direction * step_lenght;

    vec2 pos = position;

    for (int i = 0; i < 1500; i++) {

        if (map.get(pos.x, pos.y) != '.')
            return i * step_lenght;   // if pos == solid block

        pos += step_move;

    }
    return 100;
}
float Camera::saveing_raycoast(vec2 const& position, vec2 const& direction, Map const& map, int ray_number)
{
    float step_lenght = 0.02; // lenght of reycoast lenght
    vec2 step_move = direction * step_lenght;

    vec2 pos = position;

    for (int i = 0; i < 1500; i++) {

        if (map.get(pos.x, pos.y) != '.') {// if pos == solid block
            lenghts[ray_number] = i * step_lenght;
            lights[ray_number] = map.get_light_level(pos.x, pos.y);
            return i * step_lenght;
        }
        pos += step_move;
    }
    return 100;
}

void Camera::multiray_reycoast(vec2 const& position, vec2 const& direction, Map const& map)
{
    for (int i = 0; i < ray_count; i++) {
        // raycoast method can save lenght and etc it on his own
        saveing_raycoast(position, FOVRotators[i] * direction, map, i);
    }
}

void Camera::draw_raycoast_result_on_screen()
{
    float ray_width = 1.0 / ray_count;

    for (int i = 0; i < ray_count; i++)
    {
        float ray_height = 0.1 / lenghts[i]; // barier height * screen distance / lenght to barrier * screen size
        ray_height *= FOCRayCos[i];
        float yoffset = (1 - ray_height) * 0.5;

        int ray_light_level = (lights[i] - lenghts[i] * lenghts[i] * 3);

        drawer->rectangle(
            ray_width * i, yoffset,
            ray_width * (i + 1), ray_height + yoffset,
            sf::Color(ray_light_level, ray_light_level, ray_light_level));
    }

}