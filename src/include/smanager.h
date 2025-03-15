#ifndef SMANAGER_H_
#define SMANAGER_H_

#include "state.h"
#include "window.h"

typedef struct {
    state_t *state;
    size_t len, cap;
    int active;
} smanager_t;

smanager_t smanager_init(int cap);
void smanager_deinit(smanager_t *smgr);
void smanager_next(smanager_t *s, int n);
void smanager_prev(smanager_t *s, int n);
void smanager_create(smanager_t *s, window_t *win, const char *file);
void smanager_swap_w_state(window_t *w, smanager_t *s);

#endif // SMANAGER_H_
