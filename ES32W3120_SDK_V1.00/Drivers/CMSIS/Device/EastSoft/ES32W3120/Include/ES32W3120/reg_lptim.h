/**
  **************************************************************************************
  * @file    REG_LP16T.h
  * @brief   LP16T Head File
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

#ifndef __LP16T_H__
#define __LP16T_H__


/******************************************************************************/
/*                              设备特殊寄存器结构定义                        */
/******************************************************************************/

/*   允许匿名结构和匿名联合    */
 

/****************** Bit definition for LP16T_CON0 register ************************/

#define	LP16T_CON0_PRELOAD_POS	22U 
#define	LP16T_CON0_PRELOAD_MSK	BIT(LP16T_CON0_PRELOAD_POS)

#define	LP16T_CON0_WAVEPOL_POS	21U 
#define	LP16T_CON0_WAVEPOL_MSK	BIT(LP16T_CON0_WAVEPOL_POS)

#define	LP16T_CON0_WAVE_POSS	19U 
#define	LP16T_CON0_WAVE_POSE	20U 
#define	LP16T_CON0_WAVE_MSK	BITS(LP16T_CON0_WAVE_POSS,LP16T_CON0_WAVE_POSE)

#define	LP16T_CON0_TRIGEN_POSS	17U 
#define	LP16T_CON0_TRIGEN_POSE	18U 
#define	LP16T_CON0_TRIGEN_MSK	BITS(LP16T_CON0_TRIGEN_POSS,LP16T_CON0_TRIGEN_POSE)

#define	LP16T_CON0_TRIGSEL_POSS	13U 
#define	LP16T_CON0_TRIGSEL_POSE	15U 
#define	LP16T_CON0_TRIGSEL_MSK	BITS(LP16T_CON0_TRIGSEL_POSS,LP16T_CON0_TRIGSEL_POSE)

#define	LP16T_CON0_PRESC_POSS	9U 
#define	LP16T_CON0_PRESC_POSE	11U 
#define	LP16T_CON0_PRESC_MSK	BITS(LP16T_CON0_PRESC_POSS,LP16T_CON0_PRESC_POSE)

#define	LP16T_CON0_TRGFLT_POSS	6U 
#define	LP16T_CON0_TRGFLT_POSE	7U 
#define	LP16T_CON0_TRGFLT_MSK	BITS(LP16T_CON0_TRGFLT_POSS,LP16T_CON0_TRGFLT_POSE)

#define	LP16T_CON0_CKFLT_POSS	3U 
#define	LP16T_CON0_CKFLT_POSE	4U 
#define	LP16T_CON0_CKFLT_MSK	BITS(LP16T_CON0_CKFLT_POSS,LP16T_CON0_CKFLT_POSE)

#define	LP16T_CON0_CKPOL_POS	1U 
#define	LP16T_CON0_CKPOL_MSK	BIT(LP16T_CON0_CKPOL_POS)

#define	LP16T_CON0_CKSEL_POS	0U 
#define	LP16T_CON0_CKSEL_MSK	BIT(LP16T_CON0_CKSEL_POS)

/****************** Bit definition for LP16T_CON1 register ************************/

#define	LP16T_CON1_CNTSTRT_POS	2U 
#define	LP16T_CON1_CNTSTRT_MSK	BIT(LP16T_CON1_CNTSTRT_POS)

#define	LP16T_CON1_SNGSTRT_POS	1U 
#define	LP16T_CON1_SNGSTRT_MSK	BIT(LP16T_CON1_SNGSTRT_POS)

#define	LP16T_CON1_ENABLE_POS	0U 
#define	LP16T_CON1_ENABLE_MSK	BIT(LP16T_CON1_ENABLE_POS)

/****************** Bit definition for LP16T_ARR register ************************/

#define	LP16T_ARR_ARR_POSS	0U 
#define	LP16T_ARR_ARR_POSE	15U 
#define	LP16T_ARR_ARR_MSK	BITS(LP16T_ARR_ARR_POSS,LP16T_ARR_ARR_POSE)

