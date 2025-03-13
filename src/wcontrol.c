#include "wcontrol.h"
#include <math.h>

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
    struct vec2_t win_size = get_window_size(w);
    float xx = fabs(new_posx) + win_size.x;
    float yy = fabs(new_posy) + win_size.y;

    if (new_posx > 0)
        new_posx = w->state->rec.x;
    else if (xx > w->state->rec.w)
        new_posx = w->state->rec.x;

    if (new_posy > 0)
        new_posy = w->state->rec.y;
    else if (yy > w->state->rec.h)
        new_posy = w->state->rec.y;

    w->state->rec.y = new_posy;
    w->state->rec.x = new_posx;
}
