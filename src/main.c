#include <Imlib2.h>
#include <SDL3/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "include/argparse.h"
#include "include/image.h"
#include "include/state.h"
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

    state_t state = state_init();

    window_t w = window_init();
    if (window_SDL_init(&w) < 0) {
        return 1;
    }
    w.state = &state;

    load_image(&w, opt.file_in.data[0].data);

    window_loop(&w, (vec2_t){.x = opt.ws.x, .y = opt.ws.y});

    parse_args_deinit(&opt);
    state_deinit(&state);
    window_deinit(&w);
    return 0;
}
