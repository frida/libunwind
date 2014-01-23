/* libunwind - a platform-independent unwind library
   Copyright (C) 2003-2005 Hewlett-Packard Co
	Contributed by David Mosberger-Tang <davidm@hpl.hp.com>

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

#include <limits.h>
#include <stdio.h>

#include "libunwind_i.h"
#include "map_info.h"
#include "os-linux.h"

/* ANDROID support update. */
struct map_info *
maps_create_list(pid_t pid)
{
  struct map_iterator mi;
  unsigned long start, end, offset, flags;
  struct map_info *map_list = NULL;
  struct map_info *cur_map;

  if (maps_init (&mi, pid) < 0)
    return NULL;

  while (maps_next (&mi, &start, &end, &offset, &flags))
    {
      cur_map = (struct map_info *)malloc(sizeof(struct map_info));
      if (cur_map == NULL)
        break;
      cur_map->next = map_list;
      cur_map->start = start;
      cur_map->end = end;
      cur_map->offset = offset;
      cur_map->flags = flags;
      cur_map->path = strdup(mi.path);
      cur_map->ei.size = 0;
      cur_map->ei.image = NULL;

      map_list = cur_map;
    }

  maps_close (&mi);

  return map_list;
}

void
maps_destroy_list(struct map_info *map_info)
{
  struct map_info *map;
  while (map_info)
    {
      map = map_info;
      map_info = map->next;
      if (map->ei.image != MAP_FAILED && map->ei.image != NULL)
        munmap(map->ei.image, map->ei.size);
      if (map->path)
        free(map->path);
      free(map);
    }
}

static struct map_info *
get_map(struct map_info *map_list, unw_word_t addr)
{
  while (map_list)
    {
      if (addr >= map_list->start && addr < map_list->end)
        return map_list;
      map_list = map_list->next;
    }
  return NULL;
}

int maps_is_readable(struct map_info *map_list, unw_word_t addr)
{
  /* If there is no map, assume everything is okay. */
  if (map_list == NULL)
    return 1;
  struct map_info *map = get_map(map_list, addr);
  if (map != NULL)
    return map->flags & PROT_READ;
  return 0;
}

int maps_is_writable(struct map_info *map_list, unw_word_t addr)
{
  /* If there is no map, assume everything is okay. */
  if (map_list == NULL)
    return 1;
  struct map_info *map = get_map(map_list, addr);
  if (map != NULL)
    return map->flags & PROT_WRITE;
  return 0;
}
/* End of ANDROID update. */

PROTECTED struct map_info*
tdep_get_elf_image(unw_addr_space_t as, pid_t pid, unw_word_t ip)
{
  /* ANDROID support update. */
  struct map_info *map;

  if (as->map_list == NULL)
    as->map_list = maps_create_list(pid);

  map = as->map_list;
  while (map)
    {
      if (ip >= map->start && ip < map->end)
        break;
      map = map->next;
    }
  if (!map)
    return NULL;

  if (map->ei.image == NULL)
    {
      int ret = elf_map_image(&map->ei, map->path);
      if (ret < 0)
        {
          map->ei.image = NULL;
          return NULL;
        }
    }
  /* End of ANDROID update. */
  return map;
}
