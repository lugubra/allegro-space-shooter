#ifndef _BULLETS_H
#define _BULLETS_H

#include <allegro5/allegro.h>

#include "./physics.h"

#define BULLET_RADIUS 8
#define BULLETS_MAX 20

typedef struct Bullet {
    Point coordinate;
    Rectangle area;
    bool alive;
} Bullet;

Bullet* bullets_init();
Bullet new_bullet();
Point bullet_initial_position();
Rectangle get_bullet_area(Point);

void bullets_move(Bullet*);
void bullets_render(Bullet*);

#endif
