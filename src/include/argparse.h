#ifndef ARGPARSE_H_
#define ARGPARSE_H_

#include "str.h"
#include <stdio.h>

typedef struct {
    bool check_wayland;
    arrstr_t file_in;
} popt_t;

bool check_args(int argc, char *argv[], size_t min);
popt_t parse_args(int argc, char *argv[]);
void parse_args_deinit(popt_t *popt);

#endif // ARGPARSE_H_
