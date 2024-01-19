# 1 "SPL/MDR32Fx/src/MDR32F9Qx_timer.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 383 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "SPL/MDR32Fx/src/MDR32F9Qx_timer.c" 2
# 23 "SPL/MDR32Fx/src/MDR32F9Qx_timer.c"
# 1 "./SPL/MDR32Fx/inc\\MDR32F9Qx_timer.h" 1
# 32 "./SPL/MDR32Fx/inc\\MDR32F9Qx_timer.h"
# 1 "./SPL/MDR32Fx\\MDR32F9Qx_config.h" 1
# 54 "./SPL/MDR32Fx\\MDR32F9Qx_config.h"
# 1 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdint.h" 1 3
# 56 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdint.h" 3
typedef signed char int8_t;
typedef signed short int int16_t;
typedef signed int int32_t;
typedef signed long long int int64_t;


typedef unsigned char uint8_t;
typedef unsigned short int uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long int uint64_t;





typedef signed char int_least8_t;
typedef signed short int int_least16_t;
typedef signed int int_least32_t;
typedef signed long long int int_least64_t;


typedef unsigned char uint_least8_t;
typedef unsigned short int uint_least16_t;
typedef unsigned int uint_least32_t;
typedef unsigned long long int uint_least64_t;




typedef signed int int_fast8_t;
typedef signed int int_fast16_t;
typedef signed int int_fast32_t;
typedef signed long long int int_fast64_t;


typedef unsigned int uint_fast8_t;
typedef unsigned int uint_fast16_t;
typedef unsigned int uint_fast32_t;
typedef unsigned long long int uint_fast64_t;






typedef signed int intptr_t;
typedef unsigned int uintptr_t;



typedef signed long long intmax_t;
typedef unsigned long long uintmax_t;
# 55 "./SPL/MDR32Fx\\MDR32F9Qx_config.h" 2
# 1 "./RTE/_Target_1\\RTE_Components.h" 1
# 56 "./SPL/MDR32Fx\\MDR32F9Qx_config.h" 2
# 81 "./SPL/MDR32Fx\\MDR32F9Qx_config.h"
# 1 "./CMSIS/MDR32Fx/DeviceSupport/MDR1986VE9x/inc\\MDR32Fx.h" 1
# 30 "./CMSIS/MDR32Fx/DeviceSupport/MDR1986VE9x/inc\\MDR32Fx.h"
typedef enum IRQn
{

  NonMaskableInt_IRQn = -14,
  HardFault_IRQn = -13,
  MemoryManagement_IRQn = -12,
  BusFault_IRQn = -11,
  UsageFault_IRQn = -10,
  SVCall_IRQn = -5,
  PendSV_IRQn = -2,
  SysTick_IRQn = -1,


  CAN1_IRQn = 0,
  CAN2_IRQn = 1,
  USB_IRQn = 2,
  DMA_IRQn = 5,
  UART1_IRQn = 6,
  UART2_IRQn = 7,
  SSP1_IRQn = 8,
  I2C_IRQn = 10,
  POWER_IRQn = 11,
  WWDG_IRQn = 12,
  Timer1_IRQn = 14,
  Timer2_IRQn = 15,
  Timer3_IRQn = 16,
  ADC_IRQn = 17,
  COMPARATOR_IRQn = 19,
  SSP2_IRQn = 20,
  BACKUP_IRQn = 27,
  EXT_INT1_IRQn = 28,
  EXT_INT2_IRQn = 29,
  EXT_INT3_IRQn = 30,
  EXT_INT4_IRQn = 31
}IRQn_Type;
# 79 "./CMSIS/MDR32Fx/DeviceSupport/MDR1986VE9x/inc\\MDR32Fx.h"
# 1 "./SPL/MDR32Fx\\MDR32F9Qx_config.h" 1
# 80 "./CMSIS/MDR32Fx/DeviceSupport/MDR1986VE9x/inc\\MDR32Fx.h" 2
# 1 "./CMSIS/MDR32Fx/CoreSupport/CM3\\core_cm3.h" 1
# 140 "./CMSIS/MDR32Fx/CoreSupport/CM3\\core_cm3.h"
# 1 "./CMSIS/MDR32Fx/CoreSupport/CM3\\core_cmInstr.h" 1
# 325 "./CMSIS/MDR32Fx/CoreSupport/CM3\\core_cmInstr.h"
__attribute__( ( always_inline ) ) static inline void __NOP(void)
{
  __asm volatile ("nop");
}







__attribute__( ( always_inline ) ) static inline void __WFI(void)
{
  __asm volatile ("wfi");
}







__attribute__( ( always_inline ) ) static inline void __WFE(void)
{
  __asm volatile ("wfe");
}






__attribute__( ( always_inline ) ) static inline void __SEV(void)
{
  __asm volatile ("sev");
}
# 369 "./CMSIS/MDR32Fx/CoreSupport/CM3\\core_cmInstr.h"
__attribute__( ( always_inline ) ) static inline void __ISB(void)
{
  __asm volatile ("isb");
}







__attribute__( ( always_inline ) ) static inline void __DSB(void)
{
  __asm volatile ("dsb");
}







__attribute__( ( always_inline ) ) static inline void __DMB(void)
{
  __asm volatile ("dmb");
}
# 404 "./CMSIS/MDR32Fx/CoreSupport/CM3\\core_cmInstr.h"
__attribute__( ( always_inline ) ) static inline uint32_t __REV(uint32_t value)
{



  uint32_t result;

  __asm volatile ("rev %0, %1" : "=r" (result) : "r" (value) );
  return(result);

}
# 424 "./CMSIS/MDR32Fx/CoreSupport/CM3\\core_cmInstr.h"
__attribute__( ( always_inline ) ) static inline uint32_t __REV16(uint32_t value)
{
  uint32_t result;

  __asm volatile ("rev16 %0, %1" : "=r" (result) : "r" (value) );
  return(result);
}
# 440 "./CMSIS/MDR32Fx/CoreSupport/CM3\\core_cmInstr.h"
__attribute__( ( always_inline ) ) static inline int32_t __REVSH(int32_t value)
{



  uint32_t result;

  __asm volatile ("revsh %0, %1" : "=r" (result) : "r" (value) );
  return(result);

}
# 461 "./CMSIS/MDR32Fx/CoreSupport/CM3\\core_cmInstr.h"
__attribute__( ( always_inline ) ) static inline uint32_t __ROR(uint32_t op1, uint32_t op2)
{
  return (op1 >> op2) | (op1 << (32 - op2));
}
# 487 "./CMSIS/MDR32Fx/CoreSupport/CM3\\core_cmInstr.h"
__attribute__( ( always_inline ) ) static inline uint32_t __RBIT(uint32_t value)
{
  uint32_t result;

   __asm volatile ("rbit %0, %1" : "=r" (result) : "r" (value) );
   return(result);
}
# 503 "./CMSIS/MDR32Fx/CoreSupport/CM3\\core_cmInstr.h"
__attribute__( ( always_inline ) ) static inline uint8_t __LDREXB(volatile uint8_t *addr)
{
    uint32_t result;







   __asm volatile ("ldrexb %0, [%1]" : "=r" (result) : "r" (addr) : "memory" );

   return ((uint8_t) result);
}
# 526 "./CMSIS/MDR32Fx/CoreSupport/CM3\\core_cmInstr.h"
__attribute__( ( always_inline ) ) static inline uint16_t __LDREXH(volatile uint16_t *addr)
{
    uint32_t result;







   __asm volatile ("ldrexh %0, [%1]" : "=r" (result) : "r" (addr) : "memory" );

   return ((uint16_t) result);
}
# 549 "./CMSIS/MDR32Fx/CoreSupport/CM3\\core_cmInstr.h"
__attribute__( ( always_inline ) ) static inline uint32_t __LDREXW(volatile uint32_t *addr)
{
    uint32_t result;

   __asm volatile ("ldrex %0, %1" : "=r" (result) : "Q" (*addr) );
   return(result);
}
# 567 "./CMSIS/MDR32Fx/CoreSupport/CM3\\core_cmInstr.h"
__attribute__( ( always_inline ) ) static inline uint32_t __STREXB(uint8_t value, volatile uint8_t *addr)
{
   uint32_t result;

   __asm volatile ("strexb %0, %2, %1" : "=&r" (result), "=Q" (*addr) : "r" ((uint32_t)value) );
   return(result);
}
# 585 "./CMSIS/MDR32Fx/CoreSupport/CM3\\core_cmInstr.h"
__attribute__( ( always_inline ) ) static inline uint32_t __STREXH(uint16_t value, volatile uint16_t *addr)
{
   uint32_t result;

   __asm volatile ("strexh %0, %2, %1" : "=&r" (result), "=Q" (*addr) : "r" ((uint32_t)value) );
   return(result);
}
# 603 "./CMSIS/MDR32Fx/CoreSupport/CM3\\core_cmInstr.h"
__attribute__( ( always_inline ) ) static inline uint32_t __STREXW(uint32_t value, volatile uint32_t *addr)
{
   uint32_t result;

   __asm volatile ("strex %0, %2, %1" : "=&r" (result), "=Q" (*addr) : "r" (value) );
   return(result);
}







__attribute__( ( always_inline ) ) static inline void __CLREX(void)
{
  __asm volatile ("clrex" ::: "memory");
}
# 662 "./CMSIS/MDR32Fx/CoreSupport/CM3\\core_cmInstr.h"
__attribute__( ( always_inline ) ) static inline uint8_t __CLZ(uint32_t value)
{
  uint32_t result;

  __asm volatile ("clz %0, %1" : "=r" (result) : "r" (value) );
   return ((uint8_t) result);
}
# 141 "./CMSIS/MDR32Fx/CoreSupport/CM3\\core_cm3.h" 2
# 1 "./CMSIS/MDR32Fx/CoreSupport/CM3\\core_cmFunc.h" 1
# 329 "./CMSIS/MDR32Fx/CoreSupport/CM3\\core_cmFunc.h"
__attribute__( ( always_inline ) ) static inline void __enable_irq(void)
{
  __asm volatile ("cpsie i" : : : "memory");
}







__attribute__( ( always_inline ) ) static inline void __disable_irq(void)
{
  __asm volatile ("cpsid i" : : : "memory");
}
# 352 "./CMSIS/MDR32Fx/CoreSupport/CM3\\core_cmFunc.h"
__attribute__( ( always_inline ) ) static inline uint32_t __get_CONTROL(void)
{
  uint32_t result;

  __asm volatile ("MRS %0, control" : "=r" (result) );
  return(result);
}
# 367 "./CMSIS/MDR32Fx/CoreSupport/CM3\\core_cmFunc.h"
__attribute__( ( always_inline ) ) static inline void __set_CONTROL(uint32_t control)
{
  __asm volatile ("MSR control, %0" : : "r" (control) : "memory");
}
# 379 "./CMSIS/MDR32Fx/CoreSupport/CM3\\core_cmFunc.h"
__attribute__( ( always_inline ) ) static inline uint32_t __get_IPSR(void)
{
  uint32_t result;

  __asm volatile ("MRS %0, ipsr" : "=r" (result) );
  return(result);
}
# 394 "./CMSIS/MDR32Fx/CoreSupport/CM3\\core_cmFunc.h"
__attribute__( ( always_inline ) ) static inline uint32_t __get_APSR(void)
{
  uint32_t result;

  __asm volatile ("MRS %0, apsr" : "=r" (result) );
  return(result);
}
# 409 "./CMSIS/MDR32Fx/CoreSupport/CM3\\core_cmFunc.h"
__attribute__( ( always_inline ) ) static inline uint32_t __get_xPSR(void)
{
  uint32_t result;

  __asm volatile ("MRS %0, xpsr" : "=r" (result) );
  return(result);
}
# 424 "./CMSIS/MDR32Fx/CoreSupport/CM3\\core_cmFunc.h"
__attribute__( ( always_inline ) ) static inline uint32_t __get_PSP(void)
{
  register uint32_t result;

  __asm volatile ("MRS %0, psp\n" : "=r" (result) );
  return(result);
}
# 439 "./CMSIS/MDR32Fx/CoreSupport/CM3\\core_cmFunc.h"
__attribute__( ( always_inline ) ) static inline void __set_PSP(uint32_t topOfProcStack)
{
  __asm volatile ("MSR psp, %0\n" : : "r" (topOfProcStack) : "sp");
}
# 451 "./CMSIS/MDR32Fx/CoreSupport/CM3\\core_cmFunc.h"
__attribute__( ( always_inline ) ) static inline uint32_t __get_MSP(void)
{
  register uint32_t result;

  __asm volatile ("MRS %0, msp\n" : "=r" (result) );
  return(result);
}
# 466 "./CMSIS/MDR32Fx/CoreSupport/CM3\\core_cmFunc.h"
__attribute__( ( always_inline ) ) static inline void __set_MSP(uint32_t topOfMainStack)
{
  __asm volatile ("MSR msp, %0\n" : : "r" (topOfMainStack) : "sp");
}
# 478 "./CMSIS/MDR32Fx/CoreSupport/CM3\\core_cmFunc.h"
__attribute__( ( always_inline ) ) static inline uint32_t __get_PRIMASK(void)
{
  uint32_t result;

  __asm volatile ("MRS %0, primask" : "=r" (result) );
  return(result);
}
# 493 "./CMSIS/MDR32Fx/CoreSupport/CM3\\core_cmFunc.h"
__attribute__( ( always_inline ) ) static inline void __set_PRIMASK(uint32_t priMask)
{
  __asm volatile ("MSR primask, %0" : : "r" (priMask) : "memory");
}
# 506 "./CMSIS/MDR32Fx/CoreSupport/CM3\\core_cmFunc.h"
__attribute__( ( always_inline ) ) static inline void __enable_fault_irq(void)
{
  __asm volatile ("cpsie f" : : : "memory");
}







