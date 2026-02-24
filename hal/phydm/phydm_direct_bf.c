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
 ***************************************************************/

#include "mp_precomp.h"
#include "phydm_precomp.h"
#ifdef CONFIG_DIRECTIONAL_BF
#ifdef PHYDM_COMPILE_IC_2SS
void phydm_iq_gen_en(void *dm_void)
{
	struct dm_struct *dm = (struct dm_struct *)dm_void;
	enum rf_path i = RF_PATH_A;
	enum rf_path path = RF_PATH_A;

	#if (ODM_IC_11AC_SERIES_SUPPORT)
	if (dm->support_ic_type & ODM_RTL8822B) {
		for (i = RF_PATH_A; i <= RF_PATH_B; i++) {
			/*RF mode table write enable*/
			odm_set_rf_reg(dm, path, RF_0xef, BIT(19), 0x1);
			/*Select RX mode*/
			odm_set_rf_reg(dm, path, RF_0x33, 0xF, 3);
			/*Set Table data*/
			odm_set_rf_reg(dm, path, RF_0x3e, 0xfffff, 0x00036);
			/*Set Table data*/
			odm_set_rf_reg(dm, path, RF_0x3f, 0xfffff, 0x5AFCE);
			/*RF mode table write disable*/
			odm_set_rf_reg(dm, path, RF_0xef, BIT(19), 0x0);
		}
	}
	#endif

	#if (ODM_IC_11N_SERIES_SUPPORT)
	if (dm->support_ic_type & ODM_RTL8192F) {
		/*RF mode table write enable*/
		odm_set_rf_reg(dm, RF_PATH_A, RF_0xef, 0x80000, 0x1);
		odm_set_rf_reg(dm, RF_PATH_B, RF_0xef, 0x80000, 0x1);
		/* Path A */
		odm_set_rf_reg(dm, RF_PATH_A, RF_0x30, 0xfffff, 0x08000);
		odm_set_rf_reg(dm, RF_PATH_A, RF_0x31, 0xfffff, 0x0005f);
		odm_set_rf_reg(dm, RF_PATH_A, RF_0x32, 0xfffff, 0x01042);
		odm_set_rf_reg(dm, RF_PATH_A, RF_0x30, 0xfffff, 0x18000);
		odm_set_rf_reg(dm, RF_PATH_A, RF_0x31, 0xfffff, 0x0004f);
		odm_set_rf_reg(dm, RF_PATH_A, RF_0x32, 0xfffff, 0x71fc2);
		/* Path B */
		odm_set_rf_reg(dm, RF_PATH_B, RF_0x30, 0xfffff, 0x08000);
		odm_set_rf_reg(dm, RF_PATH_B, RF_0x31, 0xfffff, 0x00050);
		odm_set_rf_reg(dm, RF_PATH_B, RF_0x32, 0xfffff, 0x01042);
		odm_set_rf_reg(dm, RF_PATH_B, RF_0x30, 0xfffff, 0x18000);
		odm_set_rf_reg(dm, RF_PATH_B, RF_0x31, 0xfffff, 0x00040);
		odm_set_rf_reg(dm, RF_PATH_B, RF_0x32, 0xfffff, 0x71fc2);
		/*RF mode table write disable*/
		odm_set_rf_reg(dm, RF_PATH_A, RF_0xef, 0x80000, 0x0);
		odm_set_rf_reg(dm, RF_PATH_B, RF_0xef, 0x80000, 0x0);
	}
	#endif

	#ifdef PHYDM_IC_JGR3_SERIES_SUPPORT
	if (dm->support_ic_type & ODM_RTL8197G) {
		/*RF mode table write enable*/
		/* Path A */
		odm_set_rf_reg(dm, RF_PATH_A, RF_0xef, 0x80000, 0x1);
		odm_set_rf_reg(dm, RF_PATH_A, RF_0x30, 0xfffff, 0x18000);
		odm_set_rf_reg(dm, RF_PATH_A, RF_0x31, 0xfffff, 0x000cf);
		odm_set_rf_reg(dm, RF_PATH_A, RF_0x32, 0xfffff, 0x71fc2);
		odm_set_rf_reg(dm, RF_PATH_A, RF_0xef, 0x80000, 0x0);

		/* Path B */
		odm_set_rf_reg(dm, RF_PATH_B, RF_0xef, 0x80000, 0x1);
		odm_set_rf_reg(dm, RF_PATH_B, RF_0x30, 0xfffff, 0x18000);
		odm_set_rf_reg(dm, RF_PATH_B, RF_0x31, 0xfffff, 0x000cf);
		odm_set_rf_reg(dm, RF_PATH_B, RF_0x32, 0xfffff, 0x71fc2);
		odm_set_rf_reg(dm, RF_PATH_B, RF_0x30, 0xfffff, 0x08000);
		odm_set_rf_reg(dm, RF_PATH_B, RF_0x31, 0xfffff, 0x000ef);
		odm_set_rf_reg(dm, RF_PATH_B, RF_0x32, 0xfffff, 0x01042);
		odm_set_rf_reg(dm, RF_PATH_B, RF_0xef, 0x80000, 0x0);
	}
	#endif

}

