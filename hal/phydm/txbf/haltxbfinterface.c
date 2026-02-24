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
/*************************************************************
 * Description:
 *
 * This file is for TXBF interface mechanism
 *
 ************************************************************/
#include "mp_precomp.h"
#include "../phydm_precomp.h"

#ifdef PHYDM_BEAMFORMING_SUPPORT

u32 beamforming_get_report_frame(
	void *dm_void,
	union recv_frame *precv_frame)
{
	struct dm_struct *dm = (struct dm_struct *)dm_void;
	u32 ret = _SUCCESS;
	struct _RT_BEAMFORMEE_ENTRY *beamform_entry = NULL;
	u8 *pframe = precv_frame->u.hdr.rx_data;
	u32 frame_len = precv_frame->u.hdr.len;
	u8 *TA;
	u8 idx, offset;

	/*@Memory comparison to see if CSI report is the same with previous one*/
	TA = get_addr2_ptr(pframe);
	beamform_entry = phydm_beamforming_get_bfee_entry_by_addr(dm, TA, &idx);
	if (beamform_entry->beamform_entry_cap & BEAMFORMER_CAP_VHT_SU)
		offset = 31; /*@24+(1+1+3)+2  MAC header+(Category+ActionCode+MIMOControlField)+SNR(nc=2)*/
	else if (beamform_entry->beamform_entry_cap & BEAMFORMER_CAP_HT_EXPLICIT)
		offset = 34; /*@24+(1+1+6)+2  MAC header+(Category+ActionCode+MIMOControlField)+SNR(nc=2)*/
	else
		return ret;

	return ret;
}

boolean
send_fw_ht_ndpa_packet(
	void *dm_void,
	u8 *RA,
	enum channel_width BW)
{
	struct dm_struct *dm = (struct dm_struct *)dm_void;
	struct _ADAPTER *adapter = dm->adapter;
	struct xmit_frame *pmgntframe;
	struct pkt_attrib *pattrib;
	struct rtw_ieee80211_hdr *pwlanhdr;
	struct xmit_priv *pxmitpriv = &(adapter->xmitpriv);
	struct mlme_ext_priv *pmlmeext = &adapter->mlmeextpriv;
	struct mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);
	u8 action_hdr[4] = {ACT_CAT_VENDOR, 0x00, 0xe0, 0x4c};
	u8 *pframe;
	u16 *fctrl;
	u16 duration = 0;
	u8 a_sifs_time = 0, ndp_tx_rate = 0, idx = 0;
	struct _RT_BEAMFORMING_INFO *beam_info = &(dm->beamforming_info);
	struct _RT_BEAMFORMEE_ENTRY *beamform_entry = phydm_beamforming_get_bfee_entry_by_addr(dm, RA, &idx);

	pmgntframe = alloc_mgtxmitframe(pxmitpriv);

	if (pmgntframe == NULL) {
		PHYDM_DBG(dm, DBG_TXBF, "%s, alloc mgnt frame fail\n",
			  __func__);
		return false;
	}

	/* update attribute */
	pattrib = &pmgntframe->attrib;
	update_mgntframe_attrib(adapter, pattrib);

	pattrib->qsel = QSLT_BEACON;
	ndp_tx_rate = beamforming_get_htndp_tx_rate(dm, beamform_entry->comp_steering_num_of_bfer);
	PHYDM_DBG(dm, DBG_TXBF, "[%s] ndp_tx_rate =%d\n", __func__,
		  ndp_tx_rate);
	pattrib->rate = ndp_tx_rate;
	pattrib->bwmode = BW;
	pattrib->order = 1;
	pattrib->subtype = WIFI_ACTION_NOACK;

	_rtw_memset(pmgntframe->buf_addr, 0, WLANHDR_OFFSET + TXDESC_OFFSET);

	pframe = (u8 *)(pmgntframe->buf_addr) + TXDESC_OFFSET;

	pwlanhdr = (struct rtw_ieee80211_hdr *)pframe;

	fctrl = &pwlanhdr->frame_ctl;
	*(fctrl) = 0;

	set_order_bit(pframe);
	set_frame_sub_type(pframe, WIFI_ACTION_NOACK);

	_rtw_memcpy(pwlanhdr->addr1, RA, ETH_ALEN);
	_rtw_memcpy(pwlanhdr->addr2, beamform_entry->my_mac_addr, ETH_ALEN);
	_rtw_memcpy(pwlanhdr->addr3, get_my_bssid(&(pmlmeinfo->network)), ETH_ALEN);

	if (pmlmeext->cur_wireless_mode == WIRELESS_11B)
		a_sifs_time = 10;
	else
		a_sifs_time = 16;

	duration = 2 * a_sifs_time + 40;

	if (BW == CHANNEL_WIDTH_40)
		duration += 87;
	else
		duration += 180;

	set_duration(pframe, duration);

	/* @HT control field */
	SET_HT_CTRL_CSI_STEERING(pframe + 24, 3);
	SET_HT_CTRL_NDP_ANNOUNCEMENT(pframe + 24, 1);

	_rtw_memcpy(pframe + 28, action_hdr, 4);

	pattrib->pktlen = 32;

	pattrib->last_txcmdsz = pattrib->pktlen;

	dump_mgntframe(adapter, pmgntframe);

	return true;
}

