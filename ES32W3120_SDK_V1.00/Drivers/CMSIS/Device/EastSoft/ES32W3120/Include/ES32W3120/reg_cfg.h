/**
  **************************************************************************************
  * @file    REG_CFG.h
  * @brief   CFG Head File
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

#ifndef __CFG_H__
#define __CFG_H__


/******************************************************************************/
/*                              设备特殊寄存器结构定义                        */
/******************************************************************************/

/*   允许匿名结构和匿名联合    */
 

/****************** Bit definition for CFG_CHIP register ************************/

#define	CFG_CHIP_SRAM_SIZE_POSS	4U 
#define	CFG_CHIP_SRAM_SIZE_POSE	6U 
#define	CFG_CHIP_SRAM_SIZE_MSK	BITS(CFG_CHIP_SRAM_SIZE_POSS,CFG_CHIP_SRAM_SIZE_POSE)

#define	CFG_CHIP_FLASH_SIZE_POSS	0U 
#define	CFG_CHIP_FLASH_SIZE_POSE	2U 
#define	CFG_CHIP_FLASH_SIZE_MSK	BITS(CFG_CHIP_FLASH_SIZE_POSS,CFG_CHIP_FLASH_SIZE_POSE)

/****************** Bit definition for CFG_BOOT register ************************/

#define	CFG_BOOT_BOOT_POSS	0U 
#define	CFG_BOOT_BOOT_POSE	31U 
#define	CFG_BOOT_BOOT_MSK	BITS(CFG_BOOT_BOOT_POSS,CFG_BOOT_BOOT_POSE)

/****************** Bit definition for CFG_WORD0 register ************************/

#define	CFG_WORD0_BOR09VS_POSS	14U 
#define	CFG_WORD0_BOR09VS_POSE	15U 
#define	CFG_WORD0_BOR09VS_MSK	BITS(CFG_WORD0_BOR09VS_POSS,CFG_WORD0_BOR09VS_POSE)

#define	CFG_WORD0_WWDTEN_POS	13U 
#define	CFG_WORD0_WWDTEN_MSK	BIT(CFG_WORD0_WWDTEN_POS)

#define	CFG_WORD0_BOOT_POS	12U 
#define	CFG_WORD0_BOOT_MSK	BIT(CFG_WORD0_BOOT_POS)

#define	CFG_WORD0_BOR33VS_POSS	10U 
#define	CFG_WORD0_BOR33VS_POSE	11U 
#define	CFG_WORD0_BOR33VS_MSK	BITS(CFG_WORD0_BOR33VS_POSS,CFG_WORD0_BOR33VS_POSE)

#define	CFG_WORD0_PWRTEN_POS	9U 
#define	CFG_WORD0_PWRTEN_MSK	BIT(CFG_WORD0_PWRTEN_POS)

#define	CFG_WORD0_XTAL_POS	8U 
#define	CFG_WORD0_XTAL_MSK	BIT(CFG_WORD0_XTAL_POS)

#define	CFG_WORD0_IWDTEN_POS	3U 
#define	CFG_WORD0_IWDTEN_MSK	BIT(CFG_WORD0_IWDTEN_POS)

#define	CFG_WORD0_TM_ENB_POS	2U 
#define	CFG_WORD0_TM_ENB_MSK	BIT(CFG_WORD0_TM_ENB_POS)

#define	CFG_WORD0_LOSMEN_POS	1U 
#define	CFG_WORD0_LOSMEN_MSK	BIT(CFG_WORD0_LOSMEN_POS)

#define	CFG_WORD0_LOSCEN_POS	0U 
#define	CFG_WORD0_LOSCEN_MSK	BIT(CFG_WORD0_LOSCEN_POS)

/****************** Bit definition for CFG_WRPT0 register ************************/

#define	CFG_WRPT0_WRP0_EN_POS	15U 
#define	CFG_WRPT0_WRP0_EN_MSK	BIT(CFG_WRPT0_WRP0_EN_POS)

#define	CFG_WRPT0_WRP0_ED_POSS	8U 
#define	CFG_WRPT0_WRP0_ED_POSE	14U 
#define	CFG_WRPT0_WRP0_ED_MSK	BITS(CFG_WRPT0_WRP0_ED_POSS,CFG_WRPT0_WRP0_ED_POSE)

#define	CFG_WRPT0_WRP0_ST_POSS	0U 
#define	CFG_WRPT0_WRP0_ST_POSE	6U 
#define	CFG_WRPT0_WRP0_ST_MSK	BITS(CFG_WRPT0_WRP0_ST_POSS,CFG_WRPT0_WRP0_ST_POSE)

/****************** Bit definition for CFG_WRPT1 register ************************/

#define	CFG_WRPT1_WRP1_EN_POS	15U 
#define	CFG_WRPT1_WRP1_EN_MSK	BIT(CFG_WRPT1_WRP1_EN_POS)

