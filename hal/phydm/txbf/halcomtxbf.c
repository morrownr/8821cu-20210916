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
/*@************************************************************
 * Description:
 *
 * This file is for TXBF mechanism
 *
 ************************************************************/
#include "mp_precomp.h"
#include "../phydm_precomp.h"

#ifdef PHYDM_BEAMFORMING_SUPPORT
/*@Beamforming halcomtxbf API create by YuChen 2015/05*/

void hal_com_txbf_beamform_init(
	void *dm_void)
{
	struct dm_struct *dm = (struct dm_struct *)dm_void;
	boolean is_iqgen_setting_ok = false;

	if (dm->support_ic_type & ODM_RTL8814A) {
		is_iqgen_setting_ok = phydm_beamforming_set_iqgen_8814A(dm);
		PHYDM_DBG(dm, DBG_TXBF, "[%s] is_iqgen_setting_ok = %d\n",
			  __func__, is_iqgen_setting_ok);
	}
}

/*Only used for MU BFer Entry when get GID management frame (self as MU STA)*/
void hal_com_txbf_config_gtab(
	void *dm_void)
{
	struct dm_struct *dm = (struct dm_struct *)dm_void;

	if (dm->support_ic_type & ODM_RTL8822B)
		hal_txbf_8822b_config_gtab(dm);
}

void phydm_beamform_set_sounding_enter(
	void *dm_void)
{
	struct dm_struct *dm = (struct dm_struct *)dm_void;
	hal_com_txbf_enter_work_item_callback(dm);
}

void phydm_beamform_set_sounding_leave(
	void *dm_void)
{
	struct dm_struct *dm = (struct dm_struct *)dm_void;
	hal_com_txbf_leave_work_item_callback(dm);
}

void phydm_beamform_set_sounding_rate(
	void *dm_void)
{
	struct dm_struct *dm = (struct dm_struct *)dm_void;
	hal_com_txbf_rate_work_item_callback(dm);
}

void phydm_beamform_set_sounding_status(
	void *dm_void)
{
	struct dm_struct *dm = (struct dm_struct *)dm_void;
	hal_com_txbf_status_work_item_callback(dm);
}

void phydm_beamform_set_sounding_fw_ndpa(
	void *dm_void)
{
	struct dm_struct *dm = (struct dm_struct *)dm_void;
	hal_com_txbf_fw_ndpa_work_item_callback(dm);
}

void phydm_beamform_set_sounding_clk(
	void *dm_void)
{
	struct dm_struct *dm = (struct dm_struct *)dm_void;
	phydm_run_in_thread_cmd(dm, hal_com_txbf_clk_work_item_callback, dm);
}

void phydm_beamform_set_reset_tx_path(
	void *dm_void)
{
	struct dm_struct *dm = (struct dm_struct *)dm_void;
	hal_com_txbf_reset_tx_path_work_item_callback(dm);
}

void phydm_beamform_set_get_tx_rate(
	void *dm_void)
{
	struct dm_struct *dm = (struct dm_struct *)dm_void;
	hal_com_txbf_get_tx_rate_work_item_callback(dm);
}

void hal_com_txbf_enter_work_item_callback(
	void *dm_void
	)
{
	struct dm_struct *dm = (struct dm_struct *)dm_void;
	struct _HAL_TXBF_INFO *p_txbf_info = &dm->beamforming_info.txbf_info;
	u8 idx = p_txbf_info->txbf_idx;

	PHYDM_DBG(dm, DBG_TXBF, "[%s] Start!\n", __func__);

	if (dm->support_ic_type & (ODM_RTL8812 | ODM_RTL8821))
		hal_txbf_jaguar_enter(dm, idx);
	else if (dm->support_ic_type & ODM_RTL8192E)
		hal_txbf_8192e_enter(dm, idx);
	else if (dm->support_ic_type & ODM_RTL8814A)
		hal_txbf_8814a_enter(dm, idx);
	else if (dm->support_ic_type & ODM_RTL8822B)
		hal_txbf_8822b_enter(dm, idx);
}

void hal_com_txbf_leave_work_item_callback(
	void *dm_void
	)
{
	struct dm_struct *dm = (struct dm_struct *)dm_void;
	struct _HAL_TXBF_INFO *p_txbf_info = &dm->beamforming_info.txbf_info;

	u8 idx = p_txbf_info->txbf_idx;

	PHYDM_DBG(dm, DBG_TXBF, "[%s] Start!\n", __func__);

	if (dm->support_ic_type & (ODM_RTL8812 | ODM_RTL8821))
		hal_txbf_jaguar_leave(dm, idx);
	else if (dm->support_ic_type & ODM_RTL8192E)
		hal_txbf_8192e_leave(dm, idx);
	else if (dm->support_ic_type & ODM_RTL8814A)
		hal_txbf_8814a_leave(dm, idx);
	else if (dm->support_ic_type & ODM_RTL8822B)
		hal_txbf_8822b_leave(dm, idx);
}

void hal_com_txbf_fw_ndpa_work_item_callback(
	void *dm_void
	)
{
	struct dm_struct *dm = (struct dm_struct *)dm_void;
	struct _HAL_TXBF_INFO *p_txbf_info = &dm->beamforming_info.txbf_info;
	u8 idx = p_txbf_info->ndpa_idx;

	PHYDM_DBG(dm, DBG_TXBF, "[%s] Start!\n", __func__);

	if (dm->support_ic_type & (ODM_RTL8812 | ODM_RTL8821))
		hal_txbf_jaguar_fw_txbf(dm, idx);
	else if (dm->support_ic_type & ODM_RTL8192E)
		hal_txbf_8192e_fw_tx_bf(dm, idx);
	else if (dm->support_ic_type & ODM_RTL8814A)
		hal_txbf_8814a_fw_txbf(dm, idx);
	else if (dm->support_ic_type & ODM_RTL8822B)
		hal_txbf_8822b_fw_txbf(dm, idx);
}

