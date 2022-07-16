#ifndef _GAME_H
#define _GAME_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

#include "./asteroids.h"
#include "./ship.h"
#include "./bullets.h"

#define BORDER_LIMIT 10
#define BORDER_TOP_X BORDER_LIMIT
#define BORDER_TOP_Y BORDER_LIMIT+15
#define BORDER_BOTTOM_X SCREEN_WIDTH-BORDER_LIMIT
#define BORDER_BOTTOM_Y SCREEN_HEIGHT-BORDER_LIMIT
#define HUD_WIDTH 1

#define LIVES 3
#define BACKGROUND_COLOR al_map_rgb(0, 0, 0)

extern ALLEGRO_FONT *font;
extern ALLEGRO_BITMAP *ship;

bool init_font();
bool init_ship();

typedef enum {
    Won, Lost, Paused, Quit, Playing
} GameStatus;

typedef struct Game {
    GameStatus status;

    Ship *ship;

    Asteroid *asteroids;

    int score;
    int lives;
    float asteroid_spawn;
    int asteroid_spawn_turn;

} Game;

Game* new_game();

void handle_key_status(ALLEGRO_KEYBOARD_STATE*, Game*, float);

void draw_game(Game*, float);

void draw_hud(Game*);

void draw_ship(Ship*);

void draw_bullets(Bullet*);

void draw_asteroids(Game*, float);

void add_asteroid(Game*, float);

void destroy_game(Game*);

#endif
