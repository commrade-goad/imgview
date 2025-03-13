#ifndef STATE_H_
#define STATE_H_

#include <SDL3/SDL.h>

struct state_t {
    SDL_Texture *texture;
    float zoom;
    SDL_FRect rec;
    bool can_reset;
    struct state_t *next;
};

void deinit_state(struct state_t *state);
struct state_t init_state();

#endif // STATE_H_