void hal_com_txbf_clk_work_item_callback(
	void *dm_void
	)
{
	struct dm_struct *dm = (struct dm_struct *)dm_void;

	PHYDM_DBG(dm, DBG_TXBF, "[%s] Start!\n", __func__);

	if (dm->support_ic_type & ODM_RTL8812)
		hal_txbf_jaguar_clk_8812a(dm);
}

void hal_com_txbf_rate_work_item_callback(
	void *dm_void
	)
{
	struct dm_struct *dm = (struct dm_struct *)dm_void;
	struct _HAL_TXBF_INFO *p_txbf_info = &dm->beamforming_info.txbf_info;
	u8 BW = p_txbf_info->BW;
	u8 rate = p_txbf_info->rate;

	PHYDM_DBG(dm, DBG_TXBF, "[%s] Start!\n", __func__);

	if (dm->support_ic_type & ODM_RTL8812)
		hal_txbf_8812a_set_ndpa_rate(dm, BW, rate);
	else if (dm->support_ic_type & ODM_RTL8192E)
		hal_txbf_8192e_set_ndpa_rate(dm, BW, rate);
	else if (dm->support_ic_type & ODM_RTL8814A)
		hal_txbf_8814a_set_ndpa_rate(dm, BW, rate);
}


void hal_com_txbf_status_work_item_callback(
	void *dm_void
	)
{
	struct dm_struct *dm = (struct dm_struct *)dm_void;
	struct _HAL_TXBF_INFO *p_txbf_info = &dm->beamforming_info.txbf_info;

	u8 idx = p_txbf_info->txbf_idx;

	PHYDM_DBG(dm, DBG_TXBF, "[%s] Start!\n", __func__);

	if (dm->support_ic_type & (ODM_RTL8812 | ODM_RTL8821))
		hal_txbf_jaguar_status(dm, idx);
	else if (dm->support_ic_type & ODM_RTL8192E)
		hal_txbf_8192e_status(dm, idx);
	else if (dm->support_ic_type & ODM_RTL8814A)
		hal_txbf_8814a_status(dm, idx);
	else if (dm->support_ic_type & ODM_RTL8822B)
		hal_txbf_8822b_status(dm, idx);
}

void hal_com_txbf_reset_tx_path_work_item_callback(
	void *dm_void
	)
{
	struct dm_struct *dm = (struct dm_struct *)dm_void;
	struct _HAL_TXBF_INFO *p_txbf_info = &dm->beamforming_info.txbf_info;

	u8 idx = p_txbf_info->txbf_idx;

	if (dm->support_ic_type & ODM_RTL8814A)
		hal_txbf_8814a_reset_tx_path(dm, idx);
}

void hal_com_txbf_get_tx_rate_work_item_callback(
	void *dm_void
	)
{
	struct dm_struct *dm = (struct dm_struct *)dm_void;

	if (dm->support_ic_type & ODM_RTL8814A)
		hal_txbf_8814a_get_tx_rate(dm);
}

boolean
hal_com_txbf_set(
	void *dm_void,
	u8 set_type,
	void *p_in_buf)
{
	struct dm_struct *dm = (struct dm_struct *)dm_void;
	u8 *p_u1_tmp = (u8 *)p_in_buf;
	struct _HAL_TXBF_INFO *p_txbf_info = &dm->beamforming_info.txbf_info;

	PHYDM_DBG(dm, DBG_TXBF, "[%s] set_type = 0x%X\n", __func__, set_type);

	switch (set_type) {
	case TXBF_SET_SOUNDING_ENTER:
		p_txbf_info->txbf_idx = *p_u1_tmp;
		phydm_beamform_set_sounding_enter(dm);
		break;

	case TXBF_SET_SOUNDING_LEAVE:
		p_txbf_info->txbf_idx = *p_u1_tmp;
		phydm_beamform_set_sounding_leave(dm);
		break;

	case TXBF_SET_SOUNDING_RATE:
		p_txbf_info->BW = p_u1_tmp[0];
		p_txbf_info->rate = p_u1_tmp[1];
		phydm_beamform_set_sounding_rate(dm);
		break;

	case TXBF_SET_SOUNDING_STATUS:
		p_txbf_info->txbf_idx = *p_u1_tmp;
		phydm_beamform_set_sounding_status(dm);
		break;

	case TXBF_SET_SOUNDING_FW_NDPA:
		p_txbf_info->ndpa_idx = *p_u1_tmp;
		phydm_beamform_set_sounding_fw_ndpa(dm);
		break;

	case TXBF_SET_SOUNDING_CLK:
		phydm_beamform_set_sounding_clk(dm);
		break;

	case TXBF_SET_TX_PATH_RESET:
		p_txbf_info->txbf_idx = *p_u1_tmp;
		phydm_beamform_set_reset_tx_path(dm);
		break;

	case TXBF_SET_GET_TX_RATE:
		phydm_beamform_set_get_tx_rate(dm);
		break;
	}

	return true;
}

#endif
