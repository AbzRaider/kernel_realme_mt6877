// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2019 MediaTek Inc.
 */

#ifdef CONFIG_MTK_TINYSYS_SSPM_SUPPORT
#include <sspm_mbox.h>
#endif

#include "mtk_lp_plat_apmcu_mbox.h"

struct mbox_ops {
	void (*write)(int id, int *buf, unsigned int len);
	void (*read)(int id, int *buf, unsigned int len);
};

static void apmcu_sspm_mailbox_write(int id, int *buf, unsigned int len)
{
#ifdef CONFIG_MTK_TINYSYS_SSPM_SUPPORT
	sspm_mbox_write(APMCU_SSPM_MBOX_ID, id, (void *)buf, len);
#endif
}

static void apmcu_sspm_mailbox_read(int id, int *buf, unsigned int len)
{
#ifdef CONFIG_MTK_TINYSYS_SSPM_SUPPORT
	sspm_mbox_read(APMCU_SSPM_MBOX_ID, id, (void *)&buf, len);
#endif
}

static void apmcu_mcupm_mailbox_write(int id, int *buf, unsigned int len)
{
#ifdef CONFIG_MTK_TINYSYS_MCUPM_SUPPORT
	mcupm_mbox_read(APMCU_MCUPM_MBOX_ID, id, (void *)&buf, len);
#endif
}

static void apmcu_mcupm_mailbox_read(int id, int *buf, unsigned int len)
{
#ifdef CONFIG_MTK_TINYSYS_MCUPM_SUPPORT
	mcupm_mbox_read(APMCU_MCUPM_MBOX_ID, id, (void *)&buf, len);
#endif
}

static struct mbox_ops mbox[NF_MBOX] = {
	[MBOX_SSPM] = {
		.write = apmcu_sspm_mailbox_write,
		.read = apmcu_sspm_mailbox_read
	},
	[MBOX_MCUPM] = {
		.write = apmcu_mcupm_mailbox_write,
		.read = apmcu_mcupm_mailbox_read
	},
};


void mtk_set_sspm_lp_cmd(void *buf)
{
	mbox[MBOX_SSPM].write(APMCU_SSPM_MBOX_SPM_CMD,
			(int *)buf,
			APMCU_SSPM_MBOX_SPM_CMD_SIZE);
}

void mtk_clr_sspm_lp_cmd(void)
{
	int buf[APMCU_SSPM_MBOX_SPM_CMD_SIZE] = {0};

	mbox[MBOX_SSPM].write(APMCU_SSPM_MBOX_SPM_CMD,
			(int *)buf,
			APMCU_SSPM_MBOX_SPM_CMD_SIZE);
}

void mtk_mcupm_pwr_ctrl_en(int dev)
{
	unsigned int en_mask;

	mbox[MBOX_MCUPM].read(APMCU_MCUPM_MBOX_PWR_CTRL_EN, &en_mask, 1);
	en_mask |= (dev & MCUPM_PWR_CTRL_MASK);
	mbox[MBOX_MCUPM].write(APMCU_MCUPM_MBOX_PWR_CTRL_EN, &en_mask, 1);
}

void mtk_mcupm_pwr_ctrl_dis(int dev)
{
	unsigned int en_mask;

	mbox[MBOX_MCUPM].read(APMCU_MCUPM_MBOX_PWR_CTRL_EN, &en_mask, 1);
	en_mask &= ~(dev & MCUPM_PWR_CTRL_MASK);
	mbox[MBOX_MCUPM].write(APMCU_MCUPM_MBOX_PWR_CTRL_EN, &en_mask, 1);
}

void mtk_set_mcupm_pll_mode(unsigned int mode)
{
	if (mode < NF_MCUPM_ARMPLL_MODE)
		mbox[MBOX_MCUPM].write(APMCU_MCUPM_MBOX_ARMPLL_MODE, &mode, 1);
}

int mtk_get_mcupm_pll_mode(void)
{
	int mode = 0;

	mbox[MBOX_MCUPM].read(APMCU_MCUPM_MBOX_ARMPLL_MODE, &mode, 1);

	return mode;
}

void mtk_set_mcupm_buck_mode(unsigned int mode)
{
	if (mode < NF_MCUPM_BUCK_MODE)
		mbox[MBOX_MCUPM].write(APMCU_MCUPM_MBOX_BUCK_MODE, &mode, 1);
}

int mtk_get_mcupm_buck_mode(void)
{
	int mode = 0;

	mbox[MBOX_MCUPM].read(APMCU_MCUPM_MBOX_BUCK_MODE, &mode, 1);

	return mode;
}

void mtk_notify_mcupm_infra_off(void)
{
	int pwrdn = 1;

	mbox[MBOX_MCUPM].write(APMCU_MCUPM_MBOX_INFRA_PWRDN, &pwrdn, 1);
}

void mtk_notify_mcupm_infra_on(void)
{
	int pwrdn = 0;

	mbox[MBOX_MCUPM].write(APMCU_MCUPM_MBOX_INFRA_PWRDN, &pwrdn, 1);
}

void __init mtk_lp_plat_mbox_init(void)
{
	int ready = 1;

	mbox[MBOX_SSPM].write(APMCU_SSPM_MBOX_AP_READY, &ready, 1);
	mbox[MBOX_MCUPM].write(APMCU_MCUPM_MBOX_AP_READY, &ready, 1);
}
