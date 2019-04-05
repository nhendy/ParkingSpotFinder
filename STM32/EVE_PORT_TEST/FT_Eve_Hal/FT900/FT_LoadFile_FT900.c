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

#include "ff.h"

void Ft_Hal_LoadSDCard()
{

	static FATFS s_FatFS;
	static SDHOST_STATUS sd_status = SDHOST_ERROR;
	static int fatfs_loaded = 0;
	sd_status = sdhost_card_detect();


	if (SDHOST_CARD_INSERTED == sd_status) {
		if (fatfs_loaded == 0 && FR_OK != f_mount(&s_FatFS, "", 1)) {
			ESD_print("FatFS mount failed\n");
		}
		else {
			fatfs_loaded = 1;
			ESD_print("FatFS mounted successfully\n");
		}
	}

}


int Ft_Hal_LoadRawFile(Ft_Gpu_Hal_Context_t *phost, ft_uint32_t address, const char *filename)
{
	FRESULT fResult;
	FIL InfSrc;

	ft_int32_t blocklen, filesize;
	ft_uint8_t g_random_buffer[512L];
	ft_uint32_t addr = address;

	fResult = f_open(&InfSrc, filename, FA_READ | FA_OPEN_EXISTING);
	if (fResult == FR_OK)
	{
		filesize = f_size(&InfSrc);
		while (filesize > 0)
		{
			fResult = f_read(&InfSrc, g_random_buffer, 512, &blocklen);	// read a chunk of src file
			filesize -= blocklen;
			Ft_Gpu_Hal_WrMem(phost, addr, g_random_buffer, blocklen);
			addr += blocklen;
		}
		f_close(&InfSrc);
		return 1;
	}
	else
	{
		ESD_print("Unable to open file: \"%s\"\n", filename);
		return 0;
	}
}

int Ft_Hal_LoadInflateFile(Ft_Gpu_Hal_Context_t *phost, ft_uint32_t address, const char *filename)
{
	FRESULT fResult;
	FIL InfSrc;

	ft_int32_t blocklen, filesize;
	ft_uint8_t g_random_buffer[512L];

	fResult = f_open(&InfSrc, filename, FA_READ | FA_OPEN_EXISTING);
	if (fResult == FR_OK)
	{
		Ft_Gpu_Hal_WrCmd32(phost, CMD_INFLATE);
		Ft_Gpu_Hal_WrCmd32(phost, address);
		filesize = f_size(&InfSrc);
		while (filesize > 0)
		{
			fResult = f_read(&InfSrc, g_random_buffer, 512, &blocklen);	// read a chunk of src file
			filesize -= blocklen;
			blocklen += 3;
			blocklen -= blocklen % 4;
			Ft_Gpu_Hal_WrCmdBuf(phost, (char *)g_random_buffer, blocklen);
		}
		Ft_Gpu_Hal_WaitCmdfifo_empty(phost);

		f_close(&InfSrc);
		return 1;
	}
	else
	{
		ESD_print("Unable to open file: \"%s\"\n", filename);
		return 0;
	}
}

int Ft_Hal_LoadImageFile(Ft_Gpu_Hal_Context_t *phost, ft_uint32_t address, const char *filename)
{
	FRESULT fResult;
	FIL InfSrc;

	ft_int32_t blocklen, filesize;
	ft_uint8_t g_random_buffer[512L];

	fResult = f_open(&InfSrc, filename, FA_READ | FA_OPEN_EXISTING);
	if (fResult == FR_OK)
	{
		Ft_Gpu_Hal_WrCmd32(phost, CMD_LOADIMAGE);
		Ft_Gpu_Hal_WrCmd32(phost, address);
		Ft_Gpu_Hal_WrCmd32(phost, OPT_NODL);
		filesize = f_size(&InfSrc);
		while (filesize > 0)
		{
			fResult = f_read(&InfSrc, g_random_buffer, 512, &blocklen);	// read a chunk of src file
			filesize -= blocklen;
			blocklen += 3;
			blocklen -= blocklen % 4;
			Ft_Gpu_Hal_WrCmdBuf(phost, (char *)g_random_buffer, blocklen);
		}
		Ft_Gpu_Hal_WaitCmdfifo_empty(phost);
		f_close(&InfSrc);
		return 1;
	}
	else
	{
		ESD_print("Unable to open file: \"%s\"\n", filename);
		return 0;
	}
}

#endif

/* end of file */
