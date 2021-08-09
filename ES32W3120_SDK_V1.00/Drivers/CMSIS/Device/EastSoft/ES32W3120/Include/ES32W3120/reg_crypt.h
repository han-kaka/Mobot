/**
  **************************************************************************************
  * @file    REG_CRYPT.h
  * @brief   CRYPT Head File
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

#ifndef __CRYPT_H__
#define __CRYPT_H__


/******************************************************************************/
/*                              设备特殊寄存器结构定义                        */
/******************************************************************************/

/*   允许匿名结构和匿名联合    */
 

/****************** Bit definition for CRYPT_DATA0 register ************************/

#define  CRYPT_DATA0_DATA0_POSS  0U 
#define  CRYPT_DATA0_DATA0_POSE  31U 
#define  CRYPT_DATA0_DATA0_MSK  BITS(CRYPT_DATA0_DATA0_POSS,CRYPT_DATA0_DATA0_POSE)

/****************** Bit definition for CRYPT_DATA1 register ************************/

#define  CRYPT_DATA1_DATA1_POSS  0U 
#define  CRYPT_DATA1_DATA1_POSE  31U 
#define  CRYPT_DATA1_DATA1_MSK  BITS(CRYPT_DATA1_DATA1_POSS,CRYPT_DATA1_DATA1_POSE)

/****************** Bit definition for CRYPT_DATA2 register ************************/

#define  CRYPT_DATA2_DATA2_POSS  0U 
#define  CRYPT_DATA2_DATA2_POSE  31U 
#define  CRYPT_DATA2_DATA2_MSK  BITS(CRYPT_DATA2_DATA2_POSS,CRYPT_DATA2_DATA2_POSE)

/****************** Bit definition for CRYPT_DATA3 register ************************/

#define  CRYPT_DATA3_DATA3_POSS  0U 
#define  CRYPT_DATA3_DATA3_POSE  31U 
#define  CRYPT_DATA3_DATA3_MSK  BITS(CRYPT_DATA3_DATA3_POSS,CRYPT_DATA3_DATA3_POSE)

/****************** Bit definition for CRYPT_KEY0 register ************************/

#define  CRYPT_KEY0_KEY0_POSS  0U 
#define  CRYPT_KEY0_KEY0_POSE  31U 
#define  CRYPT_KEY0_KEY0_MSK  BITS(CRYPT_KEY0_KEY0_POSS,CRYPT_KEY0_KEY0_POSE)

/****************** Bit definition for CRYPT_KEY1 register ************************/

#define  CRYPT_KEY1_KEY1_POSS  0U 
#define  CRYPT_KEY1_KEY1_POSE  31U 
#define  CRYPT_KEY1_KEY1_MSK  BITS(CRYPT_KEY1_KEY1_POSS,CRYPT_KEY1_KEY1_POSE)

/****************** Bit definition for CRYPT_KEY2 register ************************/

#define  CRYPT_KEY2_KEY2_POSS  0U 
#define  CRYPT_KEY2_KEY2_POSE  31U 
#define  CRYPT_KEY2_KEY2_MSK  BITS(CRYPT_KEY2_KEY2_POSS,CRYPT_KEY2_KEY2_POSE)

/****************** Bit definition for CRYPT_KEY3 register ************************/

#define  CRYPT_KEY3_KEY3_POSS  0U 
#define  CRYPT_KEY3_KEY3_POSE  31U 
#define  CRYPT_KEY3_KEY3_MSK  BITS(CRYPT_KEY3_KEY3_POSS,CRYPT_KEY3_KEY3_POSE)

/****************** Bit definition for CRYPT_KEY4 register ************************/

#define  CRYPT_KEY4_KEY4_POSS  0U 
#define  CRYPT_KEY4_KEY4_POSE  31U 
#define  CRYPT_KEY4_KEY4_MSK  BITS(CRYPT_KEY4_KEY4_POSS,CRYPT_KEY4_KEY4_POSE)

/****************** Bit definition for CRYPT_KEY5 register ************************/

#define  CRYPT_KEY5_KEY5_POSS  0U 
#define  CRYPT_KEY5_KEY5_POSE  31U 
#define  CRYPT_KEY5_KEY5_MSK  BITS(CRYPT_KEY5_KEY5_POSS,CRYPT_KEY5_KEY5_POSE)

/****************** Bit definition for CRYPT_KEY6 register ************************/

#define  CRYPT_KEY6_KEY6_POSS  0U 
#define  CRYPT_KEY6_KEY6_POSE  31U 
#define  CRYPT_KEY6_KEY6_MSK  BITS(CRYPT_KEY6_KEY6_POSS,CRYPT_KEY6_KEY6_POSE)