void phydm_dis_cdd(void *dm_void)
{
	struct dm_struct *dm = (struct dm_struct *)dm_void;

	#if (ODM_IC_11AC_SERIES_SUPPORT)
	if (dm->support_ic_type & ODM_IC_11AC_SERIES) {
		odm_set_bb_reg(dm, R_0x808, 0x3ffff00, 0);
		odm_set_bb_reg(dm, R_0x9ac, 0x1fff, 0);
		odm_set_bb_reg(dm, R_0x9ac, BIT(13), 1);
	}
	#endif
	#if (ODM_IC_11N_SERIES_SUPPORT)
	if (dm->support_ic_type & ODM_IC_11N_SERIES) {
		odm_set_bb_reg(dm, R_0x90c, 0xffffffff, 0x83321333);
		/* Set Tx delay setting for CCK pathA,B*/
		odm_set_bb_reg(dm, R_0xa2c, 0xf0000000, 0);
		/*Enable Tx CDD for HT part when spatial expansion is applied*/
		odm_set_bb_reg(dm, R_0xd00, BIT(8), 0);
		/* Tx CDD for Legacy*/
		odm_set_bb_reg(dm, R_0xd04, 0xf0000, 0);
		/* Tx CDD for non-HT*/
		odm_set_bb_reg(dm, R_0xd0c, 0x3c0, 0);
		/* Tx CDD for HT SS1*/
		odm_set_bb_reg(dm, R_0xd0c, 0xf8000, 0);
	}
	#endif
	#ifdef PHYDM_IC_JGR3_SERIES_SUPPORT
	if (dm->support_ic_type & ODM_IC_JGR3_SERIES) {
		/* Tx CDD for Legacy Preamble*/
		odm_set_bb_reg(dm, R_0x1cc0, 0xffffffff, 0x24800000);
		/* Tx CDD for HT Preamble*/
		odm_set_bb_reg(dm, R_0x1cb0, 0xffffffff, 0);
	}
	#endif
}

void phydm_pathb_q_matrix_rotate_en(void *dm_void)
{
	struct dm_struct *dm = (struct dm_struct *)dm_void;

	phydm_iq_gen_en(dm);

	/*#ifdef PHYDM_COMMON_API_SUPPORT*/
	/*path selection is controlled by driver*/
	#if 0
	if (!phydm_api_trx_mode(dm, BB_PATH_AB, BB_PATH_AB, BB_PATH_AB))
		return;
	#endif

	phydm_dis_cdd(dm);
	phydm_pathb_q_matrix_rotate(dm, 0);

	#if (ODM_IC_11AC_SERIES_SUPPORT)
	if (dm->support_ic_type & ODM_IC_11AC_SERIES) {
		/*Set Q matrix r_v11 =1*/
		odm_set_bb_reg(dm, R_0x195c, MASKDWORD, 0x40000);
		/*Set Q matrix enable*/
		odm_set_bb_reg(dm, R_0x191c, BIT(7), 1);
	}
	#endif
}

void phydm_pathb_q_matrix_rotate(void *dm_void, u16 idx)
{
	struct dm_struct *dm = (struct dm_struct *)dm_void;
	#if (ODM_IC_11AC_SERIES_SUPPORT)
	u32 phase_table_0[ANGLE_NUM] = {0x40000, 0x376CF, 0x20000, 0x00000,
					0xFE0000, 0xFC8930, 0xFC0000,
					0xFC8930, 0xFDFFFF, 0x000000,
					0x020000, 0x0376CF};
	u32 phase_table_1[ANGLE_NUM] = {0x00000, 0x1FFFF, 0x376CF, 0x40000,
					0x0376CF, 0x01FFFF, 0x000000,
					0xFDFFFF, 0xFC8930, 0xFC0000,
					0xFC8930, 0xFDFFFF};
	#endif
	#if (ODM_IC_11N_SERIES_SUPPORT)
	u32 phase_table_n_0[ANGLE_NUM] = {0x00, 0x0B, 0x02, 0x00, 0x02, 0x02,
					  0x04, 0x02, 0x0D, 0x09, 0x04, 0x0B};
	u32 phase_table_n_1[ANGLE_NUM] = {0x40000100, 0x377F00DD, 0x201D8880,
					  0x00000000, 0xE01D8B80, 0xC8BF0322,
					  0xC000FF00, 0xC8BF0322, 0xDFE2777F,
					  0xFFC003FF, 0x20227480, 0x377F00DD};
	u32 phase_table_n_2[ANGLE_NUM] = {0x00, 0x1E, 0x3C, 0x4C, 0x3C, 0x1E,
					  0x0F, 0xD2, 0xC3, 0xC4, 0xC3, 0xD2};
	#endif
	if (idx >= ANGLE_NUM) {
		pr_debug("[%s]warning Phase Set Error: %d\n", __func__, idx);
		return;
	}

	switch (dm->ic_ip_series) {
	#if (ODM_IC_11AC_SERIES_SUPPORT == 1)
	case PHYDM_IC_AC:
		/*Set Q matrix r_v21*/
		odm_set_bb_reg(dm, R_0x1954, 0xffffff, phase_table_0[idx]);
		odm_set_bb_reg(dm, R_0x1950, 0xffffff, phase_table_1[idx]);
		break;
	#endif

	#if (ODM_IC_11N_SERIES_SUPPORT == 1)
	case PHYDM_IC_N:
		/*Set Q matrix r_v21*/
		odm_set_bb_reg(dm, R_0xc4c, 0xff000000, phase_table_n_0[idx]);
		odm_set_bb_reg(dm, R_0xc88, 0xffffffff, phase_table_n_1[idx]);
		odm_set_bb_reg(dm, R_0xc9c, 0xff000000, phase_table_n_2[idx]);
		break;
	#endif

	default:
		break;
	}
}

/*Before use this API, Fill correct Tx Des. and Disable STBC in advance*/
void phydm_set_direct_bfer(void *dm_void, u16 phs_idx, u8 su_idx)
{
	struct dm_struct *dm = (struct dm_struct *)dm_void;
} //end function

/*Before use this API, Disable STBC in advance*/
/*only 1SS rate can improve performance*/
void phydm_set_direct_bfer_txdesc_en(void *dm_void, u8 enable)
{
	struct dm_struct *dm = (struct dm_struct *)dm_void;
} //end function
#endif
#endif
