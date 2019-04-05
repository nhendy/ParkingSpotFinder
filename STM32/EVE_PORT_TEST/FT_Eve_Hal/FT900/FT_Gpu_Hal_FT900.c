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

#include "FT_Platform.h"
#if defined(FT900_PLATFORM)

#include "FT_Gpu_Hal_FT900.h"

/* API to initialize the SPI interface */
ft_bool_t  Ft_Gpu_Hal_Init(Ft_Gpu_HalInit_t *halinit)
{
	halinit->TotalChannelNum = 1;
	// Initialize SPIM HW
	sys_enable(sys_device_spi_master);

	gpio_function(27, pad_spim_sck); /* GPIO27 to SPIM_CLK */
	gpio_function(28, pad_spim_ss0); /* GPIO28 as CS */
	gpio_function(29, pad_spim_mosi); /* GPIO29 to SPIM_MOSI */
	gpio_function(30, pad_spim_miso); /* GPIO30 to SPIM_MISO */

	gpio_dir(27, pad_dir_output);
	gpio_dir(28, pad_dir_output);
	gpio_dir(29, pad_dir_output);
	gpio_dir(30, pad_dir_input);
#if (defined(ENABLE_SPI_QUAD))
	/* Initialize IO2 and IO3 pad/pin for quad settings */
	gpio_function(31, pad_spim_io2); /* GPIO31 to IO2 */
	gpio_function(32, pad_spim_io3); /* GPIO32 to IO3 */
	gpio_dir(31, pad_dir_output);
	gpio_dir(32, pad_dir_output);
#endif

#if defined(PANL70) || defined(PANL70PLUS)
	gpio_function(GOODIXGPIO, pad_gpio33);
	gpio_dir(GOODIXGPIO, pad_dir_output);
	gpio_write(GOODIXGPIO, 1);
#endif

	gpio_write(28, 1);
	spi_init(SPIM, spi_dir_master, spi_mode_0, 16);//SPISysInit(SPIM);

	return TRUE;
}


ft_void_t Ft_Gpu_Hal_ESD_Idle(Ft_Gpu_Hal_Context_t *host)
{
#if defined(PANL35) || defined(PANL70) || defined(PANL70PLUS)
	panl_bacnet_task();
#endif    
}

ft_bool_t    Ft_Gpu_Hal_Open(Ft_Gpu_Hal_Context_t *host)
{
	host->hal_config.channel_no = 0;
	host->hal_config.pdn_pin_no = FT800_PD_N;
	host->hal_config.spi_cs_pin_no = FT800_SEL_PIN;
	gpio_function(host->hal_config.spi_cs_pin_no, pad_spim_ss0); /* GPIO28 as CS */
	gpio_write(host->hal_config.spi_cs_pin_no, 1);

	gpio_function(host->hal_config.pdn_pin_no, pad_gpio43);
	gpio_dir(host->hal_config.pdn_pin_no, pad_dir_output);

	gpio_write(host->hal_config.pdn_pin_no, 1);

	/* Initialize the context valriables */
	host->spinumdummy = 1;//by default ft800/801/810/811 goes with single dummy byte for read
	host->spichannel = 0;
	host->status = FT_GPU_HAL_OPENED;

	return TRUE;
}

ft_void_t  Ft_Gpu_Hal_Close(Ft_Gpu_Hal_Context_t *host)
{
	host->status = FT_GPU_HAL_CLOSED;
	//spi_close(SPIM,0);
}


ft_void_t Ft_Gpu_Hal_DeInit()
{
	spi_uninit(SPIM);
}


/*The APIs for reading/writing transfer continuously only with small buffer system*/
ft_void_t  Ft_Gpu_Hal_StartTransfer(Ft_Gpu_Hal_Context_t *host, FT_GPU_TRANSFERDIR_T rw, ft_uint32_t addr)
{
	if (FT_GPU_READ == rw)
	{
		ft_uint8_t spidata[4];
		spidata[0] = (addr >> 16);
		spidata[1] = (addr >> 8);
		spidata[2] = addr & 0xff;
		spi_open(SPIM, host->hal_config.spi_cs_pin_no);
		spi_writen(SPIM, spidata, 3);
		host->status = FT_GPU_HAL_READING;
	}
	else
	{
		ft_uint8_t spidata[4];
		spidata[0] = (0x80 | (addr >> 16));
		spidata[1] = (addr >> 8);
		spidata[2] = addr;

		spi_open(SPIM, host->hal_config.spi_cs_pin_no);
		spi_writen(SPIM, spidata, 3);

		host->status = FT_GPU_HAL_WRITING;
	}
}

/*The APIs for writing transfer continuously only*/
ft_void_t  Ft_Gpu_Hal_StartCmdTransfer(Ft_Gpu_Hal_Context_t *host, FT_GPU_TRANSFERDIR_T rw, ft_uint16_t count)
{
	Ft_Gpu_Hal_StartTransfer(host, rw, REG_CMDB_WRITE);
}