/****************** Bit definition for CRYPT_KEY7 register ************************/

#define  CRYPT_KEY7_KEY7_POSS  0U 
#define  CRYPT_KEY7_KEY7_POSE  31U 
#define  CRYPT_KEY7_KEY7_MSK  BITS(CRYPT_KEY7_KEY7_POSS,CRYPT_KEY7_KEY7_POSE)

/****************** Bit definition for CRYPT_IV0 register ************************/

#define  CRYPT_IV0_IV0_POSS  0U 
#define  CRYPT_IV0_IV0_POSE  31U 
#define  CRYPT_IV0_IV0_MSK  BITS(CRYPT_IV0_IV0_POSS,CRYPT_IV0_IV0_POSE)

/****************** Bit definition for CRYPT_IV1 register ************************/

#define  CRYPT_IV1_IV1_POSS  0U 
#define  CRYPT_IV1_IV1_POSE  31U 
#define  CRYPT_IV1_IV1_MSK  BITS(CRYPT_IV1_IV1_POSS,CRYPT_IV1_IV1_POSE)

/****************** Bit definition for CRYPT_IV2 register ************************/

#define  CRYPT_IV2_IV2_POSS  0U 
#define  CRYPT_IV2_IV2_POSE  31U 
#define  CRYPT_IV2_IV2_MSK  BITS(CRYPT_IV2_IV2_POSS,CRYPT_IV2_IV2_POSE)

/****************** Bit definition for CRYPT_IV3 register ************************/

#define  CRYPT_IV3_IV3_POSS  0U 
#define  CRYPT_IV3_IV3_POSE  31U 
#define  CRYPT_IV3_IV3_MSK  BITS(CRYPT_IV3_IV3_POSS,CRYPT_IV3_IV3_POSE)

/****************** Bit definition for CRYPT_RES0 register ************************/

#define  CRYPT_RES0_RES0_POSS  0U 
#define  CRYPT_RES0_RES0_POSE  31U 
#define  CRYPT_RES0_RES0_MSK  BITS(CRYPT_RES0_RES0_POSS,CRYPT_RES0_RES0_POSE)

/****************** Bit definition for CRYPT_RES1 register ************************/

#define  CRYPT_RES1_RES1_POSS  0U 
#define  CRYPT_RES1_RES1_POSE  31U 
#define  CRYPT_RES1_RES1_MSK  BITS(CRYPT_RES1_RES1_POSS,CRYPT_RES1_RES1_POSE)

/****************** Bit definition for CRYPT_RES2 register ************************/

#define  CRYPT_RES2_RES2_POSS  0U 
#define  CRYPT_RES2_RES2_POSE  31U 
#define  CRYPT_RES2_RES2_MSK  BITS(CRYPT_RES2_RES2_POSS,CRYPT_RES2_RES2_POSE)

/****************** Bit definition for CRYPT_RES3 register ************************/

#define  CRYPT_RES3_RES3_POSS  0U 
#define  CRYPT_RES3_RES3_POSE  31U 
#define  CRYPT_RES3_RES3_MSK  BITS(CRYPT_RES3_RES3_POSS,CRYPT_RES3_RES3_POSE)

#define CRYPT_CON_CRYSEL_POSS   30U
#define CRYPT_CON_CRYSEL_POSE   31U
#define CRYPT_CON_CRYSEL_MSK    BITS(CRYPT_CON_CRYSEL_POSS,CRYPT_CON_CRYSEL_POSE)

#define CRYPT_CON_SM4INVALID_POS    17U
#define CRYPT_CON_SM4INVALID_MSK    BIT(CRYPT_CON_SM4INVALID_POS)

#define CRYPT_CON_SM4SOFTRST_POS    16U
#define CRYPT_CON_SM4SOFTRST_MSK    BIT(CRYPT_CON_SM4SOFTRST_POS)

#define CRYPT_CON_RESCLR_POS    15U
#define CRYPT_CON_RESCLR_MSK    BIT(CRYPT_CON_RESCLR_POS)

#define CRYPT_CON_DMAEN_POS 14U
#define CRYPT_CON_DMAEN_MSK BIT(CRYPT_CON_DMAEN_POS)

#define CRYPT_CON_FIFOODR_POS   13U
#define CRYPT_CON_FIFOODR_MSK   BIT(CRYPT_CON_FIFOODR_POS)

#define CRYPT_CON_FIFOEN_POS    12U
#define CRYPT_CON_FIFOEN_MSK    BIT(CRYPT_CON_FIFOEN_POS)

