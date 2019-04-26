#include "Ft_Esd.h"
#include "Confirmation.h"
#include "global.h"
ESD_METHOD(Confirmation_getParkingSpotID_Signal, Context = Confirmation)
void Confirmation_getParkingSpotID_Signal(Confirmation *context)
{
//parkingSpotID = getParkingSpotID();
	cCode[0] = '\0';
	printf("going into parking spot id signal, parking spot id = %d", parkingSpotID);
	context->parkingSpotIDState = parkingSpotID;
	context->parkingSpotNumber = parkingSpotID;
}

