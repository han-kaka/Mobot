/**
  **************************************************************************************
  * @file    REG_MSC.h
  * @brief   MSC Head File
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

#ifndef __MSC_H__
#define __MSC_H__


/******************************************************************************/
/*                              设备特殊寄存器结构定义                        */
/******************************************************************************/

/*   允许匿名结构和匿名联合    */
 

/****************** Bit definition for MSC_IAPCR register ************************/

#define	MSC_IAPCR_IAPCKS_POSS	4U 
#define	MSC_IAPCR_IAPCKS_POSE	6U 
#define	MSC_IAPCR_IAPCKS_MSK	BITS(MSC_IAPCR_IAPCKS_POSS,MSC_IAPCR_IAPCKS_POSE)

#define	MSC_IAPCR_FLASH_ACK_POS	3U 
#define	MSC_IAPCR_FLASH_ACK_MSK	BIT(MSC_IAPCR_FLASH_ACK_POS)

#define	MSC_IAPCR_FLASH_REQ_POS	2U 
#define	MSC_IAPCR_FLASH_REQ_MSK	BIT(MSC_IAPCR_FLASH_REQ_POS)

#define	MSC_IAPCR_IAPRST_POS	1U 
#define	MSC_IAPCR_IAPRST_MSK	BIT(MSC_IAPCR_IAPRST_POS)

#define	MSC_IAPCR_IAPEN_POS	0U 
#define	MSC_IAPCR_IAPEN_MSK	BIT(MSC_IAPCR_IAPEN_POS)

/****************** Bit definition for MSC_IAPA register ************************/

#define	MSC_IAPA_IFREN_POS	19U 
#define	MSC_IAPA_IFREN_MSK	BIT(MSC_IAPA_IFREN_POS)

#define	MSC_IAPA_IAPPA_POSS	12U 
#define	MSC_IAPA_IAPPA_POSE	18U 
#define	MSC_IAPA_IAPPA_MSK	BITS(MSC_IAPA_IAPPA_POSS,MSC_IAPA_IAPPA_POSE)

#define	MSC_IAPA_IAPCA_POSS	0U 
#define	MSC_IAPA_IAPCA_POSE	11U 
#define	MSC_IAPA_IAPCA_MSK	BITS(MSC_IAPA_IAPCA_POSS,MSC_IAPA_IAPCA_POSE)

/****************** Bit definition for MSC_IAPT register ************************/

#define	MSC_IAPT_TRIG_POSS	0U 
#define	MSC_IAPT_TRIG_POSE	31U 
#define	MSC_IAPT_TRIG_MSK	BITS(MSC_IAPT_TRIG_POSS,MSC_IAPT_TRIG_POSE)

/****************** Bit definition for MSC_IAPUL register ************************/

#define	MSC_IAPUL_UL_POSS	0U 
#define	MSC_IAPUL_UL_POSE	31U 
#define	MSC_IAPUL_UL_MSK	BITS(MSC_IAPUL_UL_POSS,MSC_IAPUL_UL_POSE)

/****************** Bit definition for MSC_IAPSR register ************************/

#define	MSC_IAPSR_DFLS_F_POS	19U 
#define	MSC_IAPSR_DFLS_F_MSK	BIT(MSC_IAPSR_DFLS_F_POS)

#define	MSC_IAPSR_GBRDP_F_POS	18U 
#define	MSC_IAPSR_GBRDP_F_MSK	BIT(MSC_IAPSR_GBRDP_F_POS)

#define	MSC_IAPSR_WRP_F_POS	17U 
#define	MSC_IAPSR_WRP_F_MSK	BIT(MSC_IAPSR_WRP_F_POS)

#define	MSC_IAPSR_PCRDP_F_POS	16U 
#define	MSC_IAPSR_PCRDP_F_MSK	BIT(MSC_IAPSR_PCRDP_F_POS)

#define	MSC_IAPSR_MERASE_END_POS	6U 
#define	MSC_IAPSR_MERASE_END_MSK	BIT(MSC_IAPSR_MERASE_END_POS)

