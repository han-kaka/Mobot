/**
  **************************************************************************************
  * @file    REG_TRNG.h
  * @brief   TRNG Head File
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

#ifndef __TRNG_H__
#define __TRNG_H__


/******************************************************************************/
/*                              设备特殊寄存器结构定义                        */
/******************************************************************************/

/*   允许匿名结构和匿名联合    */
 

/****************** Bit definition for TRNG_CR register ************************/

#define	TRNG_CR_ADJC_POSS	16U 
#define	TRNG_CR_ADJC_POSE	17U 
#define	TRNG_CR_ADJC_MSK	BITS(TRNG_CR_ADJC_POSS,TRNG_CR_ADJC_POSE)

#define	TRNG_CR_SDSEL_POSS	10U 
#define	TRNG_CR_SDSEL_POSE	11U 
#define	TRNG_CR_SDSEL_MSK	BITS(TRNG_CR_SDSEL_POSS,TRNG_CR_SDSEL_POSE)

#define	TRNG_CR_DSEL_POSS	8U 
#define	TRNG_CR_DSEL_POSE	9U 
#define	TRNG_CR_DSEL_MSK	BITS(TRNG_CR_DSEL_POSS,TRNG_CR_DSEL_POSE)

#define	TRNG_CR_POSTEN_POS	3U 
#define	TRNG_CR_POSTEN_MSK	BIT(TRNG_CR_POSTEN_POS)

#define	TRNG_CR_TRNGSEL_POS	2U 
#define	TRNG_CR_TRNGSEL_MSK	BIT(TRNG_CR_TRNGSEL_POS)

#define	TRNG_CR_ADJM_POS	1U 
#define	TRNG_CR_ADJM_MSK	BIT(TRNG_CR_ADJM_POS)

#define	TRNG_CR_TRNGEN_POS	0U 
#define	TRNG_CR_TRNGEN_MSK	BIT(TRNG_CR_TRNGEN_POS)

/****************** Bit definition for TRNG_SR register ************************/

#define	TRNG_SR_TRNG1_SEED_POS	28U 
#define	TRNG_SR_TRNG1_SEED_MSK	BIT(TRNG_SR_TRNG1_SEED_POS)

#define	TRNG_SR_TRNG1_CLK_POS	27U 
#define	TRNG_SR_TRNG1_CLK_MSK	BIT(TRNG_SR_TRNG1_CLK_POS)

#define	TRNG_SR_TRNG1_SO_POS	26U 
#define	TRNG_SR_TRNG1_SO_MSK	BIT(TRNG_SR_TRNG1_SO_POS)

#define	TRNG_SR_TRNG0_CLK_POS	25U 
#define	TRNG_SR_TRNG0_CLK_MSK	BIT(TRNG_SR_TRNG0_CLK_POS)

#define	TRNG_SR_TRNG0_SO_POSS	16U 
#define	TRNG_SR_TRNG0_SO_POSE	24U 
#define	TRNG_SR_TRNG0_SO_MSK	BITS(TRNG_SR_TRNG0_SO_POSS,TRNG_SR_TRNG0_SO_POSE)

#define	TRNG_SR_OVER_POS	3U 
#define	TRNG_SR_OVER_MSK	BIT(TRNG_SR_OVER_POS)

#define	TRNG_SR_SERR_POS	2U 
#define	TRNG_SR_SERR_MSK	BIT(TRNG_SR_SERR_POS)

#define	TRNG_SR_DAVLD_POS	1U 
#define	TRNG_SR_DAVLD_MSK	BIT(TRNG_SR_DAVLD_POS)

#define	TRNG_SR_START_POS	0U 
#define	TRNG_SR_START_MSK	BIT(TRNG_SR_START_POS)

/****************** Bit definition for TRNG_DR register ************************/

#define	TRNG_DR_DATA_POSS	0U 
#define	TRNG_DR_DATA_POSE	31U 
#define	TRNG_DR_DATA_MSK	BITS(TRNG_DR_DATA_POSS,TRNG_DR_DATA_POSE)

