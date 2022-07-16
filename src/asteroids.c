#include <stdlib.h>
#include <stdio.h>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>

#include "./main.h"
#include "./game.h"
#include "./asteroids.h"

Asteroid* asteroids_init() {
    Asteroid *asteroids = malloc(sizeof(Asteroid) * ASTEROIDS_MAX);

    for (int i = 0; i < ASTEROIDS_MAX; ++i)
    {
        asteroids[i] = new_asteroid();
    }

    return asteroids;
}

Asteroid new_asteroid() {
    Asteroid asteroid;

    int min = BORDER_TOP_X + ASTEROID_RADIUS;
    int max = BORDER_BOTTOM_X - ASTEROID_RADIUS - min;

    asteroid.x = rand() % max + min;
    asteroid.y = BORDER_TOP_Y + ASTEROID_RADIUS;
    asteroid.alive = false;

    return asteroid;
}

void asteroid_insert_in_list(Asteroid *list, int pos) {
    list[pos] = new_asteroid();
    list[pos].alive = true;
}

void asteroids_move(Asteroid *list) {
    for (int i = 0; i < ASTEROIDS_MAX; ++i)
    {
        if (list[i].alive)
        {
            list[i].y = list[i].y + ASTEROID_SPEED;
            if (list[i].y > BORDER_BOTTOM_Y-ASTEROID_RADIUS)
            {
                list[i] = new_asteroid();
            }
        }
    }
}

void asteroids_render(Asteroid *list) {
    for (int i = 0; i < ASTEROIDS_MAX; ++i)
    {
        if (list[i].alive)
        {
            al_draw_filled_circle(list[i].x, list[i].y, ASTEROID_RADIUS, al_map_rgb(140, 70, 0));
        }
    }
}
