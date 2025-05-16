#include <stdint.h>
#include "tm4c123gh6pm.h"
#include <stdint.h>
#include "UART_PROTOTYPE.h"
#include "GPIO.h"

uint8_t UART_RX(uint8_t UART_SEL)
{
	switch(UART_SEL)
	{
		case 0:
    while(GET_BIT(UART0_FR_R,4));
		return (uint8_t)(UART0_DR_R & 0xFF);
		break; 
		
		case 1:
    while(GET_BIT(UART1_FR_R,4));
		return (uint8_t)(UART1_DR_R & 0xFF);
		break; 
		
		case 2:
    while(GET_BIT(UART2_FR_R,4));
		return (uint8_t)(UART2_DR_R & 0xFF);
		break; 
		
		case 3:
    while(GET_BIT(UART3_FR_R,4));
		return (uint8_t)(UART3_DR_R & 0xFF);
		break; 
		
		case 4:
    while(GET_BIT(UART4_FR_R,4));
		return (uint8_t)(UART4_DR_R & 0xFF);
		break; 
		
		case 5:
    while(GET_BIT(UART5_FR_R,4));
		return (uint8_t)(UART5_DR_R & 0xFF);
		break; 
 
  	case 6:
    while(GET_BIT(UART6_FR_R,4));
		return	(uint8_t)(UART6_DR_R& 0xFF);
		break; 
	
		case 7:
    while(GET_BIT(UART7_FR_R,4));
		return (uint8_t)(UART7_DR_R & 0xFF);
		break; 
		
	default: ;
		return 0 ;
	}
	
 }


void UART_RX_String (uint8_t UART_SEL,char *str, char terminator)
{

    char c;
    while (*str)
    {
        c = UART_RX( UART_SEL);   // Read a character from UART
        if (c == terminator)    // Stop if terminator is received
            break;
        *str++ = c;             // Store character in string
    }
    *str = '\0'; // Null-terminate the string
}


