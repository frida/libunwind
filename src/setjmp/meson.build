sources = [
  'longjmp.c',
  'siglongjmp.c',
]

libunwind_setjmp = library('unwind-setjmp', sources + setjmp_backend_sources,
  version: setjmp_version,
  include_directories: libunwind_internal_incdirs,
  dependencies: [libunwind_generic_dep, libunwind_dep],
  install: true,
)
libunwind_setjmp_dep = declare_dependency(
  link_with: libunwind_setjmp,
  include_directories: libunwind_public_incdirs,
)

pkg = import('pkgconfig')
pkg.generate(libunwind_setjmp,
  name: 'libunwind-setjmp',
  description: 'libunwind setjmp library',
)

meson.override_dependency('libunwind-setjmp', libunwind_setjmp_dep)
