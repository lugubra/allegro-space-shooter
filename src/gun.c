#include <stdio.h>

#include <allegro5/allegro5.h>

#include "./gun.h"
#include "./bullets.h"
#include "./ship.h"

Gun* new_gun(int *shipPos) {
    Gun *gun = malloc(sizeof(Gun));

    gun->bullets = bullets_init();
    gun->reload = 0.0;
    gun->chamber = 0;

    gun->pos[0] = shipPos[X1] + SHIP_WIDTH_HALF;
    gun->pos[1] = shipPos[Y1];

    return gun;
}

void gun_insert_bullet_in_chamber(Gun *gun) {
	gun->bullets[gun->chamber] = new_bullet();
    gun->bullets[gun->chamber].x = gun->pos[X1];
    gun->bullets[gun->chamber].y = gun->pos[Y1];
    gun->bullets[gun->chamber].alive = true;
}