__attribute__( ( always_inline ) ) static inline void __disable_fault_irq(void)
{
  __asm volatile ("cpsid f" : : : "memory");
}
# 529 "./CMSIS/MDR32Fx/CoreSupport/CM3\\core_cmFunc.h"
__attribute__( ( always_inline ) ) static inline uint32_t __get_BASEPRI(void)
{
  uint32_t result;

  __asm volatile ("MRS %0, basepri_max" : "=r" (result) );
  return(result);
}
# 544 "./CMSIS/MDR32Fx/CoreSupport/CM3\\core_cmFunc.h"
__attribute__( ( always_inline ) ) static inline void __set_BASEPRI(uint32_t value)
{
  __asm volatile ("MSR basepri, %0" : : "r" (value) : "memory");
}
# 556 "./CMSIS/MDR32Fx/CoreSupport/CM3\\core_cmFunc.h"
__attribute__( ( always_inline ) ) static inline uint32_t __get_FAULTMASK(void)
{
  uint32_t result;

  __asm volatile ("MRS %0, faultmask" : "=r" (result) );
  return(result);
}
# 571 "./CMSIS/MDR32Fx/CoreSupport/CM3\\core_cmFunc.h"
__attribute__( ( always_inline ) ) static inline void __set_FAULTMASK(uint32_t faultMask)
{
  __asm volatile ("MSR faultmask, %0" : : "r" (faultMask) : "memory");
}
# 142 "./CMSIS/MDR32Fx/CoreSupport/CM3\\core_cm3.h" 2
# 215 "./CMSIS/MDR32Fx/CoreSupport/CM3\\core_cm3.h"
typedef union
{
  struct
  {

    uint32_t _reserved0:27;





    uint32_t Q:1;
    uint32_t V:1;
    uint32_t C:1;
    uint32_t Z:1;
    uint32_t N:1;
  } b;
  uint32_t w;
} APSR_Type;




typedef union
{
  struct
  {
    uint32_t ISR:9;
    uint32_t _reserved0:23;
  } b;
  uint32_t w;
} IPSR_Type;




typedef union
{
  struct
  {
    uint32_t ISR:9;

    uint32_t _reserved0:15;





    uint32_t T:1;
    uint32_t IT:2;
    uint32_t Q:1;
    uint32_t V:1;
    uint32_t C:1;
    uint32_t Z:1;
    uint32_t N:1;
  } b;
  uint32_t w;
} xPSR_Type;




