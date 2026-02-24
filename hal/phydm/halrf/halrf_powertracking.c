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

/*@************************************************************
 * include files
 * ************************************************************
 */
#include "mp_precomp.h"
#include "phydm_precomp.h"

boolean
odm_check_power_status(void *dm_void)
{
	return true;
}

void halrf_update_pwr_track(void *dm_void, u8 rate)
{
	struct dm_struct *dm = (struct dm_struct *)dm_void;

	RF_DBG(dm, DBG_RF_TX_PWR_TRACK, "Pwr Track Get rate=0x%x\n", rate);

	dm->tx_rate = rate;
}

void halrf_set_pwr_track(void *dm_void, u8 enable)
{
	struct dm_struct *dm = (struct dm_struct *)dm_void;
	struct dm_rf_calibration_struct *cali_info = &dm->rf_calibrate_info;
	struct _hal_rf_ *rf = &(dm->rf_table);
	struct txpwrtrack_cfg c;
	u8 i;

	configure_txpower_track(dm, &c);
	if (enable) {
		rf->rf_supportability = rf->rf_supportability | HAL_RF_TX_PWR_TRACK;
		if (cali_info->txpowertrack_control == 1 || cali_info->txpowertrack_control == 3)
			halrf_do_tssi(dm);
	} else {
		rf->rf_supportability = rf->rf_supportability & ~HAL_RF_TX_PWR_TRACK;
		odm_clear_txpowertracking_state(dm);
		halrf_do_tssi(dm);
		halrf_calculate_tssi_codeword(dm);
		halrf_set_tssi_codeword(dm);
		
	}

	if (cali_info->txpowertrack_control == 2 ||
		cali_info->txpowertrack_control == 3 ||
		cali_info->txpowertrack_control == 4 ||
		cali_info->txpowertrack_control == 5)
		halrf_txgapk_reload_tx_gain(dm);
}

