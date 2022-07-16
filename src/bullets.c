#include <stdio.h>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>

#include "./game.h"
#include "./bullets.h"
#include "./gun.h"

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

    bullet.x = 0;
    bullet.y = 0;
    bullet.alive = false;

    return bullet;
}

void bullets_move(Bullet *bullets) {
	for (int i = 0; i < BULLETS_MAX; ++i)
    {
        if (bullets[i].alive)
        {
            bullets[i].y = bullets[i].y - GUN_SHOOT_SPEED;
            if (bullets[i].y < BORDER_TOP_Y)
            {
                bullets[i] = new_bullet();
            }
        }
    }
}

void bullets_render(Bullet *bullets) {
	for (int i = 0; i < BULLETS_MAX; ++i)
    {
        if (bullets[i].alive)
        {
            al_draw_filled_circle(bullets[i].x, bullets[i].y, ASTEROID_RADIUS, al_map_rgb(255, 255, 255));
        }
    }
}
