#include <stdio.h>
#include <math.h>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#include "./main.h"
#include "./game.h"
#include "./ship.h"
#include "./asteroids.h"
#include "./physics.h"

ALLEGRO_FONT *font = NULL;

bool init_font() {
    al_init_font_addon();
    font = al_create_builtin_font();

    return font != NULL;
}

Game* new_game() {
    Game *game = malloc(sizeof(Game));

    game->screen = get_game_screen();
    game->ship = new_ship();
    game->asteroids = asteroids_init();

    game->status = Menu;
    game->score = 0;
    game->lives = LIVES;
    game->asteroid_spawn = ASTEROID_SPAWN;
    game->asteroid_spawn_turn = 0;

    return game;
}

Rectangle get_game_screen() {
    Rectangle screen = {
        .x1 = BORDER_TOP_X,
        .y1 = BORDER_TOP_Y,
        .x2 = BORDER_BOTTOM_X,
        .y2 = BORDER_BOTTOM_Y
    };

    return screen;
}

void handle_menu_key_status(ALLEGRO_KEYBOARD_STATE *keys, Game *game) {
    if (al_key_down(keys, ALLEGRO_KEY_ESCAPE))
        game->status = Quit;

    if (al_key_down(keys, ALLEGRO_KEY_ENTER))
        game->status = Playing;
}

void draw_menu(Game *game) {
    al_clear_to_color(BACKGROUND_COLOR);

    draw_hud(game);

    al_draw_textf(
        font,
        al_map_rgb(255, 255, 255),
        SCREEN_WIDTH/2,
        SCREEN_HEIGHT/2,
        ALLEGRO_ALIGN_CENTER,
        "Press <ENTER> to start the game"
    );
}

void draw_game_lost(Game *game) {
    al_clear_to_color(BACKGROUND_COLOR);

    draw_hud(game);

    al_draw_textf(
        font,
        al_map_rgb(255, 255, 255),
        SCREEN_WIDTH/2,
        SCREEN_HEIGHT/2,
        ALLEGRO_ALIGN_CENTER,
        "GAME OVER"
    );
    al_draw_textf(
        font,
        al_map_rgb(255, 255, 255),
        SCREEN_WIDTH/2,
        SCREEN_HEIGHT/2+10,
        ALLEGRO_ALIGN_CENTER,
        "Score: %d", game->score
    );
    al_draw_textf(
        font,
        al_map_rgb(255, 255, 255),
        SCREEN_WIDTH/2,
        SCREEN_HEIGHT/2+20,
        ALLEGRO_ALIGN_CENTER,
        "Press <ENTER> to start a new game"
    );
}

void handle_key_status(ALLEGRO_KEYBOARD_STATE *keys, Game *game, float now) {
    if (al_key_down(keys, ALLEGRO_KEY_ESCAPE))
        game->status = Quit;

    if (al_key_down(keys, ALLEGRO_KEY_SPACE))
        ship_fire(game->ship, now);

    if (al_key_down(keys, ALLEGRO_KEY_UP))
        ship_move_up(game->ship);

    if (al_key_down(keys, ALLEGRO_KEY_RIGHT))
        ship_move_right(game->ship);

    if (al_key_down(keys, ALLEGRO_KEY_DOWN))
        ship_move_down(game->ship);

    if (al_key_down(keys, ALLEGRO_KEY_LEFT))
        ship_move_left(game->ship);
}

void compute_game_frame(Game *game, float now) {
    /** game events */
    add_asteroid(game, now);

    /** game object actions */
    asteroids_move(game->asteroids);
    bullets_move(game->ship->gun->bullets);

    /** trigger events */
    check_ship_screen_collision(game);
    check_asteroid_screen_collision(game);
    check_bullet_screen_collision(game);
    check_bullet_asteroid_collision(game);
    check_ship_asteroid_collision(game);
    check_game_over(game);
}

