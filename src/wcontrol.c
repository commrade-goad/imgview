#include <math.h>
#include <stdbool.h>
#include <stdio.h>

#include "include/eval.h"
#include "include/str.h"
#include "include/wcontrol.h"

void wcontrol_zoom(window_t *w, int zoom_lvl) {
    state_t *s = w->state;
    s->can_reset = false;
    size_t new_zoom_val = s->zoom + zoom_lvl;
    if (new_zoom_val < 10 || new_zoom_val > 500) {
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
}

void wcontrol_move(window_t *w, int dx, int dy) {
    w->state->can_reset = false;
    SDL_FRect *state_rec = &w->state->rec;
    state_rec->x += dx;
    state_rec->y += dy;
}

void wcontrol_handle_event(window_t *w, SDL_Event *e) {
    const bool *key_state = SDL_GetKeyboardState(NULL);
    if (key_state[SDL_SCANCODE_ESCAPE]) {
        w->quit = true;
        return;
    }

    const int movement_incr = 20;
    const int zoom_incr     = 10;

    // only available in normal mode
    if (!w->state->command_mode) {
        if (key_state[SDL_SCANCODE_H])
            wcontrol_move(w, movement_incr, 0);
        if (key_state[SDL_SCANCODE_J])
            wcontrol_move(w, 0, -movement_incr);
        if (key_state[SDL_SCANCODE_K])
            wcontrol_move(w, 0, movement_incr);
        if (key_state[SDL_SCANCODE_L])
            wcontrol_move(w, -movement_incr, 0);
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
                    wcontrol_zoom(w, -zoom_incr);
                }
                if (e->key.key == SDLK_EQUALS) {
                    wcontrol_zoom(w, zoom_incr);
                }
                if (e->key.key == SDLK_R) {
                    w->state->can_reset = true;
                    w->state->zoom = 100;
                }
            }
            // only available in command mode
            if (w->state->command_mode) {
                if (e->key.key == SDLK_BACKSPACE) {
                    str_pop_chr(&w->state->cmd_buffer);
                } else if (e->key.key == SDLK_RETURN) {
                    w->state->command_mode = false;
                    evaluate_command(w);
                    str_clear(&w->state->cmd_buffer);
                } else if (e->key.key == SDLK_ESCAPE) {
                    w->state->command_mode = false;
                    str_clear(&w->state->cmd_buffer);
                } else {
                    // ascii range from space to z to cover all of the needed
                    // keys
                    if (e->key.key >= SDLK_SPACE && e->key.key <= SDLK_Z) {
                        str_push_chr(&w->state->cmd_buffer, e->key.key);
                    }
                }
            }
            // global hotkey.
            if (e->key.key == SDLK_SEMICOLON) {
                w->state->command_mode = !w->state->command_mode;
                if (!w->state->command_mode) {
                    str_clear(&w->state->cmd_buffer);
                }
            }
            break;
        default:
            break;
        }
    }
}
