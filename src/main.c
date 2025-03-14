#include <Imlib2.h>
#include <SDL3/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "image.h"
#include "state.h"
#include "window.h"

bool check_args(int argc, char **argv) {
    (void)argv;
    if (argc <= 1) {
        fprintf(stderr, "ERROR: Need atleast 1 image to open.");
        return false;
    }
    return true;
}

int main(int argc, char **argv) {
    bool valid_args = check_args(argc, argv);
    if (!valid_args)
        return -1;

    const char *session_type = getenv("XDG_SESSION_TYPE");
    if (!session_type) {
        fprintf(stderr, "ERROR: Could not find `XDG_SESSION_TYPE` env var.\n");
        return -1;
    }
    if (SDL_strcmp(session_type, "wayland") == 0) {
        SDL_SetHint(SDL_HINT_VIDEO_DRIVER, "wayland");
    }

    struct state_t state = init_state();

    struct window_t w = init_window();
    if (init_SDL(&w) < 0) {
        return 1;
    }
    w.state = &state;

    load_image(&w, argv[1]);

    state.rec = (SDL_FRect){
        .w = state.texture->w,
        .h = state.texture->h,
        .x = 0,
        .y = 0,
    };

    window_loop(&w);

    deinit_state(&state);
    deinit_SDL(&w);
    return 0;
}
