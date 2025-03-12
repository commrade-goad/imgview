#include <SDL3/SDL.h>
#include <Imlib2.h>
#include <stdbool.h>

#include "window.h"
#include "state.h"

bool check_args(int argc, char **argv)
{
    (void) argv;
    if (argc <= 1) {
        fprintf(stderr, "ERROR: Need atleast 1 image to open.");
        return false;
    }
    return true;
}

/* WIP */
void load_image(struct window_t *win, struct state_t *state, const char *img_path) {
    imlib_set_cache_size(10 * 1024 * 1024);
    Imlib_Image img = imlib_load_image(img_path);
    if (!img) {
        fprintf(stderr, "ERROR: Failed to load image %s\n", img_path);
        SDL_Quit();
        return;
    }
    imlib_context_set_image(img);
    if (!imlib_image_has_alpha()) {
        imlib_image_set_has_alpha(1);
    }

    int img_width = imlib_image_get_width();
    int img_height = imlib_image_get_height();
    DATA32 *image_data = imlib_image_get_data();

    SDL_Surface *surface = SDL_CreateSurfaceFrom(
        img_width, img_height,
        SDL_PIXELFORMAT_BGRA32,
        image_data,
        img_width * 4
    );

    if (!surface) {
        fprintf(stderr, "ERROR: Failed to create the surface %s\n", SDL_GetError());
        return;
    }
    state->texture = SDL_CreateTextureFromSurface(win->ren, surface);
    if (!state->texture) {
        fprintf(stderr, "ERROR: Failed to create the texture from the surface %s\n", SDL_GetError());
        return;
    }
    SDL_DestroySurface(surface);
    imlib_free_image();
}

int main(int argc, char **argv)
{

    bool valid_args = check_args(argc, argv);
    if (!valid_args) return -1;

    struct state_t state = {
        .zoom = 1.0f,
        .texture = NULL,
        .rec = {0},
    };

    struct window_t w = window_t_init();
    if (init_SDL(&w) < 0) {
        return 1;
    }
    load_image(&w, &state, argv[1]);

    state.rec = (SDL_FRect) {
        .w = state.texture->w,
        .h = state.texture->h,
        .x = 0,
        .y = 0,
    };
    w.state = &state;

    window_loop(&w);

    deinit_state(&state);
    deinit_SDL(&w);
    return 0;
}
