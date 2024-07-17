#ifndef _SHIP_H
#define _SHIP_H

#include <allegro5/allegro.h>

#include "./physics.h"
#include "./gun.h"

#define SHIP_WIDTH 35
#define SHIP_HEIGHT 35
#define SHIP_SPEED 5
#define SHIP_WIDTH_HALF SHIP_WIDTH / 2

typedef struct Ship {
	ALLEGRO_BITMAP *skin;
	Point coordinate;
	Rectangle area;
	Gun *gun;
} Ship;

Ship* new_ship();

ALLEGRO_BITMAP* ship_load_skin();

void ship_fire(Ship*, float);
void ship_move_up(Ship*);
void ship_move_right(Ship*);
void ship_move_down(Ship*);
void ship_move_left(Ship*);
void ship_render(Ship *ship);
Point ship_initial_position();
Rectangle get_ship_area(Point);

#endif
