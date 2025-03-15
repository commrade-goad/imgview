#include <string.h>

#include "include/argparse.h"

bool check_args(int argc, char **argv, size_t min) {
    (void)argv;
    if (argc < (int)min) {
        fprintf(stderr, "ERROR: Need atleast 1 image to open.");
        return false;
    }
    return true;
}

popt_t parse_args(int argc, char *argv[]) {
    bool capture_mode = false;
    popt_t opt = {.file_in = arrstr_init(10),
                  .check_wayland = true,
                  .ws = (vec2_t){
                      .x = 1280,
                      .y = 720,
                  }};

    for (int i = 1; i < argc; i++) {
        char *current = argv[i];
        size_t current_len = strlen(current);

        if (current[0] == '-') {
            for (size_t j = 1; j < current_len; j++) {
                switch (current[j]) {
                case 'x':
                    opt.check_wayland = false;
                    break;
                case 'w':
                    capture_mode = true;
                    break;
                default:
                    fprintf(stderr, "ERROR: Unknown option: %c\n", current[j]);
                    break;
                }
            }
        } else {
            if (!capture_mode) {
                arrstr_push(&opt.file_in, current);
                continue;
            }

            int xpos = -1;
            for (int j = 0; j < (int)current_len; j++) {
                if (current[j] == 'x') {
                    xpos = j;
                    break;
                }
            }

            if (xpos < 0) {
                fprintf(stderr, "ERROR: Not a valid WxH format.\n");
                return opt;
            }

            size_t rside = atoll(current + (xpos + 1));
            current[xpos] = '\0';
            size_t lside = atoll(current);
            current[xpos] = 'x';

            opt.ws = (vec2_t){
                .x = lside > 100 ? lside : 1280,
                .y = rside > 100 ? rside : 720,
            };
            capture_mode = false;
        }
    }
    return opt;
}

void parse_args_deinit(popt_t *popt) {
    arrstr_deinit(&popt->file_in);
}
