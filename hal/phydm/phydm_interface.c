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
 ************************************************************/

#include "mp_precomp.h"
#include "phydm_precomp.h"

/*@
 * ODM IO Relative API.
 */

u8 odm_read_1byte(struct dm_struct *dm, u32 reg_addr)
{
	void *adapter = dm->adapter;
	return rtw_read8(adapter, reg_addr);
}

u16 odm_read_2byte(struct dm_struct *dm, u32 reg_addr)
{
	void *adapter = dm->adapter;
	return rtw_read16(adapter, reg_addr);
}

u32 odm_read_4byte(struct dm_struct *dm, u32 reg_addr)
{
	void *adapter = dm->adapter;
	return rtw_read32(adapter, reg_addr);
}

void odm_write_1byte(struct dm_struct *dm, u32 reg_addr, u8 data)
{
	void *adapter = dm->adapter;
	rtw_write8(adapter, reg_addr, data);

	if (dm->en_reg_mntr_byte)
		pr_debug("1byte:addr=0x%x, data=0x%x\n", reg_addr, data);
}

void odm_write_2byte(struct dm_struct *dm, u32 reg_addr, u16 data)
{
	void *adapter = dm->adapter;
	rtw_write16(adapter, reg_addr, data);

	if (dm->en_reg_mntr_byte)
		pr_debug("2byte:addr=0x%x, data=0x%x\n", reg_addr, data);
}

void odm_write_4byte(struct dm_struct *dm, u32 reg_addr, u32 data)
{
	void *adapter = dm->adapter;
	rtw_write32(adapter, reg_addr, data);

	if (dm->en_reg_mntr_byte)
		pr_debug("4byte:addr=0x%x, data=0x%x\n", reg_addr, data);
}

void odm_set_mac_reg(struct dm_struct *dm, u32 reg_addr, u32 bit_mask, u32 data)
{
#if (DM_ODM_SUPPORT_TYPE & (ODM_AP))
	phy_set_bb_reg(dm->priv, reg_addr, bit_mask, data);
#elif (DM_ODM_SUPPORT_TYPE & ODM_WIN)
	void *adapter = dm->adapter;
	PHY_SetBBReg(adapter, reg_addr, bit_mask, data);
#elif (DM_ODM_SUPPORT_TYPE & ODM_CE) && defined(DM_ODM_CE_MAC80211)
	struct rtl_priv *rtlpriv = (struct rtl_priv *)dm->adapter;

	rtl_set_bbreg(rtlpriv->hw, reg_addr, bit_mask, data);
#elif (DM_ODM_SUPPORT_TYPE & ODM_CE) && defined(DM_ODM_CE_MAC80211_V2)
	struct rtw_dev *rtwdev = dm->adapter;

	rtw_set_reg_with_mask(rtwdev, reg_addr, bit_mask, data);
#elif (DM_ODM_SUPPORT_TYPE & ODM_IOT)
	phy_set_bb_reg(dm->adapter, reg_addr, bit_mask, data);
#else
	phy_set_bb_reg(dm->adapter, reg_addr, bit_mask, data);
#endif

	if (dm->en_reg_mntr_mac)
		pr_debug("MAC:addr=0x%x, mask=0x%x, data=0x%x\n",
			 reg_addr, bit_mask, data);
}

u32 odm_get_mac_reg(struct dm_struct *dm, u32 reg_addr, u32 bit_mask)
{
#if (DM_ODM_SUPPORT_TYPE & (ODM_AP))
	return phy_query_bb_reg(dm->priv, reg_addr, bit_mask);
#elif (DM_ODM_SUPPORT_TYPE & ODM_WIN)
	return PHY_QueryMacReg(dm->adapter, reg_addr, bit_mask);
#elif (DM_ODM_SUPPORT_TYPE & ODM_CE) && defined(DM_ODM_CE_MAC80211)
	struct rtl_priv *rtlpriv = (struct rtl_priv *)dm->adapter;

	return rtl_get_bbreg(rtlpriv->hw, reg_addr, bit_mask);
#elif (DM_ODM_SUPPORT_TYPE & ODM_CE) && defined(DM_ODM_CE_MAC80211_V2)
	struct rtw_dev *rtwdev = dm->adapter;

	return rtw_get_reg_with_mask(rtwdev, reg_addr, bit_mask);
#elif (DM_ODM_SUPPORT_TYPE & ODM_IOT)
	return phy_query_bb_reg(dm->adapter, reg_addr, bit_mask);
#else
	return phy_query_mac_reg(dm->adapter, reg_addr, bit_mask);
#endif
}

