#ifndef EVAL_H_
#define EVAL_H_

#include <stdbool.h>
#include "window.h"

#define RESET 'r'
#define ZOOM  'z'
#define NEXT  'n'
#define PREV  'p'

typedef enum {
    TReset,
    TZoom,
    TNext,
    TPrev,
    TUnknown
} TKind;

struct Token{
    TKind kind;
    int value;
};

void tokenize(str_t *cmd, struct Token *tokens);
bool evaluate_command(struct window_t *w);

#endif // EVAL_H_

