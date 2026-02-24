/******************************************************************************
 *
 * Copyright(c) 2007 - 2017 Realtek Corporation.
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

#include "mp_precomp.h"
#include "phydm_precomp.h"

#if (defined(CONFIG_BB_TXBF_API))
#if (RTL8822B_SUPPORT == 1 || RTL8192F_SUPPORT == 1 || RTL8812F_SUPPORT == 1 ||\
	RTL8822C_SUPPORT == 1 || RTL8198F_SUPPORT == 1 || RTL8814B_SUPPORT == 1)
/*@Add by YuChen for 8822B MU-MIMO API*/

/*this function is only used for BFer*/
u8 phydm_get_ndpa_rate(void *dm_void)
{
	struct dm_struct *dm = (struct dm_struct *)dm_void;
	u8 ndpa_rate = ODM_RATE6M;

	if (dm->rssi_min >= 30) /*@link RSSI > 30%*/
		ndpa_rate = ODM_RATE24M;
	else if (dm->rssi_min <= 25)
		ndpa_rate = ODM_RATE6M;

	PHYDM_DBG(dm, DBG_TXBF, "[%s] ndpa_rate = 0x%x\n", __func__, ndpa_rate);

	return ndpa_rate;
}

/*this function is only used for BFer*/
u8 phydm_get_beamforming_sounding_info(void *dm_void, u16 *throughput,
				       u8 total_bfee_num, u8 *tx_rate)
{
	u8 idx = 0;
	u8 snddecision = 0xff;
	struct dm_struct *dm = (struct dm_struct *)dm_void;

	for (idx = 0; idx < total_bfee_num; idx++) {
		if (dm->support_ic_type & (ODM_RTL8814A)) {
			if ((tx_rate[idx] >= ODM_RATEVHTSS3MCS7 &&
			     tx_rate[idx] <= ODM_RATEVHTSS3MCS9))
				snddecision = snddecision & ~(1 << idx);
		} else if (dm->support_ic_type & (ODM_RTL8822B | ODM_RTL8822C |
			   ODM_RTL8812 | ODM_RTL8192F)) {
			if ((tx_rate[idx] >= ODM_RATEVHTSS2MCS7 &&
			     tx_rate[idx] <= ODM_RATEVHTSS2MCS9))
				snddecision = snddecision & ~(1 << idx);
		} else if (dm->support_ic_type & (ODM_RTL8814B)) {
			if ((tx_rate[idx] >= ODM_RATEVHTSS4MCS7 &&
			     tx_rate[idx] <= ODM_RATEVHTSS4MCS9))
				snddecision = snddecision & ~(1 << idx);
		}
	}

	for (idx = 0; idx < total_bfee_num; idx++) {
		if (throughput[idx] <= 10)
			snddecision = snddecision & ~(1 << idx);
	}

	PHYDM_DBG(dm, DBG_TXBF, "[%s] soundingdecision = 0x%x\n", __func__,
		  snddecision);

	return snddecision;
}

/*this function is only used for BFer*/
u8 phydm_get_mu_bfee_snding_decision(void *dm_void, u16 throughput)
{
	u8 snding_score = 0;
	struct dm_struct *dm = (struct dm_struct *)dm_void;

	/*throughput unit is Mbps*/
	if (throughput >= 500)
		snding_score = 100;
	else if (throughput >= 450)
		snding_score = 90;
	else if (throughput >= 400)
		snding_score = 80;
	else if (throughput >= 350)
		snding_score = 70;
	else if (throughput >= 300)
		snding_score = 60;
	else if (throughput >= 250)
		snding_score = 50;
	else if (throughput >= 200)
		snding_score = 40;
	else if (throughput >= 150)
		snding_score = 30;
	else if (throughput >= 100)
		snding_score = 20;
	else if (throughput >= 50)
		snding_score = 10;
	else
		snding_score = 0;

	PHYDM_DBG(dm, DBG_TXBF, "[%s] snding_score = 0x%x\n", __func__,
		  snding_score);

	return snding_score;
}

