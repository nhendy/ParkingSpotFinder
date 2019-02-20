/**************************************************************************
 *
 *                  FTDIChip AN_xxx FT812 with ARM - Version 1.0
 *
 **************************************************************************
 * FileName:        FT812.h
 * Purpose:         This header file contains the display list and graphics
 *                  processor commands for the FTDI FT812 graphics controller chip
 * Dependencies:    See INCLUDES section below
 * Company:         Future Technology Devices International Ltd.
 *
 * Software License Agreement
 *
 * This code is provided as an example only and is not guaranteed by FTDI.
 * FTDI accept no responsibility for any issues resulting from its use.
 * The developer of the final application incorporating any parts of this
 * sample project is responsible for ensuring its safe and correct operation
 * and for any conequences resulting from its use.
 *
 * Author	Date				Rev		Comment
 **************************************************************************
 * BR			2014-03-01	1.0		Initial version - adapted from AN_275 source
 **************************************************************************

*/

#ifndef FT812_h
#define FT812_h

/*****************************************************************************/
/************************* I N C L U D E S ***********************************/
/*****************************************************************************/

/*****************************************************************************/
/********************** D E C L A R A T I O N S ******************************/
/*****************************************************************************/

#define FT_DL_SIZE            (8*1024)  //8KB Display List buffer size
#define FT_CMD_FIFO_SIZE      (4*1024)  //4KB coprocessor Fifo size
#define FT_CMD_SIZE           (4)       //4 byte per coprocessor command of EVE

#define FT812_VERSION         "1.0"

// FT812 Chip Commands - use with cmdWrite
#define FT812_ACTIVE					0x00			// Initializes FT812
#define FT812_STANDBY					0x41			// Place FT812 in Standby (clk running)
#define FT812_SLEEP						0x42			// Place FT812 in Sleep (clk off)
#define FT812_PWRDOWN					0x50			// Place FT812 in Power Down (core off)
#define FT812_CLKEXT					0x44			// Select external clock source
#define FT812_CLK48M					0x62			// Select 48MHz PLL
#define FT812_CLK36M					0x61			// Select 36MHz PLL
#define FT812_CORERST					0x68			// Reset core - all registers default

// FT812 Memory Commands - use with FT812memWritexx and FT812memReadxx
#define MEM_WRITE							0x80			// FT812 Host Memory Write
#define MEM_READ							0x00			// FT812 Host Memory Read


// Refer to the FT812 Datasheet

// FT812 Memory Map Addresses
#define RAM_CMD               0x308000UL
#define RAM_DL                0x300000UL
#define RAM_G                 0x000000UL
#define ROM_FONT			  0x1E0000UL
#define ROM_FONT_ADDR		  0x2FFFFCUL
#define RAM_REG               0x302000UL

