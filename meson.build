project('libunwind', 'c',
  version: '1.6-rc1',
  default_options: [
    'c_std=gnu99',
  ],
)

os_from_meson = {
  'android': 'linux',
}

arch_from_meson = {
  'parisc': 'hppa',
  'mips64': 'mips',
  'riscv32': 'riscv',
  'riscv64': 'riscv',
  'ppc': 'ppc32',
  'sh4': 'sh',
}

host_os = host_machine.system()
host_os = os_from_meson.get(host_os, host_os)
host_arch = host_machine.cpu_family()
host_arch = arch_from_meson.get(host_arch, host_arch)

target_os = target_machine.system()
target_os = os_from_meson.get(target_os, target_os)
target_arch = target_machine.cpu_family()
target_arch = arch_from_meson.get(target_arch, target_arch)

lt_cur = 8
lt_rev = 1
lt_age = 0

if host_os in ['hpux', 'netbsd', 'openbsd', 'sunos']
  unwind_version = '@0@.@1@'.format(lt_cur, lt_rev)
  default_version = '0.0'
elif host_os == 'qnx'
  unwind_version = lt_cur.to_string()
  default_version = '0'
else
  unwind_version = '@0@.@1@.@2@'.format(lt_cur - lt_age, lt_age, lt_rev)
  default_version = '0.0.0'
endif

coredump_version = default_version
ptrace_version = default_version
setjmp_version = default_version

add_project_arguments(
  '-DHAVE_CONFIG_H',
  '-D_GNU_SOURCE',
  language: 'c')

cc = meson.get_compiler('c')

# Suppress all compiler warnings when we're a subproject
if meson.is_subproject()
  if cc.get_argument_syntax() == 'msvc'
    add_project_arguments('/w', language : 'c')
  else
    add_project_arguments('-w', language : 'c')
  endif
endif

cdata = configuration_data()

cdata.set('arch', target_arch)

project_name = meson.project_name()
project_version = meson.project_version()
cdata.set_quoted('PACKAGE', project_name)
cdata.set_quoted('PACKAGE_NAME', project_name)
cdata.set_quoted('PACKAGE_TARNAME', project_name)
cdata.set_quoted('PACKAGE_VERSION', project_version)
cdata.set('PKG_MAJOR', 1)
cdata.set('PKG_MINOR', 6)
cdata.set('PKG_EXTRA', '-rc1')
cdata.set_quoted('VERSION', project_version)
cdata.set_quoted('PACKAGE_STRING', project_name + ' ' + project_version)
cdata.set_quoted('PACKAGE_URL', '')
cdata.set_quoted('PACKAGE_BUGREPORT', 'libunwind-devel@nongnu.org')

cdata.set('STDC_HEADERS', 1)

system_headers = [
  'asm/ptrace.h',
  'asm/ptrace_offsets.h',
  'byteswap.h',
  'dlfcn.h',
  'elf.h',
  'endian.h',
  'execinfo.h',
  'ia64intrin.h',
  'inttypes.h',
  'link.h',
  'memory.h',
  'signal.h',
  'stdalign.h',
  'stdatomic.h',
  'stdint.h',
  'stdlib.h',
  'string.h',
  'strings.h',
  'sys/elf.h',
  'sys/endian.h',
  'sys/link.h',
  'sys/param.h',
  'sys/procfs.h',
  'sys/ptrace.h',
  'sys/stat.h',
  'sys/syscall.h',
  'sys/types.h',
  'sys/uc_access.h',
  'unistd.h',
]
foreach h : system_headers
  if cc.check_header(h)
    cdata.set('HAVE_' + h.underscorify().to_upper(), 1)
  endif
endforeach

cdata.set('SIZEOF_OFF_T', cc.sizeof('off_t'))

if cc.has_member('struct dl_phdr_info', 'dlpi_subs',
                 args: ['-D_GNU_SOURCE=1'],
                 prefix: '#include <link.h>')
  cdata.set('HAVE_STRUCT_DL_PHDR_INFO_DLPI_SUBS', 1)
endif

prstatus_types = [
  'struct elf_prstatus',
  'struct prstatus',
]
prstatus_prefix = '''#if @0@
                     # include <sys/procfs.h>
                     #endif'''.format(cdata.has('HAVE_SYS_PROCFS_H').to_int())
foreach t : prstatus_types
  if cc.has_type(t, prefix: prstatus_prefix)
    cdata.set('HAVE_' + t.underscorify().to_upper(), 1)
  endif
endforeach

ptrace_decls = [
  'PTRACE_POKEUSER',
  'PTRACE_POKEDATA',
  'PTRACE_SETREGSET',
  'PTRACE_TRACEME',
  'PTRACE_CONT',
  'PTRACE_SINGLESTEP',
  'PTRACE_SYSCALL',
  'PT_IO',
  'PT_GETREGS',
  'PT_GETFPREGS',
  'PT_CONTINUE',
  'PT_TRACE_ME',
  'PT_STEP',
  'PT_SYSCALL',
]
ptrace_prefix = '''#if @0@
                   # include <sys/types.h>
                   #endif'''.format(cdata.has('HAVE_SYS_TYPES_H').to_int())
foreach d : ptrace_decls
  cdata.set10('HAVE_DECL_' + d, cc.has_header_symbol('sys/ptrace.h', d, prefix: ptrace_prefix))
endforeach

