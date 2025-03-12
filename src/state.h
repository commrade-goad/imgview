#ifndef STATE_H_
#define STATE_H_

#include <SDL3/SDL.h>

struct state_t {
    SDL_Texture *texture;
    float zoom;
    SDL_FRect rec;
};

void deinit_state(struct state_t *state);

#endif // STATE_H_
