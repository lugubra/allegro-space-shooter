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

    asteroid.coordinate = asteroid_initial_position();
    asteroid.area = get_asteroid_area(asteroid.coordinate);
    asteroid.alive = false;

    return asteroid;
}

Point asteroid_initial_position() {
    Point coordinate;

    int min = BORDER_TOP_X + ASTEROID_RADIUS;
    int max = BORDER_BOTTOM_X - ASTEROID_RADIUS - min;

    coordinate.x = rand() % max + min;
    coordinate.y = BORDER_TOP_Y + ASTEROID_RADIUS;

    return coordinate;
}

Rectangle get_asteroid_area(Point coordinate) {
    Rectangle area = {
        .x1 = coordinate.x - ASTEROID_RADIUS,
        .y1 = coordinate.y - ASTEROID_RADIUS,
        .x2 = coordinate.x + ASTEROID_RADIUS,
        .y2 = coordinate.y + ASTEROID_RADIUS
    };

    return area;
}

void asteroid_insert_in_list(Asteroid *list, int pos) {
    list[pos] = new_asteroid();
    list[pos].alive = true;
}

void asteroids_move(Asteroid *asteroids) {
    for (int i = 0; i < ASTEROIDS_MAX; ++i)
    {
        if (asteroids[i].alive) {
            asteroids[i].coordinate.y += ASTEROID_SPEED;
            asteroids[i].area = get_asteroid_area(asteroids[i].coordinate);
        }
    }
}

void asteroids_render(Asteroid *asteroids) {
    for (int i = 0; i < ASTEROIDS_MAX; ++i)
    {
        if (asteroids[i].alive)
            al_draw_filled_circle(
                asteroids[i].coordinate.x,
                asteroids[i].coordinate.y,
                ASTEROID_RADIUS,
                al_map_rgb(140, 70, 0)
            );
    }
}
