/* libunwind - a platform-independent unwind library
   Copyright (C) 2009 Google, Inc
	Contributed by Paul Pluzhnikov <ppluzhnikov@google.com>
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

#include "offsets.h"

/*  int _Ux86_getcontext (ucontext_t *ucp)

  Saves the machine context in UCP necessary for libunwind.
  Unlike the libc implementation, we don't save the signal mask
  and hence avoid the cost of a system call per unwind.

*/

	.global _Ux86_getcontext
	.type _Ux86_getcontext, @function
_Ux86_getcontext:
	.cfi_startproc
	mov	4(%esp),%eax  /* ucontext_t* */

	/* EAX is not preserved. */
	movl	$0, (QNX_UC_MCONTEXT_CPU_OFF+QNX_CR_EAX_OFF)(%eax)

	movl	%ebx, (QNX_UC_MCONTEXT_CPU_OFF+QNX_CR_EBX_OFF)(%eax)
	movl	%ecx, (QNX_UC_MCONTEXT_CPU_OFF+QNX_CR_ECX_OFF)(%eax)
	movl	%edx, (QNX_UC_MCONTEXT_CPU_OFF+QNX_CR_EDX_OFF)(%eax)
	movl	%edi, (QNX_UC_MCONTEXT_CPU_OFF+QNX_CR_EDI_OFF)(%eax)
	movl	%esi, (QNX_UC_MCONTEXT_CPU_OFF+QNX_CR_ESI_OFF)(%eax)
	movl	%ebp, (QNX_UC_MCONTEXT_CPU_OFF+QNX_CR_EBP_OFF)(%eax)

	movl	(%esp), %ecx
	movl	%ecx, (QNX_UC_MCONTEXT_CPU_OFF+QNX_CR_EIP_OFF)(%eax)

	leal	4(%esp), %ecx		/* Exclude the return address.  */
	movl	%ecx, (QNX_UC_MCONTEXT_CPU_OFF+QNX_CR_ESP_OFF)(%eax)

	leal	QNX_UC_MCONTEXT_FPU_OFF(%eax), %ecx
	fnstenv	(%ecx)
	fldenv	(%ecx)

	xor	%eax, %eax
	ret
	.cfi_endproc
	.size	_Ux86_getcontext, . - _Ux86_getcontext

	/* We do not need executable stack.  */
	.section        .note.GNU-stack,"",@progbits
