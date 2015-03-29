#define UNW_LOCAL_ONLY
#include <libunwind.h>
#include <stdio.h>

static void
print_backtrace (void)
{
  unw_context_t context;
  unw_cursor_t cursor;
  int i;

  printf ("* grabbing context\n");
  unw_getcontext (&context);

  printf ("* initializing\n");
  unw_init_local (&cursor, &context);

  printf ("* stepping into loop\n");
  for (i = 0; unw_step (&cursor) > 0; i++)
  {
    unw_word_t pc;

    unw_get_reg (&cursor, UNW_REG_IP, &pc);
    printf ("backtrace[%d] = %d\n", i, pc);
  }

  printf ("* done\n");
}

static void
snake (void)
{
  print_backtrace ();
}

static void
mushroom (void)
{
  snake ();
}

static void
badger (void)
{
  mushroom ();
}

#define xstr(s) str (s)
#define str(s) #s

#define PRINT_REG_OFFSET(R, r) \
  printf ("#define QNX_CR_" xstr(R) "_OFF\t\t0x%02x\n", __builtin_offsetof (X86_CPU_REGISTERS, r))

static void
dump_offsets (void)
{
  printf ("#define QNX_UC_MCONTEXT_CPU_OFF\t0x%02x\n", __builtin_offsetof (ucontext_t, uc_mcontext) + __builtin_offsetof (mcontext_t, cpu));
  printf ("#define QNX_UC_MCONTEXT_FPU_OFF\t0x%02x\n", __builtin_offsetof (ucontext_t, uc_mcontext) + __builtin_offsetof (mcontext_t, fpu));
  PRINT_REG_OFFSET (EDI, edi);
  PRINT_REG_OFFSET (ESI, esi);
  PRINT_REG_OFFSET (EBP, ebp);
  PRINT_REG_OFFSET (EXX, exx);
  PRINT_REG_OFFSET (EBX, ebx);
  PRINT_REG_OFFSET (EDX, edx);
  PRINT_REG_OFFSET (ECX, ecx);
  PRINT_REG_OFFSET (EAX, eax);
  PRINT_REG_OFFSET (EIP, eip);
  PRINT_REG_OFFSET (CS, cs);
  PRINT_REG_OFFSET (EFL, efl);
  PRINT_REG_OFFSET (ESP, esp);
  PRINT_REG_OFFSET (SS, ss);
}

int
main (int argc, char * argv[])
{
  dump_offsets ();
  badger ();
  return 0;
}
