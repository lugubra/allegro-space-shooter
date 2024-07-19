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
    ship->coordinate = ship_initial_position();
    ship->area = get_ship_area(ship->coordinate);
    ship->gun = new_gun(ship->coordinate);

    return ship;
}

ALLEGRO_BITMAP* ship_load_skin() {
    ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
    al_set_path_filename(path, "assets/ship.png");
    ALLEGRO_BITMAP *skin = al_load_bitmap(al_path_cstr(path, '/'));
    al_destroy_path(path);
    return skin;
}

Point ship_initial_position() {
    Point coordinate = {
        .x = SCREEN_WIDTH/2,
        .y = SCREEN_HEIGHT-BORDER_LIMIT-SHIP_WIDTH,
    };

    return coordinate;
}

Rectangle get_ship_area(Point coordinate) {
    Rectangle area = {
        .x1 = coordinate.x - SHIP_WIDTH_HALF,
        .y1 = coordinate.y - SHIP_HEIGHT_HALF,
        .x2 = coordinate.x + SHIP_WIDTH_HALF,
        .y2 = coordinate.y + SHIP_HEIGHT_HALF
    };

    return area;
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
    }
}

void ship_move_up(Ship *ship) {
    ship->coordinate.y -= SHIP_SPEED;
    ship->area = get_ship_area(ship->coordinate);
    ship->gun->pos[1] = ship->area.y1;
}

void ship_move_right(Ship *ship) {
    ship->coordinate.x += SHIP_SPEED;
    ship->area = get_ship_area(ship->coordinate);
    ship->gun->pos[0] = ship->coordinate.x;
}

void ship_move_down(Ship *ship) {
    ship->coordinate.y += SHIP_SPEED;
    ship->area = get_ship_area(ship->coordinate);
    ship->gun->pos[1] = ship->area.y1;
}

void ship_move_left(Ship *ship) {
    ship->coordinate.x -= SHIP_SPEED;
    ship->area = get_ship_area(ship->coordinate);
    ship->gun->pos[0] = ship->coordinate.x;
}

void ship_render(Ship *ship) {
    al_draw_bitmap(ship->skin, ship->coordinate.x-SHIP_WIDTH_HALF, ship->coordinate.y-SHIP_HEIGHT_HALF, ALLEGRO_ALIGN_CENTER);
}