#define	MSC_IAPSR_PPROGE_END_POS	5U 
#define	MSC_IAPSR_PPROGE_END_MSK	BIT(MSC_IAPSR_PPROGE_END_POS)

#define	MSC_IAPSR_PPROGD_END_POS	4U 
#define	MSC_IAPSR_PPROGD_END_MSK	BIT(MSC_IAPSR_PPROGD_END_POS)

#define	MSC_IAPSR_PPROGS_END_POS	3U 
#define	MSC_IAPSR_PPROGS_END_MSK	BIT(MSC_IAPSR_PPROGS_END_POS)

#define	MSC_IAPSR_WPROG_END_POS	2U 
#define	MSC_IAPSR_WPROG_END_MSK	BIT(MSC_IAPSR_WPROG_END_POS)

#define	MSC_IAPSR_PERASE_END_POS	1U 
#define	MSC_IAPSR_PERASE_END_MSK	BIT(MSC_IAPSR_PERASE_END_POS)

#define	MSC_IAPSR_BUSY_POS	0U 
#define	MSC_IAPSR_BUSY_MSK	BIT(MSC_IAPSR_BUSY_POS)

/****************** Bit definition for MSC_IAPDL register ************************/

#define	MSC_IAPDL_DATAL_POSS	0U 
#define	MSC_IAPDL_DATAL_POSE	31U 
#define	MSC_IAPDL_DATAL_MSK	BITS(MSC_IAPDL_DATAL_POSS,MSC_IAPDL_DATAL_POSE)

/****************** Bit definition for MSC_IAPDH register ************************/

#define	MSC_IAPDH_DATAH_POSS	0U 
#define	MSC_IAPDH_DATAH_POSE	31U 
#define	MSC_IAPDH_DATAH_MSK	BITS(MSC_IAPDH_DATAH_POSS,MSC_IAPDH_DATAH_POSE)

/****************** Bit definition for MSC_MEMWAIT register ************************/

#define	MSC_MEMWAIT_SRAM_W_POSS	8U 
#define	MSC_MEMWAIT_SRAM_W_POSE	9U 
#define	MSC_MEMWAIT_SRAM_W_MSK	BITS(MSC_MEMWAIT_SRAM_W_POSS,MSC_MEMWAIT_SRAM_W_POSE)

#define	MSC_MEMWAIT_FLASH_W_POSS	0U 
#define	MSC_MEMWAIT_FLASH_W_POSE	3U 
#define	MSC_MEMWAIT_FLASH_W_MSK	BITS(MSC_MEMWAIT_FLASH_W_POSS,MSC_MEMWAIT_FLASH_W_POSE)

/****************** Bit definition for MSC_FREPSR register ************************/

#define	MSC_FREPSR_REP1LS_POS	24U 
#define	MSC_FREPSR_REP1LS_MSK	BIT(MSC_FREPSR_REP1LS_POS)

#define	MSC_FREPSR_REP1_POSS	16U 
#define	MSC_FREPSR_REP1_POSE	23U 
#define	MSC_FREPSR_REP1_MSK	BITS(MSC_FREPSR_REP1_POSS,MSC_FREPSR_REP1_POSE)

#define	MSC_FREPSR_REP0LS_POS	8U 
#define	MSC_FREPSR_REP0LS_MSK	BIT(MSC_FREPSR_REP0LS_POS)

#define	MSC_FREPSR_REP0_POSS	0U 
#define	MSC_FREPSR_REP0_POSE	7U 
#define	MSC_FREPSR_REP0_MSK	BITS(MSC_FREPSR_REP0_POSS,MSC_FREPSR_REP0_POSE)

typedef struct
{
	__IO uint32_t IAPCR;
	__IO uint32_t IAPA;
	uint32_t RESERVED0 ;
	__IO uint32_t IAPT;
	__IO uint32_t IAPUL;
	__I uint32_t IAPSR;
	__IO uint32_t IAPDL;
	__IO uint32_t IAPDH;
	uint32_t RESERVED1[2] ;
	__IO uint32_t MEMWAIT;
	uint32_t RESERVED2 ;
	__I uint32_t FREPSR;
} MSC_TypeDef;





#endif
