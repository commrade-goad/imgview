#include "window.h"
#include <math.h>
#include <stdio.h>

float clamp(float value, float min, float max) {
    return fminf(fmaxf(value, min), max);
}

int init_SDL(struct window_t *w) {
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

void set_window_size(struct window_t *win) {
    SDL_SetWindowSize(win->win, win->state->texture->w, win->state->texture->h);
}

void window_loop(struct window_t *w) {
    set_window_size(w);
    SDL_Event event;

    Uint64 current_time = SDL_GetTicksNS();

    while (!w->quit) {
        handle_event(w, &event, &current_time);
        SDL_SetRenderDrawColor(w->ren, 0x1e, 0x1e, 0x2e, 255);
        SDL_RenderClear(w->ren);

        // render the image texture
        if (w->state->texture) {
            SDL_RenderTexture(w->ren, w->state->texture, NULL, &w->state->rec);
        }

        SDL_RenderPresent(w->ren);
    }
}

void deinit_SDL(struct window_t *w) {
    SDL_DestroyRenderer(w->ren);
    SDL_DestroyWindow(w->win);
    SDL_Quit();
}

struct window_t init_window() {
    return (struct window_t){
        .win = NULL,
        .ren = NULL,
        .quit = false,
        .state = NULL,
    };
}

void do_zoom(struct window_t *w) {
    w->state->rec.w = w->state->texture->w * w->state->zoom;
    w->state->rec.h = w->state->texture->h * w->state->zoom;
}

void do_move(struct window_t *w, float dx, float dy) {
    float new_posx = w->state->rec.x + dx;
    float new_posy = w->state->rec.y + dy;
    // make it so that cant move the image out of the window
    if (new_posx > w->state->rec.w * 0.2)
        new_posx = w->state->rec.x;
    if (new_posy > w->state->rec.h * 0.2)
        new_posy = w->state->rec.y;
    w->state->rec.y = new_posy;
    w->state->rec.x = new_posx;
}

void handle_event(struct window_t *w, SDL_Event *e, Uint64 *current_time) {
    double future_time = SDL_GetTicksNS();
    double dt = (double)(future_time - *current_time) / 1000000000.0;
    *current_time = future_time;

    const bool *key_state = SDL_GetKeyboardState(NULL);
    if (key_state[SDL_SCANCODE_ESCAPE]) {
        w->quit = true;
        return;
    }

    static const float scroll_speed = 400.0;
    if (key_state[SDL_SCANCODE_H])
        do_move(w, scroll_speed * dt, 0);
    if (key_state[SDL_SCANCODE_J])
        do_move(w, 0, -scroll_speed * dt);
    if (key_state[SDL_SCANCODE_K])
        do_move(w, 0, scroll_speed * dt);
    if (key_state[SDL_SCANCODE_L])
        do_move(w, -scroll_speed * dt, 0);
    if (key_state[SDL_SCANCODE_MINUS]) {
        w->state->zoom -= 0.07;
        do_zoom(w);
    }
    if (key_state[SDL_SCANCODE_EQUALS]) {
        w->state->zoom += 0.07;
        do_zoom(w);
    }
    if (key_state[SDL_SCANCODE_R]) {
        w->state->rec.x = 0;
        w->state->rec.y = 0;
    }

    while (SDL_PollEvent(e)) {
        if (e->type == SDL_EVENT_QUIT) {
            w->quit = true;
            return;
        }
    }
}
