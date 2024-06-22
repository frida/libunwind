arch_independent_sources = {
  'common': [
    'mi' / 'init.c',
    'mi' / 'flush_cache.c',
    'mi' / 'mempool.c',
    'mi' / 'strerror.c',
  ],
  'local_unwind': [
    'unwind' / 'Backtrace.c',
    'unwind' / 'DeleteException.c',
    'unwind' / 'FindEnclosingFunction.c',
    'unwind' / 'ForcedUnwind.c',
    'unwind' / 'GetBSP.c',
    'unwind' / 'GetCFA.c',
    'unwind' / 'GetDataRelBase.c',
    'unwind' / 'GetGR.c',
    'unwind' / 'GetIP.c',
    'unwind' / 'GetLanguageSpecificData.c',
    'unwind' / 'GetRegionStart.c',
    'unwind' / 'GetTextRelBase.c',
    'unwind' / 'RaiseException.c',
    'unwind' / 'Resume.c',
    'unwind' / 'Resume_or_Rethrow.c',
    'unwind' / 'SetGR.c',
    'unwind' / 'SetIP.c',
    'unwind' / 'GetIPInfo.c',
  ],
  'local_unwind:linux': [
    'mi' / '_ReadULEB.c',
    'mi' / '_ReadSLEB.c',
  ],
  'local_nounwind': [
    'mi' / 'backtrace.c',
    'mi' / 'dyn-cancel.c',
    'mi' / 'dyn-info-list.c',
    'mi' / 'dyn-register.c',
    'mi' / 'Ldyn-extract.c',
    'mi' / 'Lfind_dynamic_proc_info.c',
    'mi' / 'Lget_accessors.c',
    'mi' / 'Lget_proc_info_by_ip.c',
    'mi' / 'Lget_proc_name.c',
    'mi' / 'Lput_dynamic_unwind_info.c',
    'mi' / 'Ldestroy_addr_space.c',
    'mi' / 'Lget_reg.c',
    'mi' / 'Lset_reg.c',
    'mi' / 'Lget_fpreg.c',
    'mi' / 'Lset_fpreg.c',
    'mi' / 'Lset_caching_policy.c',
    'mi' / 'Lset_cache_size.c',
  ],
  'generic': [
    'mi' / 'Gdyn-extract.c',
    'mi' / 'Gdyn-remote.c',
    'mi' / 'Gfind_dynamic_proc_info.c',
    'mi' / 'Gget_accessors.c',
    'mi' / 'Gget_proc_info_by_ip.c',
    'mi' / 'Gget_proc_name.c',
    'mi' / 'Gput_dynamic_unwind_info.c',
    'mi' / 'Gdestroy_addr_space.c',
    'mi' / 'Gget_reg.c',
    'mi' / 'Gset_reg.c',
    'mi' / 'Gget_fpreg.c',
    'mi' / 'Gset_fpreg.c',
    'mi' / 'Gset_caching_policy.c',
    'mi' / 'Gset_cache_size.c',
  ],
}

os_sources = {
  'linux': {
    'common': ['os-linux.c', 'dl-iterate-phdr.c'],
    'x86-local': ['Los-linux.c', 'getcontext-linux.S'],
    'x86-generic': ['Gos-linux.c'],
    'x86_64-local': ['Los-linux.c'],
    'x86_64-generic': ['Gos-linux.c'],
    'arm-local': ['Los-linux.c'],
    'arm-generic': ['Gos-linux.c'],
  },
  'hpux': {
    'common': ['os-hpux.c'],
  },
  'freebsd': {
    'common': ['os-freebsd.c'],
    'x86-local': ['Los-freebsd.c', 'getcontext-freebsd.S'],
    'x86-generic': ['Gos-freebsd.c'],
    'x86_64-local': ['Los-freebsd.c'],
    'x86_64-generic': ['Gos-freebsd.c'],
    'arm-local': ['Los-freebsd.c'],
    'arm-generic': ['Gos-freebsd.c'],
  },
  'qnx': {
    'common': ['os-qnx.c', 'dl-iterate-phdr.c'],
    'arm-local': ['Los-other.c'],
    'arm-generic': ['Gos-other.c'],
  },
  'sunos': {
    'common': ['os-solaris.c'],
    'x86_64-local': ['Los-solaris.c'],
    'x86_64-generic': ['Gos-solaris.c'],
  },
}

