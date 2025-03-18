#include <stdio.h>
#include <math.h>

#include "include/image.h"

bool generate_texture(DATA32 *image_data, window_t *w) {
    int img_width = imlib_image_get_width();
    int img_height = imlib_image_get_height();

    SDL_Surface *surface =
        SDL_CreateSurfaceFrom(img_width, img_height, SDL_PIXELFORMAT_BGRA32,
                              image_data, img_width * 4);

    if (!surface) {
        fprintf(stderr, "ERROR: Failed to create the surface %s\n",
                SDL_GetError());
        return false;
    }

    if (w->ren == NULL || w->state == NULL)
        return false;
    w->state->texture = SDL_CreateTextureFromSurface(w->ren, surface);

    if (!w->state->texture) {
        fprintf(stderr,
                "ERROR: Failed to create the texture from the surface %s\n",
                SDL_GetError());
        return false;
    }
    SDL_DestroySurface(surface);
    return true;
}

void center_image(window_t *win) {
    state_t *s = win->state;
    vec2_t winsize = get_window_size(win);

    double window_aspect = (double)winsize.x / winsize.y;
    double image_aspect = (double)s->texture->w / s->texture->h;

    if (window_aspect < image_aspect) {
        s->rec.w = winsize.x;
        s->rec.h = round(winsize.x / image_aspect);
    } else {
        s->rec.h = winsize.y;
        s->rec.w = round(winsize.y * image_aspect);
    }

    s->rec.x = round((winsize.x - s->rec.w) / 2);
    s->rec.y = round((winsize.y - s->rec.h) / 2);

    s->zoom = round((s->rec.w / s->texture->w) * 100);
}

bool load_image(window_t *win, const char *img_path) {
    imlib_set_cache_size(10 * 1024 * 1024);
    Imlib_Image img = imlib_load_image(img_path);
    if (!img) {
        fprintf(stderr, "ERROR: Failed to load image %s\n", img_path);
        return false;
    }
    imlib_context_set_image(img);
    if (!imlib_image_has_alpha()) {
        imlib_image_set_has_alpha(1);
    }

    DATA32 *image_data = imlib_image_get_data();
    if (generate_texture(image_data, win)) {
        center_image(win);
        imlib_free_image();
        return true;
    };
    imlib_free_image();
    return false;
}
