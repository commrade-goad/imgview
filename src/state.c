#include "state.h"

void state_deinit(state_t *state) {
    str_deinit(&state->cmd_buffer);
    SDL_DestroyTexture(state->texture);
}

state_t state_init() {
    return (state_t){
        .zoom = 100,
        .texture = NULL,
        .rec = {0},
        .can_reset = true,
        .command_mode = false,
        .cmd_buffer = str_init(8),
    };
}