// FT812 Register Addresses
#define REG_ANA_COMP         0x302184UL /* only listed in datasheet */
#define REG_BIST_EN          0x302174UL /* only listed in datasheet */
#define REG_CLOCK            0x302008UL
#define REG_CMDB_SPACE       0x302574UL
#define REG_CMDB_WRITE       0x302578UL
#define REG_CMD_DL           0x302100UL
#define REG_CMD_READ         0x3020f8UL
#define REG_CMD_WRITE        0x3020fcUL
#define REG_CPURESET         0x302020UL
#define REG_CSPREAD          0x302068UL
#define REG_CTOUCH_EXTENDED  0x302108UL
#define REG_CTOUCH_TOUCH0_XY 0x302124UL /* only listed in datasheet */
#define REG_CTOUCH_TOUCH4_X  0x30216cUL
#define REG_CTOUCH_TOUCH4_Y  0x302120UL
#define REG_CTOUCH_TOUCH1_XY 0x30211cUL
#define REG_CTOUCH_TOUCH2_XY 0x30218cUL
#define REG_CTOUCH_TOUCH3_XY 0x302190UL
#define REG_TOUCH_CONFIG     0x302168UL
#define REG_DATESTAMP        0x302564UL /* only listed in datasheet */
#define REG_DITHER           0x302060UL
#define REG_DLSWAP           0x302054UL
#define REG_FRAMES           0x302004UL
#define REG_FREQUENCY        0x30200cUL
#define REG_GPIO             0x302094UL
#define REG_GPIOX            0x30209cUL
#define REG_GPIOX_DIR        0x302098UL
#define REG_GPIO_DIR         0x302090UL
#define REG_HCYCLE           0x30202cUL
#define REG_HOFFSET          0x302030UL
#define REG_HSIZE            0x302034UL
#define REG_HSYNC0           0x302038UL
#define REG_HSYNC1           0x30203cUL
#define REG_ID               0x302000UL
#define REG_INT_EN           0x3020acUL
#define REG_INT_FLAGS        0x3020a8UL
#define REG_INT_MASK         0x3020b0UL
#define REG_MACRO_0          0x3020d8UL
#define REG_MACRO_1          0x3020dcUL
#define REG_MEDIAFIFO_READ   0x309014UL /* only listed in programmers guide */
#define REG_MEDIAFIFO_WRITE  0x309018UL /* only listed in programmers guide */
#define REG_OUTBITS          0x30205cUL
#define REG_PCLK             0x302070UL
#define REG_PCLK_POL         0x30206cUL
#define REG_PLAY             0x30208cUL
#define REG_PLAYBACK_FORMAT  0x3020c4UL
#define REG_PLAYBACK_FREQ    0x3020c0UL
#define REG_PLAYBACK_LENGTH  0x3020b8UL
#define REG_PLAYBACK_LOOP    0x3020c8UL
#define REG_PLAYBACK_PLAY    0x3020ccUL
#define REG_PLAYBACK_READPTR 0x3020bcUL
#define REG_PLAYBACK_START   0x3020b4UL
#define REG_PWM_DUTY         0x3020d4UL
#define REG_PWM_HZ           0x3020d0UL
#define REG_RENDERMODE       0x302010UL /* only listed in datasheet */
#define REG_ROTATE           0x302058UL
#define REG_SNAPFORMAT       0x30201cUL /* only listed in datasheet */
#define REG_SNAPSHOT         0x302018UL /* only listed in datasheet */
#define REG_SNAPY            0x302014UL /* only listed in datasheet */
#define REG_SOUND            0x302088UL
#define REG_SPI_WIDTH        0x302188UL /* listed with false offset in programmers guide V1.1 */
#define REG_SWIZZLE          0x302064UL
#define REG_TAG              0x30207cUL
#define REG_TAG_X            0x302074UL
#define REG_TAG_Y            0x302078UL
#define REG_TAP_CRC          0x302024UL /* only listed in datasheet */
#define REG_TAP_MASK         0x302028UL /* only listed in datasheet */
#define REG_TOUCH_ADC_MODE   0x302108UL
#define REG_TOUCH_CHARGE     0x30210cUL
#define REG_TOUCH_DIRECT_XY  0x30218cUL
#define REG_TOUCH_DIRECT_Z1Z2 0x302190UL
#define REG_TOUCH_MODE       0x302104UL
#define REG_TOUCH_OVERSAMPLE 0x302114UL
#define REG_TOUCH_RAW_XY     0x30211cUL
#define REG_TOUCH_RZ         0x302120UL
#define REG_TOUCH_RZTHRESH   0x302118UL
#define REG_TOUCH_SCREEN_XY  0x302124UL
#define REG_TOUCH_SETTLE     0x302110UL
#define REG_TOUCH_TAG        0x30212cUL
#define REG_TOUCH_TAG1       0x302134UL /* only listed in datasheet */
#define REG_TOUCH_TAG1_XY    0x302130UL /* only listed in datasheet */
#define REG_TOUCH_TAG2       0x30213cUL /* only listed in datasheet */
#define REG_TOUCH_TAG2_XY    0x302138UL /* only listed in datasheet */
#define REG_TOUCH_TAG3       0x302144UL /* only listed in datasheet */
#define REG_TOUCH_TAG3_XY    0x302140UL /* only listed in datasheet */
#define REG_TOUCH_TAG4       0x30214cUL /* only listed in datasheet */
#define REG_TOUCH_TAG4_XY    0x302148UL /* only listed in datasheet */
#define REG_TOUCH_TAG_XY     0x302128UL
#define REG_TOUCH_TRANSFORM_A 0x302150UL
#define REG_TOUCH_TRANSFORM_B 0x302154UL
#define REG_TOUCH_TRANSFORM_C 0x302158UL
#define REG_TOUCH_TRANSFORM_D 0x30215cUL
#define REG_TOUCH_TRANSFORM_E 0x302160UL
#define REG_TOUCH_TRANSFORM_F 0x302164UL
#define REG_TRACKER          0x309000UL /* only listed in programmers guide */
#define REG_TRACKER_1        0x309004UL /* only listed in programmers guide */
#define REG_TRACKER_2        0x309008UL /* only listed in programmers guide */
#define REG_TRACKER_3        0x30900cUL /* only listed in programmers guide */
#define REG_TRACKER_4        0x309010UL /* only listed in programmers guide */
#define REG_TRIM             0x302180UL
#define REG_VCYCLE           0x302040UL
#define REG_VOFFSET          0x302044UL
#define REG_VOL_PB           0x302080UL
#define REG_VOL_SOUND        0x302084UL
#define REG_VSIZE            0x302048UL
#define REG_VSYNC0           0x30204cUL
#define REG_VSYNC1           0x302050UL

