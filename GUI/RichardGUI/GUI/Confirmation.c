#include "Ft_Esd.h"
#include "Confirmation.h"
#include "global.h"
ESD_METHOD(Confirmation_getParkingSpotID_Signal, Context = Confirmation)
void Confirmation_getParkingSpotID_Signal(Confirmation *context)
{
	context->ParkingSpotNumber = parkingSpotID;
	printf("Checking how it works %d", confirmationCode);
}
