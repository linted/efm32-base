/***************************************************************************//**
 * Module Configuration Header
 * Copyright 2018 Silicon Laboratories, Inc.
 *
 * # License
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software.@n
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.@n
 * 3. This notice may not be removed or altered from any source distribution.
 *
 * DISCLAIMER OF WARRANTY/LIMITATION OF REMEDIES: Silicon Laboratories, Inc.
 * has no obligation to support this Software. Silicon Laboratories, Inc. is
 * providing the Software "AS IS", with no express or implied warranties of any
 * kind, including, but not limited to, any implied warranties of
 * merchantability or fitness for any particular purpose or warranties against
 * infringement of any proprietary rights of a third party.
 *
 * Silicon Laboratories, Inc. will not be liable for any consequential,
 * incidental, or special damages, or any other relief, or for any claim by
 * any third party, arising from your use of this Software.
 ******************************************************************************/
 
#ifndef SL_MODULE_MGM12P32F1024GA_H
#define SL_MODULE_MGM12P32F1024GA_H

#include "em_cmu.h"
#include "em_emu.h"

#ifdef __cplusplus
extern "C" {
#endif

#define BSP_CLK_HFXO_CTUNE 		282
#define BSP_CLK_HFXO_FREQ 		38400000UL
#define BSP_CLK_HFXO_INIT 		CMU_HFXOINIT_DEFAULT
#define BSP_CLK_HFXO_PRESENT 	1U

#define BSP_CLK_LFXO_CTUNE 		32U 
#define BSP_CLK_LFXO_FREQ 		32768UL
#define BSP_CLK_LFXO_INIT 		CMU_LFXOINIT_DEFAULT
#define BSP_CLK_LFXO_PRESENT 	1U

#define BSP_DCDC_INIT 			EMU_DCDCINIT_DEFAULT
#define BSP_DCDC_PRESENT 		1U

#ifndef HAL_DCDC_BYPASS
#define HAL_DCDC_BYPASS 		0U
#endif //HAL_DCDC_BYPASS

#ifndef BSP_PA_VOLTAGE
#define BSP_PA_VOLTAGE 			3300U
#endif //BSP_PA_VOLTAGE

// Configure integrated FEM
#define HAL_FEM_ENABLE 	        1U
#define HAL_FEM_RX_ACTIVE 		1U
#define BSP_FEM_RX_PIN 			10U
#define BSP_FEM_RX_PORT 		gpioPortD
#define BSP_FEM_RX_LOC  		0U
#define BSP_FEM_RX_CHANNEL 		5U
#define BSP_FEM_SLEEP_PIN 		11U
#define BSP_FEM_SLEEP_PORT 		gpioPortD
#define BSP_FEM_SLEEP_LOC 		13U
#define BSP_FEM_SLEEP_CHANNEL 	6U
#define HAL_FEM_TX_ACTIVE 		0U
#define BSP_FEM_TX_PIN 			10U
#define BSP_FEM_TX_PORT 		gpioPortD
#define BSP_FEM_TX_LOC  		0U
#define BSP_FEM_TX_CHANNEL 		5U
// Disable other FEM settings
#define HAL_FEM_TX_HIGH_POWER 	0U
#define BSP_FEM_TXPOWER         0U
#define HAL_FEM_BYPASS_ENABLE 	0U
#define BSP_FEM_BYPASS          0U

#ifdef __cplusplus
}
#endif

#endif // SL_MODULE_MGM12P32F1024GA_H