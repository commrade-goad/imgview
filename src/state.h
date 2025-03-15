#ifndef STATE_H_
#define STATE_H_

#include <SDL3/SDL.h>
#include "str.h"

typedef struct {
    SDL_Texture *texture;
    int zoom;
    SDL_FRect rec;
    bool can_reset;
    bool command_mode;
    str_t cmd_buffer;
} state_t;

state_t state_init();
void state_deinit(state_t *state);

#endif // STATE_H_
