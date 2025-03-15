#ifndef WCONTROL_H_
#define WCONTROL_H_

#include "window.h"
#include "smanager.h"

void wcontrol_zoom(window_t *w, int zoom_lvl);
void wcontrol_move(window_t *w, int dx, int dy);
void wcontrol_handle_event(window_t *w, SDL_Event *e, smanager_t *s);

#endif // WCONTROL_H_
