#include <stdbool.h>
#include <math.h>

#include "./physics.h"

bool collision(Rectangle object_1, Rectangle object_2)
{
    double total_width = object_1.x2 - object_1.x1 + object_2.x2 - object_2.x1;
    double total_height = object_1.y2 - object_1.y1 + object_2.y2 - object_2.y1;

    double x_distance = (object_1.x1 + object_1.x2) / 2 - (object_2.x1 + object_2.x2) / 2;
    double y_distance = (object_1.y1 + object_1.y2) / 2 - (object_2.y1 + object_2.y2) / 2;

    if (
        fabs(y_distance) < fabs(total_height/2) && fabs(x_distance) < fabs(total_width/2)
    ) {
        return true;
    }

    return false;
}