ft_uint8_t    Ft_Gpu_Hal_Transfer8(Ft_Gpu_Hal_Context_t *host, ft_uint8_t value)
{
	ft_uint8_t ReadByte;

	if (host->status == FT_GPU_HAL_WRITING)
	{
		spi_write(SPIM, value);
	}
	else
	{
		spi_read(SPIM, ReadByte);
	}
	return ReadByte;
}

ft_void_t   Ft_Gpu_Hal_EndTransfer(Ft_Gpu_Hal_Context_t *host)
{
	spi_close(SPIM, host->hal_config.spi_cs_pin_no);
	host->status = FT_GPU_HAL_OPENED;
}


ft_uint8_t  Ft_Gpu_Hal_Rd8(Ft_Gpu_Hal_Context_t *host, ft_uint32_t addr)
{
	ft_uint8_t value;

	ft_uint8_t spiData[4] = { 0 };
	Ft_Gpu_Hal_StartTransfer(host, FT_GPU_READ, addr);
	spi_readn(SPIM, spiData, host->spinumdummy + 1);
	value = spiData[host->spinumdummy];

	Ft_Gpu_Hal_EndTransfer(host);
	return value;
}

ft_uint16_t Ft_Gpu_Hal_Rd16(Ft_Gpu_Hal_Context_t *host, ft_uint32_t addr)
{
	ft_uint16_t value;
	ft_uint8_t spiData[4] = { 0 };
	Ft_Gpu_Hal_StartTransfer(host, FT_GPU_READ, addr);
	spi_readn(SPIM, spiData, host->spinumdummy + 2);
	value = spiData[host->spinumdummy] | (spiData[host->spinumdummy + 1] << 8);
	Ft_Gpu_Hal_EndTransfer(host);
	return value;
}

ft_uint32_t Ft_Gpu_Hal_Rd32(Ft_Gpu_Hal_Context_t *host, ft_uint32_t addr)
{
	ft_uint32_t value;
	ft_uint8_t spiData[8] = { 0 };
	Ft_Gpu_Hal_StartTransfer(host, FT_GPU_READ, addr);
	spi_readn(SPIM, spiData, host->spinumdummy + 4);
	value = (spiData[host->spinumdummy + 3] << 24) | (spiData[host->spinumdummy + 2] << 16) | (spiData[host->spinumdummy + 1] << 8) | spiData[host->spinumdummy];

	Ft_Gpu_Hal_EndTransfer(host);
	return value;
}

ft_void_t Ft_Gpu_Hal_Wr8(Ft_Gpu_Hal_Context_t *host, ft_uint32_t addr, ft_uint8_t v)
{
	Ft_Gpu_Hal_StartTransfer(host, FT_GPU_WRITE, addr);
	Ft_Gpu_Hal_Transfer8(host, v);
	Ft_Gpu_Hal_EndTransfer(host);
}

ft_void_t Ft_Gpu_Hal_Wr16(Ft_Gpu_Hal_Context_t *host, ft_uint32_t addr, ft_uint16_t v)
{
	Ft_Gpu_Hal_StartTransfer(host, FT_GPU_WRITE, addr);
	Ft_Gpu_Hal_Transfer16(host, v);
	Ft_Gpu_Hal_EndTransfer(host);
}

ft_void_t Ft_Gpu_Hal_Wr32(Ft_Gpu_Hal_Context_t *host, ft_uint32_t addr, ft_uint32_t v)
{
	Ft_Gpu_Hal_StartTransfer(host, FT_GPU_WRITE, addr);
	Ft_Gpu_Hal_Transfer32(host, v);
	Ft_Gpu_Hal_EndTransfer(host);
}

ft_void_t Ft_Gpu_HostCommand(Ft_Gpu_Hal_Context_t *host, ft_uint8_t cmd)
{
	ft_uint8_t hcmd[4] = { 0 };
	hcmd[0] = cmd;
	hcmd[1] = 0;
	hcmd[2] = 0;
	hcmd[3] = 0;

	spi_open(SPIM, host->hal_config.spi_cs_pin_no);
	spi_writen(SPIM, hcmd, 3);
	spi_close(SPIM, host->hal_config.spi_cs_pin_no);
}
//This API sends a 3byte command to the host
ft_void_t Ft_Gpu_HostCommand_Ext3(Ft_Gpu_Hal_Context_t *host, ft_uint32_t cmd)
{
	ft_uint8_t hcmd[4] = { 0 };
	hcmd[0] = cmd & 0xff;
	hcmd[1] = (cmd >> 8) & 0xff;
	hcmd[2] = (cmd >> 16) & 0xff;
	hcmd[3] = 0;
	spi_open(SPIM, host->hal_config.spi_cs_pin_no);
	spi_writen(SPIM, hcmd, 3);
	spi_close(SPIM, host->hal_config.spi_cs_pin_no);
}


