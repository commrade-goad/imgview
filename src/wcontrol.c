#include "wcontrol.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

bool check_viewport(struct window_t *w)
{
    if ((w->state->rec.x + w->state->rec.w) <= 0) {
        return false;
    }
    return true;
}

void do_zoom(struct window_t *w, float zinc)
{
    printf("WIP: ZOOM\n");
}

void do_move(struct window_t *w, float dx, float dy)
{
    w->state->can_reset = false;
    struct vec2_t force = {
        .x = dx * w->dt,
        .y = dy * w->dt,
    };
    struct vec2_t winsize = get_window_size(w);
    SDL_FRect *state_rec = &w->state->rec;
    struct vec2_t new_pos = {
        .x = state_rec->x + force.x,
        .y = state_rec->y + force.y,
    };
    if (new_pos.x + state_rec->w <= (winsize.x / 8) * 7 ||
        new_pos.x >= winsize.x / 8) {
        new_pos.x = state_rec->x;
    }
    if (new_pos.y + state_rec->h <= (winsize.y / 8) * 7 ||
        new_pos.y >= winsize.y / 8) {
        new_pos.y = state_rec->y;
    }
    state_rec->x = new_pos.x;
    state_rec->y = new_pos.y;
}
