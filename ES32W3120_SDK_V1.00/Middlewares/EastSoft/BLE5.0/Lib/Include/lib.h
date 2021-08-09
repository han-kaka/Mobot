#ifndef _LIB_H_
#define _LIB_H_

#include <stdint.h>

#define BLECB_SECTION(id)		__attribute__((section(".blecb."id)))
#define BLECB_REGI_SEG(tbl, id)	\
			__attribute__((used)) const lib_tbl_t __blecb_##tbl BLECB_SECTION(id) = \
			{tbl, sizeof(tbl)/sizeof(lib_hdl_tbl_t)}

#define BLECB_REGI(list)	BLECB_REGI_SEG(list, "1")

typedef void (*blecb_regi_t)(uint8_t idx, const void *evt);

typedef struct _lib_hdl_tbl_t
{
	uint8_t		id;
	void		(*hdl)(const void *evt);
} lib_hdl_tbl_t;

typedef struct _lib_tbl_t
{
	lib_hdl_tbl_t *addr;
	uint32_t		size;
} lib_tbl_t;

void lib_ble_cb_hdl(uint8_t idx, const void *evt);

#endif
