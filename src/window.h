#ifndef WINDOW_H_
#define WINDOW_H_

#include <SDL3/SDL.h>
#include "state.h"

struct window_t {
    SDL_Window *win;
    SDL_Renderer *ren;
    bool quit;
    struct state_t *state;
};

struct window_t init_window();

int init_SDL(struct window_t *w);
void window_loop(struct window_t *w);
void deinit_SDL(struct window_t *w);
void handle_event(struct window_t *w, SDL_Event *e, Uint64 *start_time);

#endif // WINDOW_H_
