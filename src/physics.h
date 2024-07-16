#ifndef _PHYSICS_H
#define _PHYSICS_H

typedef struct Rectangle {
    int x1;
    int y1;
    int x2;
    int y2;
} Rectangle;

typedef struct Point {
    int x;
    int y;
} Point;

bool collision(Rectangle, Rectangle);

#endif
