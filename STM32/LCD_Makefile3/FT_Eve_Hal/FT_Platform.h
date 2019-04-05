/*

Copyright (c) BridgeTek Pte Ltd 2015

THIS SOFTWARE IS PROVIDED BY BridgeTek Pte Ltd "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL
BridgeTek Pte Ltd BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
OF SUBSTITUTE GOODS OR SERVICES LOSS OF USE, DATA, OR PROFITS OR BUSINESS INTERRUPTION)
HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

FTDI DRIVERS MAY BE USED ONLY IN CONJUNCTION WITH PRODUCTS BASED ON FTDI PARTS.

FTDI DRIVERS MAY BE DISTRIBUTED IN ANY FORM AS LONG AS LICENSE INFORMATION IS NOT MODIFIED.

IF A CUSTOM VENDOR ID AND/OR PRODUCT ID OR DESCRIPTION STRING ARE USED, IT IS THE
RESPONSIBILITY OF THE PRODUCT MANUFACTURER TO MAINTAIN ANY CHANGES AND SUBSEQUENT WHQL
RE-CERTIFICATION AS A RESULT OF MAKING THESE CHANGES.

Abstract:

This file contains is functions for all UI fields.
*/

#ifndef _FT_PLATFORM_H_
#define _FT_PLATFORM_H_


#include "FT_EveModule.h"
//#include "main.c"
/* FT900 Platform */
#ifndef STM32F7
 #define STM32F7								(1)
#endif


#define FT800_PD_N	GPIO_PIN_0
#define FT800_CS_N	GPIO_PIN_1

//#define USE_RTC_I2C
//#define ENABLE_OV2640_CAMERA

/* Module specific configurations */
/* MM900 series modules */
//#define MM900EV1A									(1)
//#define MM900EV2A									(1)
//#define MM900EV3A									(1)
//#define MM900EV_LITE								(1)
//#define FT900DEMOBOARD								(1)

/* ME8XX series modules */
// #define ME800A_HV35R								(1)
//#define ME810A_HV35R								(1)
// #define ME813A_WV7C								(1)
 // #define ME812A_WH50R								(1)
//#define VM800B43_50									(1)

/* CleO modules */
//#define CLEO35										(1)
//#define CLEO50										(1)


#if (defined(MM900EV1A) || defined(MM900EV2A) || defined(MM900EV3A) || defined(MM900EV_LITE) || defined(FT900DEMOBOARD))

/* RTC configurations */
#define FT900_PLATFORM_RTC_I2C						(1)
#define RTC_PRESENT									(1)

#endif

#if (defined(CLEO35) || defined(CLEO50))

/* RTC configurations */
#define FT900_PLATFORM_RTC_I2C						(1)
#define RTC_PRESENT									(1)

#endif


#ifdef VM800B43_50
#define ENABLE_SPI_SINGLE							(1)
#define FT_800_ENABLE								(1)
#define DISPLAY_RESOLUTION_WQVGA					(1)
#define RESISTANCE_THRESHOLD						(1200)
#endif

#ifdef ME800A_HV35R

#define ENABLE_SPI_SINGLE							(1)
#define FT_800_ENABLE								(1)
#define DISPLAY_RESOLUTION_HVGA_PORTRAIT			(1)
#define ENABLE_ILI9488_HVGA_PORTRAIT				(1)
#define RESISTANCE_THRESHOLD						(1800)

#endif /* #ifdef ME800A_HV35R */

#ifdef ME810A_HV35R

#define ENABLE_SPI_QUAD								(1)
#define FT_810_ENABLE								(1)
#define DISPLAY_RESOLUTION_HVGA_PORTRAIT			(1)
#define ENABLE_ILI9488_HVGA_PORTRAIT				(1)
#define RESISTANCE_THRESHOLD						(1800)
#endif /* #ifdef ME800A_HV35R */

#ifdef ME813A_WV7C

#define ENABLE_SPI_QUAD								(1)
#define FT_813_ENABLE								(1)
#define DISPLAY_RESOLUTION_WVGA						(1)

#endif /* #ifdef ME813A_WV7C */

#ifdef ME812A_WH50R

#define ENABLE_SPI_SINGLE							(1)
#define FT_812_ENABLE								(1)
#define DISPLAY_RESOLUTION_WVGA						(1)
#define RESISTANCE_THRESHOLD						(1800)

#endif /* #ifdef ME813A_WV7C */


#ifdef CLEO35

#define ENABLE_SPI_QUAD								(1)
#define FT_810_ENABLE								(1)
#define DISPLAY_RESOLUTION_HVGA_PORTRAIT			(1)
#define ENABLE_ILI9488_HVGA_PORTRAIT				(1)
#define RESISTANCE_THRESHOLD						(1800)

#endif /* #ifdef ME813A_WV7C */

#ifdef CLEO50

