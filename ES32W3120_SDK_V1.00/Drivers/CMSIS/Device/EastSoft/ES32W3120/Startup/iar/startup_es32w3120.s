;*******************************************************************************
; *file       : startup_ESW3120.s
; *description: ESW3120 Device Startup File
; *author     : Eastsoft AE Team
; *data       : 27 Jun 2019
;
; *Copyright (C) 2019 Shanghai Eastsoft Microelectronics Co., Ltd.
; *
; * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
; * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
; * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
; * ARM SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
; * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
;*******************************************************************************
;
; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Stack_Size      EQU     0x00000A00

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp

; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x00000000

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit

                PRESERVE8
                THUMB

; Vector Table Mapped to Address 0 at Reset

                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size

__Vectors       DCD     __initial_sp                    ; Top of Stack
                DCD     Reset_Handler                   ;1, Reset Handler
                DCD     NMI_Handler                     ;2, NMI Handler
                DCD     HardFault_Handler               ;3, HardFault Handler
                DCD     MemManage_Handler               ;4, MemManage Handler
                DCD     BusFault_Handler                ;5, BusFault Handler
                DCD     UsageFault_Handler              ;6, UsageFault Handler
                DCD     0                               ;7, Reserved
                DCD     0                               ;8, Reserved
                DCD     0                               ;9, Reserved
                DCD     0                               ;10, Reserved
                DCD     SVC_Handler                     ;11, SVCall Handler
                DCD     DebugMon_Handler                ;12, DebugMonitor Handler
                DCD     0                               ;13, Reserved
                DCD     PendSV_Handler                  ;14, PendSV Handler
                DCD     SysTick_Handler                 ;15, Systick Handler

                ; External Interrupts
                DCD     WWDG_IRQHandler                 ;16, WWDG IRQHandler
                DCD     IWDG_IRQHandler                 ;17, IWDG IRQHandler
                DCD     LVD_IRQHandler                  ;18, LVD IRQHandler
                DCD     RTC_WAKE_IRQHandler             ;19, RTC_WAKE IRQHandler
                DCD     RTC_ALARM_IRQHandler            ;20, RTC_ALARM IRQHandler
                DCD     0                               ;21, Reserved
                DCD     CMU_IRQHandler                  ;22, CMU IRQHandler
                DCD     ADC_IRQHandler                  ;23, ADC IRQHandler
                DCD     LP16T_IRQHandler                ;24, LP16T IRQHandler
                DCD     0                               ;25, Reserved
                DCD     BS16T0_IRQHandler               ;26, BS16T0 IRQHandler
                DCD     BS16T1_IRQHandler               ;27, BS16T1 IRQHandler
                DCD     GP16C4T0_IRQHandler             ;28, GP16C4T0 IRQHandler
                DCD     0                               ;29, Reserved
                DCD     0                               ;30, Reserved
                DCD     0                               ;31, Reserved
                DCD     GP16C4T1_IRQHandler             ;32, GP16C4T1 IRQHandler
                DCD     0                               ;33, Reserved
                DCD     0                               ;34, Reserved
                DCD     0                               ;35, Reserved
                DCD     AD16C4T0_BRK_IRQHandler         ;36, AD16C4T0_BRK IRQHandler
                DCD     AD16C4T0_UP_IRQHandler          ;37, AD16C4T0_UP IRQHandler
                DCD     AD16C4T0_TRIG_COM_IRQHandler    ;38, AD16C4T0_TRIG_COM IRQHandler
                DCD     AD16C4T0_CC_IRQHandler          ;39, AD16C4T0_CC IRQHandler
                DCD     AD16C4T1_BRK_IRQHandler         ;40, AD16C4T1_BRK IRQHandler
                DCD     AD16C4T1_UP_IRQHandler          ;41, AD16C4T1_UP IRQHandler
                DCD     AD16C4T1_TRIG_COM_IRQHandler    ;42, AD16C4T1_TRIG_COM IRQHandler
                DCD     AD16C4T1_CC_IRQHandler          ;43, AD16C4T1_CC IRQHandler
                DCD     I2C0_EV_IRQHandler              ;44, I2C0_EV IRQHandler
                DCD     I2C0_ERR_IRQHandler             ;45, I2C0_ERR IRQHandler
                DCD     I2C1_EV_IRQHandler              ;46, I2C1_EV IRQHandler
                DCD     I2C1_ERR_IRQHandler             ;47, I2C1_ERR IRQHandler
                DCD     SPI0_I2S0_IRQHandler            ;48, SPI0_I2S0 IRQHandler
                DCD     SPI1_I2S1_IRQHandler            ;49, SPI1_I2S1 IRQHandler
                DCD     UART0_IRQHandler                ;50, UART0 IRQHandler
                DCD     UART1_IRQHandler                ;51, UART1 IRQHandler
                DCD     UART2_IRQHandler                ;52, UART2 IRQHandler
                DCD     0                               ;53, Reserved
                DCD     PDM2PCM_IRQHandler              ;54, PDM2PCM IRQHandler
                DCD     TK_IRQHandler                   ;55, TK IRQHandler
                DCD     KSCAN_IRQHandler                ;56, KSCAN IRQHandler
                DCD     QSPI_IRQHandler                 ;57, QSPI IRQHandler
                DCD     CRYPT_IRQHandler                ;58, CRYPT IRQHandler
                DCD     ADPCM_IRQHandler                ;59, ADPCM IRQHandler
                DCD     0                               ;60, Reserved
                DCD     HASH_IRQHandler                 ;61, HASH IRQHandler
                DCD     0                               ;62, Reserved
                DCD     ECC_IRQHandler                  ;63, ECC IRQHandler
                DCD     TRNG_IRQHandler                 ;64, TRNG IRQHandler
                DCD     0                               ;65, Reserved
                DCD     EXTI0_IRQHandler                ;66, EXTI0 IRQHandler
                DCD     EXTI1_IRQHandler                ;67, EXTI1 IRQHandler
                DCD     EXTI2_IRQHandler                ;68, EXTI2 IRQHandler
                DCD     EXTI3_IRQHandler                ;69, EXTI3 IRQHandler
                DCD     EXTI4_IRQHandler                ;70, EXTI4 IRQHandler
                DCD     EXTI5_IRQHandler                ;71, EXTI5 IRQHandler
                DCD     EXTI6_IRQHandler                ;72, EXTI6 IRQHandler
                DCD     EXTI7_IRQHandler                ;73, EXTI7 IRQHandler
                DCD     EXTI8_IRQHandler                ;74, EXTI8 IRQHandler
                DCD     EXTI9_IRQHandler                ;75, EXTI9 IRQHandler
                DCD     EXTI10_IRQHandler               ;76, EXTI10 IRQHandler
                DCD     EXTI11_IRQHandler               ;77, EXTI11 IRQHandler
                DCD     EXTI12_IRQHandler               ;78, EXTI12 IRQHandler
                DCD     EXTI13_IRQHandler               ;79, EXTI13 IRQHandler
                DCD     EXTI14_IRQHandler               ;80, EXTI14 IRQHandler
                DCD     EXTI15_IRQHandler               ;81, EXTI15 IRQHandler
                DCD     DMA_IRQHandler                  ;82, DMA IRQHandler
                DCD     0                               ;83, Reserved
                DCD     0                               ;84, Reserved
                DCD     0                               ;85, Reserved
                DCD     0                               ;86, Reserved
                DCD     0                               ;87, Reserved
                DCD     0                               ;88, Reserved
                DCD     0                               ;89, Reserved
                DCD     0                               ;90, Reserved
                DCD     0                               ;91, Reserved
                DCD     0                               ;92, Reserved
                DCD     0                               ;93, Reserved
                DCD     0                               ;94, Reserved
                DCD     0                               ;95, Reserved
                DCD     BLE_ERROR_IRQHandler            ;96, BLE_ERROR IRQHandler
                DCD     BLE_HSLOT_IRQHandler            ;97, BLE_HSLOT IRQHandler
                DCD     BLE_RX_IRQHandler               ;98, BLE_RX IRQHandler
                DCD     BLE_TX_IRQHandler               ;99, BLE_TX IRQHandler
                DCD     BLE_START_IRQHandler            ;100, BLE_START IRQHandler
                DCD     BLE_END_IRQHandler              ;101, BLE_END IRQHandler
                DCD     BLE_SKIP_IRQHandler             ;102, BLE_SKIP IRQHandler
                DCD     BLE_SLP_IRQHandler              ;103, BLE_SLP IRQHandler
                DCD     BLE_CRYPT_IRQHandler            ;104, BLE_CRYPT IRQHandler
                DCD     BLE_GROSSTGTIM_IRQHandler       ;105, BLE_GROSSTGTIM IRQHandler
                DCD     BLE_FINETGTIM_IRQHandler        ;106, BLE_FINETGTIM IRQHandler
                DCD     BLE_TIMESTAMP_TGT_IRQHandler    ;107, BLE_TIMESTAMP_TGT IRQHandler
                DCD     BLE_SW_IRQHandler               ;108, BLE_SW IRQHandler
                DCD     BLE_AUDIO0_IRQHandler           ;109, BLE_AUDIO0 IRQHandler
                DCD     BLE_AUDIO1_IRQHandler           ;110, BLE_AUDIO1 IRQHandler
                DCD     BLE_AUDIO2_IRQHandler           ;111, BLE_AUDIO2 IRQHandler