void odm_set_bb_reg(struct dm_struct *dm, u32 reg_addr, u32 bit_mask, u32 data)
{
#if (DM_ODM_SUPPORT_TYPE & (ODM_AP))
	phy_set_bb_reg(dm->priv, reg_addr, bit_mask, data);
#elif (DM_ODM_SUPPORT_TYPE & ODM_WIN)
	void *adapter = dm->adapter;
	PHY_SetBBReg(adapter, reg_addr, bit_mask, data);
#elif (DM_ODM_SUPPORT_TYPE & ODM_CE) && defined(DM_ODM_CE_MAC80211)
	struct rtl_priv *rtlpriv = (struct rtl_priv *)dm->adapter;

	rtl_set_bbreg(rtlpriv->hw, reg_addr, bit_mask, data);
#elif (DM_ODM_SUPPORT_TYPE & ODM_CE) && defined(DM_ODM_CE_MAC80211_V2)
	struct rtw_dev *rtwdev = dm->adapter;

	rtw_set_reg_with_mask(rtwdev, reg_addr, bit_mask, data);
#elif (DM_ODM_SUPPORT_TYPE & ODM_IOT)
	phy_set_bb_reg(dm->adapter, reg_addr, bit_mask, data);
#else
	phy_set_bb_reg(dm->adapter, reg_addr, bit_mask, data);
#endif

	if (dm->en_reg_mntr_bb)
		pr_debug("BB:addr=0x%x, mask=0x%x, data=0x%x\n",
			 reg_addr, bit_mask, data);
}

u32 odm_get_bb_reg(struct dm_struct *dm, u32 reg_addr, u32 bit_mask)
{
#if (DM_ODM_SUPPORT_TYPE & (ODM_AP))
	return phy_query_bb_reg(dm->priv, reg_addr, bit_mask);
#elif (DM_ODM_SUPPORT_TYPE & ODM_WIN)
	void *adapter = dm->adapter;
	return PHY_QueryBBReg(adapter, reg_addr, bit_mask);
#elif (DM_ODM_SUPPORT_TYPE & ODM_CE) && defined(DM_ODM_CE_MAC80211)
	struct rtl_priv *rtlpriv = (struct rtl_priv *)dm->adapter;

	return rtl_get_bbreg(rtlpriv->hw, reg_addr, bit_mask);
#elif (DM_ODM_SUPPORT_TYPE & ODM_CE) && defined(DM_ODM_CE_MAC80211_V2)
	struct rtw_dev *rtwdev = dm->adapter;

	return rtw_get_reg_with_mask(rtwdev, reg_addr, bit_mask);
#elif (DM_ODM_SUPPORT_TYPE & ODM_IOT)
	return phy_query_bb_reg(dm->adapter, reg_addr, bit_mask);
#else
	return phy_query_bb_reg(dm->adapter, reg_addr, bit_mask);
#endif
}

void odm_set_rf_reg(struct dm_struct *dm, u8 e_rf_path, u32 reg_addr,
		    u32 bit_mask, u32 data)
{
	phy_set_rf_reg(dm->adapter, e_rf_path, reg_addr, bit_mask, data);

	if (dm->en_reg_mntr_rf)
		pr_debug("RF:path=0x%x, addr=0x%x, mask=0x%x, data=0x%x\n",
			 e_rf_path, reg_addr, bit_mask, data);
}

u32 odm_get_rf_reg(struct dm_struct *dm, u8 e_rf_path, u32 reg_addr,
		   u32 bit_mask)
{
#if (DM_ODM_SUPPORT_TYPE & (ODM_AP))
	return phy_query_rf_reg(dm->priv, e_rf_path, reg_addr, bit_mask, 1);
#elif (DM_ODM_SUPPORT_TYPE & ODM_WIN)
	void *adapter = dm->adapter;
	return PHY_QueryRFReg(adapter, e_rf_path, reg_addr, bit_mask);
#elif (DM_ODM_SUPPORT_TYPE & ODM_CE) && defined(DM_ODM_CE_MAC80211)
	struct rtl_priv *rtlpriv = (struct rtl_priv *)dm->adapter;

	return rtl_get_rfreg(rtlpriv->hw, e_rf_path, reg_addr, bit_mask);
#elif (DM_ODM_SUPPORT_TYPE & ODM_CE) && defined(DM_ODM_CE_MAC80211_V2)
	struct rtw_dev *rtwdev = dm->adapter;

	return rtw_read_rf(rtwdev, e_rf_path, reg_addr, bit_mask);
#elif (DM_ODM_SUPPORT_TYPE & ODM_IOT)
	return phy_query_rf_reg(dm->adapter, e_rf_path, reg_addr, bit_mask);
#else
	return phy_query_rf_reg(dm->adapter, e_rf_path, reg_addr, bit_mask);
#endif
}

