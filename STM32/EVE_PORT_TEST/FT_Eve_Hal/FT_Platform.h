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

/*

For compilation, both a graphics module as well as a processor module must be
selected through the following precompiler definition options:

List of graphics modules:
- ME810A_HV35R
- ME813A_WV7C
- ME813AU_WH50C
- ME812A_WH50R

List of processor modules:
- MM900EV1A
- MM900EV2A
- MM900EV3A
- MM900EV_LITE
- MSVC_PLATFORM_SPI_LIBFT4222
- MSVC_PLATFORM_SPI_LIBMPSSE

List of combined (graphics + processor) modules:
- PANL35			(FT811 + FT90x)
- PANL70			(FT811 + FT90x)
- PANL70PLUS		(FT811 + FT90x)
- VM816CU50A		(BT816 + SPI FT4222)
- VM816C50A         (BT816 + SPI MPSSE)
- FT801_GENERIC     (BT801 + FT90x)         (Generic for emulator test)
- FT811_GENERIC     (BT811 + FT90x)         (Generic for emulator test)
- BT815_GENERIC     (BT815 + FT90x)         (Generic for emulator test)

When using a custom module, define the precompiler options as they would
normally be set by the various platforms manually.

*/

#ifndef FT_PLATFORM_H
#define FT_PLATFORM_H


#if defined(ESD_SIMULATION) && !defined(BT8XXEMU_PLATFORM)
// Under ESD always enable use of emulator.
#define BT8XXEMU_PLATFORM
#endif


#if defined(ME810A_HV35R)

#define ENABLE_SPI_QUAD
#define FT_810_ENABLE
#define DISPLAY_RESOLUTION_HVGA_PORTRAIT
#define ENABLE_ILI9488_HVGA_PORTRAIT
#define RESISTANCE_THRESHOLD                    (1800)

#elif defined(ME812A_WH50R)

#define ENABLE_SPI_QUAD
#define FT_812_ENABLE
#define DISPLAY_RESOLUTION_WVGA
#define RESISTANCE_THRESHOLD                    (1800)

#elif defined(ME813A_WV7C)

#define ENABLE_SPI_QUAD
#define FT_813_ENABLE
#define DISPLAY_RESOLUTION_WVGA

#elif defined(ME813AU_WH50C)

#define FT_813_ENABLE
#define DISPLAY_RESOLUTION_WVGA
#define ENABLE_SPI_QUAD
#define MSVC_PLATFORM_SPI_LIBFT4222

#elif defined(VM816CU50A)

#define BT_816_ENABLE
#define DISPLAY_RESOLUTION_WVGA
#define ENABLE_SPI_QUAD
#define MSVC_PLATFORM_SPI_LIBFT4222
#define RESISTANCE_THRESHOLD                    (1800)

#elif defined(VM816C50A)

#define BT_816_ENABLE
#define DISPLAY_RESOLUTION_WVGA
// #define ENABLE_SPI_QUAD
#define MSVC_PLATFORM_SPI_LIBMPSSE
#define RESISTANCE_THRESHOLD                    (1800)

#elif defined(PANL35)

#define ENABLE_SPI_QUAD
#define FT_811_ENABLE
#define DISPLAY_RESOLUTION_HVGA_PORTRAIT
#define ENABLE_KD2401_HVGA_PORTRAIT

#if !(defined(BT8XXEMU_PLATFORM))
#define malloc                                  pvPortMalloc
#define calloc                                  vPortCalloc
#define free                                    vPortFree
#define PANL_HEAP_SIZE                          (20 * 1024)
#define TINYPRINTF_OVERRIDE_LIBC                (0)
#endif

#elif defined(PANL70)

#define ENABLE_SPI_QUAD
#define FT_811_ENABLE

#define DISPLAY_RESOLUTION_WVGA

#if !(defined(BT8XXEMU_PLATFORM))
#define malloc                                  pvPortMalloc
#define calloc                                  vPortCalloc
#define free                                    vPortFree
#define PANL_HEAP_SIZE                          (20 * 1024)
#define TINYPRINTF_OVERRIDE_LIBC                (0)
#endif

