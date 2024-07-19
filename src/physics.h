#ifndef _PHYSICS_H
#define _PHYSICS_H

typedef struct Rectangle {
    float x1;
    float y1;
    float x2;
    float y2;
} Rectangle;

typedef struct Point {
    float x;
    float y;
} Point;

bool collision(Rectangle, Rectangle);
bool box_collision(Rectangle, Rectangle);

#endif