enum hal_status
phydm_set_reg_by_fw(struct dm_struct *dm, enum phydm_halmac_param config_type,
		    u32 offset, u32 data, u32 mask, enum rf_path e_rf_path,
		    u32 delay_time)
{
	PHYDM_DBG(dm, DBG_CMN, "Not support for CE MAC80211 driver!\n");
	return HAL_STATUS_FAILURE;
}

/*@
 * ODM Memory relative API.
 */
void odm_allocate_memory(struct dm_struct *dm, void **ptr, u32 length)
{
	*ptr = rtw_zvmalloc(length);
}

/* @length could be ignored, used to detect memory leakage. */
void odm_free_memory(struct dm_struct *dm, void *ptr, u32 length)
{
	rtw_vmfree(ptr, length);
}

void odm_move_memory(struct dm_struct *dm, void *dest, void *src, u32 length)
{
	_rtw_memcpy(dest, src, length);
}

void odm_memory_set(struct dm_struct *dm, void *pbuf, s8 value, u32 length)
{
	_rtw_memset(pbuf, value, length);
}

s32 odm_compare_memory(struct dm_struct *dm, void *buf1, void *buf2, u32 length)
{
	return _rtw_memcmp(buf1, buf2, length);
}

/*@
 * ODM MISC relative API.
 */
void odm_acquire_spin_lock(struct dm_struct *dm, enum rt_spinlock_type type)
{
	void *adapter = dm->adapter;
	rtw_odm_acquirespinlock(adapter, type);
}

void odm_release_spin_lock(struct dm_struct *dm, enum rt_spinlock_type type)
{
	void *adapter = dm->adapter;
	rtw_odm_releasespinlock(adapter, type);
}


/*@
 * ODM Timer relative API.
 */

void ODM_delay_ms(u32 ms)
{
	rtw_mdelay_os(ms);
}

void ODM_delay_us(u32 us)
{
	rtw_udelay_os(us);
}

void ODM_sleep_ms(u32 ms)
{
	rtw_msleep_os(ms);
}

void ODM_sleep_us(u32 us)
{
	rtw_usleep_os(us);
}

void odm_set_timer(struct dm_struct *dm, struct phydm_timer_list *timer,
		   u32 ms_delay)
{
	_set_timer(timer, ms_delay); /* @ms */
}

void odm_initialize_timer(struct dm_struct *dm, struct phydm_timer_list *timer,
			  void *call_back_func, void *context,
			  const char *sz_id)
{
	struct _ADAPTER *adapter = dm->adapter;

	_init_timer(timer, adapter->pnetdev, call_back_func, dm);
}

void odm_cancel_timer(struct dm_struct *dm, struct phydm_timer_list *timer)
{
	_cancel_timer_ex(timer);
}

void odm_release_timer(struct dm_struct *dm, struct phydm_timer_list *timer)
{

}

u8 phydm_trans_h2c_id(struct dm_struct *dm, u8 phydm_h2c_id)
{
	u8 platform_h2c_id = phydm_h2c_id;

	switch (phydm_h2c_id) {
	/* @1 [0] */
	case ODM_H2C_RSSI_REPORT:

		platform_h2c_id = H2C_RSSI_SETTING;


		break;

	/* @1 [3] */
	case ODM_H2C_WIFI_CALIBRATION:

		break;

	/* @1 [4] */
	case ODM_H2C_IQ_CALIBRATION:

		break;
	/* @1 [5] */
	case ODM_H2C_RA_PARA_ADJUST:



		break;

	/* @1 [6] */
	case PHYDM_H2C_DYNAMIC_TX_PATH:


		break;

	/* @[7]*/
	case PHYDM_H2C_FW_TRACE_EN:


		platform_h2c_id = 0x49;


		break;

	case PHYDM_H2C_TXBF:
		break;

	case PHYDM_H2C_MU:
		break;

	default:
		platform_h2c_id = phydm_h2c_id;
		break;
	}

	return platform_h2c_id;
}

