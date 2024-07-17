#ifndef _ASTEROIDS_H
#define _ASTEROIDS_H

#include <allegro5/allegro.h>

#include "./physics.h"

#define ASTEROID_INIT_Y 22
#define ASTEROID_RADIUS 8
#define ASTEROID_DIAMETER ASTEROID_RADIUS*2
#define ASTEROID_SPEED 5
#define ASTEROID_SPAWN 0.2
#define ASTEROIDS_MAX 10

typedef struct Asteroid {
    Point coordinate;
    Rectangle area;
    bool alive;
} Asteroid;

Asteroid* asteroids_init();
Asteroid new_asteroid();
Point asteroid_initial_position();
Rectangle get_asteroid_area(Point);

void asteroid_insert_in_list(Asteroid*, int);
void asteroids_move(Asteroid*);
void asteroids_render(Asteroid*);

#endif