#endif
u8 beamforming_get_htndp_tx_rate(void *dm_void, u8 bfer_str_num)
{
	struct dm_struct *dm = (struct dm_struct *)dm_void;
	u8 nr_index = 0;
	u8 ndp_tx_rate;
/*@Find nr*/
	ndp_tx_rate = ODM_MGN_MCS8;

	return ndp_tx_rate;
}

u8 beamforming_get_vht_ndp_tx_rate(void *dm_void, u8 bfer_str_num)
{
	struct dm_struct *dm = (struct dm_struct *)dm_void;
	u8 nr_index = 0;
	u8 ndp_tx_rate;
/*@Find nr*/
	ndp_tx_rate = ODM_MGN_VHT2SS_MCS0;

	return ndp_tx_rate;
}

#ifdef PHYDM_IC_JGR3_SERIES_SUPPORT
/*this function is only used for BFer*/
void phydm_txbf_rfmode(void *dm_void, u8 su_bfee_cnt, u8 mu_bfee_cnt)
{
	struct dm_struct *dm = (struct dm_struct *)dm_void;
	u8 i;

	if (dm->rf_type == RF_1T1R)
		return;
}

void phydm_mu_rsoml_reset(void *dm_void)
{
	struct dm_struct *dm = (struct dm_struct *)dm_void;
	struct phydm_bf_rate_info_jgr3 *rateinfo = &dm->bf_rate_info_jgr3;

	PHYDM_DBG(dm, DBG_TXBF, "[MU RSOML] %s cnt reset\n", __func__);

	odm_memory_set(dm, &rateinfo->num_mu_vht_pkt[0], 0, VHT_RATE_NUM * 2);
	odm_memory_set(dm, &rateinfo->num_qry_vht_pkt[0], 0, VHT_RATE_NUM * 2);
}

void phydm_mu_rsoml_init(void *dm_void)
{
	struct dm_struct *dm = (struct dm_struct *)dm_void;
	struct phydm_bf_rate_info_jgr3 *rateinfo = &dm->bf_rate_info_jgr3;
	u32 val = 0;

	PHYDM_DBG(dm, DBG_TXBF, "[MU RSOML] %s\n", __func__);

	/*OFDM Tx*/
	val = odm_get_bb_reg(dm, R_0x820, MASKDWORD);
	rateinfo->tx_path_en_ofdm_2sts = (u8)((val & 0xf0) >> 4);
	rateinfo->tx_path_en_ofdm_1sts = (u8)(val & 0xf);
	/*OFDM Rx*/
	rateinfo->rx_path_en_ofdm = (u8)odm_get_bb_reg(dm, R_0x824, 0xf0000);

	rateinfo->enable = 1;
	rateinfo->mu_ratio_th = 30;
	rateinfo->pre_mu_ratio = 0;
	rateinfo->mu_set_trxpath = 0;
	rateinfo->mu_been_iot = 0;

	PHYDM_DBG(dm, DBG_TXBF, "[MU RSOML] %s tx1ss=%d, tx2ss=%d, rx=%d\n",
		  __func__, rateinfo->tx_path_en_ofdm_1sts,
		  rateinfo->tx_path_en_ofdm_2sts, rateinfo->rx_path_en_ofdm);

	phydm_mu_rsoml_reset(dm);
}