// Graphics Engine Commands
// Refer to the FT812 Programmers Guide
/* additional commands for BT81x */
#define CMD_SYNC             0xFFFFFF42		/* does not need a dedicated function, just use EVE_cmd_dl(CMD_SYNC) */
#define CMD_FLASHERASE       0xFFFFFF44		/* does not need a dedicated function, just use EVE_cmd_dl(CMD_FLASHERASE) */
#define CMD_FLASHWRITE       0xFFFFFF45
#define CMD_FLASHREAD        0xFFFFFF46
#define CMD_FLASHUPDATE      0xFFFFFF47
#define CMD_FLASHDETACH      0xFFFFFF48		/* does not need a dedicated function, just use EVE_cmd_dl(CMD_FLASHDETACH) */
#define CMD_FLASHATTACH      0xFFFFFF49		/* does not need a dedicated function, just use EVE_cmd_dl(CMD_FLASHATTACH) */
#define CMD_FLASHFAST        0xFFFFFF4A
#define CMD_FLASHSPIDESEL    0xFFFFFF4B		/* does not need a dedicated function, just use EVE_cmd_dl(CMD_FLASHSPIDESEL) */
#define CMD_FLASHSPITX       0xFFFFFF4C
#define CMD_FLASHSPIRX       0xFFFFFF4D
#define CMD_FLASHSOURCE      0xFFFFFF4E
#define CMD_CLEARCACHE       0xFFFFFF4F		/* does not need a dedicated function, just use EVE_cmd_dl(CMD_CLEARCACHE) */
#define CMD_INFLATE2         0xFFFFFF50
#define CMD_ROTATEAROUND     0xFFFFFF51
#define CMD_RESETFONTS       0xFFFFFF52		/* does not need a dedicated function, just use EVE_cmd_dl(CMD_RESETFONTS) */
#define CMD_ANIMSTART        0xFFFFFF53
#define CMD_ANIMSTOP         0xFFFFFF54
#define CMD_ANIMXY           0xFFFFFF55
#define CMD_ANIMDRAW         0xFFFFFF56
#define CMD_GRADIENTA        0xFFFFFF57
#define CMD_FILLWIDTH        0xFFFFFF58
#define CMD_APPENDF          0xFFFFFF59
#define CMD_ANIMFRAME        0xFFFFFF5A
#define CMD_VIDEOSTARTF      0xFFFFFF5F		/* does not need a dedicated function, just use EVE_cmd_dl(CMD_VIDEOSTARTF) */


/* additional registers for BT81x */
#define REG_ADAPTIVE_FRAMERATE 0x30257cUL
#define REG_PLAYBACK_PAUSE     0x3025ecUL
#define REG_FLASH_STATUS       0x3025f0UL
#define REG_FLASH_SIZE         0x309024UL
#define REG_PLAY_CONTROL       0x30914eUL
#define REG_COPRO_PATCH_DTR    0x309162UL


