#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

#include "eval.h"
#include "image.h"
#include "wcontrol.h"
#include "str.h"

bool evaluate_command(window_t *w) {
    if (w->state->cmd_buffer.len <= 0)
        return false;
    str_t *cmd = &w->state->cmd_buffer;
    printf("submiting cmd: %s\n", cmd->data);
    token_t token;
    tokenize(cmd, &token);
    switch (token.kind) {
    case TReset:
        printf("INFO: Reseting the image pos.\n");
        center_image(w);
        break;
    case TZoom:
        size_t diff = token.value - w->state->zoom;
        wcontrol_zoom(w, diff);
        break;
    case TNext:
        printf("NOT YET IMPLEMENTED\n");
        break;
    case TPrev:
        printf("NOT YET IMPLEMENTED\n");
        break;
    default:
        return false;
    }
    return true;
}

void tokenize(str_t *cmd, token_t *token) {
    if (cmd->len <= 0) {
        token->kind = TUnknown;
        return;
    }
    // reset is a special case that doesn't need any additional arguments
    if (cmd->data[0] == RESET) {
        *token = (token_t){
            .kind = TReset,
            .value = 0,
        };
        return;
    }
    char *cursor = cmd->data;
    char buffer[4] = {0};
    size_t buffer_len = 0;
    while (*cursor != '\0') {
        if (buffer_len >= 4) {
            token->kind = TUnknown;
            return;
        }
        if (isdigit(*cursor)) {
            buffer[buffer_len] = *cursor;
            buffer_len += 1;
        } else if (buffer_len > 0 && buffer_len < 4) {
            switch (*cursor) {
            case ZOOM:
                token->kind = TZoom;
                token->value = atoi(buffer);
                break;
            case NEXT:
                token->kind = TNext;
                token->value = atoi(buffer);
                break;
            case PREV:
                token->kind = TPrev;
                token->value = atoi(buffer);
                break;
            default:
                token->kind = TUnknown;
                break;
            }
            if (token->kind != TUnknown) {
                buffer_len = 0;
                break;
            }
        }
        cursor += 1;
    }
}
