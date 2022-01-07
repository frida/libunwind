sources = [
  '_UPT_elf.c',
  '_UPT_accessors.c',
  '_UPT_access_fpreg.c',
  '_UPT_access_mem.c',
  '_UPT_access_reg.c',
  '_UPT_create.c',
  '_UPT_destroy.c',
  '_UPT_find_proc_info.c',
  '_UPT_get_dyn_info_list_addr.c',
  '_UPT_put_unwind_info.c',
  '_UPT_get_proc_name.c',
  '_UPT_reg_offset.c',
  '_UPT_resume.c',
]

libunwind_ptrace = library('unwind-ptrace', sources,
  version: ptrace_version,
  include_directories: libunwind_internal_incdirs,
  dependencies: [libunwind_generic_dep, libunwind_dep] + libunwind_deps,
  install: true,
)
libunwind_ptrace_dep = declare_dependency(
  link_with: libunwind_ptrace,
  include_directories: libunwind_public_incdirs,
)

pkg = import('pkgconfig')
pkg.generate(libunwind_ptrace,
  name: 'libunwind-ptrace',
  description: 'libunwind ptrace library',
)

meson.override_dependency('libunwind-ptrace', libunwind_ptrace_dep)
