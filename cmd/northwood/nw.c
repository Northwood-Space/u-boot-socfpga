/*
 * Copyright 2025
 * Cameron Dart <cameron@northwoodspace.io>
 */
#include <asm/psci.h>
#include <common.h>
#include <command.h>
#include <linux/arm-smccc.h>
#include <linux/compiler.h>
#include <linux/psci.h>

#define CHIP_ID 0xc2000065

static int do_call(struct cmd_tbl *cmdtp, int flag, int argc,
		   char *const argv[])
{

	if (argc < 2)

	if (!strcmp(argv[0], "nw"))
		return CMD_RET_USAGE;

	if (strcmp(argv[1], "eth")) {
		struct arm_smccc_res res;
		arm_smccc_smc(CHIP_ID, 0, 0, 0, 0, 0, 0, 0, &res);
		printf("Res:  0x%lx 0x%lx 0x%lx 0x%lx\n", res.a0, res.a1, res.a2, res.a3);
		// take top 48 bits
		unsigned long long eth = (((res.a2 << 32) | res.a3) >> 16);
		printf("EthAddr: %llu", eth);
	} else {
		return CMD_RET_USAGE;
	}

	return 0;
}

U_BOOT_CMD(
	smc,	9,		2,	do_call,
	"Issue a Secure Monitor Call",
	"<fid> [arg1 ... arg6] [id]\n"
	"  - fid Function ID\n"
	"  - arg SMC arguments, passed to X1-X6 (default to zero)\n"
	"  - id  Secure OS ID / Session ID, passed to W7 (defaults to zero)\n"
);