__Vectors_End

__Vectors_Size  EQU  __Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY

; Reset Handler

Reset_Handler   PROC
                EXPORT  Reset_Handler                       [WEAK]
                IMPORT  __main
                LDR     R0, =__main
                BX      R0
                ENDP

; Dummy Exception IRQHandlers (infinite loops which can be modified)

NMI_Handler             PROC
                        EXPORT  NMI_Handler                 [WEAK]
                        B       .
                        ENDP
HardFault_Handler       PROC
                        EXPORT  HardFault_Handler           [WEAK]
                        B       .
                        ENDP
MemManage_Handler       PROC
                        EXPORT  MemManage_Handler           [WEAK]
                        B       .
                        ENDP
BusFault_Handler        PROC
                        EXPORT  BusFault_Handler            [WEAK]
                        B       .
                        ENDP
UsageFault_Handler      PROC
                        EXPORT  UsageFault_Handler          [WEAK]
                        B       .
                        ENDP
SVC_Handler             PROC
                        EXPORT  SVC_Handler                 [WEAK]
                        B       .
                        ENDP
DebugMon_Handler        PROC
                        EXPORT  DebugMon_Handler            [WEAK]
                        B       .
                        ENDP
PendSV_Handler          PROC
                        EXPORT  PendSV_Handler              [WEAK]
                        B       .
                        ENDP
