#ifndef IMAGE_H_
#define IMAGE_H_

#include <SDL3/SDL.h>
#include <Imlib2.h>
#include "window.h"

void load_image(struct window_t *win, const char *img_path);

#endif // IMAGE_H_

