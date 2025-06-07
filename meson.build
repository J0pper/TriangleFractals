project(
  'TriangleFractals',
  'c',
  default_options: [
    'default_library=static',
    'buildtype=debug',
    'warning_level=3',
    'optimization=0',
  ]
)

cc = meson.get_compiler('c')

sdl2_dep = dependency('sdl2', static: true, required: true)
math_dep = cc.find_library('m', static: true, required: true)

subdir('src')

executable('TriangleFractals', sources, dependencies: [sdl2_dep, math_dep])
