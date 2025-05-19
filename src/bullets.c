#include <stdio.h>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>

#include "../inc/game.h"
#include "../inc/bullets.h"
#include "../inc/gun.h"

Bullet* bullets_init() {
    Bullet *bullets = malloc(sizeof(Bullet) * BULLETS_MAX);

    for (int i = 0; i < BULLETS_MAX; ++i)
    {
        bullets[i] = new_bullet();
    }

    return bullets;
}

Bullet new_bullet() {
    Bullet bullet;

    bullet.coordinate = bullet_initial_position();
    bullet.area = get_bullet_area(bullet.coordinate);
    bullet.alive = false;

    return bullet;
}

Point bullet_initial_position()
{
    Point coordinate = {
        .x = 0,
        .y = 0
    };

    return coordinate;
}

Rectangle get_bullet_area(Point coordinate)
{
    Rectangle area = {
        .x1 = coordinate.x - BULLET_RADIUS,
        .y1 = coordinate.y - BULLET_RADIUS,
        .x2 = coordinate.x + BULLET_RADIUS,
        .y2 = coordinate.y + BULLET_RADIUS
    };

    return area;
}

void bullets_move(Bullet *bullets) {
	for (int i = 0; i < BULLETS_MAX; ++i)
    {
        if (bullets[i].alive) {
            bullets[i].coordinate.y -= GUN_SHOOT_SPEED;
            bullets[i].area = get_asteroid_area(bullets[i].coordinate);
        }
    }
}

void bullets_render(Bullet *bullets) {
	for (int i = 0; i < BULLETS_MAX; ++i)
    {
        if (bullets[i].alive)
            al_draw_filled_circle(
                bullets[i].coordinate.x,
                bullets[i].coordinate.y,
                BULLET_RADIUS,
                al_map_rgb(255, 255, 255)
            );
    }
}
