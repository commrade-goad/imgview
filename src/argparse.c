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
    popt_t opt = {
        .file_in = arrstr_init(10),
        .check_wayland = true,
    };
    char *program_name = argv[0];

    for (int i = 1; i < argc; i++) {
        char *current = argv[i];
        size_t current_len = strlen(current);

        if (current[0] == '-') {
            for (size_t j = 1; j < current_len; j++) {
                switch (current[j]) {
                case 'x':
                    opt.check_wayland = false;
                    break;
                default:
                    fprintf(stderr, "ERROR: Unknown option: %c\n", current[j]);
                    break;
                }
            }
        } else {
            arrstr_push(&opt.file_in, current);
        }
    }
    return opt;
}

void parse_args_deinit(popt_t *popt) {
    arrstr_deinit(&popt->file_in);
}
