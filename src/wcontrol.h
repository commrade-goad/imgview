#ifndef WCONTROL_H_
#define WCONTROL_H_

#include "window.h"

void do_zoom(struct window_t *w, float zinc);
void do_move(struct window_t *w, float dx, float dy);
bool check_viewport(struct window_t *w);

#endif // WCONTROL_H_
