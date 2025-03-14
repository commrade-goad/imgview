#include "state.h"

void deinit_state(struct state_t *state) {
    str_deinit(&state->cmd_buffer);
    SDL_DestroyTexture(state->texture);
}

struct state_t init_state() {
    return (struct state_t){
        .zoom = 100,
        .texture = NULL,
        .rec = {0},
        .can_reset = true,
        .command_mode = false,
        .cmd_buffer = str_init(8),
    };
}
