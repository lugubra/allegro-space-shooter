#include <stdio.h>

#include <allegro5/allegro5.h>

#include "./gun.h"
#include "./bullets.h"
#include "./ship.h"
#include "./physics.h"

Gun* new_gun(Point ship_coordinate) {
    Gun *gun = malloc(sizeof(Gun));

    gun->bullets = bullets_init();
    gun->reload = 0.0;
    gun->chamber = 0;

    gun->pos[0] = ship_coordinate.x;
    gun->pos[1] = ship_coordinate.y - 22;

    return gun;
}

void gun_insert_bullet_in_chamber(Gun *gun) {
	gun->bullets[gun->chamber] = new_bullet();
    gun->bullets[gun->chamber].x = gun->pos[0];
    gun->bullets[gun->chamber].y = gun->pos[1];
    gun->bullets[gun->chamber].alive = true;
}
