LOCAL_PATH := $(call my-dir)

libunwind_cflags := \
	-DHAVE_CONFIG_H \
	-DNDEBUG \
	-D_GNU_SOURCE \

libunwind_includes := \
	$(LOCAL_PATH)/src \
	$(LOCAL_PATH)/include \

ifeq ($(TARGET_ARCH),arm)
libunwind_includes += \
	$(LOCAL_PATH)/include/tdep-arm \

endif  # arm

ifeq ($(TARGET_ARCH),mips)
libunwind_includes += \
	$(LOCAL_PATH)/include/tdep-mips \

endif  # mips

ifeq ($(TARGET_ARCH),x86)
libunwind_includes += \
	$(LOCAL_PATH)/include/tdep-x86 \

endif  # x86

include $(CLEAR_VARS)

LOCAL_MODULE := libunwind

LOCAL_CFLAGS += $(libunwind_cflags)
LOCAL_C_INCLUDES := $(libunwind_includes)

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
	src/elf32.c \
	src/os-linux.c \

ifeq ($(TARGET_ARCH),arm)
LOCAL_SRC_FILES += \
	src/arm/is_fpreg.c \
	src/arm/regname.c \
	src/arm/getcontext.S \
	src/arm/Gcreate_addr_space.c \
	src/arm/Gget_proc_info.c \
	src/arm/Gget_save_loc.c \
	src/arm/Gglobal.c \
	src/arm/Ginit.c \
	src/arm/Ginit_local.c \
	src/arm/Ginit_remote.c \
	src/arm/Gis_signal_frame.c \
	src/arm/Gregs.c \
	src/arm/Gresume.c \
	src/arm/Gstep.c \
	src/arm/Gex_tables.c \
	src/arm/Lcreate_addr_space.c \
	src/arm/Lget_proc_info.c \
	src/arm/Lget_save_loc.c \
	src/arm/Lglobal.c \
	src/arm/Linit.c \
	src/arm/Linit_local.c \
	src/arm/Linit_remote.c \
	src/arm/Lis_signal_frame.c \
	src/arm/Lregs.c \
	src/arm/Lresume.c \
	src/arm/Lstep.c \
	src/arm/Lex_tables.c \

endif  # arm

ifeq ($(TARGET_ARCH),mips)
LOCAL_SRC_FILES += \
	src/mips/is_fpreg.c \
	src/mips/regname.c \
	src/mips/getcontext-android.S \
	src/mips/Gcreate_addr_space.c \
	src/mips/Gget_proc_info.c \
	src/mips/Gget_save_loc.c \
	src/mips/Gglobal.c \
	src/mips/Ginit.c \
	src/mips/Ginit_local.c \
	src/mips/Ginit_remote.c \
	src/mips/Gis_signal_frame.c \
	src/mips/Gregs.c \
	src/mips/Gresume.c \
	src/mips/Gstep.c \
	src/mips/Lcreate_addr_space.c \
	src/mips/Lget_proc_info.c \
	src/mips/Lget_save_loc.c \
	src/mips/Lglobal.c \
	src/mips/Linit.c \
	src/mips/Linit_local.c \
	src/mips/Linit_remote.c \
	src/mips/Lis_signal_frame.c \
	src/mips/Lregs.c \
	src/mips/Lresume.c \
	src/mips/Lstep.c \

endif  # mips

ifeq ($(TARGET_ARCH),x86)
LOCAL_SRC_FILES += \
	src/x86/is_fpreg.c \
	src/x86/regname.c \
	src/x86/getcontext-linux.S \
	src/x86/Gcreate_addr_space.c \
	src/x86/Gget_proc_info.c \
	src/x86/Gget_save_loc.c \
	src/x86/Gglobal.c \
	src/x86/Ginit.c \
	src/x86/Ginit_local.c \
	src/x86/Ginit_remote.c \
	src/x86/Gregs.c \
	src/x86/Gresume.c \
	src/x86/Gstep.c \
	src/x86/Gos-linux.c \
	src/x86/Lcreate_addr_space.c \
	src/x86/Lget_proc_info.c \
	src/x86/Lget_save_loc.c \
	src/x86/Lglobal.c \
	src/x86/Linit.c \
	src/x86/Linit_local.c \
	src/x86/Linit_remote.c \
	src/x86/Lregs.c \
	src/x86/Lresume.c \
	src/x86/Lstep.c \
	src/x86/Los-linux.c \

endif  # x86

LOCAL_SHARED_LIBRARIES := \
	libdl \

LOCAL_ADDITIONAL_DEPENDENCIES := \
	$(LOCAL_PATH)/Android.mk \

include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE := libunwind-ptrace

LOCAL_CFLAGS += $(libunwind_cflags)
LOCAL_C_INCLUDES := $(libunwind_includes)

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