boolean
send_sw_ht_ndpa_packet(
	void *dm_void,
	u8 *RA,
	enum channel_width BW)
{
	struct dm_struct *dm = (struct dm_struct *)dm_void;
	struct _ADAPTER *adapter = dm->adapter;
	struct xmit_frame *pmgntframe;
	struct pkt_attrib *pattrib;
	struct rtw_ieee80211_hdr *pwlanhdr;
	struct xmit_priv *pxmitpriv = &(adapter->xmitpriv);
	struct mlme_ext_priv *pmlmeext = &adapter->mlmeextpriv;
	struct mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);
	u8 action_hdr[4] = {ACT_CAT_VENDOR, 0x00, 0xe0, 0x4c};
	u8 *pframe;
	u16 *fctrl;
	u16 duration = 0;
	u8 a_sifs_time = 0, ndp_tx_rate = 0, idx = 0;
	struct _RT_BEAMFORMING_INFO *beam_info = &(dm->beamforming_info);
	struct _RT_BEAMFORMEE_ENTRY *beamform_entry = phydm_beamforming_get_bfee_entry_by_addr(dm, RA, &idx);

	ndp_tx_rate = beamforming_get_htndp_tx_rate(dm, beamform_entry->comp_steering_num_of_bfer);

	pmgntframe = alloc_mgtxmitframe(pxmitpriv);

	if (pmgntframe == NULL) {
		PHYDM_DBG(dm, DBG_TXBF, "%s, alloc mgnt frame fail\n",
			  __func__);
		return false;
	}

	/*update attribute*/
	pattrib = &pmgntframe->attrib;
	update_mgntframe_attrib(adapter, pattrib);
	pattrib->qsel = QSLT_MGNT;
	pattrib->rate = ndp_tx_rate;
	pattrib->bwmode = BW;
	pattrib->order = 1;
	pattrib->subtype = WIFI_ACTION_NOACK;

	_rtw_memset(pmgntframe->buf_addr, 0, WLANHDR_OFFSET + TXDESC_OFFSET);

	pframe = (u8 *)(pmgntframe->buf_addr) + TXDESC_OFFSET;

	pwlanhdr = (struct rtw_ieee80211_hdr *)pframe;

	fctrl = &pwlanhdr->frame_ctl;
	*(fctrl) = 0;

	set_order_bit(pframe);
	set_frame_sub_type(pframe, WIFI_ACTION_NOACK);

	_rtw_memcpy(pwlanhdr->addr1, RA, ETH_ALEN);
	_rtw_memcpy(pwlanhdr->addr2, beamform_entry->my_mac_addr, ETH_ALEN);
	_rtw_memcpy(pwlanhdr->addr3, get_my_bssid(&(pmlmeinfo->network)), ETH_ALEN);

	if (pmlmeext->cur_wireless_mode == WIRELESS_11B)
		a_sifs_time = 10;
	else
		a_sifs_time = 16;

	duration = 2 * a_sifs_time + 40;

	if (BW == CHANNEL_WIDTH_40)
		duration += 87;
	else
		duration += 180;

	set_duration(pframe, duration);

	/*@HT control field*/
	SET_HT_CTRL_CSI_STEERING(pframe + 24, 3);
	SET_HT_CTRL_NDP_ANNOUNCEMENT(pframe + 24, 1);

	_rtw_memcpy(pframe + 28, action_hdr, 4);

	pattrib->pktlen = 32;

	pattrib->last_txcmdsz = pattrib->pktlen;

	dump_mgntframe(adapter, pmgntframe);

	return true;
}

