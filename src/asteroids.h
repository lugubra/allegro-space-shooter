#ifndef _ASTEROIDS_H
#define _ASTEROIDS_H

#include <allegro5/allegro.h>

#define ASTEROID_INIT_Y 22
#define ASTEROID_RADIUS 8
#define ASTEROID_DIAMETER ASTEROID_RADIUS*2
#define ASTEROID_SPEED 5
#define ASTEROID_SPAWN 1
#define ASTEROIDS_MAX 10

typedef struct Asteroid {
    int x;
    int y;
    bool alive;
} Asteroid;

Asteroid* asteroids_init();
Asteroid new_asteroid();

void asteroid_insert_in_list(Asteroid*, int);
void asteroids_move(Asteroid*);
void asteroids_render(Asteroid*);

#endif