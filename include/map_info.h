/* libunwind - a platform-independent unwind library
   Copyright (C) 2013 The Android Open Source Project

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

#ifndef map_info_h
#define map_info_h

struct map_info
  {
    uintptr_t start;
    uintptr_t end;
    uintptr_t offset;
    int flags;
    char *path;
    struct elf_image ei;

    struct map_info *next;
  };

int maps_is_readable(struct map_info *map_list, unw_word_t addr);

int maps_is_writable(struct map_info *map_list, unw_word_t addr);

struct map_info *maps_create_list(pid_t pid);

void maps_destroy_list(struct map_info *map_info);

#endif /* map_info_h */
