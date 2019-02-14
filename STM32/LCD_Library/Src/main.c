/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 ** This notice applies to any and all portions of this file
 * that are not between comment pairs USER CODE BEGIN and
 * USER CODE END. Other portions of this file, whether
 * inserted by the user or by software development tools
 * are owned by their respective copyright owners.
 *
 * COPYRIGHT(c) 2019 STMicroelectronics
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of STMicroelectronics nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
//#include "FT812.h"
#include "main.h"
#include <FT_Platform.h>
#include <Ft_Esd.h>
#include <Ft_Esd_GpuAlloc.h>
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

SPI_HandleTypeDef hspi1;
SPI_HandleTypeDef hspi2;

/* USER CODE BEGIN PV */
// AN_312 FT800 pin definitions
#define FT800_PD_N	GPIO_PIN_0
#define FT800_CS_N	GPIO_PIN_1
static Ft_Gpu_Hal_Context_t s_Host;
static Ft_Esd_GpuAlloc s_GAlloc;
// AN312 FT800 screen size - uncomment the appropriate size
//#define LCD_QVGA																			// VM800B/C 3.5" QVGA - 320x240
//#define LCD_WQVGA
Ft_Gpu_Hal_Context_t *Ft_Esd_Host = 0; // Pointer to s_Host
Ft_Esd_GpuAlloc *Ft_Esd_GAlloc = 0; // Pointer to s_GAlloc
ft_uint32_t Ft_Esd_Millis = 0;  // Time in milliseconds for current frame
ft_uint32_t Ft_Esd_DeltaMs = 0; // Delta time in milliseconds between frames
ft_uint32_t Ft_Esd_Frame = 0;   // Number of times Render has been called
ft_rgb32_t Ft_Esd_ClearColor = 0x212121; // Screen clear color

ESD_FUNCTION(Ft_Esd_GetMillis, Type = ft_uint32_t, DisplayName = "Get Milliseconds", Category = EsdUtilities)
ft_uint32_t Ft_Esd_GetMillis() { return Ft_Esd_Millis; }

/* Difference in milliseconds since last frame Update call */
ESD_FUNCTION(Ft_Esd_GetDeltaMs, Type = ft_uint32_t, DisplayName = "Get Delta Ms", Category = EsdUtilities)
ft_uint32_t Ft_Esd_GetDeltaMs() { return Ft_Esd_DeltaMs; }

ESD_FUNCTION(Ft_Esd_GetHost, Type = Ft_Gpu_Hal_Context_t *, DisplayName = "Get EVE Host", Category = EsdUtilities)
Ft_Gpu_Hal_Context_t *Ft_Esd_GetHost() { return Ft_Esd_Host; }

ft_uint16_t Ft_Esd_FontHeight[32] = { 0 }; // Font heights of currently set bitmaps
#ifdef DISPLAY_RESOLUTION_WVGA
/* Values specific to QVGA LCD display */
FT_DispWidth = 800;
FT_DispHeight = 480;
FT_DispHCycle =  928;
FT_DispHOffset = 88;
FT_DispHSync0 = 0;
FT_DispHSync1 = 48;
FT_DispVCycle = 525;
FT_DispVOffset = 32;
FT_DispVSync0 = 0;
FT_DispVSync1 = 3;
FT_DispPCLK = 2;
FT_DispSwizzle = 0;
FT_DispPCLKPol = 1;
FT_DispCSpread = 0;
FT_DispDither = 1;
#endif

#define LCD_800480
// AN_312 Colors - fully saturated colors defined here
#define RED					0xFF0000UL													// Red
#define GREEN				0x00FF00UL													// Green
#define BLUE				0x0000FFUL													// Blue
#define WHITE				0xFFFFFFUL													// White
#define BLACK				0x000000UL													// Black

// Global Variables

// AN_312 FT800 pins
unsigned int FT800irqPin;																// Interrupt from FT800 to Arduino - not used here
unsigned int FT800pwrPin;																// PD_N from Arduino to FT800 - effectively FT800 reset
unsigned int FT800csPin;																// SPI chip select - defined separately since it's manipulated with GPIO calls

