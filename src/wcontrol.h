#ifndef WCONTROL_H_
#define WCONTROL_H_

#include "window.h"

void do_zoom(struct window_t *w, int zoom_lvl);
void do_move(struct window_t *w, int dx, int dy);
bool check_viewport(struct window_t *w);

#endif // WCONTROL_H_
