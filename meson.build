project('imgview', 'c',
  version : '0.1',
  default_options : [
    'warning_level=3',
    'c_std=c23',
    'optimization=3',
    'debug=false'
  ]
)

pname = 'imgview'
imlib2 = dependency('imlib2', method: 'pkg-config')
sdl3 = dependency('sdl3', method: 'pkg-config')

executable(
  pname,
  'src/main.c', 'src/window.c',
  'src/state.c', 'src/image.c',
  'src/wcontrol.c', 'src/str.c',
  'src/eval.c', 'src/argparse.c',
  'src/smanager.c',
  dependencies: [imlib2, sdl3],
  install : true,
  link_args : ['-lm']
)