SysTick_Handler         PROC
                        EXPORT  SysTick_Handler             [WEAK]
                        B       .
                        ENDP

Default_Handler PROC

                EXPORT  WWDG_IRQHandler                     [WEAK]
                EXPORT  IWDG_IRQHandler                     [WEAK]
                EXPORT  LVD_IRQHandler                      [WEAK]
                EXPORT  RTC_WAKE_IRQHandler                 [WEAK]
                EXPORT  RTC_ALARM_IRQHandler                [WEAK]
                EXPORT  CMU_IRQHandler                      [WEAK]
                EXPORT  ADC_IRQHandler                      [WEAK]
                EXPORT  LP16T_IRQHandler                    [WEAK]
                EXPORT  BS16T0_IRQHandler                   [WEAK]
                EXPORT  BS16T1_IRQHandler                   [WEAK]
                EXPORT  GP16C4T0_IRQHandler                 [WEAK]
                EXPORT  GP16C4T1_IRQHandler                 [WEAK]
                EXPORT  AD16C4T0_BRK_IRQHandler             [WEAK]
                EXPORT  AD16C4T0_UP_IRQHandler              [WEAK]
                EXPORT  AD16C4T0_TRIG_COM_IRQHandler        [WEAK]
                EXPORT  AD16C4T0_CC_IRQHandler              [WEAK]
                EXPORT  AD16C4T1_BRK_IRQHandler             [WEAK]
                EXPORT  AD16C4T1_UP_IRQHandler              [WEAK]
                EXPORT  AD16C4T1_TRIG_COM_IRQHandler        [WEAK]
                EXPORT  AD16C4T1_CC_IRQHandler              [WEAK]
                EXPORT  I2C0_EV_IRQHandler                  [WEAK]
                EXPORT  I2C0_ERR_IRQHandler                 [WEAK]
                EXPORT  I2C1_EV_IRQHandler                  [WEAK]
                EXPORT  I2C1_ERR_IRQHandler                 [WEAK]
                EXPORT  SPI0_I2S0_IRQHandler                [WEAK]
                EXPORT  SPI1_I2S1_IRQHandler                [WEAK]
                EXPORT  UART0_IRQHandler                    [WEAK]
                EXPORT  UART1_IRQHandler                    [WEAK]
                EXPORT  UART2_IRQHandler                    [WEAK]
                EXPORT  PDM2PCM_IRQHandler                  [WEAK]
                EXPORT  TK_IRQHandler                       [WEAK]
                EXPORT  KSCAN_IRQHandler                    [WEAK]
                EXPORT  QSPI_IRQHandler                     [WEAK]
                EXPORT  CRYPT_IRQHandler                    [WEAK]
                EXPORT  ADPCM_IRQHandler                    [WEAK]
                EXPORT  HASH_IRQHandler                     [WEAK]
                EXPORT  ECC_IRQHandler                      [WEAK]
                EXPORT  TRNG_IRQHandler                     [WEAK]
                EXPORT  EXTI0_IRQHandler                    [WEAK]
                EXPORT  EXTI1_IRQHandler                    [WEAK]
                EXPORT  EXTI2_IRQHandler                    [WEAK]
                EXPORT  EXTI3_IRQHandler                    [WEAK]
                EXPORT  EXTI4_IRQHandler                    [WEAK]
                EXPORT  EXTI5_IRQHandler                    [WEAK]
                EXPORT  EXTI6_IRQHandler                    [WEAK]
                EXPORT  EXTI7_IRQHandler                    [WEAK]
                EXPORT  EXTI8_IRQHandler                    [WEAK]
                EXPORT  EXTI9_IRQHandler                    [WEAK]
                EXPORT  EXTI10_IRQHandler                   [WEAK]
                EXPORT  EXTI11_IRQHandler                   [WEAK]
                EXPORT  EXTI12_IRQHandler                   [WEAK]
                EXPORT  EXTI13_IRQHandler                   [WEAK]
                EXPORT  EXTI14_IRQHandler                   [WEAK]
                EXPORT  EXTI15_IRQHandler                   [WEAK]
                EXPORT  DMA_IRQHandler                      [WEAK]
                EXPORT  BLE_ERROR_IRQHandler                [WEAK]
                EXPORT  BLE_HSLOT_IRQHandler                [WEAK]
                EXPORT  BLE_RX_IRQHandler                   [WEAK]
                EXPORT  BLE_TX_IRQHandler                   [WEAK]
                EXPORT  BLE_START_IRQHandler                [WEAK]
                EXPORT  BLE_END_IRQHandler                  [WEAK]
                EXPORT  BLE_SKIP_IRQHandler                 [WEAK]
                EXPORT  BLE_SLP_IRQHandler                  [WEAK]
                EXPORT  BLE_CRYPT_IRQHandler                [WEAK]
                EXPORT  BLE_GROSSTGTIM_IRQHandler           [WEAK]
                EXPORT  BLE_FINETGTIM_IRQHandler            [WEAK]
                EXPORT  BLE_TIMESTAMP_TGT_IRQHandler        [WEAK]
                EXPORT  BLE_SW_IRQHandler                   [WEAK]
                EXPORT  BLE_AUDIO0_IRQHandler               [WEAK]
                EXPORT  BLE_AUDIO1_IRQHandler               [WEAK]
                EXPORT  BLE_AUDIO2_IRQHandler               [WEAK]

