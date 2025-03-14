#include "eval.h"
#include "src/image.h"
#include "str.h"

#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

bool evaluate_command(struct window_t *w) {
    if (w->state->cmd_buffer.len <= 0)
        return false;
    str_t *cmd = &w->state->cmd_buffer;
    printf("submiting cmd: %s\n", cmd->data);
    struct Token tokens;
    tokenize(cmd, &tokens);
    switch (tokens.kind) {
    case TReset:
        printf("INFO: Reseting the image pos.\n");
        center_image(w);
        break;
    case TZoom:
        assert("Not implemented");
        /*do_zoom(w, tokens.value);*/
        break;
    case TNext:
        assert("Not implemented");
        /*next_image(w, tokens.value);*/
        break;
    case TPrev:
        assert("Not implemented");
        /*prev_image(w, tokens.value);*/
        break;
    default:
        return false;
    }
    return true;
}

void tokenize(str_t *cmd, struct Token *tokens) {
    if (cmd->len <= 0) {
        tokens->kind = TUnknown;
        return;
    }
    // reset is a special case that doesn't need any additional arguments
    if (cmd->data[0] == RESET) {
        *tokens = (struct Token){
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
            tokens->kind = TUnknown;
            return;
        }
        if (isdigit(*cursor)) {
            buffer[buffer_len] = *cursor;
            buffer_len += 1;
        } else if (buffer_len > 0 && buffer_len < 4) {
            switch (*cursor) {
            case ZOOM:
                tokens->kind = TZoom;
                tokens->value = atoi(buffer);
                break;
            case NEXT:
                tokens->kind = TNext;
                tokens->value = atoi(buffer);
                break;
            case PREV:
                tokens->kind = TPrev;
                tokens->value = atoi(buffer);
                break;
            default:
                tokens->kind = TUnknown;
                break;
            }
            if (tokens->kind != TUnknown) {
                buffer_len = 0;
                break;
            }
        }
        cursor += 1;
    }
}
