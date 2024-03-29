/* Linux-specific definitions: */

/* Define various structure offsets to simplify cross-compilation.  */

/* Offsets for x86 Linux "ucontext_t":  */

#define LINUX_UC_FLAGS_OFF      0x00
#define LINUX_UC_LINK_OFF       0x04
#define LINUX_UC_STACK_OFF      0x08
#define LINUX_UC_MCONTEXT_OFF   0x14
#define LINUX_UC_SIGMASK_OFF    0x6c
#ifdef __ANDROID__
#define LINUX_UC_FPREGS_MEM_OFF 0x74
#else
#define LINUX_UC_FPREGS_MEM_OFF 0xec
#endif

/* The struct sigcontext is located at an offset of 4
   from the stack pointer in the signal frame.         */

/* Offsets for x86 Linux "struct sigcontext":  */

#define LINUX_SC_GS_OFF         0x00
#define LINUX_SC_GSH_OFF        0x02
#define LINUX_SC_FS_OFF         0x04
#define LINUX_SC_FSH_OFF        0x06
#define LINUX_SC_ES_OFF         0x08
#define LINUX_SC_ESH_OFF        0x0a
#define LINUX_SC_DS_OFF         0x0c
#define LINUX_SC_DSH_OFF        0x0e
#define LINUX_SC_EDI_OFF        0x10
#define LINUX_SC_ESI_OFF        0x14
#define LINUX_SC_EBP_OFF        0x18
#define LINUX_SC_ESP_OFF        0x1c
#define LINUX_SC_EBX_OFF        0x20
#define LINUX_SC_EDX_OFF        0x24
#define LINUX_SC_ECX_OFF        0x28
#define LINUX_SC_EAX_OFF        0x2c
#define LINUX_SC_TRAPNO_OFF     0x30
#define LINUX_SC_ERR_OFF        0x34
#define LINUX_SC_EIP_OFF        0x38
#define LINUX_SC_CS_OFF         0x3c
#define LINUX_SC_CSH_OFF        0x3e
#define LINUX_SC_EFLAGS_OFF     0x40
#define LINUX_SC_ESP_AT_SIGNAL_OFF      0x44
#define LINUX_SC_SS_OFF         0x48
#define LINUX_SC_SSH_OFF        0x4a
#define LINUX_SC_FPSTATE_OFF    0x4c
#define LINUX_SC_OLDMASK_OFF    0x50
#define LINUX_SC_CR2_OFF        0x54

/* Offsets for x86 Linux "struct _fpstate":  */

#define LINUX_FPSTATE_CW_OFF            0x000
#define LINUX_FPSTATE_SW_OFF            0x004
#define LINUX_FPSTATE_TAG_OFF           0x008
#define LINUX_FPSTATE_IPOFF_OFF         0x00c
#define LINUX_FPSTATE_CSSEL_OFF         0x010
#define LINUX_FPSTATE_DATAOFF_OFF       0x014
#define LINUX_FPSTATE_DATASEL_OFF       0x018
#define LINUX_FPSTATE_ST0_OFF           0x01c
#define LINUX_FPSTATE_ST1_OFF           0x026
#define LINUX_FPSTATE_ST2_OFF           0x030
#define LINUX_FPSTATE_ST3_OFF           0x03a
#define LINUX_FPSTATE_ST4_OFF           0x044
#define LINUX_FPSTATE_ST5_OFF           0x04e
#define LINUX_FPSTATE_ST6_OFF           0x058
#define LINUX_FPSTATE_ST7_OFF           0x062
#define LINUX_FPSTATE_STATUS_OFF        0x06c
#define LINUX_FPSTATE_MAGIC_OFF         0x06e
#define LINUX_FPSTATE_FXSR_ENV_OFF      0x070
#define LINUX_FPSTATE_MXCSR_OFF         0x088
#define LINUX_FPSTATE_FXSR_ST0_OFF      0x090
#define LINUX_FPSTATE_FXSR_ST1_OFF      0x0a0
#define LINUX_FPSTATE_FXSR_ST2_OFF      0x0b0
#define LINUX_FPSTATE_FXSR_ST3_OFF      0x0c0
#define LINUX_FPSTATE_FXSR_ST4_OFF      0x0d0
#define LINUX_FPSTATE_FXSR_ST5_OFF      0x0e0
#define LINUX_FPSTATE_FXSR_ST6_OFF      0x0f0
#define LINUX_FPSTATE_FXSR_ST7_OFF      0x100
#define LINUX_FPSTATE_XMM0_OFF          0x110
#define LINUX_FPSTATE_XMM1_OFF          0x120
#define LINUX_FPSTATE_XMM2_OFF          0x130
#define LINUX_FPSTATE_XMM3_OFF          0x140
#define LINUX_FPSTATE_XMM4_OFF          0x150
#define LINUX_FPSTATE_XMM5_OFF          0x160
#define LINUX_FPSTATE_XMM6_OFF          0x170
#define LINUX_FPSTATE_XMM7_OFF          0x180