typedef union
{
  struct
  {
    uint32_t nPRIV:1;
    uint32_t SPSEL:1;
    uint32_t FPCA:1;
    uint32_t _reserved0:29;
  } b;
  uint32_t w;
} CONTROL_Type;
# 300 "./CMSIS/MDR32Fx/CoreSupport/CM3\\core_cm3.h"
typedef struct
{
  volatile uint32_t ISER[8];
       uint32_t RESERVED0[24];
  volatile uint32_t ICER[8];
       uint32_t RSERVED1[24];
  volatile uint32_t ISPR[8];
       uint32_t RESERVED2[24];
  volatile uint32_t ICPR[8];
       uint32_t RESERVED3[24];
  volatile uint32_t IABR[8];
       uint32_t RESERVED4[56];
  volatile uint8_t IP[240];
       uint32_t RESERVED5[644];
  volatile uint32_t STIR;
} NVIC_Type;
# 332 "./CMSIS/MDR32Fx/CoreSupport/CM3\\core_cm3.h"
typedef struct
{
  volatile const uint32_t CPUID;
  volatile uint32_t ICSR;
  volatile uint32_t VTOR;
  volatile uint32_t AIRCR;
  volatile uint32_t SCR;
  volatile uint32_t CCR;
  volatile uint8_t SHP[12];
  volatile uint32_t SHCSR;
  volatile uint32_t CFSR;
  volatile uint32_t HFSR;
  volatile uint32_t DFSR;
  volatile uint32_t MMFAR;
  volatile uint32_t BFAR;
  volatile uint32_t AFSR;
  volatile const uint32_t PFR[2];
  volatile const uint32_t DFR;
  volatile const uint32_t ADR;
  volatile const uint32_t MMFR[4];
  volatile const uint32_t ISAR[5];
       uint32_t RESERVED0[5];
  volatile uint32_t CPACR;
} SCB_Type;
# 557 "./CMSIS/MDR32Fx/CoreSupport/CM3\\core_cm3.h"
typedef struct
{
       uint32_t RESERVED0[1];
  volatile const uint32_t ICTR;



       uint32_t RESERVED1[1];

} SCnSCB_Type;
# 594 "./CMSIS/MDR32Fx/CoreSupport/CM3\\core_cm3.h"
typedef struct
{
  volatile uint32_t CTRL;
  volatile uint32_t LOAD;
  volatile uint32_t VAL;
  volatile const uint32_t CALIB;
} SysTick_Type;
# 644 "./CMSIS/MDR32Fx/CoreSupport/CM3\\core_cm3.h"
typedef struct
{
  volatile union
  {
    volatile uint8_t u8;
    volatile uint16_t u16;
    volatile uint32_t u32;
  } PORT [32];
       uint32_t RESERVED0[864];
  volatile uint32_t TER;
       uint32_t RESERVED1[15];
  volatile uint32_t TPR;
       uint32_t RESERVED2[15];
  volatile uint32_t TCR;
       uint32_t RESERVED3[29];
  volatile uint32_t IWR;
  volatile const uint32_t IRR;
  volatile uint32_t IMCR;
       uint32_t RESERVED4[43];
  volatile uint32_t LAR;
  volatile const uint32_t LSR;
       uint32_t RESERVED5[6];
  volatile const uint32_t PID4;
  volatile const uint32_t PID5;
  volatile const uint32_t PID6;
  volatile const uint32_t PID7;
  volatile const uint32_t PID0;
  volatile const uint32_t PID1;
  volatile const uint32_t PID2;
  volatile const uint32_t PID3;
  volatile const uint32_t CID0;
  volatile const uint32_t CID1;
  volatile const uint32_t CID2;
  volatile const uint32_t CID3;
} ITM_Type;
# 745 "./CMSIS/MDR32Fx/CoreSupport/CM3\\core_cm3.h"
typedef struct
{
  volatile uint32_t CTRL;
  volatile uint32_t CYCCNT;
  volatile uint32_t CPICNT;
  volatile uint32_t EXCCNT;
  volatile uint32_t SLEEPCNT;
  volatile uint32_t LSUCNT;
  volatile uint32_t FOLDCNT;
  volatile const uint32_t PCSR;
  volatile uint32_t COMP0;
  volatile uint32_t MASK0;
  volatile uint32_t FUNCTION0;
       uint32_t RESERVED0[1];
  volatile uint32_t COMP1;
  volatile uint32_t MASK1;
  volatile uint32_t FUNCTION1;
       uint32_t RESERVED1[1];
  volatile uint32_t COMP2;
  volatile uint32_t MASK2;
  volatile uint32_t FUNCTION2;
       uint32_t RESERVED2[1];
  volatile uint32_t COMP3;
  volatile uint32_t MASK3;
  volatile uint32_t FUNCTION3;
} DWT_Type;
# 890 "./CMSIS/MDR32Fx/CoreSupport/CM3\\core_cm3.h"
typedef struct
{
  volatile uint32_t SSPSR;
  volatile uint32_t CSPSR;
       uint32_t RESERVED0[2];
  volatile uint32_t ACPR;
       uint32_t RESERVED1[55];
  volatile uint32_t SPPR;
       uint32_t RESERVED2[131];
  volatile const uint32_t FFSR;
  volatile uint32_t FFCR;
  volatile const uint32_t FSCR;
       uint32_t RESERVED3[759];
  volatile const uint32_t TRIGGER;
  volatile const uint32_t FIFO0;
  volatile const uint32_t ITATBCTR2;
       uint32_t RESERVED4[1];
  volatile const uint32_t ITATBCTR0;
  volatile const uint32_t FIFO1;
  volatile uint32_t ITCTRL;
       uint32_t RESERVED5[39];
  volatile uint32_t CLAIMSET;
  volatile uint32_t CLAIMCLR;
       uint32_t RESERVED7[8];
  volatile const uint32_t DEVID;
  volatile const uint32_t DEVTYPE;
} TPI_Type;
# 1044 "./CMSIS/MDR32Fx/CoreSupport/CM3\\core_cm3.h"
typedef struct
{
  volatile const uint32_t TYPE;
  volatile uint32_t CTRL;
  volatile uint32_t RNR;
  volatile uint32_t RBAR;
  volatile uint32_t RASR;
  volatile uint32_t RBAR_A1;
  volatile uint32_t RASR_A1;
  volatile uint32_t RBAR_A2;
  volatile uint32_t RASR_A2;
  volatile uint32_t RBAR_A3;
  volatile uint32_t RASR_A3;
} MPU_Type;
# 1136 "./CMSIS/MDR32Fx/CoreSupport/CM3\\core_cm3.h"
typedef struct
{
  volatile uint32_t DHCSR;
  volatile uint32_t DCRSR;
  volatile uint32_t DCRDR;
  volatile uint32_t DEMCR;
} CoreDebug_Type;
# 1296 "./CMSIS/MDR32Fx/CoreSupport/CM3\\core_cm3.h"
static inline void NVIC_SetPriorityGrouping(uint32_t PriorityGroup)
{
  uint32_t reg_value;
  uint32_t PriorityGroupTmp = (PriorityGroup & (uint32_t)0x07);

  reg_value = ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->AIRCR;
  reg_value &= ~((0xFFFFUL << 16) | (7UL << 8));
  reg_value = (reg_value |
                ((uint32_t)0x5FA << 16) |
                (PriorityGroupTmp << 8));
  ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->AIRCR = reg_value;
}
# 1316 "./CMSIS/MDR32Fx/CoreSupport/CM3\\core_cm3.h"
static inline uint32_t NVIC_GetPriorityGrouping(void)
{
  return ((((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->AIRCR & (7UL << 8)) >> 8);
}
# 1328 "./CMSIS/MDR32Fx/CoreSupport/CM3\\core_cm3.h"
static inline void NVIC_EnableIRQ(IRQn_Type IRQn)
{
  ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ISER[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F));
}
# 1340 "./CMSIS/MDR32Fx/CoreSupport/CM3\\core_cm3.h"
static inline void NVIC_DisableIRQ(IRQn_Type IRQn)
{
  ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ICER[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F));
}
# 1356 "./CMSIS/MDR32Fx/CoreSupport/CM3\\core_cm3.h"
static inline uint32_t NVIC_GetPendingIRQ(IRQn_Type IRQn)
{
  return((uint32_t) ((((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ISPR[(uint32_t)(IRQn) >> 5] & (1 << ((uint32_t)(IRQn) & 0x1F)))?1:0));
}
# 1368 "./CMSIS/MDR32Fx/CoreSupport/CM3\\core_cm3.h"
static inline void NVIC_SetPendingIRQ(IRQn_Type IRQn)
{
  ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ISPR[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F));
}
# 1380 "./CMSIS/MDR32Fx/CoreSupport/CM3\\core_cm3.h"
static inline void NVIC_ClearPendingIRQ(IRQn_Type IRQn)
{
  ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ICPR[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F));
}
# 1395 "./CMSIS/MDR32Fx/CoreSupport/CM3\\core_cm3.h"
static inline uint32_t NVIC_GetActive(IRQn_Type IRQn)
{
  return((uint32_t)((((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->IABR[(uint32_t)(IRQn) >> 5] & (1 << ((uint32_t)(IRQn) & 0x1F)))?1:0));
}
# 1410 "./CMSIS/MDR32Fx/CoreSupport/CM3\\core_cm3.h"
static inline void NVIC_SetPriority(IRQn_Type IRQn, uint32_t priority)
{
  if(IRQn < 0) {
    ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->SHP[((uint32_t)(IRQn) & 0xF)-4] = ((priority << (8 - 3)) & 0xff); }
  else {
    ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->IP[(uint32_t)(IRQn)] = ((priority << (8 - 3)) & 0xff); }
}
# 1430 "./CMSIS/MDR32Fx/CoreSupport/CM3\\core_cm3.h"
static inline uint32_t NVIC_GetPriority(IRQn_Type IRQn)
{

  if(IRQn < 0) {
    return((uint32_t)(((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->SHP[((uint32_t)(IRQn) & 0xF)-4] >> (8 - 3))); }
  else {
    return((uint32_t)(((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->IP[(uint32_t)(IRQn)] >> (8 - 3))); }
}
# 1452 "./CMSIS/MDR32Fx/CoreSupport/CM3\\core_cm3.h"
static inline uint32_t NVIC_EncodePriority (uint32_t PriorityGroup, uint32_t PreemptPriority, uint32_t SubPriority)
{
  uint32_t PriorityGroupTmp = (PriorityGroup & 0x07);
  uint32_t PreemptPriorityBits;
  uint32_t SubPriorityBits;

  PreemptPriorityBits = ((7 - PriorityGroupTmp) > 3) ? 3 : 7 - PriorityGroupTmp;
  SubPriorityBits = ((PriorityGroupTmp + 3) < 7) ? 0 : PriorityGroupTmp - 7 + 3;

  return (
           ((PreemptPriority & ((1 << (PreemptPriorityBits)) - 1)) << SubPriorityBits) |
           ((SubPriority & ((1 << (SubPriorityBits )) - 1)))
         );
}
# 1480 "./CMSIS/MDR32Fx/CoreSupport/CM3\\core_cm3.h"
static inline void NVIC_DecodePriority (uint32_t Priority, uint32_t PriorityGroup, uint32_t* pPreemptPriority, uint32_t* pSubPriority)
{
  uint32_t PriorityGroupTmp = (PriorityGroup & 0x07);
  uint32_t PreemptPriorityBits;
  uint32_t SubPriorityBits;

  PreemptPriorityBits = ((7 - PriorityGroupTmp) > 3) ? 3 : 7 - PriorityGroupTmp;
  SubPriorityBits = ((PriorityGroupTmp + 3) < 7) ? 0 : PriorityGroupTmp - 7 + 3;

  *pPreemptPriority = (Priority >> SubPriorityBits) & ((1 << (PreemptPriorityBits)) - 1);
  *pSubPriority = (Priority ) & ((1 << (SubPriorityBits )) - 1);
}






static inline void NVIC_SystemReset(void)
{
  __DSB();

  ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->AIRCR = ((0x5FA << 16) |
                 (((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->AIRCR & (7UL << 8)) |
                 (1UL << 2));
  __DSB();
  while(1);
}
# 1537 "./CMSIS/MDR32Fx/CoreSupport/CM3\\core_cm3.h"
static inline uint32_t SysTick_Config(uint32_t ticks)
{
  if ((ticks - 1) > (0xFFFFFFUL << 0)) return (1);

  ((SysTick_Type *) ((0xE000E000UL) + 0x0010UL) )->LOAD = ticks - 1;
  NVIC_SetPriority (SysTick_IRQn, (1<<3) - 1);
  ((SysTick_Type *) ((0xE000E000UL) + 0x0010UL) )->VAL = 0;
  ((SysTick_Type *) ((0xE000E000UL) + 0x0010UL) )->CTRL = (1UL << 2) |
                   (1UL << 1) |
                   (1UL << 0);
  return (0);
}
# 1561 "./CMSIS/MDR32Fx/CoreSupport/CM3\\core_cm3.h"
extern volatile int32_t ITM_RxBuffer;
# 1575 "./CMSIS/MDR32Fx/CoreSupport/CM3\\core_cm3.h"
static inline uint32_t ITM_SendChar (uint32_t ch)
{
  if ((((ITM_Type *) (0xE0000000UL) )->TCR & (1UL << 0)) &&
      (((ITM_Type *) (0xE0000000UL) )->TER & (1UL << 0) ) )
  {
    while (((ITM_Type *) (0xE0000000UL) )->PORT[0].u32 == 0);
    ((ITM_Type *) (0xE0000000UL) )->PORT[0].u8 = (uint8_t) ch;
  }
  return (ch);
}
# 1594 "./CMSIS/MDR32Fx/CoreSupport/CM3\\core_cm3.h"
static inline int32_t ITM_ReceiveChar (void) {
  int32_t ch = -1;

  if (ITM_RxBuffer != 0x5AA55AA5) {
    ch = ITM_RxBuffer;
    ITM_RxBuffer = 0x5AA55AA5;
  }

  return (ch);
}
# 1613 "./CMSIS/MDR32Fx/CoreSupport/CM3\\core_cm3.h"
static inline int32_t ITM_CheckChar (void) {

  if (ITM_RxBuffer == 0x5AA55AA5) {
    return (0);
  } else {
    return (1);
  }
}
# 81 "./CMSIS/MDR32Fx/DeviceSupport/MDR1986VE9x/inc\\MDR32Fx.h" 2
# 1 "./CMSIS/MDR32Fx/DeviceSupport/MDR1986VE9x/startup/arm\\system_MDR32F9Qx.h" 1
# 26 "./CMSIS/MDR32Fx/DeviceSupport/MDR1986VE9x/startup/arm\\system_MDR32F9Qx.h"
extern uint32_t SystemCoreClock;
# 35 "./CMSIS/MDR32Fx/DeviceSupport/MDR1986VE9x/startup/arm\\system_MDR32F9Qx.h"
extern void SystemInit(void);
extern void SystemCoreClockUpdate(void);
# 82 "./CMSIS/MDR32Fx/DeviceSupport/MDR1986VE9x/inc\\MDR32Fx.h" 2





typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus, BitStatus;



typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;


typedef enum {ERROR = 0, SUCCESS = !ERROR} ErrorStatus;
# 111 "./CMSIS/MDR32Fx/DeviceSupport/MDR1986VE9x/inc\\MDR32Fx.h"
typedef struct
{
  volatile uint32_t ID;
  volatile uint32_t DLC;
  volatile uint32_t DATAL;
  volatile uint32_t DATAH;
}MDR_CAN_BUF_TypeDef;


typedef struct
{
  volatile uint32_t MASK;
  volatile uint32_t FILTER;
}MDR_CAN_BUF_FILTER_TypeDef;


typedef struct
{
  volatile uint32_t CONTROL;
  volatile uint32_t STATUS;
  volatile uint32_t BITTMNG;
       uint32_t RESERVED0;
  volatile uint32_t INT_EN;
       uint32_t RESERVED1[2];
  volatile uint32_t OVER;
  volatile uint32_t RXID;
  volatile uint32_t RXDLC;
  volatile uint32_t RXDATAL;
  volatile uint32_t RXDATAH;
  volatile uint32_t TXID;
  volatile uint32_t TXDLC;
  volatile uint32_t DATAL;
  volatile uint32_t DATAH;
  volatile uint32_t BUF_CON[32];
  volatile uint32_t INT_RX;
  volatile uint32_t RX;
  volatile uint32_t INT_TX;
  volatile uint32_t TX;
       uint32_t RESERVED2[76];
    MDR_CAN_BUF_TypeDef CAN_BUF[32];
       uint32_t RESERVED3[64];
    MDR_CAN_BUF_FILTER_TypeDef CAN_BUF_FILTER[32];
}MDR_CAN_TypeDef;
# 389 "./CMSIS/MDR32Fx/DeviceSupport/MDR1986VE9x/inc\\MDR32Fx.h"
typedef struct
{
  volatile uint32_t CTRL;
  volatile uint32_t STS;
  volatile uint32_t TS;
  volatile uint32_t NTS;
}MDR_USB_SEP_TypeDef;


typedef struct
{
  volatile uint32_t RXFD;
       uint32_t RESERVED0;
  volatile uint32_t RXFDC_L;
  volatile uint32_t RXFDC_H;
  volatile uint32_t RXFC;
       uint32_t RESERVED1[11];
  volatile uint32_t TXFD;
       uint32_t RESERVED2[3];
  volatile uint32_t TXFDC;
       uint32_t RESERVED3[11];
}MDR_USB_SEP_FIFO_TypeDef;


typedef struct
{
  volatile uint32_t HTXC;
  volatile uint32_t HTXT;
  volatile uint32_t HTXLC;
  volatile uint32_t HTXSE;
  volatile uint32_t HTXA;
  volatile uint32_t HTXE;
  volatile uint32_t HFN_L;
  volatile uint32_t HFN_H;
  volatile uint32_t HIS;
  volatile uint32_t HIM;
  volatile uint32_t HRXS;
  volatile uint32_t HRXP;
  volatile uint32_t HRXA;
  volatile uint32_t HRXE;
  volatile uint32_t HRXCS;
  volatile uint32_t HSTM;
       uint32_t RESERVED0[16];
  volatile uint32_t HRXFD;
       uint32_t RESERVED1;
  volatile uint32_t HRXFDC_L;
  volatile uint32_t HRXFDC_H;
  volatile uint32_t HRXFC;
       uint32_t RESERVED2[11];
  volatile uint32_t HTXFD;
       uint32_t RESERVED3[3];
  volatile uint32_t HTXFC;
       uint32_t RESERVED4[11];
    MDR_USB_SEP_TypeDef USB_SEP[4];
  volatile uint32_t SC;
  volatile uint32_t SLS;
  volatile uint32_t SIS;
  volatile uint32_t SIM;
  volatile uint32_t SA;
  volatile uint32_t SFN_L;
  volatile uint32_t SFN_H;
       uint32_t RESERVED5[9];
    MDR_USB_SEP_FIFO_TypeDef USB_SEP_FIFO[4];
  volatile uint32_t HSCR;
  volatile uint32_t HSVR;
}MDR_USB_TypeDef;
# 731 "./CMSIS/MDR32Fx/DeviceSupport/MDR1986VE9x/inc\\MDR32Fx.h"
typedef struct
{
  volatile uint32_t CMD;
  volatile uint32_t ADR;
  volatile uint32_t DI;
  volatile uint32_t DO;
  volatile uint32_t KEY;
}MDR_EEPROM_TypeDef;
# 790 "./CMSIS/MDR32Fx/DeviceSupport/MDR1986VE9x/inc\\MDR32Fx.h"
typedef struct
{
  volatile uint32_t CLOCK_STATUS;
  volatile uint32_t PLL_CONTROL;
  volatile uint32_t HS_CONTROL;
  volatile uint32_t CPU_CLOCK;
  volatile uint32_t USB_CLOCK;
  volatile uint32_t ADC_MCO_CLOCK;
  volatile uint32_t RTC_CLOCK;
  volatile uint32_t PER_CLOCK;
  volatile uint32_t CAN_CLOCK;
  volatile uint32_t TIM_CLOCK;
  volatile uint32_t UART_CLOCK;
  volatile uint32_t SSP_CLOCK;
}MDR_RST_CLK_TypeDef;
# 1046 "./CMSIS/MDR32Fx/DeviceSupport/MDR1986VE9x/inc\\MDR32Fx.h"
typedef struct
{
  volatile uint32_t STATUS;
  volatile uint32_t CFG;
  volatile uint32_t CTRL_BASE_PTR;
  volatile uint32_t ALT_CTRL_BASE_PTR;
  volatile uint32_t WAITONREQ_STATUS;
  volatile uint32_t CHNL_SW_REQUEST;
  volatile uint32_t CHNL_USEBURST_SET;
  volatile uint32_t CHNL_USEBURST_CLR;
  volatile uint32_t CHNL_REQ_MASK_SET;
  volatile uint32_t CHNL_REQ_MASK_CLR;
  volatile uint32_t CHNL_ENABLE_SET;
  volatile uint32_t CHNL_ENABLE_CLR;
  volatile uint32_t CHNL_PRI_ALT_SET;
  volatile uint32_t CHNL_PRI_ALT_CLR;
  volatile uint32_t CHNL_PRIORITY_SET;
  volatile uint32_t CHNL_PRIORITY_CLR;
       uint32_t RESERVED0[3];
  volatile uint32_t ERR_CLR;
}MDR_DMA_TypeDef;
# 1121 "./CMSIS/MDR32Fx/DeviceSupport/MDR1986VE9x/inc\\MDR32Fx.h"
typedef struct
{
  volatile uint32_t DR;
  volatile uint32_t RSR_ECR;
       uint32_t RESERVED0[4];
  volatile uint32_t FR;
       uint32_t RESERVED1;
  volatile uint32_t ILPR;
  volatile uint32_t IBRD;
  volatile uint32_t FBRD;
  volatile uint32_t LCR_H;
  volatile uint32_t CR;
  volatile uint32_t IFLS;
  volatile uint32_t IMSC;
  volatile uint32_t RIS;
  volatile uint32_t MIS;
  volatile uint32_t ICR;
  volatile uint32_t DMACR;
}MDR_UART_TypeDef;
# 1453 "./CMSIS/MDR32Fx/DeviceSupport/MDR1986VE9x/inc\\MDR32Fx.h"
typedef struct
{
  volatile uint32_t CR0;
  volatile uint32_t CR1;
  volatile uint32_t DR;
  volatile uint32_t SR;
  volatile uint32_t CPSR;
  volatile uint32_t IMSC;
  volatile uint32_t RIS;
  volatile uint32_t MIS;
  volatile uint32_t ICR;
  volatile uint32_t DMACR;
}MDR_SSP_TypeDef;
# 1634 "./CMSIS/MDR32Fx/DeviceSupport/MDR1986VE9x/inc\\MDR32Fx.h"
typedef struct
{
  volatile uint32_t PRL;
  volatile uint32_t PRH;
  volatile uint32_t CTR;
  volatile uint32_t RXD;
  volatile uint32_t STA;
  volatile uint32_t TXD;
  volatile uint32_t CMD;
}MDR_I2C_TypeDef;
# 1725 "./CMSIS/MDR32Fx/DeviceSupport/MDR1986VE9x/inc\\MDR32Fx.h"
typedef struct
{
  volatile uint32_t PVDCS;
}MDR_POWER_TypeDef;
# 1778 "./CMSIS/MDR32Fx/DeviceSupport/MDR1986VE9x/inc\\MDR32Fx.h"
typedef struct
{
  volatile uint32_t CR;
  volatile uint32_t CFR;
  volatile uint32_t SR;
}MDR_WWDG_TypeDef;
# 1836 "./CMSIS/MDR32Fx/DeviceSupport/MDR1986VE9x/inc\\MDR32Fx.h"
typedef struct
{
  volatile uint32_t KR;
  volatile uint32_t PR;
  volatile uint32_t RLR;
  volatile uint32_t SR;
}MDR_IWDG_TypeDef;
# 1878 "./CMSIS/MDR32Fx/DeviceSupport/MDR1986VE9x/inc\\MDR32Fx.h"
typedef struct
{
  volatile uint32_t CNT;
  volatile uint32_t PSG;
  volatile uint32_t ARR;
  volatile uint32_t CNTRL;
  volatile uint32_t CCR1;
  volatile uint32_t CCR2;
  volatile uint32_t CCR3;
  volatile uint32_t CCR4;
  volatile uint32_t CH1_CNTRL;
  volatile uint32_t CH2_CNTRL;
  volatile uint32_t CH3_CNTRL;
  volatile uint32_t CH4_CNTRL;
  volatile uint32_t CH1_CNTRL1;
  volatile uint32_t CH2_CNTRL1;
  volatile uint32_t CH3_CNTRL1;
  volatile uint32_t CH4_CNTRL1;
  volatile uint32_t CH1_DTG;
  volatile uint32_t CH2_DTG;
  volatile uint32_t CH3_DTG;
  volatile uint32_t CH4_DTG;
  volatile uint32_t BRKETR_CNTRL;
  volatile uint32_t STATUS;
  volatile uint32_t IE;
  volatile uint32_t DMA_RE;
  volatile uint32_t CH1_CNTRL2;
  volatile uint32_t CH2_CNTRL2;
  volatile uint32_t CH3_CNTRL2;
  volatile uint32_t CH4_CNTRL2;
  volatile uint32_t CCR11;
  volatile uint32_t CCR21;
  volatile uint32_t CCR31;
  volatile uint32_t CCR41;
}MDR_TIMER_TypeDef;
# 2144 "./CMSIS/MDR32Fx/DeviceSupport/MDR1986VE9x/inc\\MDR32Fx.h"
typedef struct
{
  volatile uint32_t ADC1_CFG;
  volatile uint32_t ADC2_CFG;
  volatile uint32_t ADC1_H_LEVEL;
  volatile uint32_t ADC2_H_LEVEL;
  volatile uint32_t ADC1_L_LEVEL;
  volatile uint32_t ADC2_L_LEVEL;
  volatile uint32_t ADC1_RESULT;
  volatile uint32_t ADC2_RESULT;
  volatile uint32_t ADC1_STATUS;
  volatile uint32_t ADC2_STATUS;
  volatile uint32_t ADC1_CHSEL;
  volatile uint32_t ADC2_CHSEL;
}MDR_ADC_TypeDef;
# 2297 "./CMSIS/MDR32Fx/DeviceSupport/MDR1986VE9x/inc\\MDR32Fx.h"
typedef struct
{
  volatile uint32_t CFG;
  volatile uint32_t DAC1_DATA;
  volatile uint32_t DAC2_DATA;
}MDR_DAC_TypeDef;
# 2374 "./CMSIS/MDR32Fx/DeviceSupport/MDR1986VE9x/inc\\MDR32Fx.h"
typedef struct
{
  volatile uint32_t CFG;
  volatile uint32_t RESULT;
  volatile uint32_t RESULT_LATCH;
}MDR_COMP_TypeDef;
# 2448 "./CMSIS/MDR32Fx/DeviceSupport/MDR1986VE9x/inc\\MDR32Fx.h"
typedef struct
{
  volatile uint32_t RXTX;
  volatile uint32_t OE;
  volatile uint32_t FUNC;
  volatile uint32_t ANALOG;
  volatile uint32_t PULL;
  volatile uint32_t PD;
  volatile uint32_t PWR;
  volatile uint32_t GFEN;
}MDR_PORT_TypeDef;
# 2595 "./CMSIS/MDR32Fx/DeviceSupport/MDR1986VE9x/inc\\MDR32Fx.h"
typedef struct
{
  volatile uint32_t REG_00;
  volatile uint32_t REG_01;
  volatile uint32_t REG_02;
  volatile uint32_t REG_03;
  volatile uint32_t REG_04;
  volatile uint32_t REG_05;
  volatile uint32_t REG_06;
  volatile uint32_t REG_07;
  volatile uint32_t REG_08;
  volatile uint32_t REG_09;
  volatile uint32_t REG_0A;
  volatile uint32_t REG_0B;
  volatile uint32_t REG_0C;
  volatile uint32_t REG_0D;
  volatile uint32_t REG_0E;
  volatile uint32_t REG_0F;
  volatile uint32_t RTC_CNT;
  volatile uint32_t RTC_DIV;
  volatile uint32_t RTC_PRL;
  volatile uint32_t RTC_ALRM;
  volatile uint32_t RTC_CS;
}MDR_BKP_TypeDef;
# 2732 "./CMSIS/MDR32Fx/DeviceSupport/MDR1986VE9x/inc\\MDR32Fx.h"
typedef struct
{
       uint32_t RESERVED0[20];
  volatile uint32_t NAND_CYCLES;
  volatile uint32_t CONTROL;



}MDR_EBC_TypeDef;
# 82 "./SPL/MDR32Fx\\MDR32F9Qx_config.h" 2
# 33 "./SPL/MDR32Fx/inc\\MDR32F9Qx_timer.h" 2
# 49 "./SPL/MDR32Fx/inc\\MDR32F9Qx_timer.h"
typedef enum
{
    TIMER_CntMode_ClkFixedDir = (((uint32_t)0x0) << 6),
    TIMER_CntMode_ClkChangeDir = (((uint32_t)0x1) << 6),
    TIMER_CntMode_EvtFixedDir = (((uint32_t)0x2) << 6),
    TIMER_CntMode_EvtChangeDir = (((uint32_t)0x3) << 6)
} TIMER_Counter_Mode_TypeDef;
# 65 "./SPL/MDR32Fx/inc\\MDR32F9Qx_timer.h"
typedef enum
{
    TIMER_CntDir_Up = (((uint32_t)0x0) << 3),
    TIMER_CntDir_Dn = (((uint32_t)0x1) << 3)
} TIMER_Counter_Dir_TypeDef;







typedef enum
{
    TIMER_EvSrc_TIM_CLK = (((uint32_t)0x0) << 8),
    TIMER_EvSrc_TM1 = (((uint32_t)0x1) << 8),
    TIMER_EvSrc_TM2 = (((uint32_t)0x2) << 8),
    TIMER_EvSrc_TM3 = (((uint32_t)0x3) << 8),
    TIMER_EvSrc_CH1 = (((uint32_t)0x4) << 8),
    TIMER_EvSrc_CH2 = (((uint32_t)0x5) << 8),
    TIMER_EvSrc_CH3 = (((uint32_t)0x6) << 8),
    TIMER_EvSrc_CH4 = (((uint32_t)0x7) << 8),
    TIMER_EvSrc_ETR = (((uint32_t)0x8) << 8)
} TIMER_Event_Src_TypeDef;
# 108 "./SPL/MDR32Fx/inc\\MDR32F9Qx_timer.h"
typedef enum
{
    TIMER_FDTS_TIMER_CLK_div_1 = (((uint32_t)0x0) << 4),
    TIMER_FDTS_TIMER_CLK_div_2 = (((uint32_t)0x1) << 4),
    TIMER_FDTS_TIMER_CLK_div_3 = (((uint32_t)0x2) << 4),
    TIMER_FDTS_TIMER_CLK_div_4 = (((uint32_t)0x3) << 4)
} TIMER_Filter_Sampl_Clk_TypeDef;
# 124 "./SPL/MDR32Fx/inc\\MDR32F9Qx_timer.h"
typedef enum
{
    TIMER_ARR_Update_Immediately = (((uint32_t)0x0) << 1),
    TIMER_ARR_Update_On_CNT_Overflow = (((uint32_t)0x1) << 1)
} TIMER_ARR_Update_Mode_TypeDef;







typedef enum
{
    TIMER_Filter_1FF_at_TIMER_CLK = ((uint32_t)0x0),
    TIMER_Filter_2FF_at_TIMER_CLK = ((uint32_t)0x1),
    TIMER_Filter_4FF_at_TIMER_CLK = ((uint32_t)0x2),
    TIMER_Filter_8FF_at_TIMER_CLK = ((uint32_t)0x3),
    TIMER_Filter_6FF_at_FTDS_div_2 = ((uint32_t)0x4),
    TIMER_Filter_8FF_at_FTDS_div_2 = ((uint32_t)0x5),
    TIMER_Filter_6FF_at_FTDS_div_4 = ((uint32_t)0x6),
    TIMER_Filter_8FF_at_FTDS_div_4 = ((uint32_t)0x7),
    TIMER_Filter_6FF_at_FTDS_div_8 = ((uint32_t)0x8),
    TIMER_Filter_8FF_at_FTDS_div_8 = ((uint32_t)0x9),
    TIMER_Filter_5FF_at_FTDS_div_16 = ((uint32_t)0xA),
    TIMER_Filter_6FF_at_FTDS_div_16 = ((uint32_t)0xB),
    TIMER_Filter_8FF_at_FTDS_div_16 = ((uint32_t)0xC),
    TIMER_Filter_5FF_at_FTDS_div_32 = ((uint32_t)0xD),
    TIMER_Filter_6FF_at_FTDS_div_32 = ((uint32_t)0xE),
    TIMER_Filter_8FF_at_FTDS_div_32 = ((uint32_t)0xF)
} TIMER_Filter_Config_TypeDef;
# 176 "./SPL/MDR32Fx/inc\\MDR32F9Qx_timer.h"
typedef enum
{
    TIMER_ETR_Prescaler_None = (((uint32_t)0x0) << 2),
    TIMER_ETR_Prescaler_div_2 = (((uint32_t)0x1) << 2),
    TIMER_ETR_Prescaler_div_4 = (((uint32_t)0x2) << 2),
    TIMER_ETR_Prescaler_div_8 = (((uint32_t)0x3) << 2)
} TIMER_ETR_Prescaler_TypeDef;
# 192 "./SPL/MDR32Fx/inc\\MDR32F9Qx_timer.h"
typedef enum
{
   TIMER_ETRPolarity_NonInverted = (((uint32_t)0x0) << 1),
   TIMER_ETRPolarity_Inverted = (((uint32_t)0x1) << 1)
} TIMER_ETR_Polarity_TypeDef;







typedef enum
{
    TIMER_BRKPolarity_NonInverted = (((uint32_t)0x0) << 0),
    TIMER_BRKPolarity_Inverted = (((uint32_t)0x1) << 0)
} TIMER_BRK_Polarity_TypeDef;







typedef enum
{
    TIMER_CHANNEL1 = ((uint32_t)0x0),
    TIMER_CHANNEL2 = ((uint32_t)0x1),
    TIMER_CHANNEL3 = ((uint32_t)0x2),
    TIMER_CHANNEL4 = ((uint32_t)0x3)
} TIMER_Channel_Number_TypeDef;
# 232 "./SPL/MDR32Fx/inc\\MDR32F9Qx_timer.h"
typedef enum
{
    TIMER_CH_MODE_PWM = (((uint32_t)0x0) << 15),
    TIMER_CH_MODE_CAPTURE = (((uint32_t)0x1) << 15)
} TIMER_CH_Mode_TypeDef;







typedef enum
{
    TIMER_CH_ETR_RESET_Disable = (((uint32_t)0x0) << 13),
    TIMER_CH_ETR_RESET_Enable = (((uint32_t)0x1) << 13)
} TIMER_CH_ETR_RESET_TypeDef;







typedef enum
{
    TIMER_CH_BRK_RESET_Disable = (((uint32_t)0x0) << 12),
    TIMER_CH_BRK_RESET_Enable = (((uint32_t)0x1) << 12)
} TIMER_CH_BRK_RESET_TypeDef;







typedef enum
{
    TIMER_CH_REF_Format0 = (((uint32_t)0x0) << 9),
    TIMER_CH_REF_Format1 = (((uint32_t)0x1) << 9),



    TIMER_CH_REF_Format2 = (((uint32_t)0x2) << 9),



    TIMER_CH_REF_Format3 = (((uint32_t)0x3) << 9),


    TIMER_CH_REF_Format4 = (((uint32_t)0x4) << 9),
    TIMER_CH_REF_Format5 = (((uint32_t)0x5) << 9),
    TIMER_CH_REF_Format6 = (((uint32_t)0x6) << 9),



    TIMER_CH_REF_Format7 = (((uint32_t)0x7) << 9)



} TIMER_CH_REF_Format_TypeDef;
# 306 "./SPL/MDR32Fx/inc\\MDR32F9Qx_timer.h"
typedef enum
{
    TIMER_CH_Prescaler_None = ((uint32_t)0x0),
    TIMER_CH_Prescaler_div_2 = ((uint32_t)0x1),
    TIMER_CH_Prescaler_div_4 = ((uint32_t)0x2),
    TIMER_CH_Prescaler_div_8 = ((uint32_t)0x3)
} TIMER_CH_Prescaler_TypeDef;
# 322 "./SPL/MDR32Fx/inc\\MDR32F9Qx_timer.h"
typedef enum
{
    TIMER_CH_EvSrc_PE = (((uint32_t)0x0) << 4),
    TIMER_CH_EvSrc_NE = (((uint32_t)0x1) << 4),
    TIMER_CH_EvSrc_PE_OC1 = (((uint32_t)0x2) << 4),
    TIMER_CH_EvSrc_PE_OC2 = (((uint32_t)0x3) << 4)
} TIMER_CH_Event_Src_TypeDef;
# 338 "./SPL/MDR32Fx/inc\\MDR32F9Qx_timer.h"
typedef enum
{
    TIMER_CH_CCR1EvSrc_PE = (((uint32_t)0x0) << 0),
    TIMER_CH_CCR1EvSrc_NE = (((uint32_t)0x1) << 0),
    TIMER_CH_CCR1EvSrc_NE_OC1 = (((uint32_t)0x2) << 0),
    TIMER_CH_CCR1EvSrc_NE_OC2 = (((uint32_t)0x3) << 0)
} TIMER_CH_CCR1_Event_Src_TypeDef;
# 354 "./SPL/MDR32Fx/inc\\MDR32F9Qx_timer.h"
typedef enum
{
    TIMER_CH_CCR_Update_Immediately = (((uint32_t)0x0) << 3),
    TIMER_CH_CCR_Update_On_CNT_eq_0 = (((uint32_t)0x1) << 3)
} TIMER_CH_CCR_Update_Mode_TypeDef;







typedef enum
{
    TIMER_CHOPolarity_NonInverted = ((uint32_t)0x0),
    TIMER_CHOPolarity_Inverted = ((uint32_t)0x1)
} TIMER_CH_OUT_Polarity_TypeDef;







typedef enum
{
    TIMER_CH_OutSrc_Only_0 = ((uint32_t)0x0),
    TIMER_CH_OutSrc_Only_1 = ((uint32_t)0x1),
    TIMER_CH_OutSrc_REF = ((uint32_t)0x2),
    TIMER_CH_OutSrc_DTG = ((uint32_t)0x3)
} TIMER_CH_OUT_Src_TypeDef;
# 394 "./SPL/MDR32Fx/inc\\MDR32F9Qx_timer.h"
typedef enum
{
    TIMER_CH_OutMode_Input = ((uint32_t)0x0),
    TIMER_CH_OutMode_Output = ((uint32_t)0x1),
    TIMER_CH_OutMode_REF_as_OE = ((uint32_t)0x2),
    TIMER_CH_OutMode_DTG_as_OE = ((uint32_t)0x3)
} TIMER_CH_OUT_Mode_TypeDef;
# 410 "./SPL/MDR32Fx/inc\\MDR32F9Qx_timer.h"
typedef enum
{
    TIMER_CH_DTG_ClkSrc_TIMER_CLK = (((uint32_t)0x0) << 4),
    TIMER_CH_DTG_ClkSrc_FDTS = (((uint32_t)0x1) << 4)
} TIMER_CH_DTG_Clk_Src_TypeDef;







typedef enum
{
    TIMER_STATUS_CNT_ZERO = (((uint32_t)0x1) << 0),
    TIMER_STATUS_CNT_ARR = (((uint32_t)0x1) << 1),
    TIMER_STATUS_ETR_RISING_EDGE = (((uint32_t)0x1) << 2),
    TIMER_STATUS_ETR_FALLING_EDGE = (((uint32_t)0x1) << 3),
    TIMER_STATUS_BRK = (((uint32_t)0x1) << 4),
    TIMER_STATUS_CCR_CAP_CH1 = (((uint32_t)0x1) << 5),
    TIMER_STATUS_CCR_CAP_CH2 = (((uint32_t)0x1) << 6),
    TIMER_STATUS_CCR_CAP_CH3 = (((uint32_t)0x1) << 7),
    TIMER_STATUS_CCR_CAP_CH4 = (((uint32_t)0x1) << 8),
    TIMER_STATUS_CCR_REF_CH1 = (((uint32_t)0x1) << 9),
    TIMER_STATUS_CCR_REF_CH2 = (((uint32_t)0x1) << 10),
    TIMER_STATUS_CCR_REF_CH3 = (((uint32_t)0x1) << 11),
    TIMER_STATUS_CCR_REF_CH4 = (((uint32_t)0x1) << 12),
    TIMER_STATUS_CCR_CAP1_CH1 = (((uint32_t)0x1) << 13),
    TIMER_STATUS_CCR_CAP1_CH2 = (((uint32_t)0x1) << 14),
    TIMER_STATUS_CCR_CAP1_CH3 = (((uint32_t)0x1) << 15),
    TIMER_STATUS_CCR_CAP1_CH4 = (((uint32_t)0x1) << 16)
} TIMER_Status_Flags_TypeDef;
# 506 "./SPL/MDR32Fx/inc\\MDR32F9Qx_timer.h"
typedef enum
{
    TIMER_HCLKdiv1 = ((uint32_t)0x00),
    TIMER_HCLKdiv2 = ((uint32_t)0x01),
    TIMER_HCLKdiv4 = ((uint32_t)0x02),
    TIMER_HCLKdiv8 = ((uint32_t)0x03),
    TIMER_HCLKdiv16 = ((uint32_t)0x04),
    TIMER_HCLKdiv32 = ((uint32_t)0x05),
    TIMER_HCLKdiv64 = ((uint32_t)0x06),
    TIMER_HCLKdiv128 = ((uint32_t)0x07)
} TIMER_Clock_BRG_TypeDef;
# 531 "./SPL/MDR32Fx/inc\\MDR32F9Qx_timer.h"
typedef struct
{

    uint16_t TIMER_IniCounter;





    uint16_t TIMER_Prescaler;



    uint16_t TIMER_Period;







    uint16_t TIMER_CounterMode;

    uint16_t TIMER_CounterDirection;

    uint16_t TIMER_EventSource;

    uint16_t TIMER_FilterSampling;

    uint16_t TIMER_ARR_UpdateMode;

    uint16_t TIMER_ETR_FilterConf;

    uint16_t TIMER_ETR_Prescaler;

    uint16_t TIMER_ETR_Polarity;

    uint16_t TIMER_BRK_Polarity;

} TIMER_CntInitTypeDef;




typedef struct
{
    uint16_t TIMER_CH_Number;

    uint16_t TIMER_CH_Mode;

    uint16_t TIMER_CH_ETR_Ena;

    uint16_t TIMER_CH_ETR_Reset;

    uint16_t TIMER_CH_BRK_Reset;

    uint16_t TIMER_CH_REF_Format;

    uint16_t TIMER_CH_Prescaler;

    uint16_t TIMER_CH_EventSource;

    uint16_t TIMER_CH_FilterConf;

    uint16_t TIMER_CH_CCR_UpdateMode;

    uint16_t TIMER_CH_CCR1_Ena;

    uint16_t TIMER_CH_CCR1_EventSource;

} TIMER_ChnInitTypeDef;




typedef struct
{
    uint16_t TIMER_CH_Number;

    uint16_t TIMER_CH_DirOut_Polarity;

    uint16_t TIMER_CH_DirOut_Source;

    uint16_t TIMER_CH_DirOut_Mode;

    uint16_t TIMER_CH_NegOut_Polarity;

    uint16_t TIMER_CH_NegOut_Source;

    uint16_t TIMER_CH_NegOut_Mode;

    uint16_t TIMER_CH_DTG_MainPrescaler;


    uint16_t TIMER_CH_DTG_AuxPrescaler;


    uint16_t TIMER_CH_DTG_ClockSource;

} TIMER_ChnOutInitTypeDef;
# 669 "./SPL/MDR32Fx/inc\\MDR32F9Qx_timer.h"
void TIMER_DeInit(MDR_TIMER_TypeDef* TIMERx);

void TIMER_CntInit(MDR_TIMER_TypeDef* TIMERx, const TIMER_CntInitTypeDef* TIMER_CntInitStruct);
void TIMER_CntStructInit(TIMER_CntInitTypeDef* TIMER_CntInitStruct);

void TIMER_Cmd(MDR_TIMER_TypeDef* TIMERx, FunctionalState NewState);





    void TIMER_SetCounter(MDR_TIMER_TypeDef* TIMERx, uint16_t Counter);
    uint16_t TIMER_GetCounter(MDR_TIMER_TypeDef* TIMERx);


void TIMER_SetCntPrescaler(MDR_TIMER_TypeDef* TIMERx, uint16_t Prescaler);
uint16_t TIMER_GetCntPrescaler(MDR_TIMER_TypeDef* TIMERx);






    void TIMER_SetCntAutoreload(MDR_TIMER_TypeDef* TIMERx, uint16_t Autoreload);
    void TIMER_CntAutoreloadConfig(MDR_TIMER_TypeDef* TIMERx, uint16_t Autoreload, TIMER_ARR_Update_Mode_TypeDef UpdateMode);
    uint16_t TIMER_GetCntAutoreload(MDR_TIMER_TypeDef* TIMERx);


void TIMER_CntEventSourceConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_Event_Src_TypeDef EventSource);
void TIMER_FilterSamplingConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_Filter_Sampl_Clk_TypeDef Prescaler);
void TIMER_CounterModeConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_Counter_Mode_TypeDef Mode);
void TIMER_SetCounterDirection(MDR_TIMER_TypeDef* TIMERx, TIMER_Counter_Dir_TypeDef Direction);
void TIMER_ETRInputConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_ETR_Prescaler_TypeDef Prescaler, TIMER_ETR_Polarity_TypeDef Polarity, TIMER_Filter_Config_TypeDef Filter);
void TIMER_ETRFilterConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_Filter_Config_TypeDef Filter);
void TIMER_ETRPrescalerConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_ETR_Prescaler_TypeDef Prescaler);
void TIMER_ETRPolarityConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_ETR_Polarity_TypeDef Polarity);
void TIMER_BRKPolarityConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_BRK_Polarity_TypeDef Polarity);
TIMER_Counter_Dir_TypeDef TIMER_GetCounterDirection(MDR_TIMER_TypeDef* TIMERx);
FlagStatus TIMER_GetCntWriteComplete(MDR_TIMER_TypeDef* TIMERx);

