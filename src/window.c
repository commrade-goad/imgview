#include "window.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

float clamp(float value, float min, float max) {
    return fminf(fmaxf(value, min), max);
}

int init_SDL(struct window_t *w)
{
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "ERROR: SDL could not initialize! SDL_Error: %s\n",
                SDL_GetError());
        return -1;
    }
    if (!SDL_CreateWindowAndRenderer("imgview", 360, 360,
                                     SDL_WINDOW_RESIZABLE | SDL_WINDOW_VULKAN,
                                     &w->win, &w->ren))
    {
        fprintf(stderr,
                "ERROR: Window and renderer could not be created! SDL_Error: %s\n",
                SDL_GetError());
        return -1;
    }
    // set to enable basic vsync
    SDL_SetRenderVSync(w->ren, 1);
    return 0;
}

void set_window_size(struct window_t *win) {
    SDL_SetWindowSize(win->win, win->state->texture->w, win->state->texture->h);
}

void window_loop(struct window_t *w)
{
    set_window_size(w);
    SDL_Event event;

    Uint64 current_time = SDL_GetTicksNS();

    while (!w->quit) {
        handle_event(w, &event, &current_time);
        SDL_SetRenderDrawColor(w->ren, 0x1e, 0x1e, 0x2e, 255);
        SDL_RenderClear(w->ren);

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
    return (struct window_t) {
        .win = NULL,
        .ren = NULL,
        .quit = false,
        .state = NULL,
    };
}

void handle_event(struct window_t *w, SDL_Event *e, Uint64 *current_time)
{
    double future_time = SDL_GetTicksNS();
    double dt = (double) (future_time - *current_time) / 1000000000.0;
    *current_time = future_time;
    printf("delta time %f\n", dt);

    const bool *key_state = SDL_GetKeyboardState(NULL);
    if (key_state[SDL_SCANCODE_ESCAPE]) {
        w->quit = true;
        return;
    }

    static const float scroll_speed = 400.0;
    if (key_state[SDL_SCANCODE_H]) w->state->rec.x += scroll_speed * dt;
    if (key_state[SDL_SCANCODE_J]) w->state->rec.y -= scroll_speed * dt;
    if (key_state[SDL_SCANCODE_K]) w->state->rec.y += scroll_speed * dt;
    if (key_state[SDL_SCANCODE_L]) w->state->rec.x -= scroll_speed * dt;

    while (SDL_PollEvent(e)) {
        if (e->type == SDL_EVENT_QUIT) {
            w->quit = true;
            return;
        }
    }
}

