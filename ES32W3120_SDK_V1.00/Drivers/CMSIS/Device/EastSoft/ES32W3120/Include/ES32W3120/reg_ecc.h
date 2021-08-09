/**
  **************************************************************************************
  * @file    REG_ECC.h
  * @brief   ECC Head File
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

#ifndef __ECC_H__
#define __ECC_H__


/******************************************************************************/
/*                       Special register structure definition                */
/******************************************************************************/

/*   Allow anonymous structures and anonymous federation    */
 

/****************** Bit definition for ECC_CON register ************************/

#define ECC_CON_RUN_POS 31U
#define ECC_CON_RUN_MSK BIT(ECC_CON_RUN_POS)

#define ECC_CON_COMB_POS    30U
#define ECC_CON_COMB_MSK    BIT(ECC_CON_COMB_POS)

#define ECC_CON_REMAP_POS   29U
#define ECC_CON_REMAP_MSK   BIT(ECC_CON_REMAP_POS)

#define ECC_CON_COMBMD_POSS 27U
#define ECC_CON_COMBMD_POSE 28U
#define ECC_CON_COMBMD_MSK  BITS(ECC_CON_COMBMD_POSS,ECC_CON_COMBMD_POSE)

#define ECC_CON_OPL_POSS    10U
#define ECC_CON_OPL_POSE    12U
#define ECC_CON_OPL_MSK BITS(ECC_CON_OPL_POSS,ECC_CON_OPL_POSE)

#define ECC_CON_OPR_POSS    7U
#define ECC_CON_OPR_POSE    9U
#define ECC_CON_OPR_MSK BITS(ECC_CON_OPR_POSS,ECC_CON_OPR_POSE)

#define ECC_CON_RES_POSS    4U
#define ECC_CON_RES_POSE    6U
#define ECC_CON_RES_MSK BITS(ECC_CON_RES_POSS,ECC_CON_RES_POSE)

#define ECC_CON_MODE_POSS   1U
#define ECC_CON_MODE_POSE   3U
#define ECC_CON_MODE_MSK    BITS(ECC_CON_MODE_POSS,ECC_CON_MODE_POSE)

#define ECC_CON_INTEN_POS   0U
#define ECC_CON_INTEN_MSK   BIT(ECC_CON_INTEN_POS)

/****************** Bit definition for ECC_STA register ************************/

#define ECC_STA_MI_ZERO_POS 4U
#define ECC_STA_MI_ZERO_MSK BIT(ECC_STA_MI_ZERO_POS)

#define ECC_STA_ECC_OVER_POS    3U
#define ECC_STA_ECC_OVER_MSK    BIT(ECC_STA_ECC_OVER_POS)

#define ECC_STA_ERR_POS 2U
#define ECC_STA_ERR_MSK BIT(ECC_STA_ERR_POS)

#define ECC_STA_DONE_POS    1U
#define ECC_STA_DONE_MSK    BIT(ECC_STA_DONE_POS)

#define ECC_STA_WK_POS  0U
#define ECC_STA_WK_MSK  BIT(ECC_STA_WK_POS)

/****************** Bit definition for ECC_PARA register ************************/

#define ECC_PARA_PARA_POSS  0U
#define ECC_PARA_PARA_POSE  31U
#define ECC_PARA_PARA_MSK   BITS(ECC_PARA_PARA_POSS,ECC_PARA_PARA_POSE)

/****************** Bit definition for ECC_SCALAR register ************************/

#define ECC_SCALAR0_SCALAR0_POSS  0U
#define ECC_SCALAR0_SCALAR0_POSE  31U
#define ECC_SCALAR0_SCALAR0_MSK   BITS(ECC_SCALAR0_SCALAR0_POSS,ECC_SCALAR0_SCALAR0_POSE)

#define ECC_SCALAR1_SCALAR1_POSS  0U
#define ECC_SCALAR1_SCALAR1_POSE  31U
#define ECC_SCALAR1_SCALAR1_MSK   BITS(ECC_SCALAR1_SCALAR1_POSS,ECC_SCALAR1_SCALAR1_POSE)

#define ECC_SCALAR2_SCALAR2_POSS  0U
#define ECC_SCALAR2_SCALAR2_POSE  31U
#define ECC_SCALAR2_SCALAR2_MSK   BITS(ECC_SCALAR2_SCALAR2_POSS,ECC_SCALAR2_SCALAR2_POSE)

#define ECC_SCALAR3_SCALAR3_POSS  0U
#define ECC_SCALAR3_SCALAR3_POSE  31U
#define ECC_SCALAR3_SCALAR3_MSK   BITS(ECC_SCALAR3_SCALAR3_POSS,ECC_SCALAR3_SCALAR3_POSE)

