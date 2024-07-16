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

    game->ship = new_ship();

    game->asteroids = asteroids_init();

    game->status = Playing;
    game->score = 0;
    game->lives = LIVES;
    game->asteroid_spawn = ASTEROID_SPAWN;
    game->asteroid_spawn_turn = 0;

    return game;
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

void draw_game(Game *game, float now) {
    al_clear_to_color(BACKGROUND_COLOR);

    draw_hud(game);
    draw_ship(game->ship);
    draw_asteroids(game, now);
    draw_bullets(game->ship->gun->bullets);

    /** continue programming from the ship_crashed event */
    ship_crashed(game);
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
        BORDER_TOP_X,
        BORDER_TOP_Y,
        BORDER_BOTTOM_X,
        BORDER_BOTTOM_Y,
        al_map_rgb(255, 255, 255),
        HUD_WIDTH
    );
}

void draw_ship(Ship *ship) {
    ship_render(ship);
}

void draw_asteroids(Game *game, float now) {
    add_asteroid(game, now);
    asteroids_move(game->asteroids);
    asteroids_render(game->asteroids);
}

void draw_bullets(Bullet *bullets) {
    bullets_move(bullets);
    bullets_render(bullets);
}

void ship_crashed(Game *game) {
    for (int i = 0; i < ASTEROIDS_MAX; ++i)
    {
        if (game->asteroids[i].alive)
        {
            Rectangle ship_area = get_ship_area(game->ship);

            if (collision(game->asteroids[i].area, ship_area))
            {
                printf("%s\n", "crash");
                game->asteroids[i] = new_asteroid();
                game->lives--;
            }
        }
    }
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

void destroy_game(Game *game) {
    free(game->asteroids);
    free(game->ship->gun->bullets);
    free(game->ship->gun);
    free(game->ship);
    free(game);
}
