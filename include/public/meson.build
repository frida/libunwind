public_headers = []

libunwind_h = configure_file(
  input: libunwind_h_in,
  output: 'libunwind.h',
  configuration: cdata,
)

if not remote_only
  public_headers += libunwind_h
  if get_option('unwind_header')
    public_headers += unwind_h
  endif
endif

public_headers += libunwind_arch_h
public_headers += libunwind_dynamic_h
public_headers += configure_file(
  input: libunwind_common_h_in,
  output: 'libunwind-common.h',
  configuration: cdata,
)

if enable_coredump
  public_headers += coredump_h
endif

if enable_ptrace
  public_headers += ptrace_h
endif

install_headers(public_headers)
