# IMGVIEW
a simple suckless like image viewer (no mouse needed)

## Option

By default it capped at 60FPS to change modify `src/window.c:7` in

```c
/* ... rest of the code  ... */

#define FPS 60

/* ... rest of the code  ... */
```

change to whatever fps target you want.

## Build

__Configure Meson :__

```sh
meson setup build
```

__Compile Application :__

```sh
ninja -C build
# or
meson compile -C build
```

## Control

| Key  | Function                 |
|------|--------------------------|
| hjkl | move around              |
| +, - | zoom in and zoom out     |
| r    | reset the view to fit in |
| n, p | next or prev image       |
| ;    | toggle command mode      |

## Args
- `-x` to specify to use X11 or XWayland (disabling the check for XDG_CURRENT_SESSION env)
- `-w WxH` to specify the size of the window (work great with `-x` on wayland kinda meh...)