ft_void_t Ft_Gpu_Hal_WrCmdBuf(Ft_Gpu_Hal_Context_t *host, ft_uint8_t *buffer, ft_uint32_t count)
{
	ft_int32_t length = 0, availablefreesize = 0;
	count = (count + 3) & ~0x3;
	do {
		length = count;
		availablefreesize = Ft_Gpu_Hal_Rd16(host, REG_CMDB_SPACE) & 4092; // max: 4095 ; last 4's multiple = 4092
		if (length > availablefreesize) length = availablefreesize;

		Ft_Gpu_Hal_StartCmdTransfer(host, FT_GPU_WRITE, length);
		spi_writen(SPIM, buffer, length);
		buffer += length;

		Ft_Gpu_Hal_EndTransfer(host);
		//printf("\n Length: %d", length);
		count -= length;
	} while (count > 0);
	//printf("\n \n\n");
}

ft_void_t Ft_Gpu_Hal_WrCmd32_Direct(Ft_Gpu_Hal_Context_t *host, ft_uint32_t cmd)
{
	Ft_Gpu_Hal_Wr32(host, REG_CMDB_WRITE, cmd);
}

ft_void_t Ft_Gpu_Hal_WrCmd32(Ft_Gpu_Hal_Context_t *host, ft_uint32_t cmd)
{
	Ft_Gpu_Hal_WrCmd32_Direct(host, cmd);
}
/* Toggle PD_N pin of FT800 board for a power cycle*/
ft_void_t Ft_Gpu_Hal_Powercycle(Ft_Gpu_Hal_Context_t *host, ft_bool_t up)
{
	if (up)
	{
		gpio_write(host->hal_config.pdn_pin_no, 0);
		ft_delay(20);
		gpio_write(host->hal_config.pdn_pin_no, 1);
		ft_delay(20);
	}
	else
	{
		gpio_write(host->hal_config.pdn_pin_no, 1);
		ft_delay(20);
		gpio_write(host->hal_config.pdn_pin_no, 0);
		ft_delay(20);
	}
}

ft_void_t Ft_Gpu_Hal_WrMem(Ft_Gpu_Hal_Context_t *host, ft_uint32_t addr, const ft_uint8_t *buffer, ft_uint32_t length)
{
	ft_uint32_t SizeTransfered = 0;
	Ft_Gpu_Hal_StartTransfer(host, FT_GPU_WRITE, addr);
	spi_writen(SPIM, buffer, length);
	Ft_Gpu_Hal_EndTransfer(host);
}

ft_void_t Ft_Gpu_Hal_RdMem(Ft_Gpu_Hal_Context_t *host, ft_uint32_t addr, ft_uint8_t *buffer, ft_uint32_t length)
{
	ft_uint32_t SizeTransfered = 0;

	Ft_Gpu_Hal_StartTransfer(host, FT_GPU_READ, addr);
	unsigned char spiData[2] = { 0 };
	spi_readn(SPIM, spiData, host->spinumdummy);
	spi_readn(SPIM, buffer, length);
	Ft_Gpu_Hal_EndTransfer(host);
}

ft_void_t Ft_Gpu_Hal_Sleep(ft_uint32_t ms)
{
	delayms(ms);
}

ft_int16_t Ft_Gpu_Hal_SetSPI(Ft_Gpu_Hal_Context_t *host, FT_GPU_SPI_NUMCHANNELS_T numchnls, FT_GPU_SPI_NUMDUMMYBYTES numdummy)
{
	ft_uint8_t writebyte = 0;

	if ((numchnls > FT_GPU_SPI_QUAD_CHANNEL) || (numdummy > FT_GPU_SPI_TWODUMMY) || (numdummy < FT_GPU_SPI_ONEDUMMY))
	{
		return -1;//error
	}

	//swicth EVE to multi channel SPI mode
	writebyte = numchnls;
	if (numdummy == FT_GPU_SPI_TWODUMMY)
		writebyte |= FT_SPI_TWO_DUMMY_BYTE;
	Ft_Gpu_Hal_Wr8(host, REG_SPI_WIDTH, writebyte);
	//FT81x swicthed to dual/quad mode, now update global HAL context 
	host->spichannel = numchnls;
	host->spinumdummy = numdummy;
	return 0;
}

ft_void_t getFlashTextString(char __flash__ *str, ft_uchar8_t *destArray, ft_uint16_t numOfChars)
{
	ft_uint16_t i;
	for (i = 0; i < numOfChars; i++)
		destArray[i] = str[i];
}


