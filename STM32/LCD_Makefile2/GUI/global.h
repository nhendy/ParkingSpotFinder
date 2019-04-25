#ifndef GLOBAL_H
#define GLOBAL_H

#define CONF_CODE_MSG "CONFIRM: "
#define GET_ID_MSG    "GETID"
#define CODE_SIZE     4

int rcvd_id;
extern char cCode[CODE_SIZE];
extern int parkingSpotID; //Retreived parking spot ID from function getParkingSpotID
void getParkingSpotID(char *);

#endif
