#ifndef _GUN_H
#define _GUN_H

#include <allegro5/allegro.h>

#include "./bullets.h"
#include "./physics.h"

#define GUN_RELOAD 0.2
#define GUN_SHOOT_SPEED 6

typedef struct Gun {
    Bullet *bullets;
    float reload;
    int chamber;
    float pos[2];
} Gun;

Gun* new_gun(Point);

void gun_insert_bullet_in_chamber(Gun*);

#endif
