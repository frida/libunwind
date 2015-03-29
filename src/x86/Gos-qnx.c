/* libunwind - a platform-independent unwind library
   Copyright (C) 2015 Ole André Vadla Ravnås <oleavr@gmail.com>

This file is part of libunwind.

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.  */

#include <stdio.h>

#include "unwind_i.h"

PROTECTED int
unw_is_signal_frame (unw_cursor_t *cursor)
{
  /* Not supported yet */
  return 0;
}

PROTECTED int
unw_handle_signal_frame (unw_cursor_t *cursor)
{
  /* Not supported yet */
  printf ("%s: implement me\n", __FUNCTION__);
  return 0;
}

HIDDEN dwarf_loc_t
x86_get_scratch_loc (struct cursor *c, unw_regnum_t reg)
{
  /* Not supported yet */
  printf ("%s: implement me\n", __FUNCTION__);
  return DWARF_NULL_LOC;
}

#ifndef UNW_REMOTE_ONLY
HIDDEN void *
x86_r_uc_addr (ucontext_t *uc, int reg)
{
  X86_CPU_REGISTERS *cr = &uc->uc_mcontext.cpu;
  void *addr;

  switch (reg)
    {
    case UNW_X86_EAX: addr = &cr->eax; break;
    case UNW_X86_EBX: addr = &cr->ebx; break;
    case UNW_X86_ECX: addr = &cr->ecx; break;
    case UNW_X86_EDX: addr = &cr->edx; break;
    case UNW_X86_ESI: addr = &cr->esi; break;
    case UNW_X86_EDI: addr = &cr->edi; break;
    case UNW_X86_EBP: addr = &cr->ebp; break;
    case UNW_X86_EIP: addr = &cr->eip; break;
    case UNW_X86_ESP: addr = &cr->esp; break;
    case UNW_X86_CS:  addr = &cr->cs; break;
    case UNW_X86_EFLAGS: addr = &cr->efl; break;
    case UNW_X86_SS:  addr = &cr->ss; break;

    default:
      addr = NULL;
    }

  return addr;
}

HIDDEN int
x86_local_resume (unw_addr_space_t as, unw_cursor_t *cursor, void *arg)
{
  /* Not supported yet */
  printf ("%s: implement me\n", __FUNCTION__);
  return -UNW_EINVAL;
}
#endif
