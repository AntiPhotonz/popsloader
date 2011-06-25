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

#include <pspkernel.h>
#include <pspreg.h>
#include <stdio.h>
#include <string.h>
#include <systemctrl.h>
#include <systemctrl_se.h>
#include <pspsysmem_kernel.h>
#include <pspiofilemgr_kernel.h>
#include <psprtc.h>
#include "utils.h"
#include "libs.h"
#include "strsafe.h"
#include "systemctrl.h"
#include "main.h"

static nid_entry SysMemForKernel_nid[] = {
	{ 0x2CFF6F90, 0xF0E0AB7A, },
	{ 0x5339A163, 0xF2FEAFD5, },
	{ 0x950BCB31, 0x52B54B93, },
	{ 0xD7E24299, 0x208F4820, },
};

static nid_entry ModuleMgrForKernel_nid[] = {
	{ 0xBB8C8FDF, 0xE6BF3960, },
	{ 0xC5A281C5, 0xFFB9B760, },
};

static nid_entry LoadExecForKernel_nid[] = {
	{ 0x9C9BB2D8, 0xFCD765C9, },
};

static nid_entry sceImpose_driver_nid[] = {
	{ 0x0BBCA0BF, 0x44F17A7A, },
	{ 0x4B02F047, 0x4C4DF719, },
	{ 0xA516434B, 0xEBC850AC, },
	{ 0xDA315C59, 0x027F21C6 , },
};

static nid_entry sceSysreg_driver_nid[] = {
	{ 0x08E0EE7E, 0xD74D9041, },
	{ 0x0E6301D0, 0x0CFD5A8A, },
	{ 0x20C9E2C4, 0xE2606FCB, },
	{ 0x410C74F7, 0x0CFD5A8A, },
	{ 0x461B8077, 0x45596E3F, },
	{ 0x48869494, 0x9E80B4E2, },
	{ 0x5F190A4E, 0xD1999F94, },
	{ 0x663D5471, 0x86FFE348, },
	{ 0x7A154A45, 0xB70793D7, },
	{ 0x823FFD7A, 0x3A98CABB, },
	{ 0x923509A1, 0x8E9E76AE, },
	{ 0xC7FC7669, 0x789597AB, },
	{ 0xE46A0890, 0x9984A972, },
};

static nid_entry sceSyscon_driver_nid[] = {
	{ 0x48728250, 0xC4931159, },
};

static nid_entry sceClockgen_driver_nid[] = {
	{ 0xD1A8E10E, 0xA02BB1D3, },
};

static nid_entry sceGe_driver_nid[] = {
	{ 0x0C9C3686, 0xD8A53104, },
	{ 0x1F226BA9, 0x2444EC4D, },
	{ 0x6663F1BD, 0x670F15ED, },
	{ 0x6849A0B0, 0xFEEC36F7, },
};

static nid_entry sceDisplay_driver_nid[] = {
	{ 0x10B1710B, 0x8930B3A9, }, // not very exactly
};

static nid_entry sceHprm_driver_nid[] = {
	{ 0xF5DBC7AA, 0xADE4B1F4, },
};

static nid_entry sceDve_driver_nid[] = {
	{ 0x0CC96C20, 0xAA085C2A, },
};

static nid_entry sceCodec_driver_nid[] = {
	{ 0xA48DE786, 0xB2EF6B19, },
};

resolver_config nid_fix_500_to_635[] = {
	NID_ENTRY(SysMemForKernel),
	NID_ENTRY(ModuleMgrForKernel),
	NID_ENTRY(LoadExecForKernel),
	NID_ENTRY(sceImpose_driver),
	NID_ENTRY(sceSysreg_driver),
	NID_ENTRY(sceSyscon_driver),
	NID_ENTRY(sceClockgen_driver),
	NID_ENTRY(sceGe_driver),
	NID_ENTRY(sceDisplay_driver),
	NID_ENTRY(sceHprm_driver),
	NID_ENTRY(sceDve_driver),
	NID_ENTRY(sceCodec_driver),
};

u32 nid_fix_500_to_635_size = NELEMS(nid_fix_500_to_635);