// AN_312 LCD display parameters
unsigned int lcdWidth;																	// Active width of LCD display
unsigned int lcdHeight;																	// Active height of LCD display
unsigned int lcdHcycle;																	// Total number of clocks per line
unsigned int lcdHoffset;																// Start of active line
unsigned int lcdHsync0;																	// Start of horizontal sync pulse
unsigned int lcdHsync1;																	// End of horizontal sync pulse
unsigned int lcdVcycle;																	// Total number of lines per screen
unsigned int lcdVoffset;																// Start of active screen
unsigned int lcdVsync0;																	// Start of vertical sync pulse
unsigned int lcdVsync1;																	// End of vertical sync pulse
unsigned char lcdPclk;																	// Pixel Clock
unsigned char lcdSwizzle;																// Define RGB output pins
unsigned char lcdPclkpol;																// Define active edge of PCLK

unsigned long ramDisplayList = RAM_DL;									// Set beginning of display list memory
unsigned long ramCommandBuffer = RAM_CMD;								// Set beginning of graphics command memory

unsigned int cmdBufferRd = 0x0000;											// Used to navigate command ring buffer
unsigned int cmdBufferWr = 0x0000;											// Used to navigate command ring buffer
unsigned int cmdOffset = 0x0000;												// Used to navigate command rung buffer
unsigned int point_size = 0x0100;												// Define a default dot size
unsigned long point_x = (96 * 16);											// Define a default point x-location (1/16 anti-aliased)
unsigned long point_y = (136 * 16);											// Define a default point y-location (1/16 anti-aliased)
unsigned long color;																		// Variable for chanign colors
unsigned char FT800Gpio;																// Used for FT800 GPIO register

// AN_312 Specific function prototypes - See full descriptions below
static void FT800cmdWrite(unsigned char);
static void FT800memWrite8(unsigned long, unsigned char);
static void FT800memWrite16(unsigned long, unsigned int);
static void FT800memWrite32(unsigned long, unsigned long);
unsigned char FT800memRead8(unsigned long);
unsigned int FT800memRead16(unsigned long);
unsigned long FT800memRead32(unsigned long);
unsigned int incCMDOffset(unsigned int, unsigned char);
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
static void MX_SPI2_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */



/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
	/* USER CODE BEGIN 1 */

	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_SPI1_Init();
	MX_SPI2_Init();
	FT800_BootupConfig();
	Ft_Esd_MainLoop();
	/* USER CODE BEGIN 2 */

	/* USER CODE END 2 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void)
{
	RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

	/**Configure the main internal regulator output voltage
	 */
	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);
	/**Initializes the CPU, AHB and APB busses clocks
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		Error_Handler();
	}
	/**Initializes the CPU, AHB and APB busses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
			|RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV2;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
	{
		Error_Handler();
	}
}

/**
 * @brief SPI1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_SPI1_Init(void)
{

	/* USER CODE BEGIN SPI1_Init 0 */

	/* USER CODE END SPI1_Init 0 */

	/* USER CODE BEGIN SPI1_Init 1 */

	/* USER CODE END SPI1_Init 1 */
	/* SPI1 parameter configuration*/
	hspi1.Instance = SPI1;
	hspi1.Init.Mode = SPI_MODE_MASTER;
	hspi1.Init.Direction = SPI_DIRECTION_2LINES;
	hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
	hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
	hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
	hspi1.Init.NSS = SPI_NSS_SOFT;
	hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
	hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
	hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi1.Init.CRCPolynomial = 7;
	hspi1.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
	hspi1.Init.NSSPMode = SPI_NSS_PULSE_DISABLE;
	if (HAL_SPI_Init(&hspi1) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN SPI1_Init 2 */

	/* USER CODE END SPI1_Init 2 */

}

/**
 * @brief SPI2 Initialization Function
 * @param None
 * @retval None
 */