#define ECC_SCALAR4_SCALAR4_POSS  0U
#define ECC_SCALAR4_SCALAR4_POSE  31U
#define ECC_SCALAR4_SCALAR4_MSK   BITS(ECC_SCALAR4_SCALAR4_POSS,ECC_SCALAR4_SCALAR4_POSE)

#define ECC_SCALAR5_SCALAR5_POSS  0U
#define ECC_SCALAR5_SCALAR5_POSE  31U
#define ECC_SCALAR5_SCALAR5_MSK   BITS(ECC_SCALAR5_SCALAR5_POSS,ECC_SCALAR5_SCALAR5_POSE)

#define ECC_SCALAR6_SCALAR6_POSS  0U
#define ECC_SCALAR6_SCALAR6_POSE  31U
#define ECC_SCALAR6_SCALAR6_MSK   BITS(ECC_SCALAR6_SCALAR6_POSS,ECC_SCALAR6_SCALAR6_POSE)

#define ECC_SCALAR7_SCALAR7_POSS  0U
#define ECC_SCALAR7_SCALAR7_POSE  31U
#define ECC_SCALAR7_SCALAR7_MSK   BITS(ECC_SCALAR7_SCALAR7_POSS,ECC_SCALAR7_SCALAR7_POSE)

/****************** Bit definition for ECC_YOC register ************************/

#define ECC_YCO0_YCO0_POSS  0U
#define ECC_YCO0_YCO0_POSE  31U
#define ECC_YCO0_YCO0_MSK   BITS(ECC_YCO0_YCO0_POSS,ECC_YCO0_YCO0_POSE)

#define ECC_YCO1_YCO1_POSS  0U
#define ECC_YCO1_YCO1_POSE  31U
#define ECC_YCO1_YCO1_MSK   BITS(ECC_YCO1_YCO1_POSS,ECC_YCO1_YCO1_POSE)

#define ECC_YCO2_YCO2_POSS  0U
#define ECC_YCO2_YCO2_POSE  31U
#define ECC_YCO2_YCO2_MSK   BITS(ECC_YCO2_YCO2_POSS,ECC_YCO2_YCO2_POSE)

#define ECC_YCO3_YCO3_POSS  0U
#define ECC_YCO3_YCO3_POSE  31U
#define ECC_YCO3_YCO3_MSK   BITS(ECC_YCO3_YCO3_POSS,ECC_YCO3_YCO3_POSE)

#define ECC_YCO4_YCO4_POSS  0U
#define ECC_YCO4_YCO4_POSE  31U
#define ECC_YCO4_YCO4_MSK   BITS(ECC_YCO4_YCO4_POSS,ECC_YCO4_YCO4_POSE)

#define ECC_YCO5_YCO5_POSS  0U
#define ECC_YCO5_YCO5_POSE  31U
#define ECC_YCO5_YCO5_MSK   BITS(ECC_YCO5_YCO5_POSS,ECC_YCO5_YCO5_POSE)

#define ECC_YCO6_YCO6_POSS  0U
#define ECC_YCO6_YCO6_POSE  31U
#define ECC_YCO6_YCO6_MSK   BITS(ECC_YCO6_YCO6_POSS,ECC_YCO6_YCO6_POSE)

#define ECC_YCO7_YCO7_POSS  0U
#define ECC_YCO7_YCO7_POSE  31U
#define ECC_YCO7_YCO7_MSK   BITS(ECC_YCO7_YCO7_POSS,ECC_YCO7_YCO7_POSE)

typedef struct
{
    uint32_t AREG[64];
    uint32_t NREG[8];
    uint32_t RESERVED0[120] ;
    __IO uint32_t CON;
    __IO uint32_t STA;
    __IO uint32_t PARA;
    uint32_t RESERVED1[5] ;
    __IO uint32_t SCALAR0;
    __IO uint32_t SCALAR1;
    __IO uint32_t SCALAR2;
    __IO uint32_t SCALAR3;
    __IO uint32_t SCALAR4;
    __IO uint32_t SCALAR5;
    __IO uint32_t SCALAR6;
    __IO uint32_t SCALAR7;
    __IO uint32_t YCO0;
    __IO uint32_t YCO1;
    __IO uint32_t YCO2;
    __IO uint32_t YCO3;
    __IO uint32_t YCO4;
    __IO uint32_t YCO5;
    __IO uint32_t YCO6;
    __IO uint32_t YCO7;
} ECC_TypeDef;





#endif  /* __ECC_H__ */
