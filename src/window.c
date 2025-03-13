#include "window.h"
#include "wcontrol.h"
#include "image.h"
#include <stdio.h>
#include <math.h>

#define SCROLL_SPEED 400

int init_SDL(struct window_t *w)
{
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "ERROR: SDL could not initialize! SDL_Error: %s\n",
                SDL_GetError());
        return -1;
    }
    if (!SDL_CreateWindowAndRenderer("imgview", 360, 360,
                                     SDL_WINDOW_RESIZABLE | SDL_WINDOW_VULKAN,
                                     &w->win, &w->ren)) {
        fprintf(stderr,
                "ERROR: Window and renderer could not be created! SDL_Error: %s\n",
                SDL_GetError());
        return -1;
    }
    // set to enable basic vsync
    SDL_SetRenderVSync(w->ren, 1);
    return 0;
}

void set_window_size(struct window_t *win)
{
    SDL_SetWindowSize(win->win, win->state->texture->w, win->state->texture->h);
}

void window_loop(struct window_t *w)
{
    set_window_size(w);
    SDL_Event event;

    Uint64 current_time = SDL_GetTicksNS();
    double future_time = SDL_GetTicksNS();

    while (!w->quit) {
        future_time = SDL_GetTicksNS();
        w->dt = (double)(future_time - current_time) / 1000000000.0;
        current_time = future_time;

        if (w->state->can_reset) center_image(w);
        handle_event(w, &event);
        SDL_SetRenderDrawColor(w->ren, 0x1e, 0x1e, 0x2e, 255);
        SDL_RenderClear(w->ren);

        // render the image texture
        if (w->state->texture) {
            SDL_RenderTexture(w->ren, w->state->texture, NULL, &w->state->rec);
        }

        SDL_RenderPresent(w->ren);
    }
}

void deinit_SDL(struct window_t *w)
{
    SDL_DestroyRenderer(w->ren);
    SDL_DestroyWindow(w->win);
    SDL_Quit();
}

struct window_t init_window()
{
    return (struct window_t){
        .win = NULL,
        .ren = NULL,
        .quit = false,
        .state = NULL,
        .dt = 0,
    };
}

void handle_event(struct window_t *w, SDL_Event *e)
{
    const bool *key_state = SDL_GetKeyboardState(NULL);
    if (key_state[SDL_SCANCODE_ESCAPE]) {
        w->quit = true;
        return;
    }

    float movement = SCROLL_SPEED;

    const float zoom_incr = 0.1;
    if (key_state[SDL_SCANCODE_H])
        do_move(w, movement, 0);
    if (key_state[SDL_SCANCODE_J])
        do_move(w, 0, -movement);
    if (key_state[SDL_SCANCODE_K])
        do_move(w, 0, movement);
    if (key_state[SDL_SCANCODE_L])
        do_move(w, -movement, 0);

    while (SDL_PollEvent(e)) {
        switch (e->type) {
            case SDL_EVENT_QUIT:
                w->quit = true;
                return;
            case SDL_EVENT_KEY_DOWN:
                if (e->key.key == SDLK_MINUS) {
                    do_zoom(w, -zoom_incr);
                }
                if (e->key.key == SDLK_EQUALS) {
                    do_zoom(w, zoom_incr);
                }
                if (e->key.key == SDLK_R) {
                    w->state->can_reset = true;
                    w->state->zoom = 1.0;
                }
                break;
            default:
                break;
        }
    }
}

struct vec2_t get_window_size(struct window_t *w)
{
    int x, y;
    SDL_GetWindowSizeInPixels(w->win, &x, &y);
    return (struct vec2_t){
        .x = x,
        .y = y,
    };
}

void resize_window(struct window_t *win, int w, int h)
{
    SDL_SetWindowSize(win->win, w, h);
    set_window_size(win);
}
