#include "state.h"

void deinit_state(struct state_t *state) { SDL_DestroyTexture(state->texture); }

struct state_t init_state() {
    return (struct state_t){
        .zoom = 100,
        .texture = NULL,
        .rec = {0},
        .next = NULL,
        .can_reset = true,
    };
}