#define	CFG_WRPT1_WRP1_ED_POSS	8U 
#define	CFG_WRPT1_WRP1_ED_POSE	14U 
#define	CFG_WRPT1_WRP1_ED_MSK	BITS(CFG_WRPT1_WRP1_ED_POSS,CFG_WRPT1_WRP1_ED_POSE)

#define	CFG_WRPT1_WRP1_ST_POSS	0U 
#define	CFG_WRPT1_WRP1_ST_POSE	6U 
#define	CFG_WRPT1_WRP1_ST_MSK	BITS(CFG_WRPT1_WRP1_ST_POSS,CFG_WRPT1_WRP1_ST_POSE)

/****************** Bit definition for CFG_DAFLS register ************************/

#define	CFG_DAFLS_DFLS_EN_POS	15U 
#define	CFG_DAFLS_DFLS_EN_MSK	BIT(CFG_DAFLS_DFLS_EN_POS)

#define	CFG_DAFLS_DFLS_ED_POSS	8U 
#define	CFG_DAFLS_DFLS_ED_POSE	14U 
#define	CFG_DAFLS_DFLS_ED_MSK	BITS(CFG_DAFLS_DFLS_ED_POSS,CFG_DAFLS_DFLS_ED_POSE)

#define	CFG_DAFLS_DFLS_ST_POSS	0U 
#define	CFG_DAFLS_DFLS_ST_POSE	6U 
#define	CFG_DAFLS_DFLS_ST_MSK	BITS(CFG_DAFLS_DFLS_ST_POSS,CFG_DAFLS_DFLS_ST_POSE)

/****************** Bit definition for CFG_GBRDP register ************************/

#define	CFG_GBRDP_GDRDP_POSS	0U 
#define	CFG_GBRDP_GDRDP_POSE	7U 
#define	CFG_GBRDP_GDRDP_MSK	BITS(CFG_GBRDP_GDRDP_POSS,CFG_GBRDP_GDRDP_POSE)

/****************** Bit definition for CFG_XTAL register ************************/

#define	CFG_XTAL_CAPCAL_POSS	0U 
#define	CFG_XTAL_CAPCAL_POSE	7U 
#define	CFG_XTAL_CAPCAL_MSK	BITS(CFG_XTAL_CAPCAL_POSS,CFG_XTAL_CAPCAL_POSE)

/****************** Bit definition for CFG_PENCRY0 register ************************/

#define	CFG_PENCRY0_ROP0_EN_POS	15U 
#define	CFG_PENCRY0_ROP0_EN_MSK	BIT(CFG_PENCRY0_ROP0_EN_POS)

#define	CFG_PENCRY0_ROP0_ED_POSS	8U 
#define	CFG_PENCRY0_ROP0_ED_POSE	14U 
#define	CFG_PENCRY0_ROP0_ED_MSK	BITS(CFG_PENCRY0_ROP0_ED_POSS,CFG_PENCRY0_ROP0_ED_POSE)

#define	CFG_PENCRY0_ROP0_ST_POSS	0U 
#define	CFG_PENCRY0_ROP0_ST_POSE	6U 
#define	CFG_PENCRY0_ROP0_ST_MSK	BITS(CFG_PENCRY0_ROP0_ST_POSS,CFG_PENCRY0_ROP0_ST_POSE)

/****************** Bit definition for CFG_PENCRY1 register ************************/

#define	CFG_PENCRY1_ROP1_EN_POS	15U 
#define	CFG_PENCRY1_ROP1_EN_MSK	BIT(CFG_PENCRY1_ROP1_EN_POS)

#define	CFG_PENCRY1_ROP1_ED_POSS	8U 
#define	CFG_PENCRY1_ROP1_ED_POSE	14U 
#define	CFG_PENCRY1_ROP1_ED_MSK	BITS(CFG_PENCRY1_ROP1_ED_POSS,CFG_PENCRY1_ROP1_ED_POSE)

#define	CFG_PENCRY1_ROP1_ST_POSS	0U 
#define	CFG_PENCRY1_ROP1_ST_POSE	6U 
#define	CFG_PENCRY1_ROP1_ST_MSK	BITS(CFG_PENCRY1_ROP1_ST_POSS,CFG_PENCRY1_ROP1_ST_POSE)

typedef struct
{
	uint32_t RESERVED0 ;
	__I uint32_t CHIP;
	__I uint32_t BOOT;
	uint32_t RESERVED1[61] ;
	__I uint32_t WORD0;
	__I uint32_t WRPT0;
	__I uint32_t WRPT1;
	__I uint32_t DAFLS;
	__I uint32_t GBRDP;
	__I uint32_t XTAL;
	uint32_t RESERVED2[58] ;
	__I uint32_t PENCRY0;
	__I uint32_t PENCRY1;
} CFG_TypeDef;





#endif