static void MX_SPI2_Init(void)
{

	/* USER CODE BEGIN SPI2_Init 0 */

	/* USER CODE END SPI2_Init 0 */

	/* USER CODE BEGIN SPI2_Init 1 */

	/* USER CODE END SPI2_Init 1 */
	/* SPI2 parameter configuration*/
	hspi2.Instance = SPI2;
	hspi2.Init.Mode = SPI_MODE_MASTER;
	hspi2.Init.Direction = SPI_DIRECTION_2LINES;
	hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
	hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
	hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
	hspi2.Init.NSS = SPI_NSS_SOFT;
	hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
	hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
	hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi2.Init.CRCPolynomial = 7;
	hspi2.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
	hspi2.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
	if (HAL_SPI_Init(&hspi2) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN SPI2_Init 2 */

	/* USER CODE END SPI2_Init 2 */

}

ft_void_t FT800_BootupConfig() {
	Ft_Gpu_Hal_Powercycle(&s_Host, FT_TRUE);
	HAL_GPIO_WritePin(GPIOB, FT800_PD_N, GPIO_PIN_SET); 	// Initial state of PD_N - high
	HAL_GPIO_WritePin(GPIOB, FT800_CS_N, GPIO_PIN_SET);		// Initial state of SPI CS - high
	HAL_Delay(20);																				// Wait 20ms
	HAL_GPIO_WritePin(GPIOB, FT800_PD_N, GPIO_PIN_RESET); // Reset FT812
	HAL_Delay(20);																				// Wait 20ms
	HAL_GPIO_WritePin(GPIOB, FT800_PD_N, GPIO_PIN_SET); 	// FT812 is awake
	HAL_Delay(20);
	/* Access address 0 to wake up the FT800 */
	Ft_Gpu_HostCommand(&s_Host, FT_GPU_EXTERNAL_OSC);
	Ft_Gpu_Hal_Sleep(20);

	Ft_Gpu_HostCommand(&s_Host, FT_GPU_ACTIVE_M);
	Ft_Gpu_Hal_Sleep(20);
	Ft_Gpu_HostCommand(&s_Host, FT_GPU_PLL_48M );
	Ft_Gpu_Hal_Sleep(20);
	//	Ft_Gpu_HostCommand(&s_Host, FT_GPU_ACTIVE_M);
	//	Ft_Gpu_Hal_Sleep(300);

	/* Set the clk to external clock */
	//#if (!defined(ME800A_HV35R) && !defined(ME810A_HV35R) && !defined(ME812A_WH50R))
	//	Ft_Gpu_HostCommand(&s_Host, FT_GPU_EXTERNAL_OSC);
	//	Ft_Gpu_Hal_Sleep(20);
	//#endif

	;{
		volatile ft_uint8_t chipid;
		//Read Register ID to check if FT800 is ready.
		chipid = Ft_Gpu_Hal_Rd8(&s_Host, REG_ID);
		while (chipid != 0x7C)
		{
			chipid = Ft_Gpu_Hal_Rd8(&s_Host, REG_ID);
			printf("VC1 register ID after wake up %x\n", chipid);
			ft_delay(100);
		}
		Ft_Gpu_Hal_Wr16(&s_Host, REG_HCYCLE, FT_DispHCycle);
		Ft_Gpu_Hal_Wr16(&s_Host, REG_HOFFSET, FT_DispHOffset);
		Ft_Gpu_Hal_Wr16(&s_Host, REG_HSYNC0, FT_DispHSync0);
		Ft_Gpu_Hal_Wr16(&s_Host, REG_HSYNC1, FT_DispHSync1);
		Ft_Gpu_Hal_Wr16(&s_Host, REG_VCYCLE, FT_DispVCycle);
		Ft_Gpu_Hal_Wr16(&s_Host, REG_VOFFSET, FT_DispVOffset);
		Ft_Gpu_Hal_Wr16(&s_Host, REG_VSYNC0, FT_DispVSync0);
		Ft_Gpu_Hal_Wr16(&s_Host, REG_VSYNC1, FT_DispVSync1);
		Ft_Gpu_Hal_Wr8(&s_Host, REG_SWIZZLE, FT_DispSwizzle);
		Ft_Gpu_Hal_Wr8(&s_Host, REG_PCLK_POL, FT_DispPCLKPol);
		Ft_Gpu_Hal_Wr16(&s_Host, REG_HSIZE, FT_DispWidth);
		Ft_Gpu_Hal_Wr16(&s_Host, REG_VSIZE, FT_DispHeight);
		Ft_Gpu_Hal_Wr16(&s_Host, REG_CSPREAD, FT_DispCSpread);
		Ft_Gpu_Hal_Wr16(&s_Host, REG_DITHER, FT_DispDither);

		// remove this later
		//		ft812memWrite16(REG_HSIZE,   lcdWidth);								// active display width
		//		ft812memWrite16(REG_HCYCLE,  lcdHcycle);							// total number of clocks per line, incl front/back porch
		//		ft812memWrite16(REG_HOFFSET, lcdHoffset);							// start of active line
		//		ft812memWrite16(REG_HSYNC0,  lcdHsync0);							// start of horizontal sync pulse
		//		ft812memWrite16(REG_HSYNC1,  lcdHsync1);							// end of horizontal sync pulse
		//		ft812memWrite16(REG_VSIZE,   lcdHeight);							// active display height
		//		ft812memWrite16(REG_VCYCLE,  lcdVcycle);							// total number of lines per screen, incl pre/post
		//		ft812memWrite16(REG_VOFFSET, lcdVoffset);							// start of active screen
		//		ft812memWrite16(REG_VSYNC0,  lcdVsync0);							// start of vertical sync pulse
		//		ft812memWrite16(REG_VSYNC1,  lcdVsync1);							// end of vertical sync pulse
		//		ft812memWrite8(REG_SWIZZLE,  lcdSwizzle);							// FT812 output to LCD - pin order
		//		ft812memWrite8(REG_PCLK_POL, lcdPclkpol);							// LCD data is clocked in on this PCLK edge

		/* Initial boot up display list */
		const ft_uint32_t FT_DLCODE_BOOTUP[] = {
				CLEAR_COLOR_RGB(255, 0, 0),
				CLEAR(1, 1, 1),
				BITMAP_HANDLE(31),
				BEGIN(BITMAPS),
				VERTEX2II(6, 0, 31, 'F'),
				VERTEX2II(29, 0, 31, 'U'),
				VERTEX2II(55, 0, 31, 'C'),
				VERTEX2II(83, 0, 31, 'K'),
				BITMAP_HANDLE(28),
				BEGIN(BITMAPS),
				VERTEX2II(7, 43, 28, 'H'),
				VERTEX2II(22, 43, 28, 'e'),
				VERTEX2II(33, 43, 28, 'l'),
				VERTEX2II(39, 43, 28, 'l'),
				VERTEX2II(45, 43, 28, 'o'),
				DISPLAY(),
		};
		for(int duty = 0; duty <= 128; duty++)
		{
			ft812memWrite8(REG_PWM_DUTY, duty);									// Turn on backlight - ramp up slowly to full brighness
			HAL_Delay(10);
		}
#if (defined(FT_800_ENABLE) || defined(FT_810_ENABLE) ||defined(FT_812_ENABLE))
		/* Touch configuration - configure the resistance value to 1200 - this value is specific to customer requirement and derived by experiment */
		Ft_Gpu_Hal_Wr16(&s_Host, REG_TOUCH_RZTHRESH, RESISTANCE_THRESHOLD);
#endif

		Ft_Gpu_Hal_Wr8(&s_Host, REG_GPIO_DIR, 0xff);
		Ft_Gpu_Hal_Wr8(&s_Host, REG_GPIO, 0xff);

		Ft_Gpu_Hal_WrMem(&s_Host, RAM_DL, (ft_uint8_t *)FT_DLCODE_BOOTUP, sizeof(FT_DLCODE_BOOTUP));
		Ft_Gpu_Hal_Wr8(&s_Host, REG_DLSWAP, DLSWAP_FRAME);

		Ft_Gpu_Hal_Wr8(&s_Host, REG_PCLK, FT_DispPCLK);//after this display is visible on the LCD

	}
}

static void MX_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1, GPIO_PIN_RESET);

	/*Configure GPIO pins : PB0 PB1 */
	GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

