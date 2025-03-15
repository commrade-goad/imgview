#include <stdio.h>

#include "include/image.h"
#include "include/wcontrol.h"
#include "include/window.h"

int window_SDL_init(window_t *w, vec2_t ws) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "ERROR: SDL could not initialize! SDL_Error: %s\n",
                SDL_GetError());
        return -1;
    }
    if (!SDL_CreateWindowAndRenderer("imgview", ws.x, ws.y,
                                     SDL_WINDOW_RESIZABLE | SDL_WINDOW_VULKAN,
                                     &w->win, &w->ren)) {
        fprintf(
            stderr,
            "ERROR: Window and renderer could not be created! SDL_Error: %s\n",
            SDL_GetError());
        return -1;
    }
    // set to enable basic vsync
    SDL_SetRenderVSync(w->ren, 1);
    return 0;
}

void _set_window_size_fromtxt(window_t *win, vec2_t ws) {
    if (win->state->texture->w > (int)ws.x ||
        win->state->texture->h > (int)ws.y) {
        window_resize(win, ws.x, ws.y);
    } else {
        window_resize(win, win->state->texture->w, win->state->texture->h);
    }
}

void window_render(window_t *w) {
    SDL_SetRenderDrawColor(w->ren, 0x1e, 0x1e, 0x2e, 255);
    SDL_RenderClear(w->ren);

    // render the image texture
    if (w->state->texture) {
        SDL_RenderTexture(w->ren, w->state->texture, NULL, &w->state->rec);
    }

    if (w->state->command_mode) {
        SDL_SetRenderDrawColor(w->ren, 0xff, 0xff, 0xff, 255);
        vec2_t wsize = get_window_size(w);
        SDL_FRect rec = {0, wsize.y - 20, wsize.x, 20};
        SDL_RenderFillRect(w->ren, &rec);
    }

    SDL_RenderPresent(w->ren);
}

void window_loop(window_t *w, void *s, vec2_t ws) {
    SDL_Event event;

    smanager_t sman = *(smanager_t *)s;

    Uint64 current_time = SDL_GetTicksNS();
    Uint64 future_time = SDL_GetTicksNS();

    _set_window_size_fromtxt(w, ws);

    while (!w->quit) {
        future_time = SDL_GetTicksNS();
        w->dt = future_time - current_time / 1000000;
        current_time = future_time;

        if (w->state) {
            if (w->state->can_reset)
                center_image(w);
            wcontrol_handle_event(w, &event, &sman);
            window_render(w);
        }
    }
}

void window_deinit(window_t *w) {
    SDL_DestroyRenderer(w->ren);
    SDL_DestroyWindow(w->win);
    SDL_Quit();
}

window_t window_init() {
    return (window_t){
        .win = NULL,
        .ren = NULL,
        .quit = false,
        .state = NULL,
        .dt = 0,
    };
}

vec2_t get_window_size(window_t *w) {
    int x, y;
    SDL_GetWindowSizeInPixels(w->win, &x, &y);
    return (vec2_t){
        .x = x,
        .y = y,
    };
}

void window_resize(window_t *win, int w, int h) {
    if (!SDL_SetWindowSize(win->win, w, h)) {
        fprintf(stderr, "ERROR: Could not resize window %s\n", SDL_GetError());
        return;
    }
}
