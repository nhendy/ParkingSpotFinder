#include "global.h"
#include <stm32f7xx_hal.h>
#include <string.h>
#include "main.h"

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart5;


void getParkingSpotID(char *confirm) {

	rcvd_id = 0;
	uint8_t buff[5];
	buff[4] = '\0';

	if (strcmp(confirm, "confCode") == 0) {
		my_printf(huart5, "CONFIRM: %s\n", cCode);
	}
	else if (strcmp(confirm, "noConfCode") == 0){
		my_printf(huart5, "GETID\n");
	}
	//my_printf(huart5, "The buff before is %s\n", buff);
	HAL_UART_Receive(&huart5, buff, sizeof(buff), 5000);
	my_printf(huart5, "The buff after is %s\n", buff);
	parkingSpotID = strtol(buff, NULL, 10);
	my_printf(huart1, "The parkingSpotID is %d\r\n", parkingSpotID);
	memset(cCode,'\0', CODE_SIZE);
//	HAL_Delay(5000);
//	parkingSpotID = -2;

//	memset(buff, 0, 5);
//	parkingSpotID = -1;
//	my_printf(huart1, "%s\r\n",cCode);
//	HAL_UART_Receive( &huart1, buff, 5,5000);
//	parkingSpotID = strtol(buff, NULL, 10);

	//return parkingSpotID;
}
