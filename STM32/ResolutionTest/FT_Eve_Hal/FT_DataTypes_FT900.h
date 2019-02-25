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

#ifndef _FT_DATATYPES_FT900_H_
#define _FT_DATATYPES_FT900_H_


#if (defined(FT900_PLATFORM))


#define FT_FALSE           (0)
#define FT_TRUE            (1)

typedef char				ft_char8_t;
typedef signed char 		ft_schar8_t;
typedef unsigned char 		ft_uchar8_t;

typedef ft_uchar8_t 		ft_uint8_t;
typedef ft_uchar8_t 		byte;
typedef short  				ft_int16_t;
typedef unsigned short 		ft_uint16_t;
typedef unsigned int 		ft_uint32_t;
typedef int 				ft_int32_t;
typedef void 				ft_void_t;
typedef long long 			ft_int64_t;
typedef unsigned long long 	ft_uint64_t;
typedef float 				ft_float_t;
typedef double 				ft_double_t;
typedef _Bool 				ft_bool_t;


typedef volatile unsigned char 	ft_vuint8_t;
typedef volatile unsigned short ft_vuint16;
typedef volatile unsigned long 	ft_vuint32;

typedef volatile char 	ft_vint8;
typedef volatile short 	ft_vint16;
typedef volatile long 	ft_vint32;

#define ft_delay(x) Ft_Gpu_Hal_Sleep(x)
#define FT_DBGPRINT(x)  ESD_print(x)
#define ft_random(x)	rand() % x
#define min(X,Y) ((X) < (Y) ?  (X) : (Y))
#define max(X,Y) ((X) > (Y) ?  (X) : (Y))

#define ft_prog_uchar8_t  ft_uchar8_t __flash__ const
#define ft_prog_char8_t   ft_char8_t __flash__ const
#define ft_prog_uint16_t  ft_uint16_t __flash__ const

#define FT_PROGMEM __flash__
#define ft_pgm_read_byte_near(x)   (*((ft_prog_uchar8_t *)(x)))
#define ft_pgm_read_byte(x)        (*((ft_prog_uchar8_t *)(x)))
#define ft_pgm_read_word(addr)   (*((ft_prog_uint16_t *)(addr)))
#define TRUE     (1)


#endif


#endif /*_FT_DATATYPES_FT900_H_*/

/* Nothing beyond this*/