dwarf_sources = {
  'common': [
    'global.c',
  ],
  'local': [
    'Lexpr.c',
    'Lfde.c',
    'Lparser.c',
    'Lpe.c',
    'Lfind_proc_info-lsb.c',
    'Lfind_unwind_table.c',
  ],
  'generic': [
    'Gexpr.c',
    'Gfde.c',
    'Gparser.c',
    'Gpe.c',
    'Gfind_proc_info-lsb.c',
    'Gfind_unwind_table.c',
  ],
}

arch_dependent_sources = {
  'aarch64': {
    'common': [
      'is_fpreg.c',
      'regname.c',
    ],
    'local': [
      'Lapply_reg_state.c',
      'Lreg_states_iterate.c',
      'Lcreate_addr_space.c',
      'Lget_proc_info.c',
      'Lget_save_loc.c',
      'Lglobal.c',
      'Linit.c',
      'Linit_local.c',
      'Linit_remote.c',
      'Lis_signal_frame.c',
      'Lregs.c',
      'Lresume.c',
      'Lstash_frame.c',
      'Lstep.c',
      'Ltrace.c',
      'getcontext.S',
    ],
    'generic': [
      'Gapply_reg_state.c',
      'Greg_states_iterate.c',
      'Gcreate_addr_space.c',
      'Gget_proc_info.c',
      'Gget_save_loc.c',
      'Gglobal.c',
      'Ginit.c',
      'Ginit_local.c',
      'Ginit_remote.c',
      'Gis_signal_frame.c',
      'Gregs.c',
      'Gresume.c',
      'Gstash_frame.c',
      'Gstep.c',
      'Gtrace.c',
    ],
    'setjmp': [
      'siglongjmp.S',
    ],
  },
  'arm': {
    'common': [
      'is_fpreg.c',
      'regname.c',
    ],
    'local': [
      'getcontext.S',
      'Lapply_reg_state.c',
      'Lreg_states_iterate.c',
      'Lcreate_addr_space.c',
      'Lget_proc_info.c',
      'Lget_save_loc.c',
      'Lglobal.c',
      'Linit.c',
      'Linit_local.c',
      'Linit_remote.c',
      'Lregs.c',
      'Lresume.c',
      'Lstep.c',
      'Lex_tables.c',
      'Lstash_frame.c',
      'Ltrace.c',
    ],
    'generic': [
      'Gapply_reg_state.c',
      'Greg_states_iterate.c',
      'Gcreate_addr_space.c',
      'Gget_proc_info.c',
      'Gget_save_loc.c',
      'Gglobal.c',
      'Ginit.c',
      'Ginit_local.c',
      'Ginit_remote.c',
      'Gregs.c',
      'Gresume.c',
      'Gstep.c',
      'Gex_tables.c',
      'Gstash_frame.c',
      'Gtrace.c',
    ],
    'setjmp': [
      'siglongjmp.S',
    ],
  },
  'ia64': {
    'common': [
      'regname.c',
    ],
    'local': [
      'dyn_info_list.S',
      'getcontext.S',
      'Lapply_reg_state.c',
      'Lreg_states_iterate.c',
      'Lcreate_addr_space.c',
      'Lget_proc_info.c',
      'Lget_save_loc.c',
      'Lglobal.c',
      'Linit.c',
      'Linit_local.c',
      'Linit_remote.c',
      'Linstall_cursor.S',
      'Lis_signal_frame.c',
      'Lparser.c',
      'Lrbs.c',
      'Lregs.c',
      'Lresume.c',
      'Lscript.c',
      'Lstep.c',
      'Ltables.c',
      'Lfind_unwind_table.c',
    ],
    'generic': [
      'Gapply_reg_state.c',
      'Greg_states_iterate.c',
      'Gcreate_addr_space.c',
      'Gget_proc_info.c',
      'Gget_save_loc.c',
      'Gglobal.c',
      'Ginit.c',
      'Ginit_local.c',
      'Ginit_remote.c',
      'Ginstall_cursor.S',
      'Gis_signal_frame.c',
      'Gparser.c',
      'Grbs.c',
      'Gregs.c',
      'Gresume.c',
      'Gscript.c',
      'Gstep.c',
      'Gtables.c',
      'Gfind_unwind_table.c',
    ],
    'setjmp': [
      'setjmp.S',
      'sigsetjmp.S',
      'longjmp.S',
      'siglongjmp.S',
    ],
  },
  'hppa': {
    'common': [
      'regname.c',
    ],
    'local': [
      'getcontext.S',
      'setcontext.S',
      'Lapply_reg_state.c',
      'Lreg_states_iterate.c',
      'Lcreate_addr_space.c',
      'Lget_save_loc.c',
      'Lglobal.c',
      'Linit.c',
      'Linit_local.c',
      'Linit_remote.c',
      'Lis_signal_frame.c',
      'Lget_proc_info.c',
      'Lregs.c',
      'Lresume.c',
      'Lstep.c',
    ],
    'generic': [
      'Gapply_reg_state.c',
      'Greg_states_iterate.c',
      'Gcreate_addr_space.c',
      'Gget_save_loc.c',
      'Gglobal.c',
      'Ginit.c',
      'Ginit_local.c',
      'Ginit_remote.c',
      'Gis_signal_frame.c',
      'Gget_proc_info.c',
      'Gregs.c',
      'Gresume.c',
      'Gstep.c',
    ],
    'setjmp': [
      'siglongjmp.S',
    ],
  },
  'mips': {
    'common': [
      'is_fpreg.c',
      'regname.c',
    ],
    'local': [
      'getcontext.S',
      'Lapply_reg_state.c',
      'Lreg_states_iterate.c',
      'Lcreate_addr_space.c',
      'Lget_proc_info.c',
      'Lget_save_loc.c',
      'Lglobal.c',
      'Linit.c',
      'Linit_local.c',
      'Linit_remote.c',
      'Lis_signal_frame.c',
      'Lregs.c',
      'Lresume.c',
      'Lstep.c',
    ],
    'generic': [
      'Gapply_reg_state.c',
      'Greg_states_iterate.c',
      'Gcreate_addr_space.c',
      'Gget_proc_info.c',
      'Gget_save_loc.c',
      'Gglobal.c',
      'Ginit.c',
      'Ginit_local.c',
      'Ginit_remote.c',
      'Gis_signal_frame.c',
      'Gregs.c',
      'Gresume.c',
      'Gstep.c',
    ],
    'setjmp': [
      'siglongjmp.S',
    ],
  },
  'tilegx': {
    'common': [
      'is_fpreg.c',
      'regname.c',
    ],
    'local': [
      'getcontext.S',
      'Lapply_reg_state.c',
      'Lreg_states_iterate.c',
      'Lcreate_addr_space.c',
      'Lget_proc_info.c',
      'Lget_save_loc.c',
      'Lglobal.c',
      'Linit.c',
      'Linit_local.c',
      'Linit_remote.c',
      'Lis_signal_frame.c',
      'Lregs.c',
      'Lresume.c',
      'Lstep.c',
    ],
    'generic': [
      'Gapply_reg_state.c',
      'Greg_states_iterate.c',
      'Gcreate_addr_space.c',
      'Gget_proc_info.c',
      'Gget_save_loc.c',
      'Gglobal.c',
      'Ginit.c',
      'Ginit_local.c',
      'Ginit_remote.c',
      'Gis_signal_frame.c',
      'Gregs.c',
      'Gresume.c',
      'Gstep.c',
    ],
    'setjmp': [
      'siglongjmp.S',
    ],
  },
  'riscv': {
    'common': [
      'is_fpreg.c',
      'regname.c',
    ],
    'local': [
      'getcontext.S',
      'setcontext.S',
      'Lapply_reg_state.c',
      'Lreg_states_iterate.c',
      'Lcreate_addr_space.c',
      'Lget_proc_info.c',
      'Lget_save_loc.c',
      'Lglobal.c',
      'Linit.c',
      'Linit_local.c',
      'Linit_remote.c',
      'Lis_signal_frame.c',
      'Lregs.c',
      'Lresume.c',
      'Lstep.c',
    ],
    'generic': [
      'Gapply_reg_state.c',
      'Greg_states_iterate.c',
      'Gcreate_addr_space.c',
      'Gget_proc_info.c',
      'Gget_save_loc.c',
      'Gglobal.c',
      'Ginit.c',
      'Ginit_local.c',
      'Ginit_remote.c',
      'Gis_signal_frame.c',
      'Gregs.c',
      'Gresume.c',
      'Gstep.c',
    ],
    'setjmp': [
      'siglongjmp.S',
    ],
  },
  'loongarch64': {
    'common': [
      'is_fpreg.c',
      'regname.c',
    ],
    'local': [
      'getcontext.S',
      'Lapply_reg_state.c',
      'Lreg_states_iterate.c',
      'Lcreate_addr_space.c',
      'Lget_proc_info.c',
      'Lget_save_loc.c',
      'Lglobal.c',
      'Linit.c',
      'Linit_local.c',
      'Linit_remote.c',
      'Lis_signal_frame.c',
      'Lregs.c',
      'Lresume.c',
      'Lstep.c',
    ],
    'generic': [
      'Gapply_reg_state.c',
      'Greg_states_iterate.c',
      'Gcreate_addr_space.c',
      'Gget_proc_info.c',
      'Gget_save_loc.c',
      'Gglobal.c',
      'Ginit.c',
      'Ginit_local.c',
      'Ginit_remote.c',
      'Gis_signal_frame.c',
      'Gregs.c',
      'Gresume.c',
      'Gstep.c',
    ],
    'setjmp': [
      'siglongjmp.S',
    ],
  },
  'x86': {
    'common': [
      'is_fpreg.c',
      'regname.c',
    ],
    'local': [
      'Lapply_reg_state.c',
      'Lreg_states_iterate.c',
      'Lcreate_addr_space.c',
      'Lget_save_loc.c',
      'Lglobal.c',
      'Linit.c',
      'Linit_local.c',
      'Linit_remote.c',
      'Lget_proc_info.c',
      'Lregs.c',
      'Lresume.c',
      'Lstep.c',
    ],
    'generic': [
      'Gapply_reg_state.c',
      'Greg_states_iterate.c',
      'Gcreate_addr_space.c',
      'Gget_save_loc.c',
      'Gglobal.c',
      'Ginit.c',
      'Ginit_local.c',
      'Ginit_remote.c',
      'Gget_proc_info.c',
      'Gregs.c',
      'Gresume.c',
      'Gstep.c',
    ],
    'setjmp': [
      'longjmp.S',
      'siglongjmp.S',
    ],
  },
  'x86_64': {
    'common': [
      'is_fpreg.c',
      'regname.c',
    ],
    'local': [
      'setcontext.S',
      'Lapply_reg_state.c',
      'Lreg_states_iterate.c',
      'Lcreate_addr_space.c',
      'Lget_save_loc.c',
      'Lglobal.c',
      'Linit.c',
      'Linit_local.c',
      'Linit_remote.c',
      'Lget_proc_info.c',
      'Lregs.c',
      'Lresume.c',
      'Lstash_frame.c',
      'Lstep.c',
      'Ltrace.c',
      'getcontext.S',
    ],
    'generic': [
      'Gapply_reg_state.c',
      'Greg_states_iterate.c',
      'Gcreate_addr_space.c',
      'Gget_save_loc.c',
      'Gglobal.c',
      'Ginit.c',
      'Ginit_local.c',
      'Ginit_remote.c',
      'Gget_proc_info.c',
      'Gregs.c',
      'Gresume.c',
      'Gstash_frame.c',
      'Gstep.c',
      'Gtrace.c',
    ],
    'setjmp': [
      'longjmp.S',
      'siglongjmp.S',
    ],
  },
  'ppc': {
    'common': [],
    'local': [
      'Lget_proc_info.c',
      'Lget_save_loc.c',
      'Linit_local.c',
      'Linit_remote.c',
      'Lis_signal_frame.c',
    ],
    'generic': [
      'Gget_proc_info.c',
      'Gget_save_loc.c',
      'Ginit_local.c',
      'Ginit_remote.c',
      'Gis_signal_frame.c',
    ],
    'setjmp': [
      'longjmp.S',
      'siglongjmp.S',
    ],
  },
  'ppc32': {
    'common': [
      'is_fpreg.c',
      'regname.c',
      'get_func_addr.c',
    ],
    'local': [
      'Lapply_reg_state.c',
      'Lreg_states_iterate.c',
      'Lcreate_addr_space.c',
      'Lglobal.c',
      'Linit.c',
      'Lregs.c',
      'Lresume.c',
      'Lstep.c',
    ],
    'generic': [
      'Gapply_reg_state.c',
      'Greg_states_iterate.c',
      'Gcreate_addr_space.c',
      'Gglobal.c',
      'Ginit.c',
      'Gregs.c',
      'Gresume.c',
      'Gstep.c',
    ],
  },
  'ppc64': {
    'common': [
      'is_fpreg.c',
      'regname.c',
      'get_func_addr.c',
    ],
    'local': [
      'Lapply_reg_state.c',
      'Lreg_states_iterate.c',
      'Lcreate_addr_space.c',
      'Lglobal.c',
      'Linit.c',
      'Lregs.c',
      'Lresume.c',
      'Lstep.c',
    ],
    'generic': [
      'Gapply_reg_state.c',
      'Greg_states_iterate.c',
      'Gcreate_addr_space.c',
      'Gglobal.c',
      'Ginit.c',
      'Gregs.c',
      'Gresume.c',
      'Gstep.c',
    ],
  },
  'sh': {
    'common': [
      'is_fpreg.c',
      'regname.c',
    ],
    'local': [
      'Lapply_reg_state.c',
      'Lreg_states_iterate.c',
      'Lcreate_addr_space.c',
      'Lget_proc_info.c',
      'Lget_save_loc.c',
      'Lglobal.c',
      'Linit.c',
      'Linit_local.c',
      'Linit_remote.c',
      'Lis_signal_frame.c',
      'Lregs.c',
      'Lresume.c',
      'Lstep.c',
    ],
    'generic': [
      'Gapply_reg_state.c',
      'Greg_states_iterate.c',
      'Gcreate_addr_space.c',
      'Gget_proc_info.c',
      'Gget_save_loc.c',
      'Gglobal.c',
      'Ginit.c',
      'Ginit_local.c',
      'Ginit_remote.c',
      'Gis_signal_frame.c',
      'Gregs.c',
      'Gresume.c',
      'Gstep.c',
    ],
    'setjmp': [
      'siglongjmp.S',
    ],
  },
  's390x': {
    'common': [
      'is_fpreg.c',
      'regname.c',
    ],
    'local': [
      'Lapply_reg_state.c',
      'Lreg_states_iterate.c',
      'Lcreate_addr_space.c',
      'Lget_save_loc.c',
      'Lglobal.c',
      'Linit.c',
      'Linit_local.c',
      'Linit_remote.c',
      'Lget_proc_info.c',
      'Lregs.c',
      'Lresume.c',
      'Lis_signal_frame.c',
      'Lstep.c',
      'getcontext.S',
      'setcontext.S',
    ],
    'generic': [
      'Gapply_reg_state.c',
      'Greg_states_iterate.c',
      'Gcreate_addr_space.c',
      'Gget_save_loc.c',
      'Gglobal.c',
      'Ginit.c',
      'Ginit_local.c',
      'Ginit_remote.c',
      'Gget_proc_info.c',
      'Gregs.c',
      'Gresume.c',
      'Gis_signal_frame.c',
      'Gstep.c',
    ],
  },
}

