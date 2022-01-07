configure_file(
  input: 'config.h.meson.in',
  output: 'config.h',
  configuration: cdata,
)

if not cdata.has('HAVE_STDALIGN_H')
  configure_file(
    input: 'win' / 'fakestdalign.h.in',
    output: 'stdalign.h',
    configuration: cdata,
  )
endif

if not cdata.has('HAVE_STDATOMIC_H')
  configure_file(
    input: 'win' / 'fakestdatomic.h.in',
    output: 'stdatomic.h',
    configuration: cdata,
  )
endif

libunwind_h_in = files('libunwind.h.in')
unwind_h = files('unwind.h')
libunwind_arch_h = files('libunwind-' + target_arch + '.h')
libunwind_dynamic_h = files('libunwind-dynamic.h')
libunwind_common_h_in = files('libunwind-common.h.in')
coredump_h = files('libunwind-coredump.h')
ptrace_h = files('libunwind-ptrace.h')

subdir('public')
subdir('tdep')