boolean
send_fw_vht_ndpa_packet(
	void *dm_void,
	u8 *RA,
	u16 AID,
	enum channel_width BW)
{
	struct dm_struct *dm = (struct dm_struct *)dm_void;
	struct _ADAPTER *adapter = dm->adapter;
	struct xmit_frame *pmgntframe;
	struct pkt_attrib *pattrib;
	struct rtw_ieee80211_hdr *pwlanhdr;
	struct xmit_priv *pxmitpriv = &(adapter->xmitpriv);
	struct mlme_ext_priv *pmlmeext = &adapter->mlmeextpriv;
	struct mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);
	struct mlme_priv *pmlmepriv = &(adapter->mlmepriv);
	u8 *pframe;
	u16 *fctrl;
	u16 duration = 0;
	u8 sequence = 0, a_sifs_time = 0, ndp_tx_rate = 0, idx = 0;
	struct _RT_BEAMFORMING_INFO *beam_info = &(dm->beamforming_info);
	struct _RT_BEAMFORMEE_ENTRY *beamform_entry = phydm_beamforming_get_bfee_entry_by_addr(dm, RA, &idx);
	struct _RT_NDPA_STA_INFO sta_info;

	pmgntframe = alloc_mgtxmitframe(pxmitpriv);

	if (pmgntframe == NULL) {
		PHYDM_DBG(dm, DBG_TXBF, "%s, alloc mgnt frame fail\n",
			  __func__);
		return false;
	}

	/* update attribute */
	pattrib = &pmgntframe->attrib;
	_rtw_memcpy(pattrib->ra, RA, ETH_ALEN);
	update_mgntframe_attrib(adapter, pattrib);

	pattrib->qsel = QSLT_BEACON;
	ndp_tx_rate = beamforming_get_vht_ndp_tx_rate(dm, beamform_entry->comp_steering_num_of_bfer);
	PHYDM_DBG(dm, DBG_TXBF, "[%s] ndp_tx_rate =%d\n", __func__,
		  ndp_tx_rate);
	pattrib->rate = ndp_tx_rate;
	pattrib->bwmode = BW;
	pattrib->subtype = WIFI_NDPA;

	_rtw_memset(pmgntframe->buf_addr, 0, WLANHDR_OFFSET + TXDESC_OFFSET);

	pframe = (u8 *)(pmgntframe->buf_addr) + TXDESC_OFFSET;

	pwlanhdr = (struct rtw_ieee80211_hdr *)pframe;

	fctrl = &pwlanhdr->frame_ctl;
	*(fctrl) = 0;

	set_frame_sub_type(pframe, WIFI_NDPA);

	_rtw_memcpy(pwlanhdr->addr1, RA, ETH_ALEN);
	_rtw_memcpy(pwlanhdr->addr2, beamform_entry->my_mac_addr, ETH_ALEN);

	if (is_supported_5g(pmlmeext->cur_wireless_mode) || is_supported_ht(pmlmeext->cur_wireless_mode))
		a_sifs_time = 16;
	else
		a_sifs_time = 10;

	duration = 2 * a_sifs_time + 44;

	if (BW == CHANNEL_WIDTH_80)
		duration += 40;
	else if (BW == CHANNEL_WIDTH_40)
		duration += 87;
	else
		duration += 180;

	set_duration(pframe, duration);

	sequence = beam_info->sounding_sequence << 2;
	if (beam_info->sounding_sequence >= 0x3f)
		beam_info->sounding_sequence = 0;
	else
		beam_info->sounding_sequence++;

	_rtw_memcpy(pframe + 16, &sequence, 1);

	if (((pmlmeinfo->state & 0x03) == WIFI_FW_ADHOC_STATE) || ((pmlmeinfo->state & 0x03) == WIFI_FW_AP_STATE))
		AID = 0;

	sta_info.aid = AID;
	sta_info.feedback_type = 0;
	sta_info.nc_index = 0;

	_rtw_memcpy(pframe + 17, (u8 *)&sta_info, 2);

	pattrib->pktlen = 19;

	pattrib->last_txcmdsz = pattrib->pktlen;

	dump_mgntframe(adapter, pmgntframe);

	return true;
}

