#ifndef STATE_H_
#define STATE_H_

#include <SDL3/SDL.h>

struct state_t {
    SDL_Texture *texture;
    int zoom;
    SDL_FRect rec;
    bool can_reset;
    bool command_mode;
    char cmd_buffer[8];
    struct state_t *next;
};

void deinit_state(struct state_t *state);
struct state_t init_state();

#endif // STATE_H_
