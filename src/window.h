#ifndef WINDOW_H_
#define WINDOW_H_

#include <SDL3/SDL.h>
#include "state.h"
#include <stdio.h>

struct window_t {
    SDL_Window *win;
    SDL_Renderer *ren;
    bool quit;
    struct state_t *state;
};

struct window_t window_t_init();

int init_SDL(struct window_t *w);
void window_loop(struct window_t *w);
void deinit_SDL(struct window_t *w);

#endif // WINDOW_H_