void TIMER_ChnInit(MDR_TIMER_TypeDef* TIMERx, const TIMER_ChnInitTypeDef* TIMER_ChnInitStruct);
void TIMER_ChnStructInit(TIMER_ChnInitTypeDef* TIMER_ChnInitStruct);






    void TIMER_SetChnCompare(MDR_TIMER_TypeDef* TIMERx, TIMER_Channel_Number_TypeDef Channel, uint16_t Compare);
    void TIMER_ChnCompareConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_Channel_Number_TypeDef Channel, uint16_t Compare, TIMER_CH_CCR_Update_Mode_TypeDef UpdateMode);
    uint16_t TIMER_GetChnCapture(MDR_TIMER_TypeDef* TIMERx, TIMER_Channel_Number_TypeDef Channel);







    void TIMER_SetChnCompare1(MDR_TIMER_TypeDef* TIMERx, TIMER_Channel_Number_TypeDef Channel, uint16_t Compare);
    void TIMER_ChnCompare1Config(MDR_TIMER_TypeDef* TIMERx, TIMER_Channel_Number_TypeDef Channel, uint16_t Compare, TIMER_CH_CCR_Update_Mode_TypeDef UpdateMode);
    uint16_t TIMER_GetChnCapture1(MDR_TIMER_TypeDef* TIMERx, TIMER_Channel_Number_TypeDef Channel);


