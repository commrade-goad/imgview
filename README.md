# IMGVIEW
a simple suckless like image viewer (no mouse needed)

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
| r    | reset the view to fit in |

## Note
still in _dev_ it didn't support alot of stuff example:

- open more than 1 file.
- cmd mode half done.
- no args support yet.