#elif defined(PANL70PLUS)

#define ENABLE_SPI_QUAD
#define FT_811_ENABLE

#define DISPLAY_RESOLUTION_WVGA

#if !(defined(BT8XXEMU_PLATFORM))
#define malloc                                  pvPortMalloc
#define calloc                                  vPortCalloc
#define free                                    vPortFree
#define PANL_HEAP_SIZE                          (20 * 1024)
#define TINYPRINTF_OVERRIDE_LIBC                (0)
#endif

#elif defined(FT801_GENERIC)

/* Configuration macro for development and testing purpose of FT801 emulator */
#define BT_815_ENABLE
#define DISPLAY_RESOLUTION_QVGA

#elif defined(FT811_GENERIC)

/* Configuration macro for development and testing purpose of FT811 emulator */
#define FT_811_ENABLE
#define DISPLAY_RESOLUTION_WVGA
#define ENABLE_SPI_QUAD

#elif defined(BT815_GENERIC)

/* Configuration macro for development and testing purpose with BT815 emulator */
#define BT_815_ENABLE
#define DISPLAY_RESOLUTION_WVGA
#define ENABLE_SPI_QUAD

#endif


/// Define global platform (MSVC_PLATFORM or FT900_PLATFORM).
/// Global platform is defined even under emulator or ESD simulation,
/// in order to permit simulation of platform specific features.
/// BT8XXEMU_PLATFORM and ESD_SIMULATION always take precedence.
#if defined(MM900EV1A) || defined(MM900EV2A) || defined(MM900EV3A) || defined(MM900EV_LITE)

#ifndef FT900_PLATFORM
#define FT900_PLATFORM
#endif

#elif defined(PANL35) || defined(PANL70) || defined(PANL70PLUS)

#ifndef FT900_PLATFORM
#define FT900_PLATFORM
#endif
#ifndef BT_MODULE_PANL
#define BT_MODULE_PANL
#endif

#elif defined(FT801_GENERIC) || defined(FT811_GENERIC) || defined(BT815_GENERIC)

#ifndef FT900_PLATFORM
#define FT900_PLATFORM
#endif

#elif defined(MSVC_PLATFORM_SPI_LIBFT4222) || defined(MSVC_PLATFORM_SPI_LIBMPSSE)

#ifndef MSVC_PLATFORM_SPI
#define MSVC_PLATFORM_SPI
#endif

#ifndef MSVC_PLATFORM
#define MSVC_PLATFORM
#endif

#endif


/// Re-Mapping FT800 Series to FT80X
#if defined(FT_800_ENABLE) || defined(FT_801_ENABLE)
#define FT_80X_ENABLE
#endif

/// Re-Mapping FT810 Series to FT81X
#if defined(FT_810_ENABLE) || defined(FT_811_ENABLE) || defined(FT_812_ENABLE) || defined(FT_813_ENABLE)
#define FT_81X_ENABLE
#endif

/// Re-Mapping BT810 Series to BT81X
#if defined(BT_815_ENABLE) || defined(BT_816_ENABLE)
#define BT_81X_ENABLE
#endif


/// Model numbered macro for versioning convenience.
/// Matches the BT8XXEMU_EmulatorMode enum values.
#if defined(FT_800_ENABLE)
#define BT_EVE_MODEL 0x0800
#elif defined(FT_801_ENABLE)
#define BT_EVE_MODEL 0x0801
#elif defined(FT_810_ENABLE)
#define BT_EVE_MODEL 0x0810
#elif defined(FT_811_ENABLE)
#define BT_EVE_MODEL 0x0811
#elif defined(FT_812_ENABLE)
#define BT_EVE_MODEL 0x0812
#elif defined(FT_813_ENABLE)
#define BT_EVE_MODEL 0x0813
#elif defined(BT_815_ENABLE)
#define BT_EVE_MODEL 0x0815
#elif defined(BT_816_ENABLE)
#define BT_EVE_MODEL 0x0816
#endif


