#include <stdint.h>
#include "tm4c123gh6pm.h"
#include <stdio.h>
#include <math.h>

#include "GPS_Consts.h"
#include "UART_PROTOTYPE.h"
#include "GPIO.h"

// ????????? ????????? ?? ????? ????
extern char GPS_FORMATARR[15][20];
extern char GPS[80];
extern char GPS_logname[];

extern float currentLat, currentLong;

// ???? GPS
void GPS_READ(void);
void GPS_FORMAT(void);
float ToDegree(float angle);
float GPS_getDistance(float currentLong, float currentLat, float destLong, float destLat);
//////////
void UpdateLEDsBySpeedAndDistance(float speed, float distance) {
    // Clear all LEDs first
    GPIO_PORTF_DATA_R &= ~0x0E;  // Clear PF1 (Red), PF2 (Blue), PF3 (Green)
// replace inside while(1) block

GPIO_PORTF_DATA_R &= ~0x0E;  // Clear all LEDs

if (distance < 25) {
    GPIO_PORTF_DATA_R |= 0x08;  // Green (PF3)
} else if (distance < 50) {
    GPIO_PORTF_DATA_R |= 0x0A;  // Yellow = Red + Green (PF1 + PF3)
}  else {
    GPIO_PORTF_DATA_R |= 0x02;  // Red (PF1)
}

}
// ???? ?????? float ??? UART
void UART_TX_Float(uint8_t uart, float number) {
    char buffer[20];
    sprintf(buffer, "%.6f", number);  // 6 ????? ?????
    UART_TX_String(uart, buffer);
}

void PortF_Init(void) {
    SYSCTL_RCGCGPIO_R |= 0x20;
    while ((SYSCTL_PRGPIO_R & 0x20) == 0);
    GPIO_PORTF_LOCK_R = 0x4C4F434B;
    GPIO_PORTF_CR_R |= 0x0E;
    GPIO_PORTF_DIR_R |= 0x0E;
    GPIO_PORTF_DEN_R |= 0x0E;
}


int main(void) {
	float distance;
	float speed;
	  SYSCTL_RCGCGPIO_R |= 0x20;      // Enable clock for Port F
while ((SYSCTL_PRGPIO_R & 0x20) == 0);

PortF_Init();


    while (1) {
	float min_distance = 1000000;
        int min_index = -1;
	int i ;
    float lat_decimal, long_decimal;

    // ???????? ???????
    float locations_lat[5] = {
        30.0634605, 30.0653043, 30.0635504, 30.0640122, 30.0652914
    };
    float locations_long[5] = {
        31.2784228, 31.2783271, 31.2802217, 31.2800418, 31.2799843
    };

    // ????? ???????
    char* names[5] = {
        "Credit", "FOUNTAIN", "HALL C ", "HALL A ", "Library"
    };

    // ????? UART
    UART_INIT(0, 9600);  // UART0 ??? Terminal
    UART_INIT(1, 9600);  // UART1 ??? GPS
		I2C_Init();
    LCD_I2C_Init();
    
			
        // ????? ?????? ?????? GPS
        GPS_READ();
        GPS_FORMAT();

        // ????? ?????????? ??? ????? ?????
        lat_decimal = ToDegree(currentLat);
        long_decimal = ToDegree(currentLong);

        // ????? ?????? ??????????? ?????
        UART_TX_String(0, "Status: ");
        UART_TX(0, GPS_FORMATARR[2][0]);  // A ?? V
        UART_TX(0, '\n');

      

        // ????? ?????????? ?????? ?????
     

        // ????? ???? ????
        
        for (i= 0; i < 5; i++) {
            float distance = GPS_getDistance(currentLong, currentLat, locations_long[i], locations_lat[i]);
            if (distance < min_distance) {
                min_distance = distance;
                min_index = i;
            }
        }

				
        // ????? ???? ????
        UART_TX_String(0, "Nearest Location: ");
        UART_TX_String(0, names[min_index]);
       LCD_I2C_Print("Nearest Location: ");
			LCD_I2C_SetCursor(0, 1);
		 LCD_I2C_Print(names[min_index]);
      UART_TX_String(0, "\nDistance: ");
        UART_TX_Float(0, min_distance);
        //UART_TX_String(0, " meters\n");

        UART_TX_String(0, "---------------------------\n");
				 delayMs(4000);
				//UART_TX_Float(0, clacDistance(31.280750, 30.063732, 31.2784228, 30.0634605));
				
				// Clear all LEDs
GPIO_PORTF_DATA_R &= ~0x0E; 
speed = GetSpeedFromGPRMC();  // e.g., from parsed GPRMC
distance = GPS_getDistance(currentLong, currentLat, locations_long[min_index], locations_lat[min_index]);

UpdateLEDsBySpeedAndDistance(speed, distance);
if (min_distance < 50) {
    GPIO_PORTF_DATA_R |= 0x08;  // Green (PF3)
} else if (min_distance < 70) {
    GPIO_PORTF_DATA_R |= 0x02;  // blue (PF1 )
} else {
    // Leave LEDs off or handle other cases
}

}

}

