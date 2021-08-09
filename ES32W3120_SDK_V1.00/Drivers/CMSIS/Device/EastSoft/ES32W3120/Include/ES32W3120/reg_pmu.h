/**
  **************************************************************************************
  * @file    REG_PMU.h
  * @brief   PMU Head File
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

#ifndef __PMU_H__
#define __PMU_H__


/******************************************************************************/
/*                              设备特殊寄存器结构定义                        */
/******************************************************************************/

/*   允许匿名结构和匿名联合    */
 

/****************** Bit definition for PMU_CR register ************************/

#define	PMU_CR_CKSWEN_POS	16U 
#define	PMU_CR_CKSWEN_MSK	BIT(PMU_CR_CKSWEN_POS)

#define	PMU_CR_CSTANDBYF_POS	3U 
#define	PMU_CR_CSTANDBYF_MSK	BIT(PMU_CR_CSTANDBYF_POS)

#define	PMU_CR_CWUF_POS	2U 
#define	PMU_CR_CWUF_MSK	BIT(PMU_CR_CWUF_POS)

#define	PMU_CR_LPM_POSS	0U 
#define	PMU_CR_LPM_POSE	1U 
#define	PMU_CR_LPM_MSK	BITS(PMU_CR_LPM_POSS,PMU_CR_LPM_POSE)

/****************** Bit definition for PMU_SR register ************************/

#define	PMU_SR_STANDBYF_POS	1U 
#define	PMU_SR_STANDBYF_MSK	BIT(PMU_SR_STANDBYF_POS)

#define	PMU_SR_WUF_POS	0U 
#define	PMU_SR_WUF_MSK	BIT(PMU_SR_WUF_POS)

/****************** Bit definition for PMU_LVDCR register ************************/

#define	PMU_LVDCR_LVDO_POS	15U 
#define	PMU_LVDCR_LVDO_MSK	BIT(PMU_LVDCR_LVDO_POS)

#define	PMU_LVDCR_LVDFLT_POS	11U 
#define	PMU_LVDCR_LVDFLT_MSK	BIT(PMU_LVDCR_LVDFLT_POS)

#define	PMU_LVDCR_LVIFS_POSS	8U 
#define	PMU_LVDCR_LVIFS_POSE	10U 
#define	PMU_LVDCR_LVIFS_MSK	BITS(PMU_LVDCR_LVIFS_POSS,PMU_LVDCR_LVIFS_POSE)

#define	PMU_LVDCR_LVDS_POSS	4U 
#define	PMU_LVDCR_LVDS_POSE	7U 
#define	PMU_LVDCR_LVDS_MSK	BITS(PMU_LVDCR_LVDS_POSS,PMU_LVDCR_LVDS_POSE)

#define	PMU_LVDCR_LVDCIF_POS	3U 
#define	PMU_LVDCR_LVDCIF_MSK	BIT(PMU_LVDCR_LVDCIF_POS)

#define	PMU_LVDCR_LVDIF_POS	2U 
#define	PMU_LVDCR_LVDIF_MSK	BIT(PMU_LVDCR_LVDIF_POS)

#define	PMU_LVDCR_LVDIE_POS	1U 
#define	PMU_LVDCR_LVDIE_MSK	BIT(PMU_LVDCR_LVDIE_POS)

#define	PMU_LVDCR_LVDEN_POS	0U 
#define	PMU_LVDCR_LVDEN_MSK	BIT(PMU_LVDCR_LVDEN_POS)

/****************** Bit definition for PMU_PWRCR register ************************/

#define	PMU_PWRCR_LDO1P1S_POS	17U 
#define	PMU_PWRCR_LDO1P1S_MSK	BIT(PMU_PWRCR_LDO1P1S_POS)

#define	PMU_PWRCR_SRAMPDS_POS	16U 
#define	PMU_PWRCR_SRAMPDS_MSK	BIT(PMU_PWRCR_SRAMPDS_POS)

#define	PMU_PWRCR_BBSRAMPD_POS	5U 
#define	PMU_PWRCR_BBSRAMPD_MSK	BIT(PMU_PWRCR_BBSRAMPD_POS)

