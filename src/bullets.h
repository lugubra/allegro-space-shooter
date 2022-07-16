#ifndef _BULLETS_H
#define _BULLETS_H

#include <allegro5/allegro.h>

#define BULLETS_MAX 20

typedef struct Bullet {
    int x;
    int y;
    bool alive;
} Bullet;

Bullet* bullets_init();
Bullet new_bullet();

void bullets_move(Bullet*);
void bullets_render(Bullet*);

#endif