/* FreeBSD-specific definitions: */

#define FREEBSD_SC_UCONTEXT_OFF         0x20
#define FREEBSD_UC_MCONTEXT_OFF         0x10

#define FREEBSD_UC_MCONTEXT_GS_OFF      0x14
#define FREEBSD_UC_MCONTEXT_FS_OFF      0x18
#define FREEBSD_UC_MCONTEXT_ES_OFF      0x1c
#define FREEBSD_UC_MCONTEXT_DS_OFF      0x20
#define FREEBSD_UC_MCONTEXT_EDI_OFF     0x24
#define FREEBSD_UC_MCONTEXT_ESI_OFF     0x28
#define FREEBSD_UC_MCONTEXT_EBP_OFF     0x2c
#define FREEBSD_UC_MCONTEXT_EBX_OFF     0x34
#define FREEBSD_UC_MCONTEXT_EDX_OFF     0x38
#define FREEBSD_UC_MCONTEXT_ECX_OFF     0x3c
#define FREEBSD_UC_MCONTEXT_EAX_OFF     0x40
#define FREEBSD_UC_MCONTEXT_TRAPNO_OFF  0x44
#define FREEBSD_UC_MCONTEXT_EIP_OFF     0x4c
#define FREEBSD_UC_MCONTEXT_ESP_OFF     0x58
#define FREEBSD_UC_MCONTEXT_CS_OFF      0x50
#define FREEBSD_UC_MCONTEXT_EFLAGS_OFF  0x54
#define FREEBSD_UC_MCONTEXT_SS_OFF      0x5c
#define FREEBSD_UC_MCONTEXT_MC_LEN_OFF  0x60
#define FREEBSD_UC_MCONTEXT_FPFORMAT_OFF 0x64
#define FREEBSD_UC_MCONTEXT_OWNEDFP_OFF 0x68
#define FREEBSD_UC_MCONTEXT_FPSTATE_OFF 0x70

#define FREEBSD_UC_MCONTEXT_CW_OFF      0x70
#define FREEBSD_UC_MCONTEXT_SW_OFF      0x74
#define FREEBSD_UC_MCONTEXT_TAG_OFF     0x78
#define FREEBSD_UC_MCONTEXT_IPOFF_OFF   0x7c
#define FREEBSD_UC_MCONTEXT_CSSEL_OFF   0x80
#define FREEBSD_UC_MCONTEXT_DATAOFF_OFF 0x84
#define FREEBSD_US_MCONTEXT_DATASEL_OFF 0x88
#define FREEBSD_UC_MCONTEXT_ST0_OFF     0x8c

#define FREEBSD_UC_MCONTEXT_CW_XMM_OFF  0x70
#define FREEBSD_UC_MCONTEXT_SW_XMM_OFF  0x72
#define FREEBSD_UC_MCONTEXT_TAG_XMM_OFF 0x74
#define FREEBSD_UC_MCONTEXT_IPOFF_XMM_OFF 0x78
#define FREEBSD_UC_MCONTEXT_CSSEL_XMM_OFF 0x7c
#define FREEBSD_UC_MCONTEXT_DATAOFF_XMM_OFF 0x80
#define FREEBSD_US_MCONTEXT_DATASEL_XMM_OFF 0x84
#define FREEBSD_UC_MCONTEXT_MXCSR_XMM_OFF 0x88
#define FREEBSD_UC_MCONTEXT_ST0_XMM_OFF 0x90
#define FREEBSD_UC_MCONTEXT_XMM0_OFF    0x110

#define FREEBSD_UC_MCONTEXT_MC_LEN_VAL  0x280
#define FREEBSD_UC_MCONTEXT_FPFMT_NODEV 0x10000
#define FREEBSD_UC_MCONTEXT_FPFMT_387   0x10001
#define FREEBSD_UC_MCONTEXT_FPFMT_XMM   0x10002
#define FREEBSD_UC_MCONTEXT_FPOWNED_NONE 0x20000
#define FREEBSD_UC_MCONTEXT_FPOWNED_FPU 0x20001
#define FREEBSD_UC_MCONTEXT_FPOWNED_PCB 0x20002

