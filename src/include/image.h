#ifndef IMAGE_H_
#define IMAGE_H_

#include <SDL3/SDL.h>
#include <Imlib2.h>

#include "window.h"

bool load_image(window_t *win, const char *img_path);
void center_image(window_t *win);

#endif // IMAGE_H_
