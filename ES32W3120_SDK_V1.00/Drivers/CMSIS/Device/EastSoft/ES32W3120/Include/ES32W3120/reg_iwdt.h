/**
  **************************************************************************************
  * @file    REG_IWDT.h
  * @brief   IWDT Head File
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

#ifndef __IWDT_H__
#define __IWDT_H__


/******************************************************************************/
/*                              设备特殊寄存器结构定义                        */
/******************************************************************************/

/*   允许匿名结构和匿名联合    */
 

/****************** Bit definition for IWDT_LOAD register ************************/

#define	IWDT_LOAD_LOAD_POSS	0U 
#define	IWDT_LOAD_LOAD_POSE	31U 
#define	IWDT_LOAD_LOAD_MSK	BITS(IWDT_LOAD_LOAD_POSS,IWDT_LOAD_LOAD_POSE)

/****************** Bit definition for IWDT_VALUE register ************************/

#define	IWDT_VALUE_VALUE_POSS	0U 
#define	IWDT_VALUE_VALUE_POSE	31U 
#define	IWDT_VALUE_VALUE_MSK	BITS(IWDT_VALUE_VALUE_POSS,IWDT_VALUE_VALUE_POSE)

/****************** Bit definition for IWDT_CON register ************************/

#define	IWDT_CON_CLKS_POS	3U 
#define	IWDT_CON_CLKS_MSK	BIT(IWDT_CON_CLKS_POS)

#define	IWDT_CON_RSTEN_POS	2U 
#define	IWDT_CON_RSTEN_MSK	BIT(IWDT_CON_RSTEN_POS)

#define	IWDT_CON_IE_POS	1U 
#define	IWDT_CON_IE_MSK	BIT(IWDT_CON_IE_POS)

#define	IWDT_CON_EN_POS	0U 
#define	IWDT_CON_EN_MSK	BIT(IWDT_CON_EN_POS)

/****************** Bit definition for IWDT_INTCLR register ************************/

#define	IWDT_INTCLR_INTCLR_POSS	0U 
#define	IWDT_INTCLR_INTCLR_POSE	31U 
#define	IWDT_INTCLR_INTCLR_MSK	BITS(IWDT_INTCLR_INTCLR_POSS,IWDT_INTCLR_INTCLR_POSE)

/****************** Bit definition for IWDT_RIS register ************************/

#define	IWDT_RIS_WDTIF_POS	0U 
#define	IWDT_RIS_WDTIF_MSK	BIT(IWDT_RIS_WDTIF_POS)

/****************** Bit definition for IWDT_LOCK register ************************/

#define	IWDT_LOCK_LOCK_POS	0U 
#define	IWDT_LOCK_LOCK_MSK	BIT(IWDT_LOCK_LOCK_POS)

typedef struct
{
	__O uint32_t LOAD;
	__I uint32_t VALUE;
	__IO uint32_t CON;
	__O uint32_t INTCLR;
	__I uint32_t RIS;
	uint32_t RESERVED0[59] ;
	__I uint32_t LOCK;
} IWDT_TypeDef;





#endif
