project('my_crossplatform_game', 'cpp',
  version : '1.0',
  default_options : [
    'warning_level=3',
    'optimization=0',
    'cpp_std=c++17'
  ]
)

sources = files('main.cpp')

sources += files(
  'core/Signal/Signal.cpp',
  'core/Processing/SignalOps.cpp',
  'core/Processing/FFT.cpp',
  'core/Processing/STFT.cpp',
  'core/Generators/Generator.cpp',
  'core/Generators/SineGenerator.cpp',
  'ui/App.cpp'
)

raylib_dep = dependency('raylib', required : true)

executable('start',
  sources,
  dependencies : [raylib_dep]
)
