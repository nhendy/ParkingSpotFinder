#include "Ft_Esd.h"
#include "Confirmation.h"
#include "global.h"
ESD_METHOD(Confirmation_getParkingSpotID_Signal, Context = Confirmation)
void Confirmation_getParkingSpotID_Signal(Confirmation *context)
{
	parkingSpotID = getParkingSpotID(confirmationCode);
	context->parkingSpotIDState = parkingSpotID;
	context->parkingSpotNumber = parkingSpotID;
	//printf("entering getParkingSpotID, %d", context->parkingSpotIDState);
}

