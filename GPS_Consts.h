#ifndef GPS_Consts
#define GPS_Consts

#define EARTH_RADIUS 6378000
#define PI 3.14159265359
#include "STD_TYPES.h"
#define MAX_SENTENCE_SIZE 15
#define SENTENCE_SIZE 100
void GPS_READ();
void GPS_FORMAT();
float ToRad(float angle);
float ToDegree(float angle);
float GPS_getDistance(float currentLong, float currentLat, float destLong, float destLat);
f32 clacDistance(f64 GPSLat, f64 GPSLong, f64 savedLat, f64 savedLong);
float GetSpeedFromGPRMC(void);
//static GPS_status_t GPSStdStatusReadMEASentence(UART_Config_t *CopyPtrUARTConfig, u8 *Copyarru8Buffer);

#endif

