/******************************************************************************
 *
 * Copyright(c) 2007 - 2017  Realtek Corporation.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * The full GNU General Public License is included in this distribution in the
 * file called LICENSE.
 *
 * Contact Information:
 * wlanfae <wlanfae@realtek.com>
 * Realtek Corporation, No. 2, Innovation Road II, Hsinchu Science Park,
 * Hsinchu 300, Taiwan.
 *
 * Larry Finger <Larry.Finger@lwfinger.net>
 *
 *****************************************************************************/
#include "mp_precomp.h"
#include "phydm_precomp.h"

void odm_bub_sort(u32 *data, u32 n)
{
	int i, j, temp, sp;

	for (i = n - 1; i >= 0; i--) {
		sp = 1;
		for (j = 0; j < i; j++) {
			if (data[j] < data[j + 1]) {
				temp = data[j];
				data[j] = data[j + 1];
				data[j + 1] = temp;
				sp = 0;
			}
		}
		if (sp == 1)
			break;
	}
}


void odm_tx_gain_gap_calibration(void *dm_void)
{
	PDM_ODM_T dm = (PDM_ODM_T)dm_void;
}