/*@ODM FW relative API.*/

void odm_fill_h2c_cmd(struct dm_struct *dm, u8 phydm_h2c_id, u32 cmd_len,
		      u8 *cmd_buf)
{
	_adapter *adapter = dm->adapter;
	u8 h2c_id = phydm_trans_h2c_id(dm, phydm_h2c_id);

	PHYDM_DBG(dm, DBG_RA, "[H2C]  h2c_id=((0x%x))\n", h2c_id);

	rtw_hal_fill_h2c_cmd(adapter, h2c_id, cmd_len, cmd_buf);
}

u8 phydm_c2H_content_parsing(void *dm_void, u8 c2h_cmd_id, u8 c2h_cmd_len,
			     u8 *tmp_buf)
{
	struct dm_struct *dm = (struct dm_struct *)dm_void;
	u8 extend_c2h_sub_id = 0;
	u8 find_c2h_cmd = true;

	if (c2h_cmd_len > 12 || c2h_cmd_len == 0) {
		pr_debug("[Warning] Error C2H ID=%d, len=%d\n",
			 c2h_cmd_id, c2h_cmd_len);

		find_c2h_cmd = false;
		return find_c2h_cmd;
	}

	switch (c2h_cmd_id) {
	case PHYDM_C2H_DBG:
		phydm_fw_trace_handler(dm, tmp_buf, c2h_cmd_len);
		break;

	case PHYDM_C2H_RA_RPT:
		phydm_c2h_ra_report_handler(dm, tmp_buf, c2h_cmd_len);
		break;

	case PHYDM_C2H_RA_PARA_RPT:
		odm_c2h_ra_para_report_handler(dm, tmp_buf, c2h_cmd_len);
		break;
#ifdef CONFIG_PATH_DIVERSITY
	case PHYDM_C2H_DYNAMIC_TX_PATH_RPT:
		if (dm->support_ic_type & (ODM_RTL8814A))
			phydm_c2h_dtp_handler(dm, tmp_buf, c2h_cmd_len);
		break;
#endif

	case PHYDM_C2H_IQK_FINISH:
		break;

	case PHYDM_C2H_CLM_MONITOR:
		phydm_clm_c2h_report_handler(dm, tmp_buf, c2h_cmd_len);
		break;

	case PHYDM_C2H_DBG_CODE:
		phydm_fw_trace_handler_code(dm, tmp_buf, c2h_cmd_len);
		break;

	case PHYDM_C2H_EXTEND:
		extend_c2h_sub_id = tmp_buf[0];
		if (extend_c2h_sub_id == PHYDM_EXTEND_C2H_DBG_PRINT)
			phydm_fw_trace_handler_8051(dm, tmp_buf, c2h_cmd_len);

		break;

	default:
		find_c2h_cmd = false;
		break;
	}

	return find_c2h_cmd;
}

u64 odm_get_current_time(struct dm_struct *dm)
{
	return rtw_get_current_time();
}

u64 odm_get_progressing_time(struct dm_struct *dm, u64 start_time)
{
	return rtw_get_passing_time_ms((systime)start_time);
}


void phydm_set_hw_reg_handler_interface(struct dm_struct *dm, u8 RegName,
					u8 *val)
{
	struct _ADAPTER *adapter = dm->adapter;

	adapter->hal_func.set_hw_reg_handler(adapter, RegName, val);

}

void phydm_get_hal_def_var_handler_interface(struct dm_struct *dm,
					     enum _HAL_DEF_VARIABLE e_variable,
					     void *value)
{
	struct _ADAPTER *adapter = dm->adapter;

	adapter->hal_func.get_hal_def_var_handler(adapter, e_variable, value);

}


void odm_set_tx_power_index_by_rate_section(struct dm_struct *dm,
					    enum rf_path path, u8 ch,
					    u8 section)
{
	phy_set_tx_power_index_by_rate_section(dm->adapter, path, ch, section);
}

u8 odm_get_tx_power_index(struct dm_struct *dm, enum rf_path path, u8 rate,
			  u8 bw, u8 ch)
{
	return phy_get_tx_power_index(dm->adapter, path, rate, bw, ch);
}

u8 odm_efuse_one_byte_read(struct dm_struct *dm, u16 addr, u8 *data,
			   boolean b_pseu_do_test)
{
	return efuse_onebyte_read(dm->adapter, addr, data, b_pseu_do_test);
}

