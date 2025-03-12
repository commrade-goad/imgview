#include "state.h"

void deinit_state(struct state_t *state)
{
    SDL_DestroyTexture(state->texture);
}
