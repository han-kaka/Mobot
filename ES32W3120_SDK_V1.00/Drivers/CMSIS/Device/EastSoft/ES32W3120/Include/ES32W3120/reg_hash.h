/**
  **************************************************************************************
  * @file    REG_HASH.h
  * @brief   HASH Head File
  *
  * @version V0.01
  * @data    8/24/2020
  * @author  Eastsoft MCU Software Team
  * @note
  *
  * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd. ALL rights reserved.
  *
  **************************************************************************************
  */

#ifndef __HASH_H__
#define __HASH_H__


/******************************************************************************/
/*                              设备特殊寄存器结构定义                        */
/******************************************************************************/

/*   允许匿名结构和匿名联合    */
 

/****************** Bit definition for HASH_DIN register ************************/

#define	HASH_DIN_DIN_POSS	0U 
#define	HASH_DIN_DIN_POSE	31U 
#define	HASH_DIN_DIN_MSK	BITS(HASH_DIN_DIN_POSS,HASH_DIN_DIN_POSE)

/****************** Bit definition for HASH_CTRL register ************************/

#define	HASH_CTRL_TRIG_POS	8U 
#define	HASH_CTRL_TRIG_MSK	BIT(HASH_CTRL_TRIG_POS)

#define	HASH_CTRL_DATATYP_POSS	6U 
#define	HASH_CTRL_DATATYP_POSE	7U 
#define	HASH_CTRL_DATATYP_MSK	BITS(HASH_CTRL_DATATYP_POSS,HASH_CTRL_DATATYP_POSE)

#define	HASH_CTRL_OUTTYP_POS	5U 
#define	HASH_CTRL_OUTTYP_MSK	BIT(HASH_CTRL_OUTTYP_POS)

#define	HASH_CTRL_ALGO_POSS	3U 
#define	HASH_CTRL_ALGO_POSE	4U 
#define	HASH_CTRL_ALGO_MSK	BITS(HASH_CTRL_ALGO_POSS,HASH_CTRL_ALGO_POSE)

#define	HASH_CTRL_DMAEN_POS	2U 
#define	HASH_CTRL_DMAEN_MSK	BIT(HASH_CTRL_DMAEN_POS)

#define	HASH_CTRL_INTEN_POS	1U 
#define	HASH_CTRL_INTEN_MSK	BIT(HASH_CTRL_INTEN_POS)

#define	HASH_CTRL_EN_POS	0U 
#define	HASH_CTRL_EN_MSK	BIT(HASH_CTRL_EN_POS)

/****************** Bit definition for HASH_STAT register ************************/

#define	HASH_STAT_GRPNUM_POSS	16U 
#define	HASH_STAT_GRPNUM_POSE	31U 
#define	HASH_STAT_GRPNUM_MSK	BITS(HASH_STAT_GRPNUM_POSS,HASH_STAT_GRPNUM_POSE)

#define	HASH_STAT_USEDFIFO_POSS	8U 
#define	HASH_STAT_USEDFIFO_POSE	11U 
#define	HASH_STAT_USEDFIFO_MSK	BITS(HASH_STAT_USEDFIFO_POSS,HASH_STAT_USEDFIFO_POSE)

#define	HASH_STAT_RND_DONE_POS	0U 
#define	HASH_STAT_RND_DONE_MSK	BIT(HASH_STAT_RND_DONE_POS)

/****************** Bit definition for HASH_RES0 register ************************/

#define	HASH_RES0_RES0_POSS	0U 
#define	HASH_RES0_RES0_POSE	31U 
#define	HASH_RES0_RES0_MSK	BITS(HASH_RES0_RES0_POSS,HASH_RES0_RES0_POSE)

/****************** Bit definition for HASH_RES1 register ************************/

#define	HASH_RES1_RES1_POSS	0U 
#define	HASH_RES1_RES1_POSE	31U 
#define	HASH_RES1_RES1_MSK	BITS(HASH_RES1_RES1_POSS,HASH_RES1_RES1_POSE)

/****************** Bit definition for HASH_RES2 register ************************/

#define	HASH_RES2_RES2_POSS	0U 
#define	HASH_RES2_RES2_POSE	31U 
#define	HASH_RES2_RES2_MSK	BITS(HASH_RES2_RES2_POSS,HASH_RES2_RES2_POSE)

/****************** Bit definition for HASH_RES3 register ************************/

#define	HASH_RES3_RES3_POSS	0U 
#define	HASH_RES3_RES3_POSE	31U 
#define	HASH_RES3_RES3_MSK	BITS(HASH_RES3_RES3_POSS,HASH_RES3_RES3_POSE)

/****************** Bit definition for HASH_RES4 register ************************/

#define	HASH_RES4_RES4_POSS	0U 
#define	HASH_RES4_RES4_POSE	31U 
#define	HASH_RES4_RES4_MSK	BITS(HASH_RES4_RES4_POSS,HASH_RES4_RES4_POSE)

/****************** Bit definition for HASH_RES5 register ************************/

#define	HASH_RES5_RES5_POSS	0U 
#define	HASH_RES5_RES5_POSE	31U 
#define	HASH_RES5_RES5_MSK	BITS(HASH_RES5_RES5_POSS,HASH_RES5_RES5_POSE)

/****************** Bit definition for HASH_RES6 register ************************/

#define	HASH_RES6_RES6_POSS	0U 
#define	HASH_RES6_RES6_POSE	31U 
#define	HASH_RES6_RES6_MSK	BITS(HASH_RES6_RES6_POSS,HASH_RES6_RES6_POSE)

/****************** Bit definition for HASH_RES7 register ************************/

#define	HASH_RES7_RES7_POSS	0U 
#define	HASH_RES7_RES7_POSE	31U 
#define	HASH_RES7_RES7_MSK	BITS(HASH_RES7_RES7_POSS,HASH_RES7_RES7_POSE)

typedef struct
{
	__O uint32_t DIN;
	__IO uint32_t CTRL;
	__IO uint32_t STAT;
	__I uint32_t RES0;
	__I uint32_t RES1;
	__I uint32_t RES2;
	__I uint32_t RES3;
	__I uint32_t RES4;
	__I uint32_t RES5;
	__I uint32_t RES6;
	__I uint32_t RES7;
} HASH_TypeDef;





#endif  /* __HASH_H__ */