void phydm_mu_rsoml_decision(void *dm_void)
{
	struct dm_struct *dm = (struct dm_struct *)dm_void;
	struct phydm_bf_rate_info_jgr3 *rateinfo = &dm->bf_rate_info_jgr3;
	struct phydm_iot_center	*iot_table = &dm->iot_table;
	u8 offset = 0;
	u32 mu_ratio = 0;
	u32 su_pkt = 0;
	u32 mu_pkt = 0;
	u32 total_pkt = 0;

	if (rateinfo->tx_path_en_ofdm_2sts != 3 ||
	    rateinfo->rx_path_en_ofdm != 3) {
		PHYDM_DBG(dm, DBG_TXBF, "[MU RSOML] Init Not 2T2R 22CE\n");
		return;
	}

	PHYDM_DBG(dm, DBG_TXBF, "[MU RSOML] RSOML Decision eanble: %d\n",
		  rateinfo->enable);

	if (!rateinfo->enable)
		return;

	for (offset = 0; offset < VHT_RATE_NUM; offset++) {
		mu_pkt +=  rateinfo->num_mu_vht_pkt[offset];
		su_pkt +=  rateinfo->num_qry_vht_pkt[offset];
	}
	total_pkt = su_pkt + mu_pkt;

	if (total_pkt == 0)
		mu_ratio = 0;
	else
		mu_ratio = (mu_pkt * 100) / total_pkt; // unit:%

	PHYDM_DBG(dm, DBG_TXBF, "[MU RSOML] MU rx ratio: %d, total pkt: %d\n",
		  mu_ratio, total_pkt);

	if (mu_ratio > rateinfo->mu_ratio_th &&
	    rateinfo->pre_mu_ratio > rateinfo->mu_ratio_th) {
		PHYDM_DBG(dm, DBG_TXBF, "[MU RSOML] RSOML status remain\n");
	} else if (mu_ratio <= rateinfo->mu_ratio_th &&
		 rateinfo->pre_mu_ratio <= rateinfo->mu_ratio_th) {
		PHYDM_DBG(dm, DBG_TXBF, "[MU RSOML] RSOML status remain\n");
	} else if (mu_ratio > rateinfo->mu_ratio_th) {
		odm_set_bb_reg(dm, R_0xc00, BIT(26), 0);
		PHYDM_DBG(dm, DBG_TXBF, "[MU RSOML] RSOML OFF\n");
	} else {
		odm_set_bb_reg(dm, R_0xc00, BIT(26), 1);
		PHYDM_DBG(dm, DBG_TXBF, "[MU RSOML] RSOML ON\n");
	}

	PHYDM_DBG(dm, DBG_TXBF, "[MU IOT] set_trxpath=%d, patch_10120200=%d\n",
		  rateinfo->mu_set_trxpath, iot_table->patch_id_10120200);
	if (rateinfo->mu_set_trxpath && iot_table->patch_id_10120200) {
		if (mu_ratio > rateinfo->mu_ratio_th) {
			phydm_api_trx_mode(dm, BB_PATH_AB, BB_PATH_A,
					   BB_PATH_AUTO);
			PHYDM_DBG(dm, DBG_TXBF, "[MU IOT] 22C IOT 2T1R\n");
			rateinfo->mu_been_iot = 1;
		} else {
			phydm_api_trx_mode(dm, BB_PATH_AB, BB_PATH_AB,
					   BB_PATH_AUTO);
			PHYDM_DBG(dm, DBG_TXBF, "[MU IOT] 22C IOT 2T2R\n");
			rateinfo->mu_been_iot = 0;
		}
	} else if (rateinfo->mu_been_iot == 1) {
		if (odm_get_bb_reg(dm, R_0x824, 0xf0000) == 1) {
			phydm_api_trx_mode(dm, BB_PATH_AB, BB_PATH_AB,
					   BB_PATH_AUTO);
			PHYDM_DBG(dm, DBG_TXBF, "[MU IOT] 22C IOT Restore\n");
			rateinfo->mu_been_iot = 0;
		}
	}

	rateinfo->pre_mu_ratio = mu_ratio;
	phydm_mu_rsoml_reset(dm);
}


#endif /*PHYSTS_3RD_TYPE_IC*/