boolean
send_sw_vht_ndpa_packet(
	void *dm_void,
	u8 *RA,
	u16 AID,
	enum channel_width BW)
{
	struct dm_struct *dm = (struct dm_struct *)dm_void;
	struct _ADAPTER *adapter = dm->adapter;
	struct xmit_frame *pmgntframe;
	struct pkt_attrib *pattrib;
	struct rtw_ieee80211_hdr *pwlanhdr;
	struct xmit_priv *pxmitpriv = &(adapter->xmitpriv);
	struct mlme_ext_priv *pmlmeext = &adapter->mlmeextpriv;
	struct mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);
	struct mlme_priv *pmlmepriv = &(adapter->mlmepriv);
	struct _RT_NDPA_STA_INFO ndpa_sta_info;
	u8 ndp_tx_rate = 0, sequence = 0, a_sifs_time = 0, idx = 0;
	u8 *pframe;
	u16 *fctrl;
	u16 duration = 0;
	struct _RT_BEAMFORMING_INFO *beam_info = &(dm->beamforming_info);
	struct _RT_BEAMFORMEE_ENTRY *beamform_entry = phydm_beamforming_get_bfee_entry_by_addr(dm, RA, &idx);

	ndp_tx_rate = beamforming_get_vht_ndp_tx_rate(dm, beamform_entry->comp_steering_num_of_bfer);
	PHYDM_DBG(dm, DBG_TXBF, "[%s] ndp_tx_rate =%d\n", __func__,
		  ndp_tx_rate);

	pmgntframe = alloc_mgtxmitframe(pxmitpriv);

	if (pmgntframe == NULL) {
		PHYDM_DBG(dm, DBG_TXBF, "%s, alloc mgnt frame fail\n",
			  __func__);
		return false;
	}

	/*update attribute*/
	pattrib = &pmgntframe->attrib;
	_rtw_memcpy(pattrib->ra, RA, ETH_ALEN);
	update_mgntframe_attrib(adapter, pattrib);
	pattrib->qsel = QSLT_MGNT;
	pattrib->rate = ndp_tx_rate;
	pattrib->bwmode = BW;
	pattrib->subtype = WIFI_NDPA;

	_rtw_memset(pmgntframe->buf_addr, 0, WLANHDR_OFFSET + TXDESC_OFFSET);

	pframe = (u8 *)(pmgntframe->buf_addr) + TXDESC_OFFSET;

	pwlanhdr = (struct rtw_ieee80211_hdr *)pframe;

	fctrl = &pwlanhdr->frame_ctl;
	*(fctrl) = 0;

	set_frame_sub_type(pframe, WIFI_NDPA);

	_rtw_memcpy(pwlanhdr->addr1, RA, ETH_ALEN);
	_rtw_memcpy(pwlanhdr->addr2, beamform_entry->my_mac_addr, ETH_ALEN);

	if (is_supported_5g(pmlmeext->cur_wireless_mode) || is_supported_ht(pmlmeext->cur_wireless_mode))
		a_sifs_time = 16;
	else
		a_sifs_time = 10;

	duration = 2 * a_sifs_time + 44;

	if (BW == CHANNEL_WIDTH_80)
		duration += 40;
	else if (BW == CHANNEL_WIDTH_40)
		duration += 87;
	else
		duration += 180;

	set_duration(pframe, duration);

	sequence = beam_info->sounding_sequence << 2;
	if (beam_info->sounding_sequence >= 0x3f)
		beam_info->sounding_sequence = 0;
	else
		beam_info->sounding_sequence++;

	_rtw_memcpy(pframe + 16, &sequence, 1);
	if (((pmlmeinfo->state & 0x03) == WIFI_FW_ADHOC_STATE) || ((pmlmeinfo->state & 0x03) == WIFI_FW_AP_STATE))
		AID = 0;

	ndpa_sta_info.aid = AID;
	ndpa_sta_info.feedback_type = 0;
	ndpa_sta_info.nc_index = 0;

	_rtw_memcpy(pframe + 17, (u8 *)&ndpa_sta_info, 2);

	pattrib->pktlen = 19;

	pattrib->last_txcmdsz = pattrib->pktlen;

	dump_mgntframe(adapter, pmgntframe);
	PHYDM_DBG(dm, DBG_TXBF, "[%s] [%d]\n", __func__, __LINE__);

	return true;
}


