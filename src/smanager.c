#include "include/smanager.h"
#include "include/image.h"
#include <stdio.h>

smanager_t smanager_init(int cap) {
    if (cap <= 0)
        cap = 10;
    smanager_t a = (smanager_t){.cap = cap,
                                .active = 0,
                                .len = 0,
                                .state = malloc(sizeof(state_t) * cap)};
    return a;
}

void smanager_deinit(smanager_t *smgr) {
    for (int i = 0; i < (int)smgr->len; i++) {
        state_deinit(&smgr->state[i]);
    }
    free(smgr->state);
}

bool smanager_create(smanager_t *s, window_t *win, const char *file) {
    state_t new_state = state_init();
    win->state = &new_state;
    if (!load_image(win, file)) {
        win->state = NULL;
        return false;
    }
    if (win->state->texture == NULL) {
        if (!smanager_swap_w_state(win, s))
            win->state = NULL;
        return false;
    }
    s->state[s->len] = new_state;
    s->len += 1;
    smanager_swap_w_state(win, s);
    return true;
}

bool smanager_swap_w_state(window_t *w, smanager_t *s) {
    if (s->active < (int)s->len) {
        w->state = &s->state[s->active];
        return true;
    }
    return false;
}

void smanager_next(smanager_t *s, int n) {
    if (s->active + n < (int)s->len)
        s->active += 1;
}
void smanager_prev(smanager_t *s, int n) {
    if (s->active - n >= 0)
        s->active -= 1;
}
