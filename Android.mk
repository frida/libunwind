LOCAL_PATH := $(call my-dir)

libunwind_cflags := \
	-DHAVE_CONFIG_H \
	-DNDEBUG \
	-D_GNU_SOURCE \
	-Wno-unused-parameter \

# For debug build it is required:
#  1. Enable flags below
#  2. On runtime export UNW_DEBUG_LEVEL=x where x controls verbosity (from 1 to 20)
#libunwind_cflags := \
	-DHAVE_CONFIG_H \
	-DDEBUG \
	-D_GNU_SOURCE \
	-U_FORTIFY_SOURCE

libunwind_includes := \
	$(LOCAL_PATH)/src \
	$(LOCAL_PATH)/include \

define libunwind-arch
$(if $(filter arm64,$(1)),aarch64,$(1))
endef

libunwind_arches := arm arm64 mips x86 x86_64

include $(CLEAR_VARS)

LOCAL_MODULE := libunwind

LOCAL_CFLAGS += $(libunwind_cflags)
LOCAL_C_INCLUDES := $(libunwind_includes)
$(foreach arch,$(libunwind_arches), \
  $(eval LOCAL_C_INCLUDES_$(arch) := $(LOCAL_PATH)/include/tdep-$(call libunwind-arch,$(arch))))

LOCAL_SRC_FILES := \
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

# 64-bit architectures
LOCAL_SRC_FILES_arm64 += src/elf64.c
LOCAL_SRC_FILES_x86_64 += src/elf64.c

# 32-bit architectures
LOCAL_SRC_FILES_arm   += src/elf32.c
LOCAL_SRC_FILES_mips  += src/elf32.c
LOCAL_SRC_FILES_x86   += src/elf32.c

# Arch specific source files.
$(foreach arch,$(libunwind_arches), \
  $(eval LOCAL_SRC_FILES_$(arch) += \
	src/$(call libunwind-arch,$(arch))/is_fpreg.c \
	src/$(call libunwind-arch,$(arch))/regname.c \
	src/$(call libunwind-arch,$(arch))/Gcreate_addr_space.c \
	src/$(call libunwind-arch,$(arch))/Gget_proc_info.c \
	src/$(call libunwind-arch,$(arch))/Gget_save_loc.c \
	src/$(call libunwind-arch,$(arch))/Gglobal.c \
	src/$(call libunwind-arch,$(arch))/Ginit.c \
	src/$(call libunwind-arch,$(arch))/Ginit_local.c \
	src/$(call libunwind-arch,$(arch))/Ginit_remote.c \
	src/$(call libunwind-arch,$(arch))/Gregs.c \
	src/$(call libunwind-arch,$(arch))/Gresume.c \
	src/$(call libunwind-arch,$(arch))/Gstep.c \
	src/$(call libunwind-arch,$(arch))/Lcreate_addr_space.c \
	src/$(call libunwind-arch,$(arch))/Lget_proc_info.c \
	src/$(call libunwind-arch,$(arch))/Lget_save_loc.c \
	src/$(call libunwind-arch,$(arch))/Lglobal.c \
	src/$(call libunwind-arch,$(arch))/Linit.c \
	src/$(call libunwind-arch,$(arch))/Linit_local.c \
	src/$(call libunwind-arch,$(arch))/Linit_remote.c \
	src/$(call libunwind-arch,$(arch))/Lregs.c \
	src/$(call libunwind-arch,$(arch))/Lresume.c \
	src/$(call libunwind-arch,$(arch))/Lstep.c \
	))

LOCAL_SRC_FILES_arm += \
	src/arm/getcontext.S \
	src/arm/Gis_signal_frame.c \
	src/arm/Gex_tables.c \
	src/arm/Lis_signal_frame.c \
	src/arm/Lex_tables.c \

LOCAL_SRC_FILES_arm64 += \
	src/aarch64/Gis_signal_frame.c \
	src/aarch64/Lis_signal_frame.c \

LOCAL_SRC_FILES_mips += \
	src/mips/getcontext-android.S \
	src/mips/Gis_signal_frame.c \
	src/mips/Lis_signal_frame.c \


LOCAL_SRC_FILES_x86 += \
	src/x86/getcontext-linux.S \
	src/x86/Gos-linux.c \
	src/x86/Los-linux.c \

LOCAL_SRC_FILES_x86_64 += \
	src/x86_64/getcontext.S \
	src/x86_64/Gstash_frame.c \
	src/x86_64/Gtrace.c \
	src/x86_64/Gos-linux.c \
	src/x86_64/Lstash_frame.c \
	src/x86_64/Ltrace.c \
	src/x86_64/Los-linux.c \
	src/x86_64/setcontext.S \

LOCAL_SHARED_LIBRARIES := \
	libdl \

LOCAL_ADDITIONAL_DEPENDENCIES := \
	$(LOCAL_PATH)/Android.mk \

include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE := libunwind-ptrace

LOCAL_CFLAGS += $(libunwind_cflags)
LOCAL_C_INCLUDES := $(libunwind_includes)
$(foreach arch,$(libunwind_arches), \
  $(eval LOCAL_C_INCLUDES_$(arch) := $(LOCAL_PATH)/include/tdep-$(call libunwind-arch,$(arch))))

# Files needed to trace running processes.
LOCAL_SRC_FILES += \
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

LOCAL_SHARED_LIBRARIES := \
	libunwind \

LOCAL_ADDITIONAL_DEPENDENCIES := \
	$(LOCAL_PATH)/Android.mk \

include $(BUILD_SHARED_LIBRARY)