ft_uint32_t Ft_Esd_GAlloc_GetTotalUsed(Ft_Esd_GpuAlloc *ga)
{
	if (!Ft_Esd_GAlloc) return 0;
	return Ft_Esd_GpuAlloc_GetTotalUsed(Ft_Esd_GAlloc);
}

ft_uint32_t Ft_Esd_GAlloc_GetTotal(Ft_Esd_GpuAlloc *ga)
{
	if (!Ft_Esd_GAlloc) return 0;
	return Ft_Esd_GpuAlloc_GetTotal(Ft_Esd_GAlloc);
}
/* USER CODE BEGIN 4 */


/******************************************************************************
 * Function:        void incCMDOffset(currentOffset, commandSize)
 * PreCondition:    None
 *                    starting a command list
 * Input:           currentOffset = graphics processor command list pointer
 *                  commandSize = number of bytes to increment the offset
 * Output:          newOffset = the new ring buffer pointer after adding the command
 * Side Effects:    None
 * Overview:        Adds commandSize to the currentOffset.
 *                  Checks for 4K ring-buffer offset roll-over
 * Note:            None
 *****************************************************************************/

unsigned int incCMDOffset(unsigned int currentOffset, unsigned char commandSize)
{
	unsigned int newOffset;															// Used to hold new offset
	newOffset = currentOffset + commandSize;						// Calculate new offset
	if(newOffset > 4095)																// If new offset past boundary...
	{
		newOffset = (newOffset - 4096);									// ... roll over pointer
	}
	return newOffset;																		// Return new offset
}
/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */

	/* USER CODE END Error_Handler_Debug */
}