void TIMER_ChnETR_Cmd(MDR_TIMER_TypeDef* TIMERx, TIMER_Channel_Number_TypeDef Channel, FunctionalState NewState);
void TIMER_ChnETRResetConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_Channel_Number_TypeDef Channel, TIMER_CH_ETR_RESET_TypeDef NewState);
void TIMER_ChnBRKResetConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_Channel_Number_TypeDef Channel, TIMER_CH_BRK_RESET_TypeDef NewState);
void TIMER_ChnREFFormatConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_Channel_Number_TypeDef Channel, TIMER_CH_REF_Format_TypeDef Format);
void TIMER_ChnCapturePrescalerConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_Channel_Number_TypeDef Channel, TIMER_CH_Prescaler_TypeDef Prescaler);
void TIMER_ChnEventSourceConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_Channel_Number_TypeDef Channel, TIMER_CH_Event_Src_TypeDef EventSource);
void TIMER_ChnFilterConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_Channel_Number_TypeDef Channel, TIMER_Filter_Config_TypeDef Filter);
FlagStatus TIMER_GetChnWriteComplete(MDR_TIMER_TypeDef* TIMERx, TIMER_Channel_Number_TypeDef Channel);
void TIMER_ChnCCR1_EventSourceConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_Channel_Number_TypeDef Channel, TIMER_CH_CCR1_Event_Src_TypeDef EventSource);
void TIMER_ChnCCR1_Cmd(MDR_TIMER_TypeDef* TIMERx, TIMER_Channel_Number_TypeDef Channel, FunctionalState NewState);

void TIMER_ChnOutInit(MDR_TIMER_TypeDef* TIMERx, const TIMER_ChnOutInitTypeDef* TIMER_ChnOutInitStruct);
void TIMER_ChnOutStructInit(TIMER_ChnOutInitTypeDef* TIMER_ChnOutInitStruct);
void TIMER_ChnOutConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_Channel_Number_TypeDef Channel, TIMER_CH_OUT_Src_TypeDef OutSource, TIMER_CH_OUT_Mode_TypeDef Mode, TIMER_CH_OUT_Polarity_TypeDef Polarity);
void TIMER_ChnOutSourceConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_Channel_Number_TypeDef Channel, TIMER_CH_OUT_Src_TypeDef OutSource);
void TIMER_ChnOutModeConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_Channel_Number_TypeDef Channel, TIMER_CH_OUT_Mode_TypeDef Mode);
void TIMER_ChnOutPolarityConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_Channel_Number_TypeDef Channel, TIMER_CH_OUT_Polarity_TypeDef Polarity);
void TIMER_ChnNOutConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_Channel_Number_TypeDef Channel, TIMER_CH_OUT_Src_TypeDef OutSource, TIMER_CH_OUT_Mode_TypeDef Mode, TIMER_CH_OUT_Polarity_TypeDef Polarity);
void TIMER_ChnNOutSourceConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_Channel_Number_TypeDef Channel, TIMER_CH_OUT_Src_TypeDef OutSource);
void TIMER_ChnNOutModeConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_Channel_Number_TypeDef Channel, TIMER_CH_OUT_Mode_TypeDef Mode);
void TIMER_ChnNOutPolarityConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_Channel_Number_TypeDef Channel, TIMER_CH_OUT_Polarity_TypeDef Polarity);
void TIMER_ChnOutDTGConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_Channel_Number_TypeDef Channel, uint32_t MainPrescaler, uint32_t AuxPrescaler, TIMER_CH_DTG_Clk_Src_TypeDef ClockSource);

uint32_t TIMER_GetStatus(MDR_TIMER_TypeDef* TIMERx);
FlagStatus TIMER_GetFlagStatus(MDR_TIMER_TypeDef* TIMERx, TIMER_Status_Flags_TypeDef Flag);
void TIMER_ClearFlag(MDR_TIMER_TypeDef* TIMERx, uint32_t Flags);



    void TIMER_DMACmd(MDR_TIMER_TypeDef* TIMERx, uint32_t TIMER_DMASource, FunctionalState NewState);


void TIMER_ITConfig(MDR_TIMER_TypeDef* TIMERx, uint32_t TIMER_IT, FunctionalState NewState);
ITStatus TIMER_GetITStatus(MDR_TIMER_TypeDef* TIMERx, TIMER_Status_Flags_TypeDef TIMER_IT);

void TIMER_BRGInit(MDR_TIMER_TypeDef* TIMERx, TIMER_Clock_BRG_TypeDef TIMER_BRG);
# 24 "SPL/MDR32Fx/src/MDR32F9Qx_timer.c" 2
# 62 "SPL/MDR32Fx/src/MDR32F9Qx_timer.c"
void TIMER_DeInit(MDR_TIMER_TypeDef* TIMERx)
{

    ((void)0U);

    TIMERx->CNTRL = 0;
    TIMERx->CNT = 0;
    TIMERx->PSG = 0;
    TIMERx->ARR = 0;

    TIMERx->CH1_CNTRL = 0;
    TIMERx->CH2_CNTRL = 0;
    TIMERx->CH3_CNTRL = 0;
    TIMERx->CH4_CNTRL = 0;
    TIMERx->CH1_CNTRL1 = 0;
    TIMERx->CH2_CNTRL1 = 0;
    TIMERx->CH3_CNTRL1 = 0;
    TIMERx->CH4_CNTRL1 = 0;
    TIMERx->CH1_CNTRL2 = 0;
    TIMERx->CH2_CNTRL2 = 0;
    TIMERx->CH3_CNTRL2 = 0;
    TIMERx->CH4_CNTRL2 = 0;

    TIMERx->CCR1 = 0;
    TIMERx->CCR2 = 0;
    TIMERx->CCR3 = 0;
    TIMERx->CCR4 = 0;
    TIMERx->CCR11 = 0;
    TIMERx->CCR21 = 0;
    TIMERx->CCR31 = 0;
    TIMERx->CCR41 = 0;
    TIMERx->CH1_DTG = 0;
    TIMERx->CH2_DTG = 0;
    TIMERx->CH3_DTG = 0;
    TIMERx->CH4_DTG = 0;
    TIMERx->BRKETR_CNTRL = 0;
    TIMERx->STATUS = 0;
    TIMERx->IE = 0;
    TIMERx->DMA_RE = 0;




}
# 118 "SPL/MDR32Fx/src/MDR32F9Qx_timer.c"
void TIMER_CntInit(MDR_TIMER_TypeDef* TIMERx, const TIMER_CntInitTypeDef* TIMER_CntInitStruct)
{
    uint32_t tmpreg_CNTRL;
    uint32_t tmpreg_BRKETR_CNTRL;


    ((void)0U);
    ((void)0U);
    ((void)0U);
    ((void)0U);
    ((void)0U);
    ((void)0U);
    ((void)0U);
    ((void)0U);
    ((void)0U);
    ((void)0U);

    TIMERx->CNT = TIMER_CntInitStruct->TIMER_IniCounter;
    TIMERx->PSG = TIMER_CntInitStruct->TIMER_Prescaler;
    TIMERx->ARR = TIMER_CntInitStruct->TIMER_Period;


    tmpreg_CNTRL = TIMER_CntInitStruct->TIMER_CounterMode
                 + TIMER_CntInitStruct->TIMER_CounterDirection
                 + TIMER_CntInitStruct->TIMER_EventSource
                 + TIMER_CntInitStruct->TIMER_FilterSampling
                 + TIMER_CntInitStruct->TIMER_ARR_UpdateMode;


    TIMERx->CNTRL = tmpreg_CNTRL;


    tmpreg_BRKETR_CNTRL = (TIMER_CntInitStruct->TIMER_ETR_FilterConf << 4)
                         + TIMER_CntInitStruct->TIMER_ETR_Prescaler
                         + TIMER_CntInitStruct->TIMER_ETR_Polarity
                         + TIMER_CntInitStruct->TIMER_BRK_Polarity;


    TIMERx->BRKETR_CNTRL = tmpreg_BRKETR_CNTRL;
}







