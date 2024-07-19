#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include "./physics.h"

bool collision(Rectangle object_1, Rectangle object_2)
{
    float total_width = object_1.x2 - object_1.x1 + object_2.x2 - object_2.x1;
    float total_height = object_1.y2 - object_1.y1 + object_2.y2 - object_2.y1;

    float x_distance = (object_1.x1 + object_1.x2) - (object_2.x1 + object_2.x2);
    float y_distance = (object_1.y1 + object_1.y2) - (object_2.y1 + object_2.y2);

    if (
        fabs(y_distance) < fabs(total_height) && fabs(x_distance) < fabs(total_width)
    ) {
        return true;
    }

    return false;
}

Collision box_collision(Rectangle box, Rectangle object)
{
    Collision collision = {
        .top = object.y1 < box.y1,
        .right = object.x2 > box.x2,
        .bottom = object.y2 > box.y2,
        .left = object.x1 < box.x1
    };

    return collision;
}