void ft812memWrite8(unsigned long ftAddress, unsigned char ftData8)
{
	unsigned char cTempAddr[3];														// FT812 Memory Address

	cTempAddr[2] = (char) (ftAddress >> 16) | 0x80;	// Compose the command and address to send
	cTempAddr[1] = (char) (ftAddress >> 8);								// middle byte
	cTempAddr[0] = (char) (ftAddress);										// low byte

	HAL_GPIO_WritePin(GPIOB, FT800_CS_N, GPIO_PIN_RESET);	// Set chip select low

	for (int i = 2; i >= 0; i--)
	{
		HAL_SPI_Transmit(&hspi1, &cTempAddr[i], 1, 0); 			// Send Memory Write plus high address byte
	}

	for (int j = 0; j < sizeof(ftData8); j++)
	{
		HAL_SPI_Transmit(&hspi1, &ftData8, 1, 0);						// Send data byte
	}

	HAL_GPIO_WritePin(GPIOB, FT800_CS_N, GPIO_PIN_SET);		// Set chip select high
}

void ft812memWrite16(unsigned long ftAddress, unsigned int ftData16)
{
	unsigned char cTempAddr[3];														// FT812 Memory Address
	unsigned char cTempData[2];														// 16-bit data to write

	cTempAddr[2] = (char) (ftAddress >> 16) | 0x80;	// Compose the command and address to send
	cTempAddr[1] = (char) (ftAddress >> 8);								// middle byte
	cTempAddr[0] = (char) (ftAddress);										// low byte

	cTempData[1] = (char) (ftData16 >> 8);								// Compose data to be sent - high byte
	cTempData[0] = (char) (ftData16);											// low byte

	HAL_GPIO_WritePin(GPIOB, FT800_CS_N, GPIO_PIN_RESET);	// Set chip select low

	for (int i = 2; i >= 0; i--)
	{
		HAL_SPI_Transmit(&hspi1, &cTempAddr[i], 1, 0); 			// Send Memory Write plus high address byte
	}

	for (int j = 0; j < sizeof(cTempData); j++)						// Start with least significant byte
	{
		HAL_SPI_Transmit(&hspi1, &cTempData[j], 1, 0);			// Send data byte
	}

	HAL_GPIO_WritePin(GPIOB, FT800_CS_N, GPIO_PIN_SET);		// Set chip select high
}

#ifdef  USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{ 
	/* USER CODE BEGIN 6 */
	/* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
	/* USER CODE END 6 */
}

// REMOVE THIS

#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