void odm_efuse_logical_map_read(struct dm_struct *dm, u8 type, u16 offset,
				u32 *data)
{
	efuse_logical_map_read(dm->adapter, type, offset, data);
}

enum hal_status
odm_iq_calibrate_by_fw(struct dm_struct *dm, u8 clear, u8 segment)
{
	enum hal_status iqk_result = HAL_STATUS_FAILURE;

	iqk_result = rtw_phydm_fw_iqk(dm, clear, segment);
	return iqk_result;
}

enum hal_status
odm_dpk_by_fw(struct dm_struct *dm)
{
	enum hal_status dpk_result = HAL_STATUS_FAILURE;
#if 0

	dpk_result = rtw_phydm_fw_dpk(dm);

#endif
	return dpk_result;
}

void phydm_cmn_sta_info_hook(struct dm_struct *dm, u8 mac_id,
			     struct cmn_sta_info *pcmn_sta_info)
{
	dm->phydm_sta_info[mac_id] = pcmn_sta_info;

	if (is_sta_active(pcmn_sta_info))
		dm->phydm_macid_table[pcmn_sta_info->mac_id] = mac_id;
}

void phydm_macid2sta_idx_table(struct dm_struct *dm, u8 entry_idx,
			       struct cmn_sta_info *pcmn_sta_info)
{
	if (is_sta_active(pcmn_sta_info))
		dm->phydm_macid_table[pcmn_sta_info->mac_id] = entry_idx;
}

void phydm_add_interrupt_mask_handler(struct dm_struct *dm, u8 interrupt_type)
{
}

void phydm_enable_rx_related_interrupt_handler(struct dm_struct *dm)
{
}

void phydm_iqk_wait(struct dm_struct *dm, u32 timeout)
{
	PHYDM_DBG(dm, DBG_CMN, "Not support for CE MAC80211 driver!\n");
}

u8 phydm_get_hwrate_to_mrate(struct dm_struct *dm, u8 rate)
{
	return 0;
}

void phydm_set_crystalcap(struct dm_struct *dm, u8 crystal_cap)
{
}

void phydm_run_in_thread_cmd(struct dm_struct *dm, void (*func)(void *),
			     void *context)
{
	PHYDM_DBG(dm, DBG_CMN, "Not support for CE MAC80211 driver!\n");
}

u8 phydm_get_tx_rate(struct dm_struct *dm)
{
	struct _hal_rf_ *rf = &dm->rf_table;
	u8 tx_rate = 0xff;
	u8 mpt_rate_index = 0;

	if (*dm->mp_mode == 1) {
#if (DM_ODM_SUPPORT_TYPE & (ODM_WIN | ODM_CE))
#ifdef CONFIG_MP_INCLUDED
		if (rf->mp_rate_index)
			mpt_rate_index = *rf->mp_rate_index;

		tx_rate = mpt_to_mgnt_rate(mpt_rate_index);
#endif
#endif
	} else {
		u16 rate = *dm->forced_data_rate;

		if (!rate) { /*auto rate*/
			if (dm->number_linked_client != 0)
				tx_rate = hw_rate_to_m_rate(dm->tx_rate);
			else
				tx_rate = rf->p_rate_index;
		} else { /*force rate*/
			tx_rate = (u8)rate;
		}
	}

	return tx_rate;
}

u8 phydm_get_tx_power_dbm(struct dm_struct *dm, u8 rf_path,
					u8 rate, u8 bandwidth, u8 channel)
{
	u8 tx_power_dbm = 0;

	tx_power_dbm = phy_get_tx_power_final_absolute_value(dm->adapter, rf_path, rate, bandwidth, channel);

	return tx_power_dbm;
}

s16 phydm_get_tx_power_mdbm(struct dm_struct *dm, u8 rf_path,
					u8 rate, u8 bandwidth, u8 channel)
{
	s16 tx_power_dbm = 0;

	tx_power_dbm = rtw_odm_get_tx_power_mbm(dm, rf_path, rate, bandwidth, channel);

	return tx_power_dbm;
}

u32 phydm_rfe_ctrl_gpio(struct dm_struct *dm, u8 gpio_num)
{
	return rtw_phydm_rfe_ctrl_gpio(dm->adapter, gpio_num);
	return 0;
}

u64 phydm_division64(u64 x, u64 y)
{
	return rtw_division64(x, y);
}