// Display list commands to be embedded in Graphics Processor
#define DL_ALPHA_FUNC       	0x09000000UL // requires OR'd arguments
#define DL_BITMAP_HANDLE    	0x05000000UL // requires OR'd arguments
#define DL_BITMAP_LAYOUT    	0x07000000UL // requires OR'd arguments
#define DL_BITMAP_SIZE      	0x08000000UL // requires OR'd arguments
#define DL_BITMAP_SOURCE    	0x01000000UL // requires OR'd arguments
#define DL_BITMAP_TFORM_A   	0x15000000UL // requires OR'd arguments
#define DL_BITMAP_TFORM_B   	0x16000000UL // requires OR'd arguments
#define DL_BITMAP_TFORM_C   	0x17000000UL // requires OR'd arguments
#define DL_BITMAP_TFORM_D   	0x18000000UL // requires OR'd arguments
#define DL_BITMAP_TFORM_E   	0x19000000UL // requires OR'd arguments
#define DL_BITMAP_TFORM_F   	0x1A000000UL // requires OR'd arguments
#define DL_BLEND_FUNC       	0x0B000000UL // requires OR'd arguments
#define DL_BEGIN            	0x1F000000UL // requires OR'd arguments
#define DL_CALL             	0x1D000000UL // requires OR'd arguments
#define DL_CLEAR            	0x26000000UL // requires OR'd arguments
#define DL_CELL             	0x06000000UL // requires OR'd arguments
#define DL_CLEAR_RGB        	0x02000000UL // requires OR'd arguments
#define DL_CLEAR_STENCIL    	0x11000000UL // requires OR'd arguments
#define DL_CLEAR_TAG        	0x12000000UL // requires OR'd arguments
#define DL_COLOR_A          	0x0F000000UL // requires OR'd arguments
#define DL_COLOR_MASK       	0x20000000UL // requires OR'd arguments
#define DL_COLOR_RGB        	0x04000000UL // requires OR'd arguments
#define DL_DISPLAY          	0x00000000UL
#define DL_END              	0x21000000UL
#define DL_JUMP             	0x1E000000UL // requires OR'd arguments
#define DL_LINE_WIDTH       	0x0E000000UL // requires OR'd arguments
#define DL_MACRO            	0x25000000UL // requires OR'd arguments
#define DL_POINT_SIZE       	0x0D000000UL // requires OR'd arguments
#define DL_RESTORE_CONTEXT  	0x23000000UL
#define DL_RETURN           	0x24000000UL
#define DL_SAVE_CONTEXT     	0x22000000UL
#define DL_SCISSOR_SIZE     	0x1C000000UL // requires OR'd arguments
#define DL_SCISSOR_XY       	0x1B000000UL // requires OR'd arguments
#define DL_STENCIL_FUNC     	0x0A000000UL // requires OR'd arguments
#define DL_STENCIL_MASK     	0x13000000UL // requires OR'd arguments
#define DL_STENCIL_OP       	0x0C000000UL // requires OR'd arguments
#define DL_TAG             		0x03000000UL // requires OR'd arguments
#define DL_TAG_MASK         	0x14000000UL // requires OR'd arguments
#define DL_VERTEX2F         	0x40000000UL // requires OR'd arguments
#define DL_VERTEX2II        	0x02000000UL // requires OR'd arguments

// Command and register value options
#define CLR_COL               0x4
#define CLR_STN               0x2
#define CLR_TAG               0x1
#define DECR                  4UL
#define DECR_WRAP             7UL
#define DLSWAP_DONE           0UL
#define DLSWAP_FRAME          2UL
#define DLSWAP_LINE           1UL
#define DST_ALPHA             3UL
#define EDGE_STRIP_A          7UL
#define EDGE_STRIP_B          8UL
#define EDGE_STRIP_L          6UL
#define EDGE_STRIP_R          5UL
#define EQUAL                 5UL
#define GEQUAL                4UL
#define GREATER               3UL
#define INCR                  3UL
#define INCR_WRAP             6UL
#define INT_CMDEMPTY          32UL
#define INT_CMDFLAG           64UL
#define INT_CONVCOMPLETE      128UL
#define INT_PLAYBACK          16UL
#define INT_SOUND             8UL
#define INT_SWAP              1UL
#define INT_TAG               4UL
#define INT_TOUCH             2UL
#define INVERT                5UL
#define KEEP                  1UL
#define L1                    1UL
#define L4                    2UL
#define L8                    3UL
#define LEQUAL                2UL
#define LESS                  1UL
#define LINEAR_SAMPLES        0UL
#define LINES                 3UL
#define LINE_STRIP            4UL
#define NEAREST               0UL
#define NEVER                 0UL
#define NOTEQUAL              6UL
#define ONE                   1UL
#define ONE_MINUS_DST_ALPHA   5UL
#define ONE_MINUS_SRC_ALPHA   4UL
#define OPT_CENTER            1536UL    // 0x6000
#define OPT_CENTERX           512UL     // 0x0200
#define OPT_CENTERY           1024UL    // 0x0400
#define OPT_FLAT              256UL     // 0x0100
#define OPT_MONO              1UL
#define OPT_NOBACK            4096UL    // 0x1000
#define OPT_NODL              2UL
#define OPT_NOHANDS           49152UL   // 0xC168
#define OPT_NOHM              16384UL   // 0x4000
#define OPT_NOPOINTER         16384UL   // 0x4000
#define OPT_NOSECS            32768UL   // 0x8000
#define OPT_NOTICKS           8192UL    // 0x2000
#define OPT_RIGHTX            2048UL    // 0x0800
#define OPT_SIGNED            256UL     // 0x0100
#define PALETTED              8UL
#define PLAYCOLOR             0x00a0a080
#define FTPOINTS              2UL       // "POINTS" is a reserved word
#define RECTS                 9UL
#define REPEAT                1UL
#define REPLACE               2UL
#define RGB332                4UL
#define RGB565                7UL
#define SRC_ALPHA             2UL
#define TEXT8X8               9UL
#define TEXTVGA               10UL
#define TOUCHMODE_CONTINUOUS  3UL
#define TOUCHMODE_FRAME       2UL
#define TOUCHMODE_OFF         0UL
#define TOUCHMODE_ONESHOT     1UL
#define ULAW_SAMPLES          1UL
#define ZERO                  0UL