/// Feature support.
/// Avoid hardcoding specific EVE models throughout the libraries.
#if (BT_EVE_MODEL >= 0x0815)
#define BT_EVE_SUPPORT_FLASH
#define BT_EVE_SUPPORT_UNICODE
#define BT_EVE_SUPPORT_ASTC
#endif
#if (BT_EVE_MODEL >= 0x0810)
#define BT_EVE_SUPPORT_PNG
#define BT_EVE_SUPPORT_VIDEO
#endif
#if ((BT_EVE_MODEL & 0x01) == 0x01)
#define BT_EVE_SCREEN_CAPACITIVE
#else
#define BT_EVE_SCREEN_RESISTIVE
#endif


#if defined(BT8XXEMU_PLATFORM)

// BT8XXEMU_PLATFORM takes priority over MSVC_PLATFORM and FT900_PLATFORM

#ifdef MSVC_PLATFORM
#undef MSVC_PLATFORM
#define PRETEND_PLATFORM_MSVC
#endif

#ifdef FT900_PLATFORM
#undef FT900_PLATFORM
#define PRETEND_PLATFORM_FT900
#endif

#endif


/// Include platform specific definitions
#if defined(BT8XXEMU_PLATFORM)
#include <FT_Platform_Simulation.h>
#elif defined(MSVC_PLATFORM)
#include <FT_Platform_MSVC.h>
#elif defined(FT900_PLATFORM)
#include <FT_Platform_FT900.h>
#endif


/// Configuration sanity checks
#if !defined(BT_EVE_MODEL)
#pragma message(": error<BT_EVE_MODEL>: No EVE model was selected")
#endif
#if !defined(BT_EVE_SUPPORT_FLASH) && defined(BT_EVE_FLASH_ENABLE)
#pragma message(": warning<BT_EVE_FLASH_ENABLE>: Cannot enable flash on EVE model which doesn't support flash")
#undef BT_EVE_FLASH_ENABLE
#endif
#if ((defined(FT900_PLATFORM) ? 1 : 0) \
    + (defined(MSVC_PLATFORM) ? 1 : 0) \
    + (defined(BT8XXEMU_PLATFORM) ? 1 : 0)) > 1
#pragma message(": warning<PLATFORM>: More than one platform has been selected")
#endif
#if (!defined(FT900_PLATFORM) && !defined(MSVC_PLATFORM) && !defined(BT8XXEMU_PLATFORM))
#pragma message(": warning<PLATFORM>: No platform was selected")
#endif
#if (defined (BT8XXEMU_PLATFORM) && !defined(PRETEND_PLATFORM_MSVC) && !defined(PRETEND_PLATFORM_FT900))
#pragma message(": warning<PLATFORM>: No platform was selected")
#endif
#if defined (BT8XXEMU_PLATFORM) \
    && (((defined(PRETEND_PLATFORM_MSVC) ? 1 : 0) \
    + (defined(PRETEND_PLATFORM_FT900) ? 1 : 0)) > 1)
#pragma message(": warning<PLATFORM>: More than one platform has been selected")
#endif


/*Define ESD_print macro*/
#ifdef NDEBUG      //Release mode
#define       ESD_print(fmt, ...)        do { } while (0)
#else             //Debug mode
#define       ESD_print(fmt, ...)        printf(fmt, ##__VA_ARGS__)

#if          !(defined(BT8XXEMU_PLATFORM) || defined(ESD_SIMULATION) || defined(MSVC_PLATFORM)) 
#undef        ESD_print
#define       ESD_print(fmt, ...)        iprintf(fmt, ##__VA_ARGS__)
#endif       /*!(defined(ESD_SIMULATION) || defined(MSVC_PLATFORM)) */
#endif  //end of NDEBUG

/*Define ESD_sprint macro*/
#if          !(defined(BT8XXEMU_PLATFORM) || defined(ESD_SIMULATION) || defined(MSVC_PLATFORM)) 
#define       ESD_sprint(str, fmt, ...)  siprintf(str, fmt, ##__VA_ARGS__)
#else 
#define       ESD_sprint(str, fmt, ...)  sprintf(str, fmt, ##__VA_ARGS__)
#endif

#endif /* FT_PLATFORM_H */

/* end of file */