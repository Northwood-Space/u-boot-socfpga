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

void to_mac_address(uint64_t val, uint8_t mac[6]) {
    mac[0] = (val >> 40) & 0xFF;
    mac[1] = (val >> 32) & 0xFF;
    mac[2] = (val >> 24) & 0xFF;
    mac[3] = (val >> 16) & 0xFF;
    mac[4] = (val >> 8)  & 0xFF;
    mac[5] = (val >> 0)  & 0xFF;

    // Ensure the first byte is a valid locally administered unicast MAC address
    mac[0] |= 0x02;  // Set LAA (bit 2)
    mac[0] &= 0xFE;  // Clear multicast bit (bit 1)
}

static int do_call(struct cmd_tbl *cmdtp, int flag, int argc,
		   char *const argv[])
{
	if (argc < 2)
		return CMD_RET_USAGE;

	const char* cmd = argv[1];

	if (!strcmp(cmd, "eth")) {
		struct arm_smccc_res res;
		uint64_t chip_id;
		uint8_t mac[6];

		arm_smccc_smc(CHIP_ID, 0, 0, 0, 0, 0, 0, 0, &res);
		printf("Res:  0x%lx 0x%lx 0x%lx 0x%lx\n", res.a0, res.a1, res.a2, res.a3);
		chip_id = ((res.a2 << 32) | res.a3);
		// take top 48 bits
		to_mac_address(chip_id, mac);
	  printf("MAC Address: %02X:%02X:%02X:%02X:%02X:%02X\n",
          mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
	} else {
		return CMD_RET_USAGE;
	}

	return 0;
}

U_BOOT_CMD(
	nw,	9,		2,	do_call,
	"Run a custom northwood command",
	"eth\n"
);
