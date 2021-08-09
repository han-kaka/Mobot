/**
  **************************************************************************************
  * @file    REG_WWDT.h
  * @brief   WWDT Head File
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

#ifndef __WWDT_H__
#define __WWDT_H__


/******************************************************************************/
/*                              设备特殊寄存器结构定义                        */
/******************************************************************************/

/*   允许匿名结构和匿名联合    */
 

/****************** Bit definition for WWDT_LOAD register ************************/

#define	WWDT_LOAD_LOAD_POSS	0U 
#define	WWDT_LOAD_LOAD_POSE	31U 
#define	WWDT_LOAD_LOAD_MSK	BITS(WWDT_LOAD_LOAD_POSS,WWDT_LOAD_LOAD_POSE)

/****************** Bit definition for WWDT_VALUE register ************************/

#define	WWDT_VALUE_VALUE_POSS	0U 
#define	WWDT_VALUE_VALUE_POSE	31U 
#define	WWDT_VALUE_VALUE_MSK	BITS(WWDT_VALUE_VALUE_POSS,WWDT_VALUE_VALUE_POSE)

/****************** Bit definition for WWDT_CON register ************************/

#define	WWDT_CON_WWDTWIN_POSS	4U 
#define	WWDT_CON_WWDTWIN_POSE	5U 
#define	WWDT_CON_WWDTWIN_MSK	BITS(WWDT_CON_WWDTWIN_POSS,WWDT_CON_WWDTWIN_POSE)

#define	WWDT_CON_CLKS_POS	3U 
#define	WWDT_CON_CLKS_MSK	BIT(WWDT_CON_CLKS_POS)

#define	WWDT_CON_RSTEN_POS	2U 
#define	WWDT_CON_RSTEN_MSK	BIT(WWDT_CON_RSTEN_POS)

#define	WWDT_CON_IE_POS	1U 
#define	WWDT_CON_IE_MSK	BIT(WWDT_CON_IE_POS)

#define	WWDT_CON_EN_POS	0U 
#define	WWDT_CON_EN_MSK	BIT(WWDT_CON_EN_POS)

/****************** Bit definition for WWDT_INTCLR register ************************/

#define	WWDT_INTCLR_INTCLR_POSS	0U 
#define	WWDT_INTCLR_INTCLR_POSE	31U 
#define	WWDT_INTCLR_INTCLR_MSK	BITS(WWDT_INTCLR_INTCLR_POSS,WWDT_INTCLR_INTCLR_POSE)

/****************** Bit definition for WWDT_RIS register ************************/

#define	WWDT_RIS_WWDTIF_POS	0U 
#define	WWDT_RIS_WWDTIF_MSK	BIT(WWDT_RIS_WWDTIF_POS)

/****************** Bit definition for WWDT_LOCK register ************************/

#define	WWDT_LOCK_LOCK_POS	0U 
#define	WWDT_LOCK_LOCK_MSK	BIT(WWDT_LOCK_LOCK_POS)

typedef struct
{
	__O uint32_t LOAD;
	__I uint32_t VALUE;
	__O uint32_t CON;
	__O uint32_t INTCLR;
	__I uint32_t RIS;
	uint32_t RESERVED0[59] ;
	__IO uint32_t LOCK;
} WWDT_TypeDef;





#endif
