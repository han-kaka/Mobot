/**
  **************************************************************************************
  * @file    REG_SYSCFG.h
  * @brief   SYSCFG Head File
  *
  * @version V0.01
  * @data    8/17/2020
  * @author  Eastsoft MCU Software Team
  * @note
  *
  * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd. ALL rights reserved.
  *
  **************************************************************************************
  */

#ifndef __SYSCFG_H__
#define __SYSCFG_H__


/******************************************************************************/
/*                              设备特殊寄存器结构定义                        */
/******************************************************************************/

/*   允许匿名结构和匿名联合    */
 

/****************** Bit definition for SYSCFG_PROT register ************************/

#define	SYSCFG_PROT_KEY_POSS	1U 
#define	SYSCFG_PROT_KEY_POSE	31U 
#define	SYSCFG_PROT_KEY_MSK	BITS(SYSCFG_PROT_KEY_POSS,SYSCFG_PROT_KEY_POSE)

#define	SYSCFG_PROT_PROT_POS	0U 
#define	SYSCFG_PROT_PROT_MSK	BIT(SYSCFG_PROT_PROT_POS)

/****************** Bit definition for SYSCFG_MEMRMP register ************************/

#define	SYSCFG_MEMRMP_BTF_POS	8U 
#define	SYSCFG_MEMRMP_BTF_MSK	BIT(SYSCFG_MEMRMP_BTF_POS)

#define	SYSCFG_MEMRMP_BLD_POS	0U 
#define	SYSCFG_MEMRMP_BLD_MSK	BIT(SYSCFG_MEMRMP_BLD_POS)

/****************** Bit definition for SYSCFG_RDPF register ************************/

#define	SYSCFG_RDPF_PCRDP_F_POS	1U 
#define	SYSCFG_RDPF_PCRDP_F_MSK	BIT(SYSCFG_RDPF_PCRDP_F_POS)

#define	SYSCFG_RDPF_GBRDP_F_POS	0U 
#define	SYSCFG_RDPF_GBRDP_F_MSK	BIT(SYSCFG_RDPF_GBRDP_F_POS)

/****************** Bit definition for SYSCFG_TIMBRK register ************************/

#define	SYSCFG_TIMBRK_LOCKBRKE_POS	2U 
#define	SYSCFG_TIMBRK_LOCKBRKE_MSK	BIT(SYSCFG_TIMBRK_LOCKBRKE_POS)

#define	SYSCFG_TIMBRK_LVDBRKE_POS	1U 
#define	SYSCFG_TIMBRK_LVDBRKE_MSK	BIT(SYSCFG_TIMBRK_LVDBRKE_POS)

#define	SYSCFG_TIMBRK_CSSBRKE_POS	0U 
#define	SYSCFG_TIMBRK_CSSBRKE_MSK	BIT(SYSCFG_TIMBRK_CSSBRKE_POS)

typedef struct
{
	__IO uint32_t PROT;
	__IO uint32_t MEMRMP;
	__O uint32_t RDPF;
	__IO uint32_t TIMBRK;
    uint32_t RESERVED0[56];
    __IO uint32_t TESTKEY;
} SYSCFG_TypeDef;





#endif