/****************** Bit definition for LP16T_CNT register ************************/

#define	LP16T_CNT_CNT_POSS	0U 
#define	LP16T_CNT_CNT_POSE	15U 
#define	LP16T_CNT_CNT_MSK	BITS(LP16T_CNT_CNT_POSS,LP16T_CNT_CNT_POSE)

/****************** Bit definition for LP16T_CMP register ************************/

#define	LP16T_CMP_CMP_POSS	0U 
#define	LP16T_CMP_CMP_POSE	15U 
#define	LP16T_CMP_CMP_MSK	BITS(LP16T_CMP_CMP_POSS,LP16T_CMP_CMP_POSE)

/****************** Bit definition for LP16T_IER register ************************/

#define	LP16T_IER_EXTTRIGIE_POS	2U 
#define	LP16T_IER_EXTTRIGIE_MSK	BIT(LP16T_IER_EXTTRIGIE_POS)

#define	LP16T_IER_ARRMIE_POS	1U 
#define	LP16T_IER_ARRMIE_MSK	BIT(LP16T_IER_ARRMIE_POS)

#define	LP16T_IER_CMPMIE_POS	0U 
#define	LP16T_IER_CMPMIE_MSK	BIT(LP16T_IER_CMPMIE_POS)

/****************** Bit definition for LP16T_ISR register ************************/

#define	LP16T_ISR_EXTTRIG_POS	2U 
#define	LP16T_ISR_EXTTRIG_MSK	BIT(LP16T_ISR_EXTTRIG_POS)

#define	LP16T_ISR_ARRM_POS	1U 
#define	LP16T_ISR_ARRM_MSK	BIT(LP16T_ISR_ARRM_POS)

#define	LP16T_ISR_CMPM_POS	0U 
#define	LP16T_ISR_CMPM_MSK	BIT(LP16T_ISR_CMPM_POS)

/****************** Bit definition for LP16T_IFC register ************************/

#define	LP16T_IFC_EXTTRIG_POS	2U 
#define	LP16T_IFC_EXTTRIG_MSK	BIT(LP16T_IFC_EXTTRIG_POS)

#define	LP16T_IFC_ARRM_POS	1U 
#define	LP16T_IFC_ARRM_MSK	BIT(LP16T_IFC_ARRM_POS)

#define	LP16T_IFC_CMPM_POS	0U 
#define	LP16T_IFC_CMPM_MSK	BIT(LP16T_IFC_CMPM_POS)

/****************** Bit definition for LP16T_UPDATE register ************************/

#define	LP16T_UPDATE_UDIS_POS	0U 
#define	LP16T_UPDATE_UDIS_MSK	BIT(LP16T_UPDATE_UDIS_POS)

/****************** Bit definition for LP16T_SYNCSTAT register ************************/

#define	LP16T_SYNCSTAT_CMPWBSY_POS	3U 
#define	LP16T_SYNCSTAT_CMPWBSY_MSK	BIT(LP16T_SYNCSTAT_CMPWBSY_POS)

#define	LP16T_SYNCSTAT_ARRWBSY_POS	2U 
#define	LP16T_SYNCSTAT_ARRWBSY_MSK	BIT(LP16T_SYNCSTAT_ARRWBSY_POS)

#define	LP16T_SYNCSTAT_CON1WBSY_POS	1U 
#define	LP16T_SYNCSTAT_CON1WBSY_MSK	BIT(LP16T_SYNCSTAT_CON1WBSY_POS)

typedef struct
{
	__IO uint32_t CON0;
	__IO uint32_t CON1;
	__IO uint32_t ARR;
	__I uint32_t CNT;
	__IO uint32_t CMP;
	uint32_t RESERVED0 ;
	__IO uint32_t IER;
	__I uint32_t ISR;
	__O uint32_t IFC;
	uint32_t RESERVED1[3] ;
	__IO uint32_t UPDATE;
	__I uint32_t SYNCSTAT;
} LPTIM_TypeDef;





#endif
