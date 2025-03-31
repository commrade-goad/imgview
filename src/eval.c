#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

#include "include/eval.h"
#include "include/image.h"
#include "include/str.h"
#include "include/wcontrol.h"

bool evaluate_command(window_t *w, smanager_t *s) {
    if (w->state->cmd_buffer.len <= 0)
        return false;
    str_t *cmd = &w->state->cmd_buffer;
    token_t token;
    tokenize(cmd, &token);
    switch (token.kind) {
    case TReset: {
        center_image(w);
        break;
    }
    case TZoom: {
        int diff = token.value - w->state->zoom;
        wcontrol_zoom(w, diff);
        break;
    }
    case TNext: {
        smanager_next(s, token.value);
        smanager_swap_w_state(w, s);
        break;
    }
    case TPrev: {
        smanager_prev(s, token.value);
        smanager_swap_w_state(w, s);
        break;
    }
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
                memset(buffer, '\0', 4);
                break;
            }
        }
        cursor += 1;
    }
}
