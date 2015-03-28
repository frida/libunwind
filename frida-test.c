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

int
main (int argc, char * argv[])
{
  badger ();
  return 0;
}