#define CRYPT_CON_DESKS_POS 11U
#define CRYPT_CON_DESKS_MSK BIT(CRYPT_CON_DESKS_POS)

#define CRYPT_CON_TDES_POS  10U
#define CRYPT_CON_TDES_MSK  BIT(CRYPT_CON_TDES_POS)

#define CRYPT_CON_TYPE_POSS 8U
#define CRYPT_CON_TYPE_POSE 9U
#define CRYPT_CON_TYPE_MSK  BITS(CRYPT_CON_TYPE_POSS,CRYPT_CON_TYPE_POSE)

#define CRYPT_CON_IE_POS    7U
#define CRYPT_CON_IE_MSK    BIT(CRYPT_CON_IE_POS)

#define CRYPT_CON_IVEN_POS  6U
#define CRYPT_CON_IVEN_MSK  BIT(CRYPT_CON_IVEN_POS)

#define CRYPT_CON_MODE_POSS 4U
#define CRYPT_CON_MODE_POSE 5U
#define CRYPT_CON_MODE_MSK  BITS(CRYPT_CON_MODE_POSS,CRYPT_CON_MODE_POSE)

#define CRYPT_CON_AESKS_POSS    2U
#define CRYPT_CON_AESKS_POSE    3U
#define CRYPT_CON_AESKS_MSK BITS(CRYPT_CON_AESKS_POSS,CRYPT_CON_AESKS_POSE)

#define CRYPT_CON_ENCS_POS  1U
#define CRYPT_CON_ENCS_MSK  BIT(CRYPT_CON_ENCS_POS)

#define CRYPT_CON_GO_POS    0U
#define CRYPT_CON_GO_MSK    BIT(CRYPT_CON_GO_POS)

/****************** Bit definition for CRYPT_IF register ************************/

#define CRYPT_IF_DONE_POS   8U
#define CRYPT_IF_DONE_MSK   BIT(CRYPT_IF_DONE_POS)

#define CRYPT_IF_SM4IF_POS  3U
#define CRYPT_IF_SM4IF_MSK  BIT(CRYPT_IF_SM4IF_POS)

#define CRYPT_IF_MULTHIF_POS    2U
#define CRYPT_IF_MULTHIF_MSK    BIT(CRYPT_IF_MULTHIF_POS)

#define CRYPT_IF_DESIF_POS  1U
#define CRYPT_IF_DESIF_MSK  BIT(CRYPT_IF_DESIF_POS)

#define CRYPT_IF_AESIF_POS  0U
#define CRYPT_IF_AESIF_MSK  BIT(CRYPT_IF_AESIF_POS)

/****************** Bit definition for CRYPT_IFC register ************************/

#define CRYPT_IFC_SM4IFC_POS    3U
#define CRYPT_IFC_SM4IFC_MSK    BIT(CRYPT_IFC_SM4IFC_POS)

#define CRYPT_IFC_MULTHIFC_POS  2U
#define CRYPT_IFC_MULTHIFC_MSK  BIT(CRYPT_IFC_MULTHIFC_POS)

#define CRYPT_IFC_DESIFC_POS    1U
#define CRYPT_IFC_DESIFC_MSK    BIT(CRYPT_IFC_DESIFC_POS)

#define CRYPT_IFC_AESIFC_POS    0U
#define CRYPT_IFC_AESIFC_MSK    BIT(CRYPT_IFC_AESIFC_POS)

/****************** Bit definition for CRYPT_FIFO register ************************/

#define CRYPT_FIFO_FIFO_POSS    0U
#define CRYPT_FIFO_FIFO_POSE    31U
#define CRYPT_FIFO_FIFO_MSK BITS(CRYPT_FIFO_FIFO_POSS,CRYPT_FIFO_FIFO_POSE)

typedef struct
{
    __IO uint32_t DATA0;
    __IO uint32_t DATA1;
    __IO uint32_t DATA2;
    __IO uint32_t DATA3;
    __IO uint32_t KEY0;
    __IO uint32_t KEY1;
    __IO uint32_t KEY2;
    __IO uint32_t KEY3;
    __IO uint32_t KEY4;
    __IO uint32_t KEY5;
    __IO uint32_t KEY6;
    __IO uint32_t KEY7;
    __IO uint32_t IV0;
    __IO uint32_t IV1;
    __IO uint32_t IV2;
    __IO uint32_t IV3;
    __I uint32_t RES0;
    __I uint32_t RES1;
    __I uint32_t RES2;
    __I uint32_t RES3;
    __IO uint32_t CON;
    __I uint32_t IF;
    __O uint32_t IFC;
    __IO uint32_t FIFO;
} CRYPT_TypeDef;





#endif  /* __CRYPT_H__ */
