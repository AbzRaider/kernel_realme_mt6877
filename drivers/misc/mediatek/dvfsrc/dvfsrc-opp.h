/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (c) 2019 MediaTek Inc.
 */
#ifndef __DVFSRC_OPP_H
#define __DVFSRC_OPP_H
#define MTK_DVFSRC_NUM_DVFS_OPP		0
#define MTK_DVFSRC_NUM_DRAM_OPP		1
#define MTK_DVFSRC_NUM_VCORE_OPP	2
#define MTK_DVFSRC_CURR_DVFS_OPP	3
#define MTK_DVFSRC_CURR_DRAM_OPP	4
#define MTK_DVFSRC_CURR_VCORE_OPP	5

#if IS_ENABLED(CONFIG_MTK_DVFSRC)
extern void register_dvfsrc_opp_handler(int (*handler)(u32 id));
extern int mtk_dvfsrc_query_opp_info(u32 id);
#else
static inline void register_dvfsrc_opp_handler(int (*handler)(u32 id))
{ }
static inline int mtk_dvfsrc_query_opp_info(u32 id)
{ return 0; }

#endif /* CONFIG_MTK_DVFSRC */
#endif