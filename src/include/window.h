#ifndef WINDOW_H_
#define WINDOW_H_

#include <SDL3/SDL.h>

#include "state.h"

#define WINDOW_SIZE_LIMIT (vec2_t){1280, 720}

typedef struct {
    SDL_Window *win;
    SDL_Renderer *ren;
    bool quit;
    state_t *state;
    size_t dt;
} window_t;

typedef struct {
    size_t x, y;
} vec2_t;

window_t window_init();
int window_SDL_init(window_t *w);
void window_loop(window_t *w);
void window_deinit(window_t *w);
void window_resize(window_t *win, int w, int h);
vec2_t get_window_size(window_t *w);
void window_render(window_t *w);

#endif // WINDOW_H_