#define ENABLE_SPI_QUAD								(1)
#define FT_812_ENABLE								(1)
#define DISPLAY_RESOLUTION_WVGA						(1)
#define RESISTANCE_THRESHOLD						(1200)

#endif /* #ifdef ME813A_WV7C */

/* Individual configurations if module specific configurations are not defined */
/* Enable the respective macros based on the custom platform */
#if (!defined(ME800A_HV35R) && !defined(ME810A_HV35R) && !defined(ME813A_WV7C) && !defined(ME812A_WH50R) && !defined(VM800B43_50) && !defined(CLEO35) && !defined(CLEO50))

/* platform specific macros */
#define FT900_PLATFORM								(1)
/* Display configuration specific macros */
#define DISPLAY_RESOLUTION_QVGA						(1)
#define DISPLAY_RESOLUTION_WQVGA					(1)
#define DISPLAY_RESOLUTION_WVGA						(1)
#define DISPLAY_RESOLUTION_HVGA_PORTRAIT			(1)

/* Chip configuration specific macros */
#define FT_800_ENABLE								(1)
#define FT_801_ENABLE								(1)
#define FT_810_ENABLE								(1)
#define FT_811_ENABLE								(1)
#define FT_812_ENABLE								(1)
#define FT_813_ENABLE								(1)

/* SPI specific macros - compile time switches for SPI single, dial and quad use cases */
#define ENABLE_SPI_SINGLE							(1)
#define ENABLE_SPI_DUAL								(1)
#define ENABLE_SPI_QUAD								(1)

/* Display driver configurations - mainly for ME900EV1 modules */
#define ENABLE_ILI9488_HVGA_PORTRAIT				(1)

#endif /* #if (!defined(ME800A) && !defined(ME813A)) */


#if (defined(FT_800_ENABLE) || defined(FT_801_ENABLE))
#define FT_80X_ENABLE								(1)
#endif

#if (defined(FT_810_ENABLE) || defined(FT_811_ENABLE) || defined(FT_812_ENABLE) || defined(FT_813_ENABLE))
#define FT_81X_ENABLE								(1)
#endif



/* Standard C libraries */
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "FT_DataTypes.h"


/* HAL inclusions */

#include "FT_Gpu_Hal.h"
#include "FT_Gpu.h"
#include "FT_CoPro_Cmds.h"
#include "FT_Hal_Utils.h"
#include "FT_ILI9488.h"

/* Hardware or Module specific macros for gpio line numbers  */
#if (defined(MM900EV1A) || defined(MM900EV2A) || defined(MM900EV3A) || defined(MM900EV_LITE))
#define FT800_SEL_PIN   						0
#define FT800_PD_N      						43//for mm900 module

#define FT900_UART0_TX							(48)
#define FT900_UART0_RX							(49)

/* Timer 1 is been utilized in case of FT900 platform */
#define	FT900_FT_MILLIS_TIMER					(timer_select_b)
#define FT900_TIMER_MAX_VALUE 					(65536L)
#define FT900_TIMER_PRESCALE_VALUE 				(100)
#define FT900_TIMER_OVERFLOW_VALUE 				(1000)

#endif

#if (defined(CLEO35))
#define FT800_SEL_PIN   						0
#define FT800_PD_N      						66//for cleo35 module

#define FT900_UART0_TX							(48)
#define FT900_UART0_RX							(49)

/* Timer 1 is been utilized in case of FT900 platform */
#define	FT900_FT_MILLIS_TIMER					(timer_select_b)
#define FT900_TIMER_MAX_VALUE 					(65536L)
#define FT900_TIMER_PRESCALE_VALUE 				(100)
#define FT900_TIMER_OVERFLOW_VALUE 				(1000)

#endif

#ifdef CLEO50
#define FT800_SEL_PIN   						0
#define FT800_PD_N      						0//for cleo50 module

#define FT900_UART0_TX							(48)
#define FT900_UART0_RX							(49)

/* Timer 1 is been utilized in case of FT900 platform */
#define	FT900_FT_MILLIS_TIMER					(timer_select_b)
#define FT900_TIMER_MAX_VALUE 					(65536L)
#define FT900_TIMER_PRESCALE_VALUE 				(100)
#define FT900_TIMER_OVERFLOW_VALUE 				(1000)
#endif

#ifdef FT900DEMOBOARD
#define FT800_SEL_PIN   						0
#define FT800_PD_N      						32

#define FT900_UART0_TX							(48)
#define FT900_UART0_RX							(49)

/* Timer 1 is been utilized in case of FT900 platform */
#define	FT900_FT_MILLIS_TIMER					(timer_select_b)
#define FT900_TIMER_MAX_VALUE 					(65536L)
#define FT900_TIMER_PRESCALE_VALUE 				(100)
#define FT900_TIMER_OVERFLOW_VALUE 				(1000)

#endif

#endif /*_FT_PLATFORM_H_*/
/* Nothing beyond this*/
