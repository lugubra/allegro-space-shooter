#include <stdio.h>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>

#include "./main.h"
#include "./game.h"
#include "./ship.h"
#include "./gun.h"

Ship* new_ship() {
    Ship *ship = malloc(sizeof(Ship));

    ship->skin = ship_load_skin();

    ship->pos[4];

    ship->pos[X1] = SCREEN_WIDTH/2;
    ship->pos[Y1] = SCREEN_HEIGHT-BORDER_LIMIT-45;
    ship->pos[X2] = ship->pos[X1] + SHIP_WIDTH;
    ship->pos[Y2] = ship->pos[Y1] + SHIP_HEIGHT;

    ship->gun = new_gun(ship->pos);

    return ship;
}

ALLEGRO_BITMAP* ship_load_skin() {
    ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
    al_set_path_filename(path, "assets/ship.png");
    ALLEGRO_BITMAP *skin = al_load_bitmap(al_path_cstr(path, '/'));
    al_destroy_path(path);
    return skin;
}

void ship_fire(Ship *ship, float now) {
    // printf("%s\n", "Fire!");
    if (now > ship->gun->reload) {
        gun_insert_bullet_in_chamber(ship->gun);
        ship->gun->reload = now + GUN_RELOAD;

        if (ship->gun->chamber < BULLETS_MAX-1) {
            ship->gun->chamber++;
        } else {
            ship->gun->chamber = 0;
        }

        printf("Gun position: X: %d, Y: %d\n", ship->gun->pos[0], ship->gun->pos[1]);
        printf("Ship TOP position: X: %d, Y: %d\n", ship->pos[X1], ship->pos[Y1]);
    }
}

void ship_move_up(Ship *ship) {
    if (ship->pos[Y1] - SHIP_SPEED < BORDER_TOP_Y) {
        ship->pos[Y1] = BORDER_TOP_Y;
        ship->pos[Y2] = ship->pos[Y1] + SHIP_HEIGHT;
    } else {
        ship->pos[Y1] = ship->pos[Y1] - SHIP_SPEED;
        ship->pos[Y2] = ship->pos[Y2] - SHIP_SPEED;
    }

    ship->gun->pos[Y1] = ship->pos[Y1];
}

void ship_move_right(Ship *ship) {
    if (ship->pos[X2] + SHIP_SPEED > BORDER_BOTTOM_X) {
        ship->pos[X2] = BORDER_BOTTOM_X;
        ship->pos[X1] = ship->pos[X2] - SHIP_WIDTH;
    } else {
        ship->pos[X2] = ship->pos[X2] + SHIP_SPEED;
        ship->pos[X1] = ship->pos[X1] + SHIP_SPEED;
    }

    ship->gun->pos[X1] = ship->pos[X1] + SHIP_WIDTH_HALF;
}

void ship_move_down(Ship *ship) {
    if (ship->pos[Y2] + SHIP_SPEED > BORDER_BOTTOM_Y) {
        ship->pos[Y2] = BORDER_BOTTOM_Y;
        ship->pos[Y1] = ship->pos[Y2] - SHIP_HEIGHT;
    } else {
        ship->pos[Y2] = ship->pos[Y2] + SHIP_SPEED;
        ship->pos[Y1] = ship->pos[Y1] + SHIP_SPEED;
    }

    ship->gun->pos[Y1] = ship->pos[Y1];
}

void ship_move_left(Ship *ship) {
    if (ship->pos[X1] - SHIP_SPEED < BORDER_TOP_X) {
        ship->pos[X1] = BORDER_TOP_X;
        ship->pos[X2] = ship->pos[X1] + SHIP_WIDTH;
    } else {
        ship->pos[X1] = ship->pos[X1] - SHIP_SPEED;
        ship->pos[X2] = ship->pos[X2] - SHIP_SPEED;
    }

    ship->gun->pos[X1] = ship->pos[X1] + SHIP_WIDTH_HALF;
}