/* commands common to EVE/EVE2/EVE3 */
#define CMD_APPEND				0xFFFFFF1E
#define CMD_BGCOLOR				0xFFFFFF09
#define CMD_BUTTON				0xFFFFFF0D
#define CMD_CALIBRATE			0xFFFFFF15
#define CMD_CLOCK				0xFFFFFF14
#define CMD_COLDSTART			0xFFFFFF32
#define CMD_DIAL				0xFFFFFF2D
#define CMD_DLSTART				0xFFFFFF00
#define CMD_FGCOLOR				0xFFFFFF0A
#define CMD_GAUGE				0xFFFFFF13
#define CMD_GETMATRIX			0xFFFFFF33
#define CMD_GETPROPS			0xFFFFFF25
#define CMD_GETPTR				0xFFFFFF23
#define CMD_GRADCOLOR			0xFFFFFF34
#define CMD_GRADIENT			0xFFFFFF0B
#define CMD_INFLATE				0xFFFFFF22
#define CMD_INTERRUPT			0xFFFFFF02
#define CMD_KEYS				0xFFFFFF0E
#define CMD_LOADIDENTITY		0xFFFFFF26
#define CMD_LOADIMAGE			0xFFFFFF24
#define CMD_LOGO				0xFFFFFF31
#define CMD_MEMCPY				0xFFFFFF1D
#define CMD_MEMCRC				0xFFFFFF18
#define CMD_MEMSET				0xFFFFFF1B
#define CMD_MEMWRITE			0xFFFFFF1A
#define CMD_MEMZERO				0xFFFFFF1C
#define CMD_NUMBER				0xFFFFFF2E
#define CMD_PROGRESS			0xFFFFFF0F
#define CMD_REGREAD				0xFFFFFF19
#define CMD_ROTATE				0xFFFFFF29
#define CMD_SCALE				0xFFFFFF28
#define CMD_SCREENSAVER			0xFFFFFF2F
#define CMD_SCROLLBAR			0xFFFFFF11
#define CMD_SETFONT				0xFFFFFF2B
#define CMD_SETMATRIX			0xFFFFFF2A
#define CMD_SKETCH				0xFFFFFF30
#define CMD_SLIDER				0xFFFFFF10
#define CMD_SNAPSHOT			0xFFFFFF1F
#define CMD_SPINNER				0xFFFFFF16
#define CMD_STOP				0xFFFFFF17
#define CMD_SWAP				0xFFFFFF01
#define CMD_TEXT				0xFFFFFF0C
#define CMD_TOGGLE				0xFFFFFF12
#define CMD_TRACK				0xFFFFFF2C
#define CMD_TRANSLATE			0xFFFFFF27

// Useful Macros
#define RGB(r, g, b)          ((((r) << 16) | (g) << 8) | (b))
#define SQ(v)                 ((v) * (v))
#define MIN(x,y)              ((x) > (y) ? (y) : (x))
#define MAX(x,y)              ((x) > (y) ? (x) : (y))
#define NOTE(n, sharp)        (((n) - 'C') + ((sharp) * 128))
#define F16(s)                (((s) * 65536))
#define INVALID_TOUCH_XY      0x8000
#define ABS(x)                ((x) > (0) ? (x) : (-x))

#endif  //FT812_h
/** EOF FT812.h ********************************************************/