void beamforming_get_ndpa_frame(
	void *dm_void,
	union recv_frame *precv_frame
	)
{
	struct dm_struct *dm = (struct dm_struct *)dm_void;
	u8 *TA;
	u8 idx, sequence;
	u8 *p_ndpa_frame = precv_frame->u.hdr.rx_data;
	struct _RT_BEAMFORMER_ENTRY *beamformer_entry = NULL; /*@Modified By Jeffery @2014-10-29*/

	if (get_frame_sub_type(p_ndpa_frame) != WIFI_NDPA)
		return;
	else if (!(dm->support_ic_type & (ODM_RTL8812 | ODM_RTL8821))) {
		PHYDM_DBG(dm, DBG_TXBF, "[%s] not 8812 or 8821A, return\n",
			  __func__);
		return;
	}
	TA = get_addr2_ptr(p_ndpa_frame);
	/*Remove signaling TA. */
	TA[0] = TA[0] & 0xFE;

	beamformer_entry = phydm_beamforming_get_bfer_entry_by_addr(dm, TA, &idx); /* @Modified By Jeffery @2014-10-29 */

	/*@Break options for Clock Reset*/
	if (beamformer_entry == NULL)
		return;
	else if (!(beamformer_entry->beamform_entry_cap & BEAMFORMEE_CAP_VHT_SU))
		return;
	/*@log_success: As long as 8812A receive NDPA and feedback CSI succeed once, clock reset is NO LONGER needed !2015-04-10, Jeffery*/
	/*@clock_reset_times: While BFer entry always doesn't receive our CSI, clock will reset again and again.So clock_reset_times is limited to 5 times.2015-04-13, Jeffery*/
	else if ((beamformer_entry->log_success == 1) || (beamformer_entry->clock_reset_times == 5)) {
		PHYDM_DBG(dm, DBG_TXBF,
			  "[%s] log_seq=%d, pre_log_seq=%d, log_retry_cnt=%d, log_success=%d, clock_reset_times=%d, clock reset is no longer needed.\n",
			  __func__, beamformer_entry->log_seq,
			  beamformer_entry->pre_log_seq,
			  beamformer_entry->log_retry_cnt,
			  beamformer_entry->log_success,
			  beamformer_entry->clock_reset_times);

		return;
	}

	sequence = (p_ndpa_frame[16]) >> 2;

	PHYDM_DBG(dm, DBG_TXBF,
		  "[%s] Start, sequence=%d, log_seq=%d, pre_log_seq=%d, log_retry_cnt=%d, clock_reset_times=%d, log_success=%d\n",
		  __func__, sequence, beamformer_entry->log_seq,
		  beamformer_entry->pre_log_seq,
		  beamformer_entry->log_retry_cnt,
		  beamformer_entry->clock_reset_times,
		  beamformer_entry->log_success);

	if (beamformer_entry->log_seq != 0 && beamformer_entry->pre_log_seq != 0) {
		/*Success condition*/
		if (beamformer_entry->log_seq != sequence && beamformer_entry->pre_log_seq != beamformer_entry->log_seq) {
			/* @break option for clcok reset, 2015-03-30, Jeffery */
			beamformer_entry->log_retry_cnt = 0;
			/*@As long as 8812A receive NDPA and feedback CSI succeed once, clock reset is no longer needed.*/
			/*That is, log_success is NOT needed to be reset to zero, 2015-04-13, Jeffery*/
			beamformer_entry->log_success = 1;

		} else { /*@Fail condition*/

			if (beamformer_entry->log_retry_cnt == 5) {
				beamformer_entry->clock_reset_times++;
				beamformer_entry->log_retry_cnt = 0;

				PHYDM_DBG(dm, DBG_TXBF,
					  "[%s] Clock Reset!!! clock_reset_times=%d\n",
					  __func__,
					  beamformer_entry->clock_reset_times);
				hal_com_txbf_set(dm, TXBF_SET_SOUNDING_CLK, NULL);

			} else
				beamformer_entry->log_retry_cnt++;
		}
	}

	/*Update log_seq & pre_log_seq*/
	beamformer_entry->pre_log_seq = beamformer_entry->log_seq;
	beamformer_entry->log_seq = sequence;
}

#endif
