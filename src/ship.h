#ifndef _SHIP_H
#define _SHIP_H

#include <allegro5/allegro.h>

#include "./rectangle.h"
#include "./gun.h"

#define SHIP_WIDTH 35
#define SHIP_HEIGHT 35
#define SHIP_SPEED 5
#define SHIP_WIDTH_HALF SHIP_WIDTH / 2

typedef enum {
    X1, Y1, X2, Y2
} ShipPos;

typedef struct Ship {
	ALLEGRO_BITMAP *skin;
	int pos[4];
	Gun *gun;
} Ship;

Ship* new_ship();

ALLEGRO_BITMAP* ship_load_skin();

void ship_fire(Ship*, float);
void ship_move_up(Ship*);
void ship_move_right(Ship*);
void ship_move_down(Ship*);
void ship_move_left(Ship*);
Rectangle get_ship_area(Ship*);

#endif