void TIMER_CntStructInit(TIMER_CntInitTypeDef* TIMER_CntInitStruct)
{
    TIMER_CntInitStruct->TIMER_IniCounter = 0;
    TIMER_CntInitStruct->TIMER_Prescaler = 0;
    TIMER_CntInitStruct->TIMER_Period = 0;
    TIMER_CntInitStruct->TIMER_CounterMode = TIMER_CntMode_ClkFixedDir;
    TIMER_CntInitStruct->TIMER_CounterDirection = TIMER_CntDir_Up;
    TIMER_CntInitStruct->TIMER_EventSource = TIMER_EvSrc_TIM_CLK;
    TIMER_CntInitStruct->TIMER_FilterSampling = TIMER_FDTS_TIMER_CLK_div_1;
    TIMER_CntInitStruct->TIMER_ARR_UpdateMode = TIMER_ARR_Update_Immediately;
    TIMER_CntInitStruct->TIMER_ETR_FilterConf = TIMER_Filter_1FF_at_TIMER_CLK;
    TIMER_CntInitStruct->TIMER_ETR_Prescaler = TIMER_ETR_Prescaler_None;
    TIMER_CntInitStruct->TIMER_ETR_Polarity = TIMER_ETRPolarity_NonInverted;
    TIMER_CntInitStruct->TIMER_BRK_Polarity = TIMER_BRKPolarity_NonInverted;
}
# 190 "SPL/MDR32Fx/src/MDR32F9Qx_timer.c"
void TIMER_Cmd(MDR_TIMER_TypeDef* TIMERx, FunctionalState NewState)
{
    uint32_t tmpreg_CNTRL;


    ((void)0U);
    ((void)0U);

    tmpreg_CNTRL = TIMERx->CNTRL;


    if (NewState != DISABLE)
    {

        tmpreg_CNTRL |= ((uint32_t)0x00000001);
    }
    else
    {

        tmpreg_CNTRL &= ~((uint32_t)0x00000001);
    }


    TIMERx->CNTRL = tmpreg_CNTRL;
}
# 228 "SPL/MDR32Fx/src/MDR32F9Qx_timer.c"
void TIMER_SetCounter(MDR_TIMER_TypeDef* TIMERx, uint16_t Counter)

{

    ((void)0U);

    TIMERx->CNT = Counter;
}
# 248 "SPL/MDR32Fx/src/MDR32F9Qx_timer.c"
uint16_t TIMER_GetCounter(MDR_TIMER_TypeDef* TIMERx)

{

    ((void)0U);

    return TIMERx->CNT;
}
# 267 "SPL/MDR32Fx/src/MDR32F9Qx_timer.c"
void TIMER_SetCntPrescaler(MDR_TIMER_TypeDef* TIMERx, uint16_t Prescaler)
{

    ((void)0U);

    TIMERx->PSG = Prescaler;
}
# 283 "SPL/MDR32Fx/src/MDR32F9Qx_timer.c"
uint16_t TIMER_GetCntPrescaler(MDR_TIMER_TypeDef* TIMERx)
{

    ((void)0U);

    return (TIMERx->PSG);
}
# 303 "SPL/MDR32Fx/src/MDR32F9Qx_timer.c"
void TIMER_SetCntAutoreload(MDR_TIMER_TypeDef* TIMERx, uint16_t Autoreload)

{

    ((void)0U);

    TIMERx->ARR = Autoreload;
}
# 325 "SPL/MDR32Fx/src/MDR32F9Qx_timer.c"
void TIMER_CntAutoreloadConfig(MDR_TIMER_TypeDef* TIMERx, uint16_t Autoreload, TIMER_ARR_Update_Mode_TypeDef UpdateMode)

{
    uint32_t tmpreg_CNTRL;


    ((void)0U);
    ((void)0U);

    tmpreg_CNTRL = TIMERx->CNTRL;
    tmpreg_CNTRL &= ~((uint32_t)0x00000002);
    tmpreg_CNTRL += UpdateMode;

    TIMERx->CNTRL = tmpreg_CNTRL;

    TIMERx->ARR = Autoreload;
}
# 354 "SPL/MDR32Fx/src/MDR32F9Qx_timer.c"
uint16_t TIMER_GetCntAutoreload(MDR_TIMER_TypeDef* TIMERx)

{

    ((void)0U);

    return (TIMERx->ARR);
}
# 372 "SPL/MDR32Fx/src/MDR32F9Qx_timer.c"
void TIMER_CntEventSourceConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_Event_Src_TypeDef EventSource)
{
    uint32_t tmpreg_CNTRL;


    ((void)0U);
    ((void)0U);

    tmpreg_CNTRL = TIMERx->CNTRL;
    tmpreg_CNTRL &= ~((uint32_t)0x00000F00);
    tmpreg_CNTRL += (uint32_t)EventSource;

    TIMERx->CNTRL = tmpreg_CNTRL;
}
# 396 "SPL/MDR32Fx/src/MDR32F9Qx_timer.c"
void TIMER_FilterSamplingConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_Filter_Sampl_Clk_TypeDef Prescaler)
{
    uint32_t tmpreg_CNTRL;


    ((void)0U);
    ((void)0U);

    tmpreg_CNTRL = TIMERx->CNTRL;
    tmpreg_CNTRL &= ~((uint32_t)0x00000030);
    tmpreg_CNTRL += (uint32_t)Prescaler;

    TIMERx->CNTRL = tmpreg_CNTRL;
}
# 420 "SPL/MDR32Fx/src/MDR32F9Qx_timer.c"
void TIMER_CounterModeConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_Counter_Mode_TypeDef Mode)
{
    uint32_t tmpreg_CNTRL;


    ((void)0U);
    ((void)0U);

    tmpreg_CNTRL = TIMERx->CNTRL;
    tmpreg_CNTRL &= ~((uint32_t)0x000000C0);
    tmpreg_CNTRL += (uint32_t)Mode;

    TIMERx->CNTRL = tmpreg_CNTRL;
}
# 444 "SPL/MDR32Fx/src/MDR32F9Qx_timer.c"
void TIMER_SetCounterDirection(MDR_TIMER_TypeDef* TIMERx, TIMER_Counter_Dir_TypeDef Direction)
{
    uint32_t tmpreg_CNTRL;


    ((void)0U);
    ((void)0U);

    tmpreg_CNTRL = TIMERx->CNTRL;
    tmpreg_CNTRL &= ~((uint32_t)0x00000008);
    tmpreg_CNTRL += (uint32_t)Direction;

    TIMERx->CNTRL = tmpreg_CNTRL;
}
# 470 "SPL/MDR32Fx/src/MDR32F9Qx_timer.c"
void TIMER_ETRInputConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_ETR_Prescaler_TypeDef Prescaler, TIMER_ETR_Polarity_TypeDef Polarity, TIMER_Filter_Config_TypeDef Filter)
{
    uint32_t tmpreg_BRKETR_CNTRL;


    ((void)0U);
    ((void)0U);
    ((void)0U);
    ((void)0U);

    tmpreg_BRKETR_CNTRL = TIMERx->BRKETR_CNTRL;
    tmpreg_BRKETR_CNTRL &= ~(((uint32_t)0x0000000C) + ((uint32_t)0x00000002) + ((uint32_t)0x000000F0));
    tmpreg_BRKETR_CNTRL += (uint32_t)Prescaler + (uint32_t)Polarity + ((uint32_t)Filter << 4);

    TIMERx->BRKETR_CNTRL = tmpreg_BRKETR_CNTRL;
}
# 496 "SPL/MDR32Fx/src/MDR32F9Qx_timer.c"
void TIMER_ETRFilterConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_Filter_Config_TypeDef Filter)
{
    uint32_t tmpreg_BRKETR_CNTRL;


    ((void)0U);
    ((void)0U);

    tmpreg_BRKETR_CNTRL = TIMERx->BRKETR_CNTRL;
    tmpreg_BRKETR_CNTRL &= ~((uint32_t)0x000000F0);
    tmpreg_BRKETR_CNTRL += (uint32_t)Filter << 4;

    TIMERx->BRKETR_CNTRL = tmpreg_BRKETR_CNTRL;
}
# 520 "SPL/MDR32Fx/src/MDR32F9Qx_timer.c"
void TIMER_ETRPrescalerConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_ETR_Prescaler_TypeDef Prescaler)
{
    uint32_t tmpreg_BRKETR_CNTRL;


    ((void)0U);
    ((void)0U);

    tmpreg_BRKETR_CNTRL = TIMERx->BRKETR_CNTRL;
    tmpreg_BRKETR_CNTRL &= ~((uint32_t)0x0000000C);
    tmpreg_BRKETR_CNTRL += (uint32_t)Prescaler;

    TIMERx->BRKETR_CNTRL = tmpreg_BRKETR_CNTRL;
}
# 544 "SPL/MDR32Fx/src/MDR32F9Qx_timer.c"
void TIMER_ETRPolarityConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_ETR_Polarity_TypeDef Polarity)
{
    uint32_t tmpreg_BRKETR_CNTRL;


    ((void)0U);
    ((void)0U);

    tmpreg_BRKETR_CNTRL = TIMERx->BRKETR_CNTRL;
    tmpreg_BRKETR_CNTRL &= ~((uint32_t)0x00000002);
    tmpreg_BRKETR_CNTRL += (uint32_t)Polarity;

    TIMERx->BRKETR_CNTRL = tmpreg_BRKETR_CNTRL;
}
# 568 "SPL/MDR32Fx/src/MDR32F9Qx_timer.c"
void TIMER_BRKPolarityConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_BRK_Polarity_TypeDef Polarity)
{
    uint32_t tmpreg_BRKETR_CNTRL;


    ((void)0U);
    ((void)0U);

    tmpreg_BRKETR_CNTRL = TIMERx->BRKETR_CNTRL;
    tmpreg_BRKETR_CNTRL &= ~((uint32_t)0x00000001);
    tmpreg_BRKETR_CNTRL += (uint32_t)Polarity;

    TIMERx->BRKETR_CNTRL = tmpreg_BRKETR_CNTRL;
}
# 591 "SPL/MDR32Fx/src/MDR32F9Qx_timer.c"
TIMER_Counter_Dir_TypeDef TIMER_GetCounterDirection(MDR_TIMER_TypeDef* TIMERx)
{
    TIMER_Counter_Dir_TypeDef bitstatus;


    ((void)0U);

    if ((TIMERx->CNTRL & ((uint32_t)0x00000008)) == 0)
    {
        bitstatus = TIMER_CntDir_Up;
    }
    else
    {
        bitstatus = TIMER_CntDir_Dn;
    }

    return bitstatus;
}
# 618 "SPL/MDR32Fx/src/MDR32F9Qx_timer.c"
FlagStatus TIMER_GetCntWriteComplete(MDR_TIMER_TypeDef* TIMERx)
{
    FlagStatus bitstatus;


    ((void)0U);

    if ((TIMERx->CNTRL & ((uint32_t)0x00000004)) == 0)
    {
        bitstatus = RESET;
    }
    else
    {
        bitstatus = SET;
    }

    return bitstatus;
}
# 649 "SPL/MDR32Fx/src/MDR32F9Qx_timer.c"
void TIMER_ChnInit(MDR_TIMER_TypeDef* TIMERx, const TIMER_ChnInitTypeDef* TIMER_ChnInitStruct)
{
    uint32_t tmpreg_CH_Number;
    uint32_t tmpreg_CH_CNTRL;
    uint32_t tmpreg_CH_CNTRL2;


    ((void)0U);
    ((void)0U);
    ((void)0U);
    ((void)0U);
    ((void)0U);
    ((void)0U);
    ((void)0U);
    ((void)0U);
    ((void)0U);
    ((void)0U);
    ((void)0U);
    ((void)0U);
    ((void)0U);

    tmpreg_CH_CNTRL = TIMER_ChnInitStruct->TIMER_CH_Mode
                    + TIMER_ChnInitStruct->TIMER_CH_ETR_Reset
                    + TIMER_ChnInitStruct->TIMER_CH_BRK_Reset
                    + TIMER_ChnInitStruct->TIMER_CH_REF_Format
                    + (TIMER_ChnInitStruct->TIMER_CH_Prescaler << 6)
                    + TIMER_ChnInitStruct->TIMER_CH_EventSource
                    + (TIMER_ChnInitStruct->TIMER_CH_FilterConf << 0);

    if (TIMER_ChnInitStruct->TIMER_CH_ETR_Ena != DISABLE)
    {
        tmpreg_CH_CNTRL += ((uint32_t)0x00000100);
    }

    tmpreg_CH_Number = TIMER_ChnInitStruct->TIMER_CH_Number;

    *(&TIMERx->CH1_CNTRL + tmpreg_CH_Number) = tmpreg_CH_CNTRL;

    tmpreg_CH_CNTRL2 = TIMER_ChnInitStruct->TIMER_CH_CCR_UpdateMode
                    + TIMER_ChnInitStruct->TIMER_CH_CCR1_EventSource;

    if (TIMER_ChnInitStruct->TIMER_CH_CCR1_Ena != DISABLE)
    {
        tmpreg_CH_CNTRL2 += ((uint32_t)0x00000004);
    }

    *(&TIMERx->CH1_CNTRL2 + tmpreg_CH_Number) = tmpreg_CH_CNTRL2;
}







void TIMER_ChnStructInit(TIMER_ChnInitTypeDef* TIMER_ChnInitStruct)
{
    TIMER_ChnInitStruct->TIMER_CH_Number = TIMER_CHANNEL1;
    TIMER_ChnInitStruct->TIMER_CH_Mode = TIMER_CH_MODE_PWM;
    TIMER_ChnInitStruct->TIMER_CH_ETR_Ena = DISABLE;
    TIMER_ChnInitStruct->TIMER_CH_ETR_Reset = TIMER_CH_ETR_RESET_Disable;
    TIMER_ChnInitStruct->TIMER_CH_BRK_Reset = TIMER_CH_BRK_RESET_Disable;
    TIMER_ChnInitStruct->TIMER_CH_REF_Format = TIMER_CH_REF_Format0;
    TIMER_ChnInitStruct->TIMER_CH_Prescaler = TIMER_CH_Prescaler_None;
    TIMER_ChnInitStruct->TIMER_CH_EventSource = TIMER_CH_EvSrc_PE;
    TIMER_ChnInitStruct->TIMER_CH_FilterConf = TIMER_Filter_1FF_at_TIMER_CLK;
    TIMER_ChnInitStruct->TIMER_CH_CCR_UpdateMode = TIMER_CH_CCR_Update_Immediately;
    TIMER_ChnInitStruct->TIMER_CH_CCR1_Ena = DISABLE;
    TIMER_ChnInitStruct->TIMER_CH_CCR1_EventSource = TIMER_CH_CCR1EvSrc_PE;
}
# 733 "SPL/MDR32Fx/src/MDR32F9Qx_timer.c"
void TIMER_SetChnCompare(MDR_TIMER_TypeDef* TIMERx, TIMER_Channel_Number_TypeDef Channel, uint16_t Compare)

