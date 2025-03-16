#include <Imlib2.h>
#include <SDL3/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "include/argparse.h"
#include "include/smanager.h"
#include "include/window.h"

int main(int argc, char *argv[]) {

    // check args.
    bool valid_args = check_args(argc, argv, 2);
    if (!valid_args)
        return -1;

    popt_t opt = parse_args(argc, argv);

    if (opt.check_wayland) {
        const char *session_type = getenv("XDG_SESSION_TYPE");
        if (!session_type) {
            fprintf(stderr,
                    "ERROR: Could not find `XDG_SESSION_TYPE` env var.\n");
            return -1;
        }
        if (SDL_strcmp(session_type, "wayland") == 0) {
            SDL_SetHint(SDL_HINT_VIDEO_DRIVER, "wayland");
        }
    }

    smanager_t sman = smanager_init(10);

    window_t w = window_init();
    if (window_SDL_init(&w, opt.ws) < 0) {
        return 1;
    }

    for (int i = 0; i < (int)opt.file_in.len; i++) {
        if (!smanager_create(&sman, &w, opt.file_in.data[i].data)) {
            fprintf(stderr, "ERROR: Failed to create the state.\n");
        }
    }

    if (w.state->texture == NULL) {
        if (!smanager_swap_w_state(&w, &sman)) {
            parse_args_deinit(&opt);
            smanager_deinit(&sman);
            window_deinit(&w);
            return -1;
        }
    }
    window_loop(&w, (void*) &sman, opt.ws);

    parse_args_deinit(&opt);
    smanager_deinit(&sman);
    window_deinit(&w);
    return 0;
}
