#include "image.h"
#include <stdio.h>

void generate_texture(DATA32 *image_data, struct window_t *w)
{
    int img_width = imlib_image_get_width();
    int img_height = imlib_image_get_height();

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
    if (w->ren == NULL || w->state == NULL) return;
    w->state->texture = SDL_CreateTextureFromSurface(w->ren, surface);
    if (!w->state->texture) {
        fprintf(stderr, "ERROR: Failed to create the texture from the surface %s\n", SDL_GetError());
        return;
    }
    SDL_DestroySurface(surface);
}

void center_image(struct window_t *win)
{
    struct vec2_t winsize = get_window_size(win);
    win->state->rec.y = (winsize.y - win->state->rec.h) / 2;
    win->state->rec.x = (winsize.x - win->state->rec.w) / 2;

    if (winsize.x < winsize.y) {
        win->state->rec.w = winsize.x;
        win->state->rec.h = (winsize.x / win->state->texture->w) * win->state->texture->h;
    } else {
        win->state->rec.h = winsize.y;
        win->state->rec.w = (winsize.y / win->state->texture->h) * win->state->texture->w;
    }
}

void load_image(struct window_t *win, const char *img_path)
{
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

    DATA32 *image_data = imlib_image_get_data();
    generate_texture(image_data, win);

    center_image(win);

    imlib_free_image();
}