{
    volatile uint32_t *tmpreg_CCRx;


    ((void)0U);
    ((void)0U);

    tmpreg_CCRx = &TIMERx->CCR1 + (uint32_t)Channel;
    *tmpreg_CCRx = Compare;
}
# 760 "SPL/MDR32Fx/src/MDR32F9Qx_timer.c"
void TIMER_ChnCompareConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_Channel_Number_TypeDef Channel, uint16_t Compare, TIMER_CH_CCR_Update_Mode_TypeDef UpdateMode)

{
    volatile uint32_t *tmpreg_CNTRL2x;
    volatile uint32_t *tmpreg_CCRx;
    uint32_t tmpreg_CNTRL2;


    ((void)0U);
    ((void)0U);
    ((void)0U);

    tmpreg_CNTRL2x = &TIMERx->CH1_CNTRL2 + (uint32_t)Channel;

    tmpreg_CNTRL2 = *tmpreg_CNTRL2x;
    tmpreg_CNTRL2 &= ~((uint32_t)0x00000008);
    tmpreg_CNTRL2 += (uint32_t)UpdateMode;
    *tmpreg_CNTRL2x = tmpreg_CNTRL2;

    tmpreg_CCRx = &TIMERx->CCR1 + Channel;

    *tmpreg_CCRx = Compare;
}
# 796 "SPL/MDR32Fx/src/MDR32F9Qx_timer.c"
uint16_t TIMER_GetChnCapture(MDR_TIMER_TypeDef* TIMERx, TIMER_Channel_Number_TypeDef Channel)

{
    volatile uint32_t *tmpreg_CCRx;
    uint32_t tmpreg;


    ((void)0U);
    ((void)0U);

    tmpreg_CCRx = &TIMERx->CCR1 + (uint32_t)Channel;
    tmpreg = *tmpreg_CCRx;

    return tmpreg;
}
# 825 "SPL/MDR32Fx/src/MDR32F9Qx_timer.c"
void TIMER_SetChnCompare1(MDR_TIMER_TypeDef* TIMERx, TIMER_Channel_Number_TypeDef Channel, uint16_t Compare)

{
    volatile uint32_t *tmpreg_CCR1x;


    ((void)0U);
    ((void)0U);

    tmpreg_CCR1x = &TIMERx->CCR11 + (uint32_t)Channel;
    *tmpreg_CCR1x = Compare;
}
# 852 "SPL/MDR32Fx/src/MDR32F9Qx_timer.c"
void TIMER_ChnCompare1Config(MDR_TIMER_TypeDef* TIMERx, TIMER_Channel_Number_TypeDef Channel, uint16_t Compare, TIMER_CH_CCR_Update_Mode_TypeDef UpdateMode)

{
    volatile uint32_t *tmpreg_CNTRL2x;
    volatile uint32_t *tmpreg_CCR1x;
    uint32_t tmpreg_CNTRL2;


    ((void)0U);
    ((void)0U);
    ((void)0U);

    tmpreg_CNTRL2x = &TIMERx->CH1_CNTRL2 + (uint32_t)Channel;

    tmpreg_CNTRL2 = *tmpreg_CNTRL2x;
    tmpreg_CNTRL2 &= ~((uint32_t)0x00000008);
    tmpreg_CNTRL2 += (uint32_t)UpdateMode;
    *tmpreg_CNTRL2x = tmpreg_CNTRL2;

    tmpreg_CCR1x = &TIMERx->CCR11 + (uint32_t)Channel;

    *tmpreg_CCR1x = Compare;
}
# 888 "SPL/MDR32Fx/src/MDR32F9Qx_timer.c"
uint16_t TIMER_GetChnCapture1(MDR_TIMER_TypeDef* TIMERx, TIMER_Channel_Number_TypeDef Channel)

{
    volatile uint32_t *tmpreg_CCR1x;
    uint32_t tmpreg;


    ((void)0U);
    ((void)0U);

    tmpreg_CCR1x = &TIMERx->CCR11 + (uint32_t)Channel;
    tmpreg = *tmpreg_CCR1x;

    return tmpreg;
}
# 914 "SPL/MDR32Fx/src/MDR32F9Qx_timer.c"
void TIMER_ChnETR_Cmd(MDR_TIMER_TypeDef* TIMERx, TIMER_Channel_Number_TypeDef Channel, FunctionalState NewState)
{
    volatile uint32_t *tmpreg_CH_CNTRLx;
    uint32_t tmpreg_CH_CNTRL;


    ((void)0U);
    ((void)0U);
    ((void)0U);

    tmpreg_CH_CNTRLx = &TIMERx->CH1_CNTRL + (uint32_t)Channel;

    tmpreg_CH_CNTRL = *tmpreg_CH_CNTRLx;


    if (NewState != DISABLE)
    {

        tmpreg_CH_CNTRL |= ((uint32_t)0x00000100);
    }
    else
    {

        tmpreg_CH_CNTRL &= ~((uint32_t)0x00000100);
    }


    *tmpreg_CH_CNTRLx = tmpreg_CH_CNTRL;
}
# 954 "SPL/MDR32Fx/src/MDR32F9Qx_timer.c"
void TIMER_ChnETRResetConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_Channel_Number_TypeDef Channel, TIMER_CH_ETR_RESET_TypeDef NewState)
{
    volatile uint32_t *tmpreg_CH_CNTRLx;
    uint32_t tmpreg_CH_CNTRL;


    ((void)0U);
    ((void)0U);
    ((void)0U);

    tmpreg_CH_CNTRLx = &TIMERx->CH1_CNTRL + (uint32_t)Channel;

    tmpreg_CH_CNTRL = *tmpreg_CH_CNTRLx;
    tmpreg_CH_CNTRL &= ~((uint32_t)0x00002000);
    tmpreg_CH_CNTRL += (uint32_t)NewState;
    *tmpreg_CH_CNTRLx = tmpreg_CH_CNTRL;
}
# 982 "SPL/MDR32Fx/src/MDR32F9Qx_timer.c"
void TIMER_ChnBRKResetConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_Channel_Number_TypeDef Channel, TIMER_CH_BRK_RESET_TypeDef NewState)
{
    volatile uint32_t *tmpreg_CH_CNTRLx;
    uint32_t tmpreg_CH_CNTRL;


    ((void)0U);
    ((void)0U);
    ((void)0U);

    tmpreg_CH_CNTRLx = &TIMERx->CH1_CNTRL + (uint32_t)Channel;

    tmpreg_CH_CNTRL = *tmpreg_CH_CNTRLx;
    tmpreg_CH_CNTRL &= ~((uint32_t)0x00001000);
    tmpreg_CH_CNTRL += (uint32_t)NewState;
    *tmpreg_CH_CNTRLx = tmpreg_CH_CNTRL;
}
# 1010 "SPL/MDR32Fx/src/MDR32F9Qx_timer.c"
void TIMER_ChnREFFormatConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_Channel_Number_TypeDef Channel, TIMER_CH_REF_Format_TypeDef Format)
{
    volatile uint32_t *tmpreg_CH_CNTRLx;
    uint32_t tmpreg_CH_CNTRL;


    ((void)0U);
    ((void)0U);
    ((void)0U);

    tmpreg_CH_CNTRLx = &TIMERx->CH1_CNTRL + (uint32_t)Channel;

    tmpreg_CH_CNTRL = *tmpreg_CH_CNTRLx;
    tmpreg_CH_CNTRL &= ~((uint32_t)0x00000E00);
    tmpreg_CH_CNTRL += (uint32_t)Format;
    *tmpreg_CH_CNTRLx = tmpreg_CH_CNTRL;
}
# 1038 "SPL/MDR32Fx/src/MDR32F9Qx_timer.c"
void TIMER_ChnCapturePrescalerConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_Channel_Number_TypeDef Channel, TIMER_CH_Prescaler_TypeDef Prescaler)
{
    volatile uint32_t *tmpreg_CH_CNTRLx;
    uint32_t tmpreg_CH_CNTRL;


    ((void)0U);
    ((void)0U);
    ((void)0U);

    tmpreg_CH_CNTRLx = &TIMERx->CH1_CNTRL + (uint32_t)Channel;

    tmpreg_CH_CNTRL = *tmpreg_CH_CNTRLx;
    tmpreg_CH_CNTRL &= ~((uint32_t)0x000000C0);
    tmpreg_CH_CNTRL += (uint32_t)Prescaler << 6;
    *tmpreg_CH_CNTRLx = tmpreg_CH_CNTRL;
}
# 1066 "SPL/MDR32Fx/src/MDR32F9Qx_timer.c"
void TIMER_ChnEventSourceConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_Channel_Number_TypeDef Channel, TIMER_CH_Event_Src_TypeDef EventSource)
{
    volatile uint32_t *tmpreg_CH_CNTRLx;
    uint32_t tmpreg_CH_CNTRL;


    ((void)0U);
    ((void)0U);
    ((void)0U);

    tmpreg_CH_CNTRLx = &TIMERx->CH1_CNTRL + (uint32_t)Channel;

    tmpreg_CH_CNTRL = *tmpreg_CH_CNTRLx;
    tmpreg_CH_CNTRL &= ~((uint32_t)0x00000030);
    tmpreg_CH_CNTRL += (uint32_t)EventSource;
    *tmpreg_CH_CNTRLx = tmpreg_CH_CNTRL;
}
# 1094 "SPL/MDR32Fx/src/MDR32F9Qx_timer.c"
void TIMER_ChnFilterConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_Channel_Number_TypeDef Channel, TIMER_Filter_Config_TypeDef Filter)
{
    volatile uint32_t *tmpreg_CH_CNTRLx;
    uint32_t tmpreg_CH_CNTRL;


    ((void)0U);
    ((void)0U);
    ((void)0U);

    tmpreg_CH_CNTRLx = &TIMERx->CH1_CNTRL + (uint32_t)Channel;

    tmpreg_CH_CNTRL = *tmpreg_CH_CNTRLx;
    tmpreg_CH_CNTRL &= ~((uint32_t)0x0000000F);
    tmpreg_CH_CNTRL += (uint32_t)Filter << 0;
    *tmpreg_CH_CNTRLx = tmpreg_CH_CNTRL;
}
# 1121 "SPL/MDR32Fx/src/MDR32F9Qx_timer.c"
FlagStatus TIMER_GetChnWriteComplete(MDR_TIMER_TypeDef* TIMERx, TIMER_Channel_Number_TypeDef Channel)
{
    volatile uint32_t *tmpreg_CH_CNTRLx;
    FlagStatus bitstatus;


    ((void)0U);
    ((void)0U);

    tmpreg_CH_CNTRLx = &TIMERx->CH1_CNTRL + (uint32_t)Channel;

    if ((*tmpreg_CH_CNTRLx & ((uint32_t)0x00004000)) == 0)
    {
        bitstatus = RESET;
    }
    else
    {
        bitstatus = SET;
    }

    return bitstatus;
}
# 1154 "SPL/MDR32Fx/src/MDR32F9Qx_timer.c"
void TIMER_ChnCCR1_EventSourceConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_Channel_Number_TypeDef Channel, TIMER_CH_CCR1_Event_Src_TypeDef EventSource)
{
    volatile uint32_t *tmpreg_CH_CNTRL2x;
    uint32_t tmpreg_CH_CNTRL2;


    ((void)0U);
    ((void)0U);
    ((void)0U);

    tmpreg_CH_CNTRL2x = &TIMERx->CH1_CNTRL2 + (uint32_t)Channel;

    tmpreg_CH_CNTRL2 = *tmpreg_CH_CNTRL2x;
    tmpreg_CH_CNTRL2 &= ~((uint32_t)0x00000003);
    tmpreg_CH_CNTRL2 += (uint32_t)EventSource;
    *tmpreg_CH_CNTRL2x = tmpreg_CH_CNTRL2;
}
# 1182 "SPL/MDR32Fx/src/MDR32F9Qx_timer.c"
void TIMER_ChnCCR1_Cmd(MDR_TIMER_TypeDef* TIMERx, TIMER_Channel_Number_TypeDef Channel, FunctionalState NewState)
{
    volatile uint32_t *tmpreg_CH_CNTRL2x;
    uint32_t tmpreg_CH_CNTRL2;


    ((void)0U);
    ((void)0U);
    ((void)0U);

    tmpreg_CH_CNTRL2x = &TIMERx->CH1_CNTRL2 + (uint32_t)Channel;

    tmpreg_CH_CNTRL2 = *tmpreg_CH_CNTRL2x;


    if (NewState != DISABLE)
    {

        tmpreg_CH_CNTRL2 |= ((uint32_t)0x00000004);
    }
    else
    {

        tmpreg_CH_CNTRL2 &= ~((uint32_t)0x00000004);
    }


    *tmpreg_CH_CNTRL2x = tmpreg_CH_CNTRL2;
}
# 1224 "SPL/MDR32Fx/src/MDR32F9Qx_timer.c"
void TIMER_ChnOutInit(MDR_TIMER_TypeDef* TIMERx, const TIMER_ChnOutInitTypeDef* TIMER_ChnOutInitStruct)
{
    uint32_t tmpreg_CH_Number;
    uint32_t tmpreg_CH_CNTRL1;
    uint32_t tmpreg_CH_DTG;


    ((void)0U);
    ((void)0U);
    ((void)0U);
    ((void)0U);
    ((void)0U);
    ((void)0U);
    ((void)0U);
    ((void)0U);
    ((void)0U);
    ((void)0U);
    ((void)0U);

    tmpreg_CH_CNTRL1 = (TIMER_ChnOutInitStruct->TIMER_CH_DirOut_Polarity << 4)
                     + (TIMER_ChnOutInitStruct->TIMER_CH_DirOut_Source << 2)
                     + (TIMER_ChnOutInitStruct->TIMER_CH_DirOut_Mode << 0)
                     + (TIMER_ChnOutInitStruct->TIMER_CH_NegOut_Polarity << 12)
                     + (TIMER_ChnOutInitStruct->TIMER_CH_NegOut_Source << 10)
                     + (TIMER_ChnOutInitStruct->TIMER_CH_NegOut_Mode << 8);

    tmpreg_CH_Number = TIMER_ChnOutInitStruct->TIMER_CH_Number;

    *(&TIMERx->CH1_CNTRL1 + tmpreg_CH_Number) = tmpreg_CH_CNTRL1;

    tmpreg_CH_DTG = (TIMER_ChnOutInitStruct->TIMER_CH_DTG_MainPrescaler << 8)
                  + (TIMER_ChnOutInitStruct->TIMER_CH_DTG_AuxPrescaler << 0)
                  + TIMER_ChnOutInitStruct->TIMER_CH_DTG_ClockSource;

    *(&TIMERx->CH1_DTG + tmpreg_CH_Number) = tmpreg_CH_DTG;
}







