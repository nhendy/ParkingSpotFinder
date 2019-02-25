/**
* This source code ("the Software") is provided by Bridgetek Pte Ltd
* ("Bridgetek") subject to the licence terms set out
*   http://brtchip.com/BRTSourceCodeLicenseAgreement/ ("the Licence Terms").
* You must read the Licence Terms before downloading or using the Software.
* By installing or using the Software you agree to the Licence Terms. If you
* do not agree to the Licence Terms then do not download or use the Software.
*
* Without prejudice to the Licence Terms, here is a summary of some of the key
* terms of the Licence Terms (and in the event of any conflict between this
* summary and the Licence Terms then the text of the Licence Terms will
* prevail).
*
* The Software is provided "as is".
* There are no warranties (or similar) in relation to the quality of the
* Software. You use it at your own risk.
* The Software should not be used in, or for, any medical device, system or
* appliance. There are exclusions of Bridgetek liability for certain types of loss
* such as: special loss or damage; incidental loss or damage; indirect or
* consequential loss or damage; loss of income; loss of business; loss of
* profits; loss of revenue; loss of contracts; business interruption; loss of
* the use of money or anticipated savings; loss of information; loss of
* opportunity; loss of goodwill or reputation; and/or loss of, damage to or
* corruption of data.
* There is a monetary cap on Bridgetek's liability.
* The Software may have subsequently been amended by another user and then
* distributed by that other user ("Adapted Software").  If so that user may
* have additional licence terms that apply to those amendments. However, Bridgetek
* has no liability in relation to those amendments.
*/
#if defined(MSVC_PLATFORM)

#ifndef _FT_PLATFORM_MSVC_H_
#define _FT_PLATFORM_MSVC_H_

/* Module connected from PC to basic modules */
#ifdef VA800A_SPI
#define ENABLE_SPI_SINGLE						(1)
#endif /* VA800A_SPI */

/* C library inclusions */
#include <Windows.h>

#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <math.h>

#include <direct.h>
#include <time.h>
#include <io.h>

/* D2xx and SPI from FTDI inclusions */
#include "ftd2xx.h"
#include "LibFT4222.h"

/* HAL inclusions */
#include "FT_DataTypes.h"
#include "FT_Gpu_Hal.h"
#include "FT_Gpu.h"
#include "FT_CoPro_Cmds.h"
#include "FT_Hal_Utils.h"

#ifdef MSVC_PLATFORM_SPI_LIBFT4222
#define FT800_SEL_PIN   1	/* GPIO is not utilized in Lib4222 as it is directly managed by firmware */
#define FT800_PD_N      GPIO_PORT0
#endif

#ifdef MSVC_PLATFORM_SPI_LIBMPSSE
#define FT800_SEL_PIN   0
#define FT800_PD_N      7
#endif

#endif /* _FT_PLATFORM_MSVC_H_ */

#endif 

/* Nothing beyond this*/
