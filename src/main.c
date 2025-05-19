#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#include "../inc/main.h"
#include "../inc/game.h"
#include "../inc/ship.h"

#define FPS 60
#define SPAWN 1

ALLEGRO_KEYBOARD_STATE *keys;

int main()
{
    printf("%s\n", "Watch out for Asteroids... good luck!");
    srand(time(NULL));

    al_init();
    al_install_keyboard();
    al_init_primitives_addon();
    al_init_image_addon();
    init_font();

    ALLEGRO_TIMER *timer = al_create_timer(1.0 / FPS);
    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    ALLEGRO_DISPLAY *disp = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);

    keys = malloc(sizeof(ALLEGRO_KEYBOARD_STATE));

    al_set_window_title(disp, "Asteroids");
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    ALLEGRO_EVENT *timerevent = malloc(sizeof(ALLEGRO_EVENT));

    Game *game = new_game();

    float now = 0.0;

    al_start_timer(timer);

    while(game->status != Quit)
    {
        while(game->status == Menu)
        {
            al_get_keyboard_state(keys);

            al_wait_for_event(queue, NULL);
            al_get_next_event(queue, timerevent);
            // No need to fill up the queue if we are late drawing frames
            al_flush_event_queue(queue);

            handle_menu_key_status(keys, game);

            draw_menu(game);

            al_flip_display();
        }

        while(game->status == Playing)
        {
            now = al_get_time();
            al_get_keyboard_state(keys);

            al_wait_for_event(queue, NULL);
            al_get_next_event(queue, timerevent);
            // No need to fill up the queue if we are late drawing frames
            al_flush_event_queue(queue);

            handle_key_status(keys, game, now);

            compute_game_frame(game, now);

            draw_game(game, now);

            al_flip_display();
        }

        while(game->status == Lost)
        {
            al_get_keyboard_state(keys);

            al_wait_for_event(queue, NULL);
            al_get_next_event(queue, timerevent);
            // No need to fill up the queue if we are late drawing frames
            al_flush_event_queue(queue);

            handle_menu_key_status(keys, game);

            draw_game_lost(game);

            al_flip_display();
        }

        if (game->status != Quit)
            game = new_game();
    }

    printf("%s\n", "GAME OVER");

    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    al_destroy_font(font);
    destroy_game(game);
    free(timerevent);
    free(keys);

    return 0;
}