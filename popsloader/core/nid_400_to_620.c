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
	{ 0x12720EDA, 0xB9796F69, },
	{ 0x3EEE43C5, 0xA4AC3934, },
	{ 0x5136926D, 0xFEB5C72B, },
	{ 0x523E300A, 0xF5780DAA, },
	// for impose.prx
	{ 0x4823B9D9, 0x864EBFD7, },
	{ 0x9CCA041E, 0x18D7F644, },
};

static nid_entry ModuleMgrForKernel_nid[] = {
	{ 0x24C5ABC2, 0xE3CCC6EA, },
	{ 0x63A3CAFB, 0xDF8FFFAB, },
};

static nid_entry LoadExecForKernel_nid[] = {
	{ 0x63D88393, 0x29413885, },
	// for impose.prx
	{ 0x2EAA8A5A, 0x63BB2F2C, },
	{ 0x6274D0D5, 0xB848CC2C, },
};

static nid_entry sceImpose_driver_nid[] = {
	{ 0x869EB4A8, 0x4D849B71, },
	{ 0xCD1291FD, 0x55864BD7, },
};

static nid_entry sceCtrl_driver_nid[] = {
	// for impose.prx
	{ 0x29A5082C, 0xF3132A07, },
	{ 0x591B3F36, 0x3CA6922B, },
	{ 0xE3870772, 0x063D8197, },
	{ 0xEB97D7AA, 0xEB6CDD17, },
};

static nid_entry sceSysreg_driver_nid[] = {
	{ 0x15574362, 0x9EBB3C43, },
	{ 0x21797DCF, 0x94914740, },
	{ 0x23D205CA, 0x774775CA, },
	{ 0x643169E5, 0xE7849809, },
	{ 0x67583EF1, 0xB733A263, },
	{ 0x88E26FBC, 0x34EED467, },
	{ 0x8E6586AD, 0x2D858336, },
	{ 0xA36C4E9E, 0x97EA6913, },
	{ 0xB60FBA15, 0x2B3BE2C8, },
	{ 0xC4B60AB3, 0x47966D28, },
	{ 0xD80E8AAF, 0x119647A7, },
	{ 0xD83733C9, 0x4643F826, },
	{ 0xE08034E0, 0x5D3DD0B3, },
	{ 0xE65B0490, 0x314A489C, },
};

static nid_entry sceSyscon_driver_nid[] = {
	{ 0x581D72B2, 0xF7E9487A, },
};

static nid_entry sceClockgen_driver_nid[] = {
	{ 0x17FA615B, 0xACC30ECE, },
};

static nid_entry sceGe_driver_nid[] = {
	{ 0x1DDA69CE, 0xD4D665C9, },
	{ 0xA402A161, 0x23E9F5FA, },
	{ 0xC545B81E, 0x862248FD, },
	{ 0xDC09D302, 0x7E2381D2, },
	{ 0xF5423CAA, 0xF489E74B, },
};

static nid_entry sceDisplay_driver_nid[] = {
	// for impose.prx
	{ 0x0E20F177, 0x0E20F177, },
	{ 0x2E6AA0AB, 0xC7161CF7, },
	{ 0x390C7E0E, 0xDC68E0EF, },
	{ 0x6E57C773, 0x6C42016A, },
	{ 0x96CFAC38, 0x96CFAC38, },
	{ 0xDB98F049, 0x2A1826A2, },
	{ 0xDEA197D4, 0xDEA197D4, },
	{ 0xE55F0D50, 0xE55F0D50, },
	{ 0xEB6C2BA3, 0xA20A245E, },
};

static nid_entry sceRtc_driver_nid[] = {
	// for impose.prx
	{ 0x1D90BCF2, 0xA0B3BF0F, },
	{ 0x8EB1DEAC, 0xCFBE4A68, },
};

static nid_entry sceCodec_driver_nid[] = {
	// for impose.prx
	{ 0x073DE131, 0xBCE58DC4, },
	{ 0x261C6EE8, 0x261C6EE8, },
	{ 0x856E7487, 0x856E7487, },
};

static nid_entry scePower_driver_nid[] = {
	// for impose.prx
	{ 0x1BA2FCAE, 0x1BA2FCAE, },
	{ 0x45BB59FE, 0x279492B3, },
	{ 0x56083981, 0x9E09D19B, },
	{ 0xAC664491, 0xE5F8596E, },
	{ 0xC35907C2, 0x4084E678, },
	{ 0xC6D21BB6, 0x7F480684, },
	{ 0xCF0F53E5, 0xC9885394, },
	{ 0xD61C63BD, 0x5202A826, },
	{ 0xFBFD57EB, 0xBC8823E8, },
};

static nid_entry sceReg_driver_nid[] = {
	// for impose.prx
	{ 0x24DDA193, 0xF3300EBF, },
	{ 0x3273A94B, 0x31F9DB91, },
	{ 0x636D5C60, 0x400BB753, },
	{ 0x9943E18A, 0x0404652C, },
	{ 0x9C756292, 0x8A0F5133, },
	{ 0xB8FD8784, 0xDC7EF81C, },
	{ 0xCDC72B4D, 0x08BEB24C, },
	{ 0xD3CD942D, 0x21928F15, },
	{ 0xE4D4F126, 0x873EB4E1, },
};

static nid_entry sceHprm_driver_nid[] = {
	// for impose.prx
	{ 0x1910B327, 0x1910B327, },
	{ 0x3459F450, 0x2E49469C, },
	{ 0x3709DC86, 0x1EECCA1A, },
	{ 0x404D9DE4, 0x62CDFB12, },
	{ 0x71E989F4, 0x732EC325, },
	{ 0xAE42F741, 0x2F028F97, },
	{ 0xCA90EB48, 0x8A898B38, },
	{ 0xE5AB910C, 0xDA01152D, },
	{ 0xF7FA0802, 0x4C9BEDA4, },
};

static nid_entry sceDve_driver_nid[] = {
	// for impose.prx
	{ 0x738FE169, 0x194FE107, },
	{ 0x89CCB808, 0x024D7064, },
	{ 0xC597DDDD, 0x2F863B65, },
};

static nid_entry KDebugForKernel_nid[] = {
	// for impose.prx
	{ 0x59E95C49, 0xD9DB4F02, },
};

static nid_entry InterruptManagerForKernel_nid[] = {
	// for impose.prx
	{ 0x169FC5A3, 0xC03C8D51, },
	{ 0xB940A5BF, 0x3C161DFB, },
};

resolver_config nid_fix_400_to_620[] = {
	NID_ENTRY(SysMemForKernel),
	NID_ENTRY(ModuleMgrForKernel),
	NID_ENTRY(LoadExecForKernel),
	NID_ENTRY(sceImpose_driver),
	NID_ENTRY(sceSysreg_driver),
	NID_ENTRY(sceSyscon_driver),
	NID_ENTRY(sceClockgen_driver),
	NID_ENTRY(sceGe_driver),
	NID_ENTRY(sceCtrl_driver),
	NID_ENTRY(sceDisplay_driver),
	NID_ENTRY(sceRtc_driver),
	NID_ENTRY(sceCodec_driver),
	NID_ENTRY(scePower_driver),
	NID_ENTRY(sceReg_driver),
	NID_ENTRY(sceHprm_driver),
	NID_ENTRY(sceDve_driver),
	NID_ENTRY(KDebugForKernel),
	NID_ENTRY(InterruptManagerForKernel),
};

u32 nid_fix_400_to_620_size = NELEMS(nid_fix_400_to_620);
