/*************************************************************************************************/
/*
Copyright	:	QingDao Eastsoft Communication Technology Co.,Ltd.
File Name	:
Description	:
Author		:	eastsoft
Version		:
Date		:
History		:	None
Note		:	None
*/
/*************************************************************************************************/

#include "lib.h"

lib_hdl_tbl_t lib_start_tbl[1] = {0};
BLECB_REGI_SEG(lib_start_tbl, "0.end");

lib_hdl_tbl_t lib_end_tbl[1] = {0};
BLECB_REGI_SEG(lib_end_tbl, "1.end");

/*************************************************************************************************/
/*
	Function	:
	Description	:
	Input		:
	Output		:
	Return		:
	Notes		:
*/
/*************************************************************************************************/
void lib_ble_cb_hdl(uint8_t idx, const void *evt)
{
	uint32_t i;
	const lib_tbl_t *tbl;

	for (tbl = &__blecb_lib_start_tbl, tbl++; tbl < &__blecb_lib_end_tbl; tbl++)
	{
		for (i = 0; i < tbl->size; i++)
		{
			if (tbl->addr[i].id != idx)
			{
				continue;
			}

			if (tbl->addr[i].hdl != 0)
			{
				tbl->addr[i].hdl(evt);
			}

			break;
		}
	}
}