void draw_game(Game *game, float now) {
    al_clear_to_color(BACKGROUND_COLOR);

    draw_hud(game);
    draw_ship(game->ship);
    draw_asteroids(game->asteroids);
    draw_bullets(game->ship->gun->bullets);
}

void add_asteroid(Game *game, float now) {
    // Add asteroid if spawn time elapsed
    if (now > game->asteroid_spawn)
    {
        asteroid_insert_in_list(game->asteroids, game->asteroid_spawn_turn);
        game->asteroid_spawn = now + ASTEROID_SPAWN;

        if (game->asteroid_spawn_turn < ASTEROIDS_MAX-1) {
            game->asteroid_spawn_turn++;
        } else {
            game->asteroid_spawn_turn = 0;
        }
    }
}

void check_ship_screen_collision(Game *game) {
    Collision collision = box_collision(game->screen, game->ship->area);

    if (collision.top)
        ship_move_down(game->ship);
    if (collision.right)
        ship_move_left(game->ship);
    if (collision.bottom)
        ship_move_up(game->ship);
    if (collision.left)
        ship_move_right(game->ship);
}

void check_asteroid_screen_collision(Game *game) {
    Collision collision;

    for (int i = 0; i < ASTEROIDS_MAX; ++i)
    {
        if (game->asteroids[i].alive) {
            collision = box_collision(game->screen, game->asteroids[i].area);

            if(collision.bottom)
                game->asteroids[i] = new_asteroid();
        }
    }
}

void check_bullet_screen_collision(Game *game) {
    Collision collision;

    for (int i = 0; i < BULLETS_MAX; ++i)
    {
        if (game->ship->gun->bullets[i].alive) {
            collision = box_collision(game->screen, game->ship->gun->bullets[i].area);

            if (collision.top)
                game->ship->gun->bullets[i] = new_bullet();
        }
    }
}

void check_bullet_asteroid_collision(Game *game) {
    for (int i = 0; i < BULLETS_MAX; ++i)
    {
        if (game->ship->gun->bullets[i].alive) {
            for (int j = 0; j < ASTEROIDS_MAX; ++j)
            {
                if (game->asteroids[j].alive) {
                    if (collision(game->ship->gun->bullets[i].area, game->asteroids[j].area)) {
                        game->ship->gun->bullets[i] = new_bullet();
                        game->asteroids[j] = new_asteroid();
                        game->score += 10;
                    }
                }
            }
        }
    }
}

void check_ship_asteroid_collision(Game *game) {
    for (int i = 0; i < ASTEROIDS_MAX; ++i)
    {
        if (game->asteroids[i].alive) {
            if (collision(game->asteroids[i].area, game->ship->area)) {
                printf("%s\n", "crashed");
                game->asteroids[i] = new_asteroid();
                game->lives--;
            }
        }
    }
}

void check_game_over(Game *game) {
    if (game->lives < 1)
        game->status = Lost;
}

void draw_hud(Game *game) {
    al_draw_textf(
        font, al_map_rgb(255, 255, 255),
        BORDER_LIMIT,
        BORDER_LIMIT,
        0,
        "SCORE: %d", game->score
    );
    al_draw_textf(
        font,
        al_map_rgb(255, 255, 255),
        SCREEN_WIDTH-BORDER_LIMIT,
        BORDER_LIMIT,
        ALLEGRO_ALIGN_RIGHT,
        "LIVES: %d", game->lives
    );
    al_draw_rectangle(
        game->screen.x1,
        game->screen.y1,
        game->screen.x2,
        game->screen.y2,
        al_map_rgb(255, 255, 255),
        HUD_WIDTH
    );
}

void draw_ship(Ship *ship) {
    ship_render(ship);
}

void draw_asteroids(Asteroid *asteroids) {
    asteroids_render(asteroids);
}

void draw_bullets(Bullet *bullets) {
    bullets_render(bullets);
}

void destroy_game(Game *game) {
    free(game->asteroids);
    free(game->ship->gun->bullets);
    free(game->ship->gun);
    free(game->ship);
    free(game);
}