void phydm_txbf_avoid_hang(void *dm_void)
{
	struct dm_struct *dm = (struct dm_struct *)dm_void;
	
	/* avoid CCK CCA hang when the BF mode */
#ifdef PHYDM_IC_JGR3_SERIES_SUPPORT	
	odm_set_bb_reg(dm, R_0x1e6c, 0x100000, 0x1);
#endif

	/* avoid CCK CCA hang when the BFee mode for 92F */
}

void phydm_bf_debug(void *dm_void, char input[][16], u32 *_used, char *output,
		    u32 *_out_len)
{
	struct dm_struct *dm = (struct dm_struct *)dm_void;
	char help[] = "-h";
	u32 var1[3] = {0};
	u32 i;

	if ((strcmp(input[1], help) == 0)) {
		PDM_SNPF(*_out_len, *_used, output + *_used, *_out_len - *_used,
			 "{BF ver1 :0}, {NO applyV:0; applyV:1; default:2}\n");
		PDM_SNPF(*_out_len, *_used, output + *_used, *_out_len - *_used,
			 "{MU RSOML:1}, {MU enable:1/0}, {MU Ratio:40}\n");
		PDM_SNPF(*_out_len, *_used, output + *_used, *_out_len - *_used,
			 "{MU TRxPath:2}, {TRxPath enable:1/0}\n");
		return;
	}
	for (i = 0; i < 3; i++) {
		PHYDM_SSCANF(input[i + 1], DCMD_DECIMAL, &var1[i]);
	}
	if (var1[0] == 0) {
		#ifdef PHYDM_BEAMFORMING_SUPPORT
		struct _RT_BEAMFORMING_INFO *beamforming_info = NULL;

		beamforming_info = &dm->beamforming_info;

		if (var1[1] == 0) {
			beamforming_info->apply_v_matrix = false;
			beamforming_info->snding3ss = true;
			PDM_SNPF(*_out_len, *_used, output + *_used,
				 *_out_len - *_used,
				"\r\n dont apply V matrix and 3SS 789 snding\n");
		} else if (var1[1] == 1) {
			beamforming_info->apply_v_matrix = true;
			beamforming_info->snding3ss = true;
			PDM_SNPF(*_out_len, *_used, output + *_used,
				 *_out_len - *_used,
				 "\r\n apply V matrix and 3SS 789 snding\n");
		} else if (var1[1] == 2) {
			beamforming_info->apply_v_matrix = true;
			beamforming_info->snding3ss = false;
			PDM_SNPF(*_out_len, *_used, output + *_used,
				 *_out_len - *_used,
				 "\r\n default txbf setting\n");
		} else {
			PDM_SNPF(*_out_len, *_used, output + *_used,
				 *_out_len - *_used,
				 "\r\n unknown cmd!!\n");
		}
		#endif
	} else if (var1[0] == 1) {
		#ifdef PHYDM_IC_JGR3_SERIES_SUPPORT
		struct dm_struct *dm = (struct dm_struct *)dm_void;
		struct phydm_bf_rate_info_jgr3 *bfinfo = &dm->bf_rate_info_jgr3;

		bfinfo->enable = (u8)var1[1];
		bfinfo->mu_ratio_th = (u8)var1[2];
		PDM_SNPF(*_out_len, *_used, output + *_used, *_out_len - *_used,
			 "[MU RSOML] enable= %d, MU ratio TH= %d\n",
			 bfinfo->enable, bfinfo->mu_ratio_th);
		#endif
	} else if (var1[0] == 2) {
		#ifdef PHYDM_IC_JGR3_SERIES_SUPPORT
		struct dm_struct *dm = (struct dm_struct *)dm_void;
		struct phydm_bf_rate_info_jgr3 *bfinfo = &dm->bf_rate_info_jgr3;

		bfinfo->mu_set_trxpath = (u8)var1[1];
		PDM_SNPF(*_out_len, *_used, output + *_used, *_out_len - *_used,
			 "[MU TRxPath] mu_set_trxpath = %d\n",
			 bfinfo->mu_set_trxpath);
		#endif
	}
}

#endif /*CONFIG_BB_TXBF_API*/
