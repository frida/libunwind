#
# Copyright (C) 2014 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

LOCAL_PATH := $(call my-dir)

build_host := false
ifeq ($(HOST_OS),linux)
ifeq ($(HOST_ARCH),$(filter $(HOST_ARCH),x86 x86_64))
build_host := true
ifneq ($(strip $(BUILD_HOST_64bit)),)
HOST_ARCH := x86_64
endif
endif
endif

common_cflags := \
	-DHAVE_CONFIG_H \
	-DNDEBUG \
	-D_GNU_SOURCE \
	-Wno-unused-parameter \

# For debug build it is required:
#  1. Enable flags below
#  2. On runtime export UNW_DEBUG_LEVEL=x where x controls verbosity (from 1 to 20)
#common_cflags := \
#	-DHAVE_CONFIG_H \
#	-DDEBUG \
#	-D_GNU_SOURCE \
#	-U_FORTIFY_SOURCE

common_c_includes := \
	$(LOCAL_PATH)/src \
	$(LOCAL_PATH)/include \

libunwind_arches := arm arm64 mips x86 x86_64

$(foreach arch,$(libunwind_arches), \
  $(eval common_c_includes_$(arch) := $(LOCAL_PATH)/include/tdep-$(arch)))

#-----------------------------------------------------------------------
# libunwind shared library
#-----------------------------------------------------------------------
libunwind_src_files := \
	src/mi/init.c \
	src/mi/flush_cache.c \
	src/mi/mempool.c \
	src/mi/strerror.c \
	src/mi/backtrace.c \
	src/mi/dyn-cancel.c \
	src/mi/dyn-info-list.c \
	src/mi/dyn-register.c \
	src/mi/maps.c \
	src/mi/Ldyn-extract.c \
	src/mi/Lfind_dynamic_proc_info.c \
	src/mi/Lget_proc_info_by_ip.c \
	src/mi/Lget_proc_name.c \
	src/mi/Lput_dynamic_unwind_info.c \
	src/mi/Ldestroy_addr_space.c \
	src/mi/Lget_reg.c \
	src/mi/Lset_reg.c \
	src/mi/Lget_fpreg.c \
	src/mi/Lset_fpreg.c \
	src/mi/Lset_caching_policy.c \
	src/mi/Gdyn-extract.c \
	src/mi/Gdyn-remote.c \
	src/mi/Gfind_dynamic_proc_info.c \
	src/mi/Gget_accessors.c \
	src/mi/Gget_proc_info_by_ip.c \
	src/mi/Gget_proc_name.c \
	src/mi/Gput_dynamic_unwind_info.c \
	src/mi/Gdestroy_addr_space.c \
	src/mi/Gget_reg.c \
	src/mi/Gset_reg.c \
	src/mi/Gget_fpreg.c \
	src/mi/Gset_fpreg.c \
	src/mi/Gset_caching_policy.c \
	src/dwarf/Lexpr.c \
	src/dwarf/Lfde.c \
	src/dwarf/Lparser.c \
	src/dwarf/Lpe.c \
	src/dwarf/Lstep.c \
	src/dwarf/Lfind_proc_info-lsb.c \
	src/dwarf/Lfind_unwind_table.c \
	src/dwarf/Gexpr.c \
	src/dwarf/Gfde.c \
	src/dwarf/Gfind_proc_info-lsb.c \
	src/dwarf/Gfind_unwind_table.c \
	src/dwarf/Gparser.c \
	src/dwarf/Gpe.c \
	src/dwarf/Gstep.c \
	src/dwarf/global.c \
	src/os-linux.c \

# Arch specific source files.
$(foreach arch,$(libunwind_arches), \
  $(eval libunwind_src_files_$(arch) += \
	src/$(arch)/is_fpreg.c \
	src/$(arch)/regname.c \
	src/$(arch)/Gcreate_addr_space.c \
	src/$(arch)/Gget_proc_info.c \
	src/$(arch)/Gget_save_loc.c \
	src/$(arch)/Gglobal.c \
	src/$(arch)/Ginit.c \
	src/$(arch)/Ginit_local.c \
	src/$(arch)/Ginit_remote.c \
	src/$(arch)/Gregs.c \
	src/$(arch)/Gresume.c \
	src/$(arch)/Gstep.c \
	src/$(arch)/Lcreate_addr_space.c \
	src/$(arch)/Lget_proc_info.c \
	src/$(arch)/Lget_save_loc.c \
	src/$(arch)/Lglobal.c \
	src/$(arch)/Linit.c \
	src/$(arch)/Linit_local.c \
	src/$(arch)/Linit_remote.c \
	src/$(arch)/Lregs.c \
	src/$(arch)/Lresume.c \
	src/$(arch)/Lstep.c \
	))

# 64-bit architectures
libunwind_src_files_arm64 += src/elf64.c
libunwind_src_files_x86_64 += src/elf64.c

# 32-bit architectures
libunwind_src_files_arm   += src/elf32.c
libunwind_src_files_mips  += src/elf32.c
libunwind_src_files_x86   += src/elf32.c

libunwind_src_files_arm += \
	src/arm/getcontext.S \
	src/arm/Gis_signal_frame.c \
	src/arm/Gex_tables.c \
	src/arm/Lis_signal_frame.c \
	src/arm/Lex_tables.c \

libunwind_src_files_arm64 += \
	src/aarch64/Gis_signal_frame.c \
	src/aarch64/Lis_signal_frame.c \

libunwind_src_files_mips += \
	src/mips/getcontext-android.S \
	src/mips/Gis_signal_frame.c \
	src/mips/Lis_signal_frame.c \

libunwind_src_files_x86 += \
	src/x86/getcontext-linux.S \
	src/x86/Gos-linux.c \
	src/x86/Los-linux.c \

libunwind_src_files_x86_64 += \
	src/x86_64/getcontext.S \
	src/x86_64/Gstash_frame.c \
	src/x86_64/Gtrace.c \
	src/x86_64/Gos-linux.c \
	src/x86_64/Lstash_frame.c \
	src/x86_64/Ltrace.c \
	src/x86_64/Los-linux.c \
	src/x86_64/setcontext.S \

libunwind_shared_libraries_target := \
	libdl \

module := libunwind
module_tag := optional
build_type := target
build_target := SHARED_LIBRARY
include $(LOCAL_PATH)/Android.build.mk
build_type := host
include $(LOCAL_PATH)/Android.build.mk

#-----------------------------------------------------------------------
# libunwind-ptrace shared library
#-----------------------------------------------------------------------
libunwind-ptrace_src_files := \
	src/ptrace/_UPT_elf.c \
	src/ptrace/_UPT_accessors.c \
	src/ptrace/_UPT_access_fpreg.c \
	src/ptrace/_UPT_access_mem.c \
	src/ptrace/_UPT_access_reg.c \
	src/ptrace/_UPT_create.c \
	src/ptrace/_UPT_destroy.c \
	src/ptrace/_UPT_find_proc_info.c \
	src/ptrace/_UPT_get_dyn_info_list_addr.c \
	src/ptrace/_UPT_put_unwind_info.c \
	src/ptrace/_UPT_get_proc_name.c \
	src/ptrace/_UPT_reg_offset.c \
	src/ptrace/_UPT_resume.c \

libunwind-ptrace_shared_libraries := \
	libunwind \

module := libunwind-ptrace
module_tag := optional
build_type := target
build_target := SHARED_LIBRARY
include $(LOCAL_PATH)/Android.build.mk
build_type := host
include $(LOCAL_PATH)/Android.build.mk
