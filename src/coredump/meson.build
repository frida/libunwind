sources = [
  '_UCD_accessors.c',
  '_UCD_create.c',
  '_UCD_destroy.c',
  '_UCD_access_mem.c',
  '_UCD_elf_map_image.c',
  '_UCD_find_proc_info.c',
  '_UCD_get_proc_name.c',
  '_UCD_corefile_elf.c',
  '_UPT_elf.c',
  '_UPT_access_fpreg.c',
  '_UPT_get_dyn_info_list_addr.c',
  '_UPT_put_unwind_info.c',
  '_UPT_resume.c',
]

if target_os == 'linux'
  sources += [
    '_UCD_access_reg_linux.c',
    '_UCD_get_threadinfo_prstatus.c',
    '_UCD_get_mapinfo_linux.c',
  ]
endif

if target_os == 'freebsd'
  sources += [
    '_UCD_access_reg_freebsd.c',
    '_UCD_get_threadinfo_prstatus.c',
    '_UCD_get_mapinfo_generic.c',
  ]
endif

libunwind_coredump = library('unwind-coredump', sources,
  version: coredump_version,
  include_directories: libunwind_internal_incdirs,
  dependencies: [libunwind_generic_dep, libunwind_dep] + libunwind_deps,
  install: true,
)
libunwind_coredump_dep = declare_dependency(
  link_with: libunwind_coredump,
  include_directories: libunwind_public_incdirs,
)

pkg = import('pkgconfig')
pkg.generate(libunwind_coredump,
  name: 'libunwind-coredump',
  description: 'libunwind coredump library',
)

meson.override_dependency('libunwind-coredump', libunwind_coredump_dep)