archs_to_include = []
if target_arch.startswith('ppc')
  archs_to_include += 'ppc'
endif
archs_to_include += target_arch

if not remote_only
  local_sources = []

  local_sources += arch_independent_sources['common']
  local_sources += arch_independent_sources['local_nounwind']

  if enable_cxx_exceptions
    local_sources += arch_independent_sources['local_unwind']
    local_sources += arch_independent_sources.get('local_unwind:' + target_os, [])
  endif

  oss = os_sources[target_os]
  local_sources += oss['common']
  foreach source : oss.get(target_arch + '-local', [])
    local_sources += target_arch / source
  endforeach

  if use_dwarf
    foreach source : dwarf_sources['common'] + dwarf_sources['local']
      local_sources += 'dwarf' / source
    endforeach
  endif

  local_sources += 'elf' + elf_helper_width + '.c'

  foreach arch : archs_to_include
    ads = arch_dependent_sources[arch]
    foreach source : ads['common'] + ads['local']
      local_sources += arch / source
    endforeach
  endforeach

  libunwind = library('unwind', local_sources,
    version: unwind_version,
    include_directories: libunwind_internal_incdirs,
    dependencies: libunwind_deps,
    link_args: ['-nostdlib', '-lc'] + libcrts,
    install: true,
  )
  libunwind_dep = declare_dependency(
    link_with: libunwind,
    include_directories: libunwind_public_incdirs,
  )

  pkg = import('pkgconfig')
  pkg.generate(libunwind,
    name: 'libunwind',
    description: 'libunwind base library',
  )
