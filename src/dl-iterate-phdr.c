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

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#if !defined(HAVE_DL_ITERATE_PHDR)

#if defined(__ANDROID__)

#include <dlfcn.h>
#include <link.h>

#include "libunwind_i.h"
#include "os-linux.h"

#ifndef IS_ELF
/* Copied from NDK header. */
#define IS_ELF(ehdr) ((ehdr).e_ident[EI_MAG0] == ELFMAG0 && \
                      (ehdr).e_ident[EI_MAG1] == ELFMAG1 && \
                      (ehdr).e_ident[EI_MAG2] == ELFMAG2 && \
                      (ehdr).e_ident[EI_MAG3] == ELFMAG3)
#endif

typedef int (*unw_iterate_phdr_impl) (int (*callback) (
                                        struct dl_phdr_info *info,
                                        size_t size, void *data),
                                      void *data);

HIDDEN int
dl_iterate_phdr (int (*callback) (struct dl_phdr_info *info, size_t size, void *data),
                 void *data)
{
  static int initialized = 0;
  static unw_iterate_phdr_impl libc_impl;
  int rc = 0;
  struct map_iterator mi;
  unsigned long start, end, offset, flags;

  if (!initialized)
    {
      libc_impl = dlsym (RTLD_NEXT, "dl_iterate_phdr");
      initialized = 1;
    }

  if (libc_impl != NULL)
    return libc_impl (callback, data);

  if (maps_init (&mi, getpid()) < 0)
    return -1;

  while (rc == 0 && maps_next (&mi, &start, &end, &offset, &flags))
    {
      Elf_W(Ehdr) *ehdr = (Elf_W(Ehdr) *) start;
      Dl_info canonical_info;

      if (mi.path[0] != '\0' && (flags & PROT_READ) != 0 && IS_ELF (*ehdr)
          && dladdr (ehdr, &canonical_info) != 0
          && ehdr == canonical_info.dli_fbase)
        {
          struct dl_phdr_info info;
          Elf_W(Phdr) *phdr = (Elf_W(Phdr) *) (start + ehdr->e_phoff);

          info.dlpi_addr = start;
          info.dlpi_name = canonical_info.dli_fname;
          info.dlpi_phdr = phdr;
          info.dlpi_phnum = ehdr->e_phnum;

          rc = callback (&info, sizeof (info), data);
        }
    }

  maps_close (&mi);

  return rc;
}

#elif defined(__PROSPERO__)

#include <link.h>
#include <string.h>
#include <sys/mman.h>

#include "libunwind_i.h"

#define UNW_PROSPERO_MAX_MODULES 256
#define UNW_PROSPERO_FIRST_JAILED_MODULE 0x2000
#define UNW_PROSPERO_MAX_JAILED_MODULES 32
#define UNW_PROSPERO_MAX_MODULE_SEGMENTS 4

typedef struct unw_prospero_handle_range unw_prospero_handle_range_t;
typedef struct unw_prospero_segment_info unw_prospero_segment_info_t;
typedef struct unw_prospero_module_info unw_prospero_module_info_t;

struct unw_prospero_handle_range
  {
    int first;
    int end;
  };

struct unw_prospero_segment_info
  {
    void *base_address;
    uint32_t size;
    int32_t prot;
  };

struct unw_prospero_module_info
  {
    size_t size;
    char name[256];
    unw_prospero_segment_info_t segments[UNW_PROSPERO_MAX_MODULE_SEGMENTS];
    uint32_t num_segments;
    uint8_t fingerprint[20];
  };

extern int sceKernelGetModuleInfo (int handle, unw_prospero_module_info_t *info);

static int unw_prospero_describe_module (const unw_prospero_module_info_t *mi,
                                         Elf_W(Phdr) *phdrs);

static const unw_prospero_handle_range_t unw_prospero_handle_ranges[] =
  {
    { 0, UNW_PROSPERO_MAX_MODULES },
    { UNW_PROSPERO_FIRST_JAILED_MODULE,
      UNW_PROSPERO_FIRST_JAILED_MODULE + UNW_PROSPERO_MAX_JAILED_MODULES },
  };

HIDDEN int
dl_iterate_phdr (int (*callback) (struct dl_phdr_info *info, size_t size,
                                  void *data),
                 void *data)
{
  size_t i;
  int rc = 0;

  for (i = 0; rc == 0 && i < ARRAY_SIZE (unw_prospero_handle_ranges); i++)
    {
      const unw_prospero_handle_range_t *handles =
        &unw_prospero_handle_ranges[i];
      int handle;

      for (handle = handles->first; rc == 0 && handle != handles->end; handle++)
        {
          unw_prospero_module_info_t mi;
          Elf_W(Phdr) phdrs[UNW_PROSPERO_MAX_MODULE_SEGMENTS + 1];
          struct dl_phdr_info info;

          memset (&mi, 0, sizeof (mi));
          mi.size = sizeof (mi);
          if (sceKernelGetModuleInfo (handle, &mi) != 0)
            continue;

          memset (&info, 0, sizeof (info));
          info.dlpi_addr = 0;
          info.dlpi_name = mi.name;
          info.dlpi_phdr = phdrs;
          info.dlpi_phnum = unw_prospero_describe_module (&mi, phdrs);

          rc = callback (&info, sizeof (info), data);
        }
    }

  return rc;
}