void TIMER_ChnOutStructInit(TIMER_ChnOutInitTypeDef* TIMER_ChnOutInitStruct)
{
    TIMER_ChnOutInitStruct->TIMER_CH_DirOut_Polarity = TIMER_CHOPolarity_NonInverted;
    TIMER_ChnOutInitStruct->TIMER_CH_DirOut_Source = TIMER_CH_OutSrc_Only_0;
    TIMER_ChnOutInitStruct->TIMER_CH_DirOut_Mode = TIMER_CH_OutMode_Input;
    TIMER_ChnOutInitStruct->TIMER_CH_NegOut_Polarity = TIMER_CHOPolarity_NonInverted;
    TIMER_ChnOutInitStruct->TIMER_CH_NegOut_Source = TIMER_CH_OutSrc_Only_0;
    TIMER_ChnOutInitStruct->TIMER_CH_NegOut_Mode = TIMER_CH_OutMode_Input;
    TIMER_ChnOutInitStruct->TIMER_CH_DTG_MainPrescaler = 0;
    TIMER_ChnOutInitStruct->TIMER_CH_DTG_AuxPrescaler = 0;
    TIMER_ChnOutInitStruct->TIMER_CH_DTG_ClockSource = TIMER_CH_DTG_ClkSrc_TIMER_CLK;
}
# 1292 "SPL/MDR32Fx/src/MDR32F9Qx_timer.c"
void TIMER_ChnOutConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_Channel_Number_TypeDef Channel, TIMER_CH_OUT_Src_TypeDef OutSource, TIMER_CH_OUT_Mode_TypeDef Mode, TIMER_CH_OUT_Polarity_TypeDef Polarity)
{
    volatile uint32_t *tmpreg_CH_CNTRL1x;
    uint32_t tmpreg_CH_CNTRL1;


    ((void)0U);
    ((void)0U);
    ((void)0U);
    ((void)0U);
    ((void)0U);

    tmpreg_CH_CNTRL1x = &TIMERx->CH1_CNTRL1 + (uint32_t)Channel;

    tmpreg_CH_CNTRL1 = *tmpreg_CH_CNTRL1x;
    tmpreg_CH_CNTRL1 &= ~(((uint32_t)0x00000010) + ((uint32_t)0x0000000C) + ((uint32_t)0x00000003));
    tmpreg_CH_CNTRL1 += ((uint32_t)Polarity << 4)
                      + ((uint32_t)OutSource << 2)
                      + ((uint32_t)Mode << 0);

    *tmpreg_CH_CNTRL1x = tmpreg_CH_CNTRL1;
}
# 1325 "SPL/MDR32Fx/src/MDR32F9Qx_timer.c"
void TIMER_ChnOutSourceConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_Channel_Number_TypeDef Channel, TIMER_CH_OUT_Src_TypeDef OutSource)
{
    volatile uint32_t *tmpreg_CH_CNTRL1x;
    uint32_t tmpreg_CH_CNTRL1;


    ((void)0U);
    ((void)0U);
    ((void)0U);

    tmpreg_CH_CNTRL1x = &TIMERx->CH1_CNTRL1 + (uint32_t)Channel;

    tmpreg_CH_CNTRL1 = *tmpreg_CH_CNTRL1x;
    tmpreg_CH_CNTRL1 &= ~((uint32_t)0x0000000C);
    tmpreg_CH_CNTRL1 += (uint32_t)OutSource << 2;
    *tmpreg_CH_CNTRL1x = tmpreg_CH_CNTRL1;
}
# 1353 "SPL/MDR32Fx/src/MDR32F9Qx_timer.c"
void TIMER_ChnOutModeConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_Channel_Number_TypeDef Channel, TIMER_CH_OUT_Mode_TypeDef Mode)
{
    volatile uint32_t *tmpreg_CH_CNTRL1x;
    uint32_t tmpreg_CH_CNTRL1;


    ((void)0U);
    ((void)0U);
    ((void)0U);

    tmpreg_CH_CNTRL1x = &TIMERx->CH1_CNTRL1 + (uint32_t)Channel;

    tmpreg_CH_CNTRL1 = *tmpreg_CH_CNTRL1x;
    tmpreg_CH_CNTRL1 &= ~((uint32_t)0x00000003);
    tmpreg_CH_CNTRL1 += (uint32_t)Mode << 0;
    *tmpreg_CH_CNTRL1x = tmpreg_CH_CNTRL1;
}
# 1381 "SPL/MDR32Fx/src/MDR32F9Qx_timer.c"
void TIMER_ChnOutPolarityConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_Channel_Number_TypeDef Channel, TIMER_CH_OUT_Polarity_TypeDef Polarity)
{
    volatile uint32_t *tmpreg_CH_CNTRL1x;
    uint32_t tmpreg_CH_CNTRL1;


    ((void)0U);
    ((void)0U);
    ((void)0U);

    tmpreg_CH_CNTRL1x = &TIMERx->CH1_CNTRL1 + (uint32_t)Channel;

    tmpreg_CH_CNTRL1 = *tmpreg_CH_CNTRL1x;
    tmpreg_CH_CNTRL1 &= ~((uint32_t)0x00000010);
    tmpreg_CH_CNTRL1 += (uint32_t)Polarity << 4;
    *tmpreg_CH_CNTRL1x = tmpreg_CH_CNTRL1;
}
# 1411 "SPL/MDR32Fx/src/MDR32F9Qx_timer.c"
void TIMER_ChnNOutConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_Channel_Number_TypeDef Channel, TIMER_CH_OUT_Src_TypeDef OutSource, TIMER_CH_OUT_Mode_TypeDef Mode, TIMER_CH_OUT_Polarity_TypeDef Polarity)
{
    volatile uint32_t *tmpreg_CH_CNTRL1x;
    uint32_t tmpreg_CH_CNTRL1;


    ((void)0U);
    ((void)0U);
    ((void)0U);
    ((void)0U);
    ((void)0U);

    tmpreg_CH_CNTRL1x = &TIMERx->CH1_CNTRL1 + (uint32_t)Channel;

    tmpreg_CH_CNTRL1 = *tmpreg_CH_CNTRL1x;
    tmpreg_CH_CNTRL1 &= ~(((uint32_t)0x00001000) + ((uint32_t)0x00000C00) + ((uint32_t)0x00000300));
    tmpreg_CH_CNTRL1 += ((uint32_t)Polarity << 12)
                      + ((uint32_t)OutSource << 10)
                      + ((uint32_t)Mode << 8);
    *tmpreg_CH_CNTRL1x = tmpreg_CH_CNTRL1;
}
# 1443 "SPL/MDR32Fx/src/MDR32F9Qx_timer.c"
void TIMER_ChnNOutSourceConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_Channel_Number_TypeDef Channel, TIMER_CH_OUT_Src_TypeDef OutSource)
{
    volatile uint32_t *tmpreg_CH_CNTRL1x;
    uint32_t tmpreg_CH_CNTRL1;


    ((void)0U);
    ((void)0U);
    ((void)0U);

    tmpreg_CH_CNTRL1x = &TIMERx->CH1_CNTRL1 + (uint32_t)Channel;

    tmpreg_CH_CNTRL1 = *tmpreg_CH_CNTRL1x;
    tmpreg_CH_CNTRL1 &= ~((uint32_t)0x00000C00);
    tmpreg_CH_CNTRL1 += (uint32_t)OutSource << 10;
    *tmpreg_CH_CNTRL1x = tmpreg_CH_CNTRL1;
}
# 1471 "SPL/MDR32Fx/src/MDR32F9Qx_timer.c"
void TIMER_ChnNOutModeConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_Channel_Number_TypeDef Channel, TIMER_CH_OUT_Mode_TypeDef Mode)
{
    volatile uint32_t *tmpreg_CH_CNTRL1x;
    uint32_t tmpreg_CH_CNTRL1;


    ((void)0U);
    ((void)0U);
    ((void)0U);

    tmpreg_CH_CNTRL1x = &TIMERx->CH1_CNTRL1 + (uint32_t)Channel;

    tmpreg_CH_CNTRL1 = *tmpreg_CH_CNTRL1x;
    tmpreg_CH_CNTRL1 &= ~((uint32_t)0x00000300);
    tmpreg_CH_CNTRL1 += (uint32_t)Mode << 8;
    *tmpreg_CH_CNTRL1x = tmpreg_CH_CNTRL1;
}
# 1499 "SPL/MDR32Fx/src/MDR32F9Qx_timer.c"
void TIMER_ChnNOutPolarityConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_Channel_Number_TypeDef Channel, TIMER_CH_OUT_Polarity_TypeDef Polarity)
{
    volatile uint32_t *tmpreg_CH_CNTRL1x;
    uint32_t tmpreg_CH_CNTRL1;


    ((void)0U);
    ((void)0U);
    ((void)0U);

    tmpreg_CH_CNTRL1x = &TIMERx->CH1_CNTRL1 + Channel;

    tmpreg_CH_CNTRL1 = *tmpreg_CH_CNTRL1x;
    tmpreg_CH_CNTRL1 &= ~((uint32_t)0x00001000);
    tmpreg_CH_CNTRL1 += (uint32_t)Polarity << 12;
    *tmpreg_CH_CNTRL1x = tmpreg_CH_CNTRL1;
}
# 1531 "SPL/MDR32Fx/src/MDR32F9Qx_timer.c"
void TIMER_ChnOutDTGConfig(MDR_TIMER_TypeDef* TIMERx, TIMER_Channel_Number_TypeDef Channel, uint32_t MainPrescaler, uint32_t AuxPrescaler, TIMER_CH_DTG_Clk_Src_TypeDef ClockSource)
{
    uint32_t tmpreg_CH_DTG;


    ((void)0U);
    ((void)0U);
    ((void)0U);
    ((void)0U);
    ((void)0U);

    tmpreg_CH_DTG = (MainPrescaler << 8)
                  + (AuxPrescaler << 0)
                  + (uint32_t)ClockSource;

    *(&TIMERx->CH1_DTG + (uint32_t)Channel) = tmpreg_CH_DTG;
}
# 1557 "SPL/MDR32Fx/src/MDR32F9Qx_timer.c"
uint32_t TIMER_GetStatus(MDR_TIMER_TypeDef* TIMERx)
{

    ((void)0U);

    return (TIMERx->STATUS);
}
# 1574 "SPL/MDR32Fx/src/MDR32F9Qx_timer.c"
FlagStatus TIMER_GetFlagStatus(MDR_TIMER_TypeDef* TIMERx, TIMER_Status_Flags_TypeDef Flag)
{
    FlagStatus bitstatus;


    ((void)0U);
    ((void)0U);

    if ((TIMERx->STATUS & Flag) == 0)
    {
        bitstatus = RESET;
    }
    else
    {
        bitstatus = SET;
    }

    return bitstatus;
}
# 1604 "SPL/MDR32Fx/src/MDR32F9Qx_timer.c"
void TIMER_ClearFlag(MDR_TIMER_TypeDef* TIMERx, uint32_t Flags)
{

    ((void)0U);
    ((void)0U);

    TIMERx->STATUS = ~Flags;
}
# 1629 "SPL/MDR32Fx/src/MDR32F9Qx_timer.c"
void TIMER_DMACmd(MDR_TIMER_TypeDef* TIMERx, uint32_t TIMER_DMASource, FunctionalState NewState)

{
    uint32_t tmpreg_DMA_RE;


    ((void)0U);
    ((void)0U);
    ((void)0U);






        tmpreg_DMA_RE = TIMERx->DMA_RE;


        if (NewState != DISABLE)
        {

            tmpreg_DMA_RE |= TIMER_DMASource;
        }
        else
        {

            tmpreg_DMA_RE &= ~TIMER_DMASource;
        }


        TIMERx->DMA_RE = tmpreg_DMA_RE;
# 1683 "SPL/MDR32Fx/src/MDR32F9Qx_timer.c"
}
# 1696 "SPL/MDR32Fx/src/MDR32F9Qx_timer.c"
void TIMER_ITConfig(MDR_TIMER_TypeDef* TIMERx, uint32_t TIMER_IT, FunctionalState NewState)
{
    uint32_t tmpreg_IE;


    ((void)0U);
    ((void)0U);
    ((void)0U);

    tmpreg_IE = TIMERx->IE;


    if (NewState != DISABLE)
    {

        tmpreg_IE |= TIMER_IT;
    }
    else
    {

        tmpreg_IE &= ~TIMER_IT;
    }


    TIMERx->IE = tmpreg_IE;
}
# 1732 "SPL/MDR32Fx/src/MDR32F9Qx_timer.c"
ITStatus TIMER_GetITStatus(MDR_TIMER_TypeDef* TIMERx, TIMER_Status_Flags_TypeDef TIMER_IT)
{
    ITStatus bitstatus;
    uint32_t tmpreg;


    ((void)0U);
    ((void)0U);

    tmpreg = TIMERx->IE;
    tmpreg = TIMERx->STATUS & tmpreg & (uint32_t)TIMER_IT;

    if (tmpreg == 0)
    {
        bitstatus = RESET;
    }
    else
    {
        bitstatus = SET;
    }

    return bitstatus;
}
# 1766 "SPL/MDR32Fx/src/MDR32F9Qx_timer.c"
void TIMER_BRGInit(MDR_TIMER_TypeDef* TIMERx, TIMER_Clock_BRG_TypeDef TIMER_BRG)
{
    uint32_t tmpreg;


    ((void)0U);
    ((void)0U);






        tmpreg = ((MDR_RST_CLK_TypeDef *) (0x40020000))->TIM_CLOCK;

    if(TIMERx == ((MDR_TIMER_TypeDef *) (0x40070000)))
    {
        tmpreg &= ~((uint32_t)0x000000FF);
        tmpreg |= TIMER_BRG << 0;
        tmpreg |= ((uint32_t)0x01000000);
    }
    else if(TIMERx == ((MDR_TIMER_TypeDef *) (0x40078000)))
    {
        tmpreg &= ~((uint32_t)0x0000FF00);
        tmpreg |= TIMER_BRG << 8;
        tmpreg |= ((uint32_t)0x02000000);
    }
    else if(TIMERx == ((MDR_TIMER_TypeDef *) (0x40080000)))
    {
        tmpreg &= ~((uint32_t)0x00FF0000);
        tmpreg |= TIMER_BRG << 16;
        tmpreg |= ((uint32_t)0x04000000);
    }
# 1811 "SPL/MDR32Fx/src/MDR32F9Qx_timer.c"
        ((MDR_RST_CLK_TypeDef *) (0x40020000))->TIM_CLOCK = tmpreg;
}