else
  libunwind_dep = disabler()
endif

meson.override_dependency('libunwind', libunwind_dep)

if get_option('generic_library').allowed()
  generic_sources = []

  generic_sources += arch_independent_sources['common']
  generic_sources += arch_independent_sources['generic']

  oss = os_sources[target_os]
  generic_sources += oss['common']
  foreach source : oss.get(target_arch + '-generic', [])
    generic_sources += target_arch / source
  endforeach

  if use_dwarf
    foreach source : dwarf_sources['common'] + dwarf_sources['generic']
      generic_sources += 'dwarf' / source
    endforeach
  endif

  generic_sources += 'elf' + elf_helper_width + '.c'

  foreach arch : archs_to_include
    ads = arch_dependent_sources[arch]
    foreach source : ads['common'] + ads['generic']
      generic_sources += target_arch / source
    endforeach
  endforeach

  generic_deps = []
  generic_deps += libunwind_deps
  if not remote_only
    generic_deps += libunwind_dep
  endif

  libunwind_generic = library('unwind-' + target_arch, generic_sources,
    version: unwind_version,
    include_directories: libunwind_internal_incdirs,
    dependencies: generic_deps,
    install: true,
  )
  libunwind_generic_dep = declare_dependency(
    link_with: libunwind_generic,
    include_directories: libunwind_public_incdirs,
  )

  pkg = import('pkgconfig')
  pkg.generate(libunwind_generic,
    name: 'libunwind-generic',
    description: 'libunwind generic library',
  )
else
  libunwind_generic_dep = disabler()
endif

meson.override_dependency('libunwind-generic', libunwind_generic_dep)

setjmp_backend_sources = []
foreach arch : archs_to_include
  ads = arch_dependent_sources[arch]
  foreach source : ads.get('setjmp', [])
    setjmp_backend_sources += files(arch / source)
  endforeach
endforeach

if enable_coredump
  subdir('coredump')
endif
if enable_ptrace
  subdir('ptrace')
endif
if enable_setjmp
  subdir('setjmp')
endif
