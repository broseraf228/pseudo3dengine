#include "camera.hpp"

#include <cmath>

#include "../Map/map.hpp"
#include "../console_draw_utils.hpp"

Camera::Camera(ConsolePrimDrawer* drawer, int ray_density) : ray_count{ ray_density }, drawer{ drawer }
{
    FOVRotators = new mtrx2[ray_count]; // create rotation matrix for create rays
    FOCRayCos = new float[ray_count];
    for (int i = 0; i < ray_count; i++) {
        float angle_by_direction = FOW / ray_count * i - FOW * 0.5;
        FOVRotators[i] = mtrx2::mtrx_rotation(angle_by_direction);
        FOCRayCos[i] = 1.0 / cos(angle_by_direction);
        FOVRotators[i].ceil();
    }

    lenghts = new float[ray_count];
}

float Camera::raycoast(vec2 const& position, vec2 const& direction, Map const& map) const
{
    float step_lenght = 0.02; // lenght of reycoast lenght
    vec2 step_move = direction * step_lenght;

    vec2 pos = position;

    for (int i = 0; i < 3000; i++) {

        if (map.get(pos.x, pos.y) != '.')
            return i * step_lenght;   // if pos == solid block

        pos += step_move;

    }

}

void Camera::multiray_reycoast(vec2 const& position, vec2 const& direction, Map const& map)
{
    for (int i = 0; i < ray_count; i++) {
        lenghts[i] = raycoast(position, FOVRotators[i] * direction, map);
    }
}

void Camera::draw_raycoast_result_on_screen()
{
    float ray_width = float(drawer->get_sx()) / ray_count;

    //drawer->rectangle(
    //    0, 0,
    //    drawer->get_sx(), drawer->get_sy()/2,
    //    ',');
    drawer->rectangle(
        0, drawer->get_sy() / 2,
        drawer->get_sx(), drawer->get_sy(),
        ';');

    for (int i = 0; i < ray_count; i++)
    {
        float ray_height = 4 * 0.25 / lenghts[i] * drawer->get_sy(); // barier height * screen distance / lenght to barrier * screen size
        ray_height *= FOCRayCos[i];
        float yoffset = (drawer->get_sy() - ray_height) * 0.5;
        drawer->rectangle(
            ray_width * i, yoffset,
            ray_width * (i + 1), ray_height + yoffset,
            '#');
    }

}