library_funcs = [
  'dl_iterate_phdr',
  'dl_phdr_removals_counter',
  'dlmodinfo',
  'getunwind',
  'mincore',
  'pipe2',
  'ttrace',
]
foreach f : library_funcs
  if cc.has_function(f)
    cdata.set('HAVE_' + f.to_upper(), 1)
  endif
endforeach

archs_where_coredump_works_well = [
  'aarch64', 'arm', 'mips', 'sh', 'x86', 'x86_64',
  'tilegx', 'riscv', 'loongarch64'
]
enable_coredump = get_option('coredump_library') \
    .disable_auto_if(host_arch not in archs_where_coredump_works_well) \
    .allowed()
message('Should build libunwind-coredump :', enable_coredump.to_string('YES', 'NO'))

enable_ptrace = get_option('ptrace_library') \
    .disable_auto_if(not cdata.has('HAVE_SYS_PTRACE_H')) \
    .allowed()
message('Should build libunwind-ptrace :', enable_ptrace.to_string('YES', 'NO'))

enable_setjmp = get_option('setjmp_library') \
    .disable_auto_if(target_arch != host_arch) \
    .allowed()
message('Should build libunwind-setjmp :', enable_setjmp.to_string('YES', 'NO'))

if get_option('weak_backtrace')
  cdata.set('CONFIG_WEAK_BACKTRACE', 1)
endif

if target_arch in ['arm', 'hppa', 'ppc32', 'x86', 'sh']
  elf_helper_width = '32'
elif target_arch in ['aarch64', 'ia64', 'ppc64', 'x86_64', 's390x', 'tilegx']
  elf_helper_width = '64'
elif target_arch in ['mips', 'riscv', 'loongarch64']
  elf_helper_width = 'xx'
else
  error('Unknown ELF target:', target_arch)
endif
message('ELF helper width :', elf_helper_width)

use_dwarf = target_arch != 'ia64'
message('Include DWARF support :', use_dwarf.to_string('YES', 'NO'))

remote_only = target_arch != host_arch
message('Restrict build to remote support :', remote_only.to_string('YES', 'NO'))
if remote_only
  add_project_arguments('-DUNW_REMOTE_ONLY', language: 'c')
endif

ndebug = get_option('b_ndebug')
optimize_for_prod = ndebug == 'true' or (ndebug == 'if-release' and not get_option('debug'))
enable_debug = get_option('unwind_debug').disable_auto_if(optimize_for_prod).allowed()
message('Debug support :', enable_debug.to_string('YES', 'NO'))
if enable_debug
  add_project_arguments('-DDEBUG', language: 'c')
endif

archs_where_cxx_eh_does_not_work_well = [
  'x86',
  'x86_64',
  'aarch64',
  'arm',
  'mips',
  'mips64',
  'tilegx',
  's390x',
  'loongarch64',
]
enable_cxx_exceptions = get_option('cxx_exceptions') \
    .disable_auto_if(target_arch in archs_where_cxx_eh_does_not_work_well) \
    .allowed()
message('C++ exception support :', enable_cxx_exceptions.to_string('YES', 'NO'))

enable_debug_frame = get_option('debug_frame') \
    .disable_auto_if(target_arch not in ['arm', 'aarch64']) \
    .allowed()
if remote_only
  enable_debug_frame = false
endif
message('Load .debug_frame sections :', enable_debug_frame.to_string('YES', 'NO'))
if enable_debug_frame
  cdata.set('CONFIG_DEBUG_FRAME', '/**/')
endif

block_signals = get_option('block_signals')
message('Block signals during mutex ops :', block_signals.to_string('YES', 'NO'))
if block_signals
  cdata.set('CONFIG_BLOCK_SIGNALS', '/**/')
endif

conservative_checks = get_option('conservative_checks')
message('Validate memory addresses before use :', conservative_checks.to_string('YES', 'NO'))
if conservative_checks
  cdata.set('CONSERVATIVE_CHECKS', 1)
endif

msabi_support = get_option('msabi_support')
message('Microsoft ABI extensions support :', msabi_support.to_string('YES', 'NO'))
if msabi_support
  cdata.set('CONFIG_MSABI_SUPPORT', '/**/')
endif

lzma_dep = dependency('liblzma',
                      required: get_option('minidebuginfo'),
                      not_found_message: 'Disabling support for LZMA-compressed symbol tables')
if lzma_dep.found()
  cdata.set('HAVE_LZMA', 1)
endif

zlib_dep = dependency('zlib',
                      required: get_option('zlibdebuginfo'),
                      not_found_message: 'Disabling support for ZLIB-compressed symbol tables')
if zlib_dep.found()
  cdata.set('HAVE_ZLIB', 1)
endif

per_thread_cache = get_option('per_thread_cache')
message('Enable UNW_CACHE_PER_THREAD :', per_thread_cache.to_string('YES', 'NO'))
if per_thread_cache
  cdata.set('HAVE___CACHE_PER_THREAD', 1)
endif

libcrts = []
if cc.get_id() == 'gcc'
  libcrts += '-lgcc_s'
endif

if cc.has_function('__builtin___clear_cache')
  cdata.set('HAVE__BUILTIN___CLEAR_CACHE', 1)
endif

if cc.has_function('__builtin_unreachable')
  cdata.set('HAVE__BUILTIN_UNREACHABLE', 1)
endif

libunwind_public_incdirs = include_directories('include' / 'public')
libunwind_internal_incdirs = include_directories(
  'include' / 'public',
  'include',
  'include' / 'tdep-' + target_arch,
  'include' / 'tdep',
  'src',
)
libunwind_deps = [lzma_dep, zlib_dep]

subdir('include')
subdir('src')
