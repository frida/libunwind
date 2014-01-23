/* libunwind - a platform-independent unwind library
   Copyright (C) 2014 The Android Open Source Project

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

#include "libunwind_i.h"

PROTECTED void
unw_map_set (unw_addr_space_t as, unw_map_cursor_t *map_cursor)
{
  if (map_cursor != NULL)
    as->map_list = map_cursor->map_list;
  else
    as->map_list = NULL;
}

PROTECTED int
unw_map_cursor_create (unw_map_cursor_t *map_cursor, pid_t pid)
{
  map_cursor->map_list = maps_create_list (pid);

  return map_cursor->map_list == NULL;
}

PROTECTED void
unw_map_cursor_destroy (unw_map_cursor_t *map_cursor)
{
  maps_destroy_list (map_cursor->map_list);
}

PROTECTED void
unw_map_cursor_reset (unw_map_cursor_t *map_cursor)
{
  map_cursor->cur_map = map_cursor->map_list;
}

PROTECTED int
unw_map_cursor_get (unw_map_cursor_t *map_cursor, unw_map_t *unw_map)
{
  struct map_info *map_info = map_cursor->cur_map;

  if (map_info == NULL)
    return 0;

  unw_map->start = map_info->start;
  unw_map->end = map_info->end;
  unw_map->flags = map_info->flags;
  unw_map->path = map_info->path;

  map_cursor->cur_map = map_info->next;

  return 1;
}
