/******************************************************************************
 *
 * Copyright(c) 2024 Realtek Corporation.
 *
 * Cooperative RX Diversity Mode
 *
 * Allows a helper USB adapter (same chipset) to contribute received frames
 * that the primary adapter missed, improving RX robustness under fading,
 * interference, or multipath conditions.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 *****************************************************************************/
#ifndef __RTW_COOPERATIVE_RX_H__
#define __RTW_COOPERATIVE_RX_H__

#include <linux/types.h>
#include <linux/spinlock.h>
#include <linux/atomic.h>
#include <linux/if_ether.h>
#include <linux/compiler.h>

/* Forward declarations — full definitions come from drv_types.h */
struct _ADAPTER;
typedef struct _ADAPTER _adapter;
struct dvobj_priv;
struct net_device;
union recv_frame;
struct dentry;

#define COOP_MAX_HELPERS		4
#define COOP_NONQOS_SEQ_CACHE_SZ	32

enum coop_rx_state {
	COOP_STATE_DISABLED = 0,
	COOP_STATE_IDLE,
	COOP_STATE_BINDING,
	COOP_STATE_ACTIVE,
	COOP_STATE_TEARDOWN,
};

/* Statistics counters for observability */
struct coop_rx_stats {
	atomic_t helper_rx_candidates;	/* frames considered from helper */
	atomic_t helper_rx_accepted;	/* frames injected into primary */
	atomic_t helper_rx_dup_dropped;	/* duplicates caught at merge */
	atomic_t helper_rx_foreign;	/* wrong BSSID/TA, rejected */
	atomic_t helper_rx_crypto_err;	/* decryption failures */
	atomic_t helper_rx_late;	/* too late for reorder window */
	atomic_t helper_rx_no_sta;	/* sta_info not found */
	atomic_t fallback_events;	/* helper disappeared/failed */
	atomic_t pair_events;		/* successful pairings */
	atomic_t unpair_events;		/* teardown events */
};

/*
 * Non-QoS sequence number cache for duplicate detection.
 * The AMPDU reorder window handles dedup for QoS/AMPDU traffic,
 * but non-QoS frames need explicit tracking.
 */
struct coop_nonqos_seq_cache {
	u16 seqs[COOP_NONQOS_SEQ_CACHE_SZ];
	u8 idx;
};

/*
 * Cooperative RX group — the central coordination object.
 * Spans across dvobj boundaries (separate USB devices).
 * Protected by spinlock for membership changes, RCU for hot-path reads.
 */
struct cooperative_rx_group {
	spinlock_t lock;
	enum coop_rx_state state;

	/* Primary adapter — the one with active STA connection */
	_adapter *primary;
	struct dvobj_priv *primary_dvobj;

	/* Helper adapter(s) — contribute RX frames only */
	_adapter *helpers[COOP_MAX_HELPERS];
	struct dvobj_priv *helper_dvobjs[COOP_MAX_HELPERS];
	int num_helpers;

	/* Session binding — which BSS we're filtering for */
	u8 bound_bssid[ETH_ALEN];
	u8 bound_ap_mac[ETH_ALEN];	/* TA of the AP */
	u8 bound_channel;
	u8 bound_bw;

	/* Non-QoS dedup cache */
	struct coop_nonqos_seq_cache nonqos_cache;

	/* Statistics */
	struct coop_rx_stats stats;

	/* Debugfs directory */
	struct dentry *debugfs_dir;
};

/* Global singleton — one cooperative group for the system */
extern struct cooperative_rx_group *rtw_coop_rx_group;
extern int rtw_cooperative_rx;	/* module parameter */

/* Lifecycle */
int rtw_coop_rx_init(void);
void rtw_coop_rx_deinit(void);

/* Pairing */
int rtw_coop_rx_set_primary(_adapter *adapter);
int rtw_coop_rx_add_helper(_adapter *adapter);
int rtw_coop_rx_remove_helper(_adapter *adapter);
void rtw_coop_rx_remove_adapter(_adapter *adapter);
int rtw_coop_rx_bind_session(_adapter *primary);
void rtw_coop_rx_unbind_session(void);

/* Helper RX hot path */
int rtw_coop_rx_submit_helper_frame(union recv_frame *precvframe,
				    _adapter *helper_adapter);

/* Query helpers — these are called from hot paths so must be fast */
static inline bool rtw_coop_rx_enabled(void)
{
	return READ_ONCE(rtw_cooperative_rx) != 0;
}

static inline bool rtw_coop_rx_active(void)
{
	struct cooperative_rx_group *grp;

	if (!rtw_coop_rx_enabled())
		return false;
	grp = READ_ONCE(rtw_coop_rx_group);
	return grp && READ_ONCE(grp->state) == COOP_STATE_ACTIVE;
}

static inline bool rtw_coop_rx_is_helper(_adapter *adapter)
{
	struct cooperative_rx_group *grp;
	int i;

	if (!rtw_coop_rx_enabled())
		return false;
	grp = READ_ONCE(rtw_coop_rx_group);
	if (!grp || READ_ONCE(grp->state) < COOP_STATE_BINDING)
		return false;
	for (i = 0; i < READ_ONCE(grp->num_helpers); i++) {
		if (READ_ONCE(grp->helpers[i]) == adapter)
			return true;
	}
	return false;
}

/* sysfs / proc interface */
int rtw_coop_rx_sysfs_init(struct net_device *ndev);
void rtw_coop_rx_sysfs_deinit(struct net_device *ndev);

/* debugfs */
int rtw_coop_rx_debugfs_init(void);
void rtw_coop_rx_debugfs_deinit(void);

#endif /* __RTW_COOPERATIVE_RX_H__ */
