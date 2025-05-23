#ifndef WINDOW_H_
#define WINDOW_H_

#include <SDL3/SDL.h>

#include "state.h"
#include "vec.h"

typedef struct {
    SDL_Window *win;
    SDL_Renderer *ren;
    bool quit;
    state_t *state;
    size_t dt;
    int fps;
    Uint64 fps_delay;
} window_t;

window_t window_init(void);
int window_SDL_init(window_t *w, vec2_t ws);
void window_loop(window_t *w, void *s, vec2_t ws);
void window_deinit(window_t *w);
void window_resize(window_t *win, int w, int h);
vec2_t get_window_size(window_t *w);
void window_render(window_t *w);

#endif // WINDOW_H_
