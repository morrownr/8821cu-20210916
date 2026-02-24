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

#ifndef __ODM_PRECOMP_H__
#define __ODM_PRECOMP_H__

#include "phydm_types.h"
#include "halrf/halrf_features.h"

	#define		TEST_FALG___		1

/* @2 Config Flags and Structs - defined by each ODM type */

	#ifdef DM_ODM_CE_MAC80211
		#include "../wifi.h"
		#include "rtl_phydm.h"
	#elif defined(DM_ODM_CE_MAC80211_V2)
		#include "../main.h"
		#include "../hw.h"
		#include "../fw.h"
	#endif
	#define __PACK
	#define __WLAN_ATTRIB_PACK__

/* @2 OutSrc Header Files */

#include "phydm.h"
#include "phydm_hwconfig.h"
#include "phydm_phystatus.h"
#include "phydm_debug.h"
#include "phydm_regdefine11ac.h"
#include "phydm_regdefine11n.h"
#include "phydm_interface.h"
#include "phydm_reg.h"
#include "halrf/halrf_debug.h"

#ifndef RTL8188E_SUPPORT
	#define	RTL8188E_SUPPORT	0
#endif
#ifndef RTL8812A_SUPPORT
	#define	RTL8812A_SUPPORT	0
#endif
#ifndef RTL8821A_SUPPORT
	#define	RTL8821A_SUPPORT	0
#endif
#ifndef RTL8192E_SUPPORT
	#define	RTL8192E_SUPPORT	0
#endif
#ifndef RTL8723B_SUPPORT
	#define	RTL8723B_SUPPORT	0
#endif
#ifndef RTL8814A_SUPPORT
	#define	RTL8814A_SUPPORT	0
#endif
#ifndef RTL8881A_SUPPORT
	#define	RTL8881A_SUPPORT	0
#endif
#ifndef RTL8822B_SUPPORT
	#define	RTL8822B_SUPPORT	0
#endif
#ifndef RTL8703B_SUPPORT
	#define	RTL8703B_SUPPORT	0
#endif
#ifndef RTL8195A_SUPPORT
	#define	RTL8195A_SUPPORT	0
#endif
#ifndef RTL8188F_SUPPORT
	#define	RTL8188F_SUPPORT	0
#endif
#ifndef RTL8723D_SUPPORT
	#define	RTL8723D_SUPPORT	0
#endif
#ifndef RTL8197F_SUPPORT
	#define	RTL8197F_SUPPORT	0
#endif
#ifndef RTL8821C_SUPPORT
	#define	RTL8821C_SUPPORT	0
#endif
#ifndef RTL8814B_SUPPORT
	#define	RTL8814B_SUPPORT	0
#endif
#ifndef RTL8198F_SUPPORT
	#define	RTL8198F_SUPPORT	0
#endif
#ifndef RTL8710B_SUPPORT
	#define	RTL8710B_SUPPORT	0
#endif
#ifndef RTL8192F_SUPPORT
	#define	RTL8192F_SUPPORT	0
#endif
#ifndef RTL8822C_SUPPORT
	#define	RTL8822C_SUPPORT	0
#endif
#ifndef RTL8195B_SUPPORT
	#define	RTL8195B_SUPPORT	0
#endif
#ifndef RTL8812F_SUPPORT
	#define	RTL8812F_SUPPORT	0
#endif
#ifndef RTL8197G_SUPPORT
	#define	RTL8197G_SUPPORT	0
#endif
#ifndef RTL8721D_SUPPORT
	#define	RTL8721D_SUPPORT	0
#endif
#ifndef RTL8710C_SUPPORT
	#define	RTL8710C_SUPPORT	0
#endif
#ifndef RTL8723F_SUPPORT
	#define	RTL8723F_SUPPORT	0
#endif
void phy_set_tx_power_limit(
	struct dm_struct *dm,
	u8 *regulation,
	u8 *band,
	u8 *bandwidth,
	u8 *rate_section,
	u8 *rf_path,
	u8 *channel,
	u8 *power_limit);

void phy_set_tx_power_limit_ex(struct dm_struct *dm, u8 regulation, u8 band,
			       u8 bandwidth, u8 rate_section, u8 rf_path,
			       u8 channel, s8 power_limit);

enum hal_status
rtw_phydm_fw_iqk(
	struct dm_struct *dm,
	u8 clear,
	u8 segment);

enum hal_status
rtw_phydm_fw_dpk(
	struct dm_struct *dm);

enum hal_status
rtw_phydm_cfg_phy_para(
	struct dm_struct *dm,
	enum phydm_halmac_param config_type,
	u32 offset,
	u32 data,
	u32 mask,
	enum rf_path e_rf_path,
	u32 delay_time);






#if (RTL8881A_SUPPORT == 1)/* @FOR_8881_IQK */
		#include "halrf/rtl8821a/halrf_iqk_8821a_ce.h"
#endif



#include "../halmac/halmac_reg2.h"








	#include "rtl8821c/phydm_hal_api8821c.h"
	#include "rtl8821c/halhwimg8821c_mac.h"
	#include "rtl8821c/halhwimg8821c_bb.h"
	#include "rtl8821c/phydm_regconfig8821c.h"
	#include "rtl8821c/phydm_rtl8821c.h"
	#include "halrf/rtl8821c/halrf_8821c.h"
	#include "halrf/rtl8821c/halhwimg8821c_rf.h"
	#include "halrf/rtl8821c/version_rtl8821c_rf.h"
	#include "rtl8821c/version_rtl8821c.h"
	#if (DM_ODM_SUPPORT_TYPE == ODM_CE)
		#ifdef DM_ODM_CE_MAC80211
		#include "../halmac/halmac_reg_8821c.h"
		#else
		#include "rtl8821c_hal.h"
		#endif
	#endif






#endif /* @__ODM_PRECOMP_H__ */