#define	PMU_PWRCR_SRAMPD_POS	4U 
#define	PMU_PWRCR_SRAMPD_MSK	BIT(PMU_PWRCR_SRAMPD_POS)

#define	PMU_PWRCR_LDO1P1EN_POS	1U 
#define	PMU_PWRCR_LDO1P1EN_MSK	BIT(PMU_PWRCR_LDO1P1EN_POS)

#define	PMU_PWRCR_IBIASEN_POS	0U 
#define	PMU_PWRCR_IBIASEN_MSK	BIT(PMU_PWRCR_IBIASEN_POS)

/****************** Bit definition for PMU_TWUR register ************************/

#define	PMU_TWUR_WKT_POSS	0U 
#define	PMU_TWUR_WKT_POSE	11U 
#define	PMU_TWUR_WKT_MSK	BITS(PMU_TWUR_WKT_POSS,PMU_TWUR_WKT_POSE)

/****************** Bit definition for PMU_VDETCR register ************************/

#define	PMU_VDETCR_SEL_POSS	4U 
#define	PMU_VDETCR_SEL_POSE	7U 
#define	PMU_VDETCR_SEL_MSK	BITS(PMU_VDETCR_SEL_POSS,PMU_VDETCR_SEL_POSE)

#define	PMU_VDETCR_EN_POS	0U 
#define	PMU_VDETCR_EN_MSK	BIT(PMU_VDETCR_EN_POS)

/****************** Bit definition for PMU_DCCR register ************************/

#define	PMU_DCCR_VCTL_POSS	20U 
#define	PMU_DCCR_VCTL_POSE	23U 
#define	PMU_DCCR_VCTL_MSK	BITS(PMU_DCCR_VCTL_POSS,PMU_DCCR_VCTL_POSE)

#define	PMU_DCCR_FI_POSS	16U 
#define	PMU_DCCR_FI_POSE	18U 
#define	PMU_DCCR_FI_MSK	BITS(PMU_DCCR_FI_POSS,PMU_DCCR_FI_POSE)

#define	PMU_DCCR_HYSCTL_POSS	12U 
#define	PMU_DCCR_HYSCTL_POSE	14U 
#define	PMU_DCCR_HYSCTL_MSK	BITS(PMU_DCCR_HYSCTL_POSS,PMU_DCCR_HYSCTL_POSE)

#define	PMU_DCCR_FC_POSS	8U 
#define	PMU_DCCR_FC_POSE	10U 
#define	PMU_DCCR_FC_MSK	BITS(PMU_DCCR_FC_POSS,PMU_DCCR_FC_POSE)

#define	PMU_DCCR_OVCCEN_POS	6U 
#define	PMU_DCCR_OVCCEN_MSK	BIT(PMU_DCCR_OVCCEN_POS)

#define	PMU_DCCR_PUPWM_POS	5U 
#define	PMU_DCCR_PUPWM_MSK	BIT(PMU_DCCR_PUPWM_POS)

#define	PMU_DCCR_MODE_POS	4U 
#define	PMU_DCCR_MODE_MSK	BIT(PMU_DCCR_MODE_POS)

#define	PMU_DCCR_PUBURST_POS	3U 
#define	PMU_DCCR_PUBURST_MSK	BIT(PMU_DCCR_PUBURST_POS)

#define	PMU_DCCR_DELAY_POS	2U 
#define	PMU_DCCR_DELAY_MSK	BIT(PMU_DCCR_DELAY_POS)

#define	PMU_DCCR_PDDC_POS	1U 
#define	PMU_DCCR_PDDC_MSK	BIT(PMU_DCCR_PDDC_POS)

typedef struct
{
	__IO uint32_t CR;
	__I uint32_t SR;
	__IO uint32_t LVDCR;
	__IO uint32_t PWRCR;
	__IO uint32_t TWUR;
	__IO uint32_t VDETCR;
	__IO uint32_t DCCR;
} PMU_TypeDef;





#endif