ft_uint32_t Ft_Gpu_CurrentFrequency(Ft_Gpu_Hal_Context_t *host)
{
	ft_uint32_t t0, t1;
	ft_uint32_t addr = REG_CLOCK;
	ft_uint8_t spidata[4];
	ft_int32_t r = 15625;

	t0 = Ft_Gpu_Hal_Rd32(host, REG_CLOCK); /* t0 read */

	__asm__
	(
		"   move.l  $r0,%0"             "\n\t"
		"   mul.l   $r0,$r0,100"                                                  "\n\t"
		"1:"               "\n\t"
		"   sub.l   $r0,$r0,3"          "\n\t" /* Subtract the loop time = 4 cycles */
		"   cmp.l   $r0,0"              "\n\t" /* Check that the counter is equal to 0 */
		"   jmpc    gt, 1b"  "\n\t"
		/* Outputs */ :
	/* Inputs */ : "r"(r)
		/* Using */ : "$r0"

		);

	//usleep(15625);
	//ft_delay(15625);

	t1 = Ft_Gpu_Hal_Rd32(host, REG_CLOCK); /* t1 read */
	return ((t1 - t0) * 64); /* bitshift 6 places is the same as multiplying 64 */
}

ft_void_t Ft_Gpu_Panl70_GOODIXGPIO(Ft_Gpu_Hal_Context_t *host)
{
#if defined(PANL70) || defined(PANL70PLUS)
	gpio_function(GOODIXGPIO, pad_gpio33);
	gpio_dir(GOODIXGPIO, pad_dir_output);
	gpio_write(GOODIXGPIO, 0);
	ft_delay(1);
	Ft_Gpu_Hal_Wr8(host, REG_CPURESET, 0);
	ft_delay(100);
	gpio_dir(GOODIXGPIO, pad_dir_input);
#endif
}

ft_void_t Ft_DisplayPanel_Init()
{
#ifdef ENABLE_ILI9488_HVGA_PORTRAIT
	ILI9488_Bootup();
	ESD_print("after ILI9488 bootup \n");
#endif

#ifdef ENABLE_KD2401_HVGA_PORTRAIT
	KD2401_Bootup();
	ESD_print("after KD2401 bootup \n");
#endif

	/* Reconfigure the SPI */
	// Initialize SPIM HW
	sys_enable(sys_device_spi_master);
	gpio_function(27, pad_spim_sck); /* GPIO27 to SPIM_CLK */
	gpio_function(28, pad_spim_ss0); /* GPIO28 as CS */
	gpio_function(29, pad_spim_mosi); /* GPIO29 to SPIM_MOSI */
	gpio_function(30, pad_spim_miso); /* GPIO30 to SPIM_MISO */

	gpio_write(28, 1);
	spi_init(SPIM, spi_dir_master, spi_mode_0, 4);

}

/* Globals for interrupt implementation */
static ft_uint32_t ft_TotalMilliseconds = 0;

ft_void_t ft_millis_init()
{
	ft_TotalMilliseconds = 0;
#if (defined(PANL35) || defined(PANL70) || defined(PANL70PLUS)) 
	panl_timer_register_ms_callback(ft_millis_ticker);
#else
	ft_millis_curr = 0;
	ft_millis_prev = 0;

	sys_enable(sys_device_timer_wdt);
	timer_prescaler(FT900_TIMER_PRESCALE_VALUE);
	timer_init(FT900_FT_MILLIS_TIMER, FT900_TIMER_OVERFLOW_VALUE, timer_direction_up, timer_prescaler_select_on, timer_mode_continuous);

	interrupt_attach(interrupt_timers, 17, ft_millis_ticker);
	/* enabling the interrupts for timer */
	timer_enable_interrupt(FT900_FT_MILLIS_TIMER);

	timer_start(FT900_FT_MILLIS_TIMER);
#endif
}

/* Need to ensure that below api is called at least once in 6.5 seconds duration for FT900 platform as this module doesnt use timer for context update */
/* global counter to loopback after ~49.71 days */
ft_uint32_t ft_millis()
{
#if (defined(PANL35) || defined(PANL70) || defined(PANL70PLUS))	    
	return panl_timer_get_time();
#else
	/* Interrupt implementation */
	return (ft_TotalMilliseconds);
#endif
}

ft_void_t ft_millis_exit()
{
	timer_stop(FT900_FT_MILLIS_TIMER);
	timer_disable_interrupt(FT900_FT_MILLIS_TIMER);
}

ft_void_t ft_millis_ticker()
{
	ft_TotalMilliseconds += 1;

	timer_disable_interrupt(FT900_FT_MILLIS_TIMER);
	/* Clear the interrupt and increment the counter */
	timer_is_interrupted(FT900_FT_MILLIS_TIMER);
	timer_enable_interrupt(FT900_FT_MILLIS_TIMER);
}
#endif