WWDG_IRQHandler
IWDG_IRQHandler
LVD_IRQHandler
RTC_WAKE_IRQHandler
RTC_ALARM_IRQHandler
CMU_IRQHandler
ADC_IRQHandler
LP16T_IRQHandler
BS16T0_IRQHandler
BS16T1_IRQHandler
GP16C4T0_IRQHandler
GP16C4T1_IRQHandler
AD16C4T0_BRK_IRQHandler
AD16C4T0_UP_IRQHandler
AD16C4T0_TRIG_COM_IRQHandler
AD16C4T0_CC_IRQHandler
AD16C4T1_BRK_IRQHandler
AD16C4T1_UP_IRQHandler
AD16C4T1_TRIG_COM_IRQHandler
AD16C4T1_CC_IRQHandler
I2C0_EV_IRQHandler
I2C0_ERR_IRQHandler
I2C1_EV_IRQHandler
I2C1_ERR_IRQHandler
SPI0_I2S0_IRQHandler
SPI1_I2S1_IRQHandler
UART0_IRQHandler
UART1_IRQHandler
UART2_IRQHandler
PDM2PCM_IRQHandler
TK_IRQHandler
KSCAN_IRQHandler
QSPI_IRQHandler
CRYPT_IRQHandler
ADPCM_IRQHandler
HASH_IRQHandler
ECC_IRQHandler
TRNG_IRQHandler
EXTI0_IRQHandler
EXTI1_IRQHandler
EXTI2_IRQHandler
EXTI3_IRQHandler
EXTI4_IRQHandler
EXTI5_IRQHandler
EXTI6_IRQHandler
EXTI7_IRQHandler
EXTI8_IRQHandler
EXTI9_IRQHandler
EXTI10_IRQHandler
EXTI11_IRQHandler
EXTI12_IRQHandler
EXTI13_IRQHandler
EXTI14_IRQHandler
EXTI15_IRQHandler
DMA_IRQHandler
BLE_ERROR_IRQHandler
BLE_HSLOT_IRQHandler
BLE_RX_IRQHandler
BLE_TX_IRQHandler
BLE_START_IRQHandler
BLE_END_IRQHandler
BLE_SKIP_IRQHandler
BLE_SLP_IRQHandler
BLE_CRYPT_IRQHandler
BLE_GROSSTGTIM_IRQHandler
BLE_FINETGTIM_IRQHandler
BLE_TIMESTAMP_TGT_IRQHandler
BLE_SW_IRQHandler
BLE_AUDIO0_IRQHandler
BLE_AUDIO1_IRQHandler
BLE_AUDIO2_IRQHandler

                B       .

                ENDP

                ALIGN

; User Initial Stack & Heap

                IF      :DEF:__MICROLIB

                EXPORT  __initial_sp
                EXPORT  __heap_base
                EXPORT  __heap_limit

                ELSE

                IMPORT  __use_two_region_memory
                EXPORT  __user_initial_stackheap
__user_initial_stackheap

                LDR     R0, =  Heap_Mem
                LDR     R1, =(Stack_Mem + Stack_Size)
                LDR     R2, = (Heap_Mem +  Heap_Size)
                LDR     R3, = Stack_Mem
                BX      LR

                ALIGN

                ENDIF

                END