static int
unw_prospero_describe_module (const unw_prospero_module_info_t *mi,
                              Elf_W(Phdr) *phdrs)
{
  const unw_prospero_segment_info_t *eh_frame_hdr = NULL;
  uint32_t i;
  int n = 0;

  for (i = 0; i != mi->num_segments; i++)
    {
      const unw_prospero_segment_info_t *segment = &mi->segments[i];
      Elf_W(Phdr) *phdr = &phdrs[n++];

      memset (phdr, 0, sizeof (*phdr));
      phdr->p_type = PT_LOAD;
      phdr->p_vaddr = (Elf_W(Addr)) segment->base_address;
      phdr->p_filesz = segment->size;
      phdr->p_memsz = segment->size;

      if (eh_frame_hdr == NULL && segment->prot == PROT_READ)
        eh_frame_hdr = segment;
    }

  if (eh_frame_hdr != NULL)
    {
      Elf_W(Phdr) *phdr = &phdrs[n++];

      memset (phdr, 0, sizeof (*phdr));
      phdr->p_type = PT_GNU_EH_FRAME;
      phdr->p_vaddr = (Elf_W(Addr)) eh_frame_hdr->base_address;
      phdr->p_filesz = eh_frame_hdr->size;
      phdr->p_memsz = eh_frame_hdr->size;
    }

  return n;
}

#elif defined(__QNX__)

#include <dlfcn.h>
#include <string.h>

#include "libunwind_i.h"

#define UNW_QNX_MODULE_FLAG_EXECUTABLE 0x00000200

typedef struct unw_qnx_list_head unw_qnx_list_head_t;
typedef struct unw_qnx_module_list unw_qnx_module_list_t;
typedef struct unw_qnx_module unw_qnx_module_t;

struct unw_qnx_list_head
  {
    unw_qnx_list_head_t *next;
    unw_qnx_list_head_t *prev;
  };

struct unw_qnx_module_list
  {
    unw_qnx_list_head_t list;
    unw_qnx_module_t *module;
    unw_qnx_list_head_t *root;
    uint32_t flags;
  };

struct unw_qnx_module
  {
    Link_map map;
    int ref_count;
    uint32_t flags;
    const char *name;
    /* ... */
  };

typedef int (*unw_iterate_phdr_callback) (const struct dl_phdr_info *info,
                                          size_t size, void *data);
typedef int (*unw_iterate_phdr_impl) (unw_iterate_phdr_callback callback,
                                      void *data);

HIDDEN int
dl_iterate_phdr (int (*callback) (struct dl_phdr_info *info, size_t size,
                                  void *data),
                 void *data)
{
  static int initialized = 0;
  static unw_iterate_phdr_impl libc_impl;
  unw_qnx_list_head_t *entries, *entry;
  int rc = 0;

  if (!initialized)
    {
      libc_impl = dlsym (RTLD_NEXT, "dl_iterate_phdr");
      initialized = 1;
    }

  if (libc_impl != NULL)
    return libc_impl ((unw_iterate_phdr_callback) callback, data);

  entries = dlopen (NULL, RTLD_NOW);

  for (entry = entries->next; rc == 0 && entry != entries; entry = entry->next)
    {
      const unw_qnx_module_list_t *l = (unw_qnx_module_list_t *) entry;
      const unw_qnx_module_t *mod = l->module;
      const Link_map *lm = &mod->map;
      Elf_W(Ehdr) *ehdr = (Elf_W(Ehdr) *) lm->l_addr;
      Elf_W(Phdr) *phdr = (Elf_W(Phdr) *) (lm->l_addr + ehdr->e_phoff);
      struct dl_phdr_info info;

      if ((mod->flags & UNW_QNX_MODULE_FLAG_EXECUTABLE) != 0)
        info.dlpi_addr = 0;
      else
        info.dlpi_addr = lm->l_addr;
      info.dlpi_name = lm->l_path;
      info.dlpi_phdr = phdr;
      info.dlpi_phnum = ehdr->e_phnum;

      rc = callback (&info, sizeof (info), data);
    }

  dlclose (entries);

  return rc;
}

#endif

#endif
