#include "global.h"
#include <stm32f7xx_hal.h>
extern UART_HandleTypeDef huart1;
int getParkingSpotID() {
	char buff[5];
	memset(buff, 0, 5);
	parkingSpotID = -1;
	my_printf(huart1, "%s\r\n",cCode);
	HAL_UART_Receive( &huart1, buff, 5,5000);
	parkingSpotID = strtol(buff, NULL, 10);
	cCode[0] = '\0';
	return parkingSpotID;
}
