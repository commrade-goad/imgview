#include "window.h"

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
    while (!w->quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                w->quit = true;
            }
        }
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

struct window_t window_t_init()
{
    return (struct window_t) {
        .win = NULL,
        .ren = NULL,
        .quit = false,
        .state = NULL,
    };
}
