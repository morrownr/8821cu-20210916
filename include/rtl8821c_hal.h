/******************************************************************************
 *
 * Copyright(c) 2016 - 2017 Realtek Corporation.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 *****************************************************************************/
#ifndef _RTL8821C_HAL_H_
#define _RTL8821C_HAL_H_

#include <osdep_service.h>		/* BIT(x) */
#include "../hal/halmac/halmac_api.h"	/* MAC REG definition */
#include "hal_data.h"
#include "rtl8821c_spec.h"
#include "../hal/rtl8821c/hal8821c_fw.h"

#include <rtl8821cu_hal.h>

#ifdef CONFIG_SUPPORT_TRX_SHARED
#define FIFO_BLOCK_SIZE		32768 /*@Block size = 32K*/
#define RX_FIFO_EXPANDING	(1 * FIFO_BLOCK_SIZE)
#else
#define RX_FIFO_EXPANDING	0
#endif


#ifndef MAX_RECVBUF_SZ
	#ifndef CONFIG_MINIMAL_MEMORY_USAGE
		/* 8821C - RX FIFO :16K, for RX agg DMA mode = 16K, Rx agg USB mode could large than 16k */
		/* For Max throughput issue, need to use USB AGG mode to replace DMA AGG mode */
		#define MAX_RECVBUF_SZ (32768)
	#else
		#define MAX_RECVBUF_SZ (4096 + RX_FIFO_EXPANDING) /* about 4K */
	#endif
#endif/* !MAX_RECVBUF_SZ*/

void init_hal_spec_rtl8821c(PADAPTER);
/* MP Functions */
#ifdef CONFIG_MP_INCLUDED
void rtl8821c_prepare_mp_txdesc(PADAPTER, struct mp_priv *);	/* rtw_mp.c */
void rtl8821c_mp_config_rfpath(PADAPTER);			/* hal_mp.c */
#endif
void rtl8821c_dl_rsvd_page(PADAPTER adapter, u8 mstatus);


#endif /* _RTL8821C_HAL_H_ */
