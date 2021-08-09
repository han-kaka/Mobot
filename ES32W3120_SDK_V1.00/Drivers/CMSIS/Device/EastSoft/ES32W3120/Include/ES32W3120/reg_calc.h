/**
  **************************************************************************************
  * @file    REG_CALC.h
  * @brief   CALC Head File
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

#ifndef __CALC_H__
#define __CALC_H__


/******************************************************************************/
/*                              设备特殊寄存器结构定义                        */
/******************************************************************************/

/*   允许匿名结构和匿名联合    */
 

/****************** Bit definition for CALC_SQRTSR register ************************/

#define	CALC_SQRTSR_BUSY_POS	0U 
#define	CALC_SQRTSR_BUSY_MSK	BIT(CALC_SQRTSR_BUSY_POS)

/****************** Bit definition for CALC_RDCND register ************************/

#define	CALC_RDCND_RADICAND_POSS	0U 
#define	CALC_RDCND_RADICAND_POSE	31U 
#define	CALC_RDCND_RADICAND_MSK	BITS(CALC_RDCND_RADICAND_POSS,CALC_RDCND_RADICAND_POSE)

/****************** Bit definition for CALC_SQRTRES register ************************/

#define	CALC_SQRTRES_RESULT_POSS	0U 
#define	CALC_SQRTRES_RESULT_POSE	15U 
#define	CALC_SQRTRES_RESULT_MSK	BITS(CALC_SQRTRES_RESULT_POSS,CALC_SQRTRES_RESULT_POSE)

/****************** Bit definition for CALC_DIVDR register ************************/

#define	CALC_DIVDR_DIVD_POSS	0U 
#define	CALC_DIVDR_DIVD_POSE	31U 
#define	CALC_DIVDR_DIVD_MSK	BITS(CALC_DIVDR_DIVD_POSS,CALC_DIVDR_DIVD_POSE)

/****************** Bit definition for CALC_DIVSR register ************************/

#define	CALC_DIVSR_DIVS_POSS	0U 
#define	CALC_DIVSR_DIVS_POSE	31U 
#define	CALC_DIVSR_DIVS_MSK	BITS(CALC_DIVSR_DIVS_POSS,CALC_DIVSR_DIVS_POSE)

/****************** Bit definition for CALC_DIVQR register ************************/

#define	CALC_DIVQR_DIVQ_POSS	0U 
#define	CALC_DIVQR_DIVQ_POSE	31U 
#define	CALC_DIVQR_DIVQ_MSK	BITS(CALC_DIVQR_DIVQ_POSS,CALC_DIVQR_DIVQ_POSE)

/****************** Bit definition for CALC_DIVRR register ************************/

#define	CALC_DIVRR_DIVS_POSS	0U 
#define	CALC_DIVRR_DIVS_POSE	31U 
#define	CALC_DIVRR_DIVS_MSK	BITS(CALC_DIVRR_DIVS_POSS,CALC_DIVRR_DIVS_POSE)

/****************** Bit definition for CALC_DIVCSR register ************************/

#define	CALC_DIVCSR_TRM_POS	9U 
#define	CALC_DIVCSR_TRM_MSK	BIT(CALC_DIVCSR_TRM_POS)

#define	CALC_DIVCSR_SIGN_POS	8U 
#define	CALC_DIVCSR_SIGN_MSK	BIT(CALC_DIVCSR_SIGN_POS)

#define	CALC_DIVCSR_DZ_POS	1U 
#define	CALC_DIVCSR_DZ_MSK	BIT(CALC_DIVCSR_DZ_POS)

#define	CALC_DIVCSR_BUSY_POS	0U 
#define	CALC_DIVCSR_BUSY_MSK	BIT(CALC_DIVCSR_BUSY_POS)

typedef struct
{
	__I uint32_t SQRTSR;
	__IO uint32_t RDCND;
	__I uint32_t SQRTRES;
	uint32_t RESERVED0[5] ;
	__IO uint32_t DIVDR;
	__IO uint32_t DIVSR;
	__I uint32_t DIVQR;
	__I uint32_t DIVRR;
	__IO uint32_t DIVCSR;
} CALC_TypeDef;





#endif
