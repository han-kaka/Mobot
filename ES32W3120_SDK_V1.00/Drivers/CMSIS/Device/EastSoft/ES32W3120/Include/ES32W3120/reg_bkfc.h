/**
  **************************************************************************************
  * @file    REG_BKPC.h
  * @brief   BKPC Head File
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

#ifndef __BKPC_H__
#define __BKPC_H__


/******************************************************************************/
/*                              设备特殊寄存器结构定义                        */
/******************************************************************************/

/*   允许匿名结构和匿名联合    */
 

/****************** Bit definition for BKPC_PROT register ************************/

#define	BKPC_PROT_KEY_POSS	0U 
#define	BKPC_PROT_KEY_POSE	31U 
#define	BKPC_PROT_KEY_MSK	BITS(BKPC_PROT_KEY_POSS,BKPC_PROT_KEY_POSE)

#define	BKPC_PROT_PROT_POS	0U 
#define	BKPC_PROT_PROT_MSK	BIT(BKPC_PROT_PROT_POS)

/****************** Bit definition for BKPC_WKR register ************************/

#define	BKPC_WKR_WKSCLR_POS	31U 
#define	BKPC_WKR_WKSCLR_MSK	BIT(BKPC_WKR_WKSCLR_POS)

#define	BKPC_WKR_WKEG_POSS	16U 
#define	BKPC_WKR_WKEG_POSE	25U 
#define	BKPC_WKR_WKEG_MSK	BITS(BKPC_WKR_WKEG_POSS,BKPC_WKR_WKEG_POSE)

#define	BKPC_WKR_Reseverd_POSS	10U 
#define	BKPC_WKR_Reseverd_POSE	15U 
#define	BKPC_WKR_Reseverd_MSK	BITS(BKPC_WKR_Reseverd_POSS,BKPC_WKR_Reseverd_POSE)

#define	BKPC_WKR_WKEN_POSS	0U 
#define	BKPC_WKR_WKEN_POSE	9U 
#define	BKPC_WKR_WKEN_MSK	BITS(BKPC_WKR_WKEN_POSS,BKPC_WKR_WKEN_POSE)

/****************** Bit definition for BKPC_WKSR register ************************/

#define	BKPC_WKSR_WKF_POSS	0U 
#define	BKPC_WKSR_WKF_POSE	9U 
#define	BKPC_WKSR_WKF_MSK	BITS(BKPC_WKSR_WKF_POSS,BKPC_WKSR_WKF_POSE)

/****************** Bit definition for BKPC_PCCR register ************************/

#define	BKPC_PCCR_RTCCKS_POS	16U 
#define	BKPC_PCCR_RTCCKS_MSK	BIT(BKPC_PCCR_RTCCKS_POS)

#define	BKPC_PCCR_ULRCEN_POS	12U 
#define	BKPC_PCCR_ULRCEN_MSK	BIT(BKPC_PCCR_ULRCEN_POS)

#define	BKPC_PCCR_LOSCPS_POS	11U 
#define	BKPC_PCCR_LOSCPS_MSK	BIT(BKPC_PCCR_LOSCPS_POS)

#define	BKPC_PCCR_LOSCPM_POS	10U 
#define	BKPC_PCCR_LOSCPM_MSK	BIT(BKPC_PCCR_LOSCPM_POS)

#define	BKPC_PCCR_LOSMEN_POS	9U 
#define	BKPC_PCCR_LOSMEN_MSK	BIT(BKPC_PCCR_LOSMEN_POS)

#define	BKPC_PCCR_LOSCEN_POS	8U 
#define	BKPC_PCCR_LOSCEN_MSK	BIT(BKPC_PCCR_LOSCEN_POS)

#define	BKPC_PCCR_Reseverd_POSS	2U 
#define	BKPC_PCCR_Reseverd_POSE	7U 
#define	BKPC_PCCR_Reseverd_MSK	BITS(BKPC_PCCR_Reseverd_POSS,BKPC_PCCR_Reseverd_POSE)

#define	BKPC_PCCR_RTCCKEN_POS	1U 
#define	BKPC_PCCR_RTCCKEN_MSK	BIT(BKPC_PCCR_RTCCKEN_POS)

#define	BKPC_PCCR_RTCCK_POS	0U 
#define	BKPC_PCCR_RTCCK_MSK	BIT(BKPC_PCCR_RTCCK_POS)

/****************** Bit definition for BKPC_PCR register ************************/

#define	BKPC_PCR_TSUDC_POSS	20U 
#define	BKPC_PCR_TSUDC_POSE	23U 
#define	BKPC_PCR_TSUDC_MSK	BITS(BKPC_PCR_TSUDC_POSS,BKPC_PCR_TSUDC_POSE)

#define	BKPC_PCR_TSULDO_POSS	16U 
#define	BKPC_PCR_TSULDO_POSE	19U 
#define	BKPC_PCR_TSULDO_MSK	BITS(BKPC_PCR_TSULDO_POSS,BKPC_PCR_TSULDO_POSE)

#define	BKPC_PCR_DCPDC_POS	10U 
#define	BKPC_PCR_DCPDC_MSK	BIT(BKPC_PCR_DCPDC_POS)

#define	BKPC_PCR_DCPWM_POS	9U 
#define	BKPC_PCR_DCPWM_MSK	BIT(BKPC_PCR_DCPWM_POS)

#define	BKPC_PCR_DCBURST_POS	8U 
#define	BKPC_PCR_DCBURST_MSK	BIT(BKPC_PCR_DCBURST_POS)

#define	BKPC_PCR_DCOPD_POS	7U 
#define	BKPC_PCR_DCOPD_MSK	BIT(BKPC_PCR_DCOPD_POS)

#define	BKPC_PCR_DCBY_POS	6U 
#define	BKPC_PCR_DCBY_MSK	BIT(BKPC_PCR_DCBY_POS)

#define	BKPC_PCR_AFEPD_POS	5U 
#define	BKPC_PCR_AFEPD_MSK	BIT(BKPC_PCR_AFEPD_POS)

#define	BKPC_PCR_DCBGPD_POS	4U 
#define	BKPC_PCR_DCBGPD_MSK	BIT(BKPC_PCR_DCBGPD_POS)

#define	BKPC_PCR_LDOSEL_POS	3U 
#define	BKPC_PCR_LDOSEL_MSK	BIT(BKPC_PCR_LDOSEL_POS)

#define	BKPC_PCR_LDOERPD_POS	2U 
#define	BKPC_PCR_LDOERPD_MSK	BIT(BKPC_PCR_LDOERPD_POS)

#define	BKPC_PCR_HPLDOEN_POS	1U 
#define	BKPC_PCR_HPLDOEN_MSK	BIT(BKPC_PCR_HPLDOEN_POS)

#define	BKPC_PCR_PWCTSEN_POS	0U 
#define	BKPC_PCR_PWCTSEN_MSK	BIT(BKPC_PCR_PWCTSEN_POS)

typedef struct
{
	__IO uint32_t PROT;
	__IO uint32_t WKR;
	__I uint32_t WKSR;
	__IO uint32_t PCCR;
	__IO uint32_t PCR;
} BKPC_TypeDef;





#endif
