#ifndef _GAME_H
#define _GAME_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

#include "./asteroids.h"
#include "./ship.h"
#include "./bullets.h"
#include "./physics.h"

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
    Menu, Score, Playing, Won, Lost, Paused, Quit
} GameStatus;

typedef struct Game {
    GameStatus status;

    Rectangle screen;
    Ship *ship;
    Asteroid *asteroids;

    int score;
    int lives;
    float asteroid_spawn;
    int asteroid_spawn_turn;

} Game;

Game* new_game();

Rectangle get_game_screen();

void handle_menu_key_status(ALLEGRO_KEYBOARD_STATE*, Game*);

void handle_key_status(ALLEGRO_KEYBOARD_STATE*, Game*, float);

void compute_game_frame(Game*, float);

void draw_menu(Game*);

void draw_game(Game*, float);

void draw_game_lost(Game*);

void add_asteroid(Game*, float);

void check_ship_screen_collision(Game*);

void check_asteroid_screen_collision(Game*);

void check_ship_asteroid_collision(Game*);

void check_bullet_screen_collision(Game*);

void check_bullet_asteroid_collision(Game*);

void check_game_over(Game*);

void draw_hud(Game*);

void draw_ship(Ship*);

void draw_bullets(Bullet*);

void draw_asteroids(Asteroid*);

void destroy_game(Game*);

#endif
