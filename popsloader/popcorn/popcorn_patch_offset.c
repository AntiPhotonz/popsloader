/*
 * This file is part of PRO CFW.

 * PRO CFW is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * PRO CFW is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with PRO CFW. If not, see <http://www.gnu.org/licenses/ .
 */

#include <pspsdk.h>
#include "popcorn_patch_offset.h"

#if !defined(CONFIG_635) && !defined(CONFIG_620) && !defined(CONFIG_639)
#error You have to define CONFIG_620 or CONFIG_635 or CONFIG_639
#endif

#ifdef CONFIG_639
PatchOffset g_639_offsets = {
	.fw_version = FW_639,
	.popsman_patch = {
		.get_rif_path = 0x00000190,
		.get_rif_path_call1 = 0x00002798,
		.get_rif_path_call2 = 0x00002C58,
		.sceNpDrmGetVersionKeyCall = 0x000029C4,
		.scePspNpDrm_driver_9A34AC9F_Call = 0x00002DA8,
		.scePopsManLoadModuleCheck = 0x00001E80,
	},
	.pops_patch = {
		.decomp = {
			{ 0x000D5654, 0x0000DC04 }, // 01G
			{ 0x000D671C, 0x0000DC04 }, // 02G
			{ 0x000D671C, 0x0000DC04 }, // 03G
			{ 0x000D670C, 0x0000DC04 }, // 04G
			{ 0x000D8698, 0x0000E31C }, // 05G
			{ 0x00000000, 0x00000000 }, // unused
			{ 0x000D670C, 0x0000DC04 }, // 07G
			{ 0x00000000, 0x00000000 }, // unused
			{ 0x000D670C, 0x0000DC04 }, // 09G
		},
		.ICON0SizeOffset = {
			0x00036F54, // 01G
			0x00037F90, // 02G
			0x00037F90, // 03G
			0x00037F90, // 04G
			0x00039D78, // 05G
			0xDEADBEEF, // unused
			0x00037F90, // 07G
			0xDEADBEEF, // unused
			0x00037F90, // 09G
		},
		.manualNameCheck = {
			0x0002541C, // 01G
			0x00025928, // 02G
			0x00025928, // 03G
			0x00025928, // 04G
			0x000261BC, // 05G
			0xDEADBEEF, // unused
			0x00025928, // 07G
			0xDEADBEEF, // unused
			0x00025928, // 09G
		},
		.sceMeAudio_67CD7972_NID = 0x67CD7972,
	},
};
#endif

#ifdef CONFIG_635
PatchOffset g_635_offsets = {
	.fw_version = FW_635,
	.popsman_patch = {
		.get_rif_path = 0x00000190,
		.get_rif_path_call1 = 0x00002798,
		.get_rif_path_call2 = 0x00002C58,
		.sceNpDrmGetVersionKeyCall = 0x000029C4,
		.scePspNpDrm_driver_9A34AC9F_Call = 0x00002DA8,
		.scePopsManLoadModuleCheck = 0x00001E80,
	},
	.pops_patch = {
		.decomp = {
			{ 0x000D5404, 0x0000DAC0 }, // 01G
			{ 0x000D64BC, 0x0000DAC0 }, // 02G
			{ 0x000D64BC, 0x0000DAC0 }, // 03G
			{ 0x000D64FC, 0x0000DB00 }, // 04G
			{ 0x000D8488, 0x0000E218 }, // 05G
			{ 0x00000000, 0x00000000 }, // unused
			{ 0x000D64FC, 0x0000DB00 }, // 07G
			{ 0x00000000, 0x00000000 }, // unused
			{ 0x000D64FC, 0x0000DB00 }, // 09G
		},
		.ICON0SizeOffset = {
			0x00036CF8, // 01G
			0x00037D34, // 02G
			0x00037D34, // 03G
			0x00037D74, // 04G
			0x00039B5C, // 05G
			0xDEADBEEF, // unused
			0x00037D74, // 07G
			0xDEADBEEF, // unused
			0x00037D74, // 09G
		},
		.manualNameCheck = {
			0x000251C0, // 01G
			0x000256CC, // 02G
			0x000256CC, // 03G
			0x0002570C, // 04G
			0x00025FA0, // 05G
			0xDEADBEEF, // unused
			0x0002570C, // 07G
			0xDEADBEEF, // unused
			0x0002570C, // 09G
		},
		.sceMeAudio_67CD7972_NID = 0x67CD7972,
	},
};
#endif

#ifdef CONFIG_620
PatchOffset g_620_offsets = {
	.fw_version = FW_620,
	.popsman_patch = {
		.get_rif_path = 0x00000190,
		.get_rif_path_call1 = 0x00002824,
		.get_rif_path_call2 = 0x00002CE4,
		.sceNpDrmGetVersionKeyCall = 0x00002A50,
		.scePspNpDrm_driver_9A34AC9F_Call = 0x00002E34,
		.scePopsManLoadModuleCheck = 0x00001EA8,
	},
	.pops_patch = {
		.decomp = {
			{ 0x000DA600, 0x0000DE18 }, // 01G
			{ 0x000DA600, 0x0000DE18 }, // 02G
			{ 0x000DA600, 0x0000DE18 }, // 03G
			{ 0x000DA630, 0x0000DE1C }, // 04G
			{ 0x000DC5CC, 0x0000E534 }, // 05G
			{ 0xDEADBEEF, 0xDEADBEEF }, // unused
			{ 0xDEADBEEF, 0xDEADBEEF }, // unused
			{ 0xDEADBEEF, 0xDEADBEEF }, // unused
			{ 0xDEADBEEF, 0xDEADBEEF }, // unused
		},
		.ICON0SizeOffset = {
			0x0003BCD0, // 01G
			0x0003BCD0, // 02G
			0x0003BCD0, // 03G
			0x0003BCFC, // 04G
			0x0003DAE4, // 05G
			0xDEADBEEF, // unused
			0xDEADBEEF, // unused
			0xDEADBEEF, // unused
			0xDEADBEEF, // unused
		},
		.manualNameCheck = {
			0x00029710, // 01G
			0x00029710, // 02G
			0x00029710, // 03G
			0x0002973C, // 04G
			0x00029FD0, // 05G
			0xDEADBEEF, // unused
			0xDEADBEEF, // unused
			0xDEADBEEF, // unused
			0xDEADBEEF, // unused
		},
		.sceMeAudio_67CD7972_NID = 0xF43E573A,
	},
};
#endif

PatchOffset *g_offs = NULL;

void setup_patch_offset_table(u32 fw_version)
{
#ifdef CONFIG_639
	if(fw_version == g_639_offsets.fw_version) {
		g_offs = &g_639_offsets;
	}
#endif

#ifdef CONFIG_635
	if(fw_version == g_635_offsets.fw_version) {
		g_offs = &g_635_offsets;
	}
#endif

#ifdef CONFIG_620
   	if(fw_version == g_620_offsets.fw_version) {
		g_offs = &g_620_offsets;
	}
#endif
}
