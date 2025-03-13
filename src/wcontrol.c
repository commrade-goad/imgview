#include "wcontrol.h"

void do_zoom(struct window_t *w)
{
    w->state->rec.w = w->state->texture->w * w->state->zoom;
    w->state->rec.h = w->state->texture->h * w->state->zoom;
}

void do_move(struct window_t *w, float dx, float dy)
{
    float new_posx = w->state->rec.x + dx;
    float new_posy = w->state->rec.y + dy;
    // make it so that cant move the image out of the window
    if (new_posx > w->state->rec.w * 0.2)
        new_posx = w->state->rec.x;
    if (new_posy > w->state->rec.h * 0.2)
        new_posy = w->state->rec.y;
    w->state->rec.y = new_posy;
    w->state->rec.x = new_posx;
}
