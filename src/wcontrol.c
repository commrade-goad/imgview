#include "wcontrol.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

bool check_viewport(struct window_t *w) {
    if ((w->state->rec.x + w->state->rec.w) <= 0) {
        return false;
    }
    return true;
}

void do_zoom(struct window_t *w, int zoom_lvl) {
    struct state_t *s = w->state;
    s->can_reset = false;
    if (s->zoom + zoom_lvl < 10 || s->zoom + zoom_lvl > 500) {
        return;
    }

    s->zoom += zoom_lvl;
    double zoom_factor = s->zoom / 100.0;

    int old_width = s->rec.w;
    int old_height = s->rec.h;

    s->rec.w = round(s->texture->w * zoom_factor);
    s->rec.h = round(s->texture->h * zoom_factor);
    s->rec.x -= (s->rec.w - old_width) / 2;
    s->rec.y -= (s->rec.h - old_height) / 2;

    /*
    // Ensure the image stays within the window boundaries if needed
    struct vec2_t winsize = get_window_size(w);

    // Optional: If you want to keep the image within window bounds
    // You can uncomment these checks
    // Adjust x position if image goes outside window
    if (s->rec.x < 0) {
        s->rec.x = 0;
    } else if (s->rec.x + s->rec.w > winsize.x) {
        s->rec.x = winsize.x - s->rec.w;
    }

    // Adjust y position if image goes outside window
    if (s->rec.y < 0) {
        s->rec.y = 0;
    } else if (s->rec.y + s->rec.h > winsize.y) {
        s->rec.y = winsize.y - s->rec.h;
    }
    */
}

void do_move(struct window_t *w, int dx, int dy) {
    w->state->can_reset = false;
    SDL_FRect *state_rec = &w->state->rec;
    state_rec->x += dx;
    state_rec->y += dy;
}

void handle_event(struct window_t *w, SDL_Event *e) {
    const bool *key_state = SDL_GetKeyboardState(NULL);
    if (key_state[SDL_SCANCODE_ESCAPE]) {
        w->quit = true;
        return;
    }

    int movement = 20;
    const int zoom_incr = 10;

    // only available in normal mode
    if (!w->state->command_mode) {
        if (key_state[SDL_SCANCODE_H])
            do_move(w, movement, 0);
        if (key_state[SDL_SCANCODE_J])
            do_move(w, 0, -movement);
        if (key_state[SDL_SCANCODE_K])
            do_move(w, 0, movement);
        if (key_state[SDL_SCANCODE_L])
            do_move(w, -movement, 0);
    }

    while (SDL_PollEvent(e)) {
        switch (e->type) {
        case SDL_EVENT_QUIT:
            w->quit = true;
            return;
        case SDL_EVENT_KEY_DOWN:
            // only available in normal mode
            if (!w->state->command_mode) {
                if (e->key.key == SDLK_MINUS) {
                    do_zoom(w, -zoom_incr);
                }
                if (e->key.key == SDLK_EQUALS) {
                    do_zoom(w, zoom_incr);
                }
                if (e->key.key == SDLK_R) {
                    w->state->can_reset = true;
                    w->state->zoom = 100;
                }
            }
            // only available in command mode
            if (w->state->command_mode) {
                for (int i = 0; i < 10; i++) {
                    if (e->key.key == SDLK_0 + i) {
                        printf("called %d\n", i);
                    }
                }
            }
            // global hotkey.
            if (e->key.key == SDLK_SEMICOLON) {
                w->state->command_mode = !w->state->command_mode;
            }
            break;
        default:
            break;
        }
    }
}
