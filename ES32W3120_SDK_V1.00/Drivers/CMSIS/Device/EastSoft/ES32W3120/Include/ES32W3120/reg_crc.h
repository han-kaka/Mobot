/**
  **************************************************************************************
  * @file    REG_CRC.h
  * @brief   CRC Head File
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

#ifndef __CRC_H__
#define __CRC_H__


/******************************************************************************/
/*                              设备特殊寄存器结构定义                        */
/******************************************************************************/

/*   允许匿名结构和匿名联合    */
 

/****************** Bit definition for CRC_CR register ************************/

#define	CRC_CR_BYTORD_POS	24U 
#define	CRC_CR_BYTORD_MSK	BIT(CRC_CR_BYTORD_POS)

#define	CRC_CR_DATLEN_POSS	22U 
#define	CRC_CR_DATLEN_POSE	23U 
#define	CRC_CR_DATLEN_MSK	BITS(CRC_CR_DATLEN_POSS,CRC_CR_DATLEN_POSE)

#define	CRC_CR_MODE_POSS	20U 
#define	CRC_CR_MODE_POSE	21U 
#define	CRC_CR_MODE_MSK	BITS(CRC_CR_MODE_POSS,CRC_CR_MODE_POSE)

#define	CRC_CR_CHSINV_POS	19U 
#define	CRC_CR_CHSINV_MSK	BIT(CRC_CR_CHSINV_POS)

#define	CRC_CR_DATINV_POS	18U 
#define	CRC_CR_DATINV_MSK	BIT(CRC_CR_DATINV_POS)

#define	CRC_CR_CHSREV_POS	17U 
#define	CRC_CR_CHSREV_MSK	BIT(CRC_CR_CHSREV_POS)

#define	CRC_CR_DATREV_POS	16U 
#define	CRC_CR_DATREV_MSK	BIT(CRC_CR_DATREV_POS)

#define	CRC_CR_DMAEN_POS	4U 
#define	CRC_CR_DMAEN_MSK	BIT(CRC_CR_DMAEN_POS)

#define	CRC_CR_CWERR_POS	3U 
#define	CRC_CR_CWERR_MSK	BIT(CRC_CR_CWERR_POS)

#define	CRC_CR_WERR_POS	2U 
#define	CRC_CR_WERR_MSK	BIT(CRC_CR_WERR_POS)

#define	CRC_CR_RST_POS	1U 
#define	CRC_CR_RST_MSK	BIT(CRC_CR_RST_POS)

#define	CRC_CR_EN_POS	0U 
#define	CRC_CR_EN_MSK	BIT(CRC_CR_EN_POS)

/****************** Bit definition for CRC_DATA register ************************/

#define	CRC_DATA_DATA_POSS	0U 
#define	CRC_DATA_DATA_POSE	31U 
#define	CRC_DATA_DATA_MSK	BITS(CRC_DATA_DATA_POSS,CRC_DATA_DATA_POSE)

/****************** Bit definition for CRC_SEED register ************************/

#define	CRC_SEED_SEED_POSS	0U 
#define	CRC_SEED_SEED_POSE	31U 
#define	CRC_SEED_SEED_MSK	BITS(CRC_SEED_SEED_POSS,CRC_SEED_SEED_POSE)

/****************** Bit definition for CRC_CHECKSUM register ************************/

#define	CRC_CHECKSUM_CHECKSUM_POSS	0U 
#define	CRC_CHECKSUM_CHECKSUM_POSE	31U 
#define	CRC_CHECKSUM_CHECKSUM_MSK	BITS(CRC_CHECKSUM_CHECKSUM_POSS,CRC_CHECKSUM_CHECKSUM_POSE)

typedef struct
{
	__IO uint32_t CR;
	__IO uint32_t DATA;
	__IO uint32_t SEED;
	__I uint32_t CHECKSUM;
} CRC_TypeDef;





#endif
