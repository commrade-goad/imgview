#ifndef EVAL_H_
#define EVAL_H_

#include <stdbool.h>
#include "window.h"
#include "smanager.h"

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
} tkind_t;

typedef struct {
    tkind_t kind;
    int value;
} token_t;

void tokenize(str_t *cmd, token_t *token);
bool evaluate_command(window_t *w, smanager_t *s);

#endif // EVAL_H_

