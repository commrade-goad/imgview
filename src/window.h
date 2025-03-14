#ifndef WINDOW_H_
#define WINDOW_H_

#include <SDL3/SDL.h>
#include "state.h"

struct window_t {
    SDL_Window *win;
    SDL_Renderer *ren;
    bool quit;
    struct state_t *state;
    size_t dt;
};

struct vec2_t {
    size_t x, y;
};

struct window_t init_window();

int init_SDL(struct window_t *w);
void window_loop(struct window_t *w);
void deinit_SDL(struct window_t *w);
void resize_window(struct window_t *win, int w, int h);
struct vec2_t get_window_size(struct window_t *w);
void render(struct window_t *w);

#endif // WINDOW_H_