/****************** Bit definition for TRNG_SEED register ************************/

#define	TRNG_SEED_SEED_POSS	0U 
#define	TRNG_SEED_SEED_POSE	31U 
#define	TRNG_SEED_SEED_MSK	BITS(TRNG_SEED_SEED_POSS,TRNG_SEED_SEED_POSE)

/****************** Bit definition for TRNG_CFGR register ************************/

#define	TRNG_CFGR_TOPLMT_POSS	16U 
#define	TRNG_CFGR_TOPLMT_POSE	24U 
#define	TRNG_CFGR_TOPLMT_MSK	BITS(TRNG_CFGR_TOPLMT_POSS,TRNG_CFGR_TOPLMT_POSE)

#define	TRNG_CFGR_CKDIV_POSS	8U 
#define	TRNG_CFGR_CKDIV_POSE	11U 
#define	TRNG_CFGR_CKDIV_MSK	BITS(TRNG_CFGR_CKDIV_POSS,TRNG_CFGR_CKDIV_POSE)

#define	TRNG_CFGR_TSTART_POSS	0U 
#define	TRNG_CFGR_TSTART_POSE	2U 
#define	TRNG_CFGR_TSTART_MSK	BITS(TRNG_CFGR_TSTART_POSS,TRNG_CFGR_TSTART_POSE)

/****************** Bit definition for TRNG_IER register ************************/

#define	TRNG_IER_SERR_POS	2U 
#define	TRNG_IER_SERR_MSK	BIT(TRNG_IER_SERR_POS)

#define	TRNG_IER_DAVLD_POS	1U 
#define	TRNG_IER_DAVLD_MSK	BIT(TRNG_IER_DAVLD_POS)

#define	TRNG_IER_START_POS	0U 
#define	TRNG_IER_START_MSK	BIT(TRNG_IER_START_POS)

/****************** Bit definition for TRNG_IFR register ************************/

#define	TRNG_IFR_SERR_POS	2U 
#define	TRNG_IFR_SERR_MSK	BIT(TRNG_IFR_SERR_POS)

#define	TRNG_IFR_DAVLD_POS	1U 
#define	TRNG_IFR_DAVLD_MSK	BIT(TRNG_IFR_DAVLD_POS)

#define	TRNG_IFR_START_POS	0U 
#define	TRNG_IFR_START_MSK	BIT(TRNG_IFR_START_POS)

/****************** Bit definition for TRNG_IFCR register ************************/

#define	TRNG_IFCR_SERRC_POS	2U 
#define	TRNG_IFCR_SERRC_MSK	BIT(TRNG_IFCR_SERRC_POS)

#define	TRNG_IFCR_DAVLDC_POS	1U 
#define	TRNG_IFCR_DAVLDC_MSK	BIT(TRNG_IFCR_DAVLDC_POS)

#define	TRNG_IFCR_STARTC_POS	0U 
#define	TRNG_IFCR_STARTC_MSK	BIT(TRNG_IFCR_STARTC_POS)

/****************** Bit definition for TRNG_ISR register ************************/

#define	TRNG_ISR_SERR_POS	2U 
#define	TRNG_ISR_SERR_MSK	BIT(TRNG_ISR_SERR_POS)

#define	TRNG_ISR_DAVLD_POS	1U 
#define	TRNG_ISR_DAVLD_MSK	BIT(TRNG_ISR_DAVLD_POS)

#define	TRNG_ISR_START_POS	0U 
#define	TRNG_ISR_START_MSK	BIT(TRNG_ISR_START_POS)

typedef struct
{
	__IO uint32_t CR;
	__I uint32_t SR;
	__I uint32_t DR;
	__IO uint32_t SEED;
	__IO uint32_t CFGR;
	__IO uint32_t IER;
	__I uint32_t IFR;
	__O uint32_t IFCR;
	__I uint32_t ISR;
} TRNG_TypeDef;





#endif  /* __TRNG_H__ */
