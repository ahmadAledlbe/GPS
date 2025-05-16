#include <stdint.h>
#include <stdlib.h>
#include <stdint.h>
#include "UART_PROTOTYPE.h"
#include "GPIO.h"


void UART_TX(uint8_t UART_SEL, uint8_t data)
{
	switch(UART_SEL)
	{
		case 0:
    while(GET_BIT(UART0_FR_R,5));
   	UART0_DR_R = data;
		break; 
		
		case 1:
    while(GET_BIT(UART1_FR_R,5));
   	UART1_DR_R = data;
		break; 
			
		case 2:
    while(GET_BIT(UART2_FR_R,5));
   	UART2_DR_R = data;
		break; 
			
		case 3:
    while(GET_BIT(UART3_FR_R,5));
   	UART3_DR_R = data;
		break; 
				
		case 4:
    while(GET_BIT(UART4_FR_R,5));
   	UART4_DR_R = data;
		break; 
					
		case 5:
    while(GET_BIT(UART5_FR_R,5));
   	UART5_DR_R = data;
		break; 
 
  	case 6:
    while(GET_BIT(UART6_FR_R,5));
		UART6_DR_R = data;
		break; 
		
		case 7:
    while(GET_BIT(UART7_FR_R,5));
   	UART7_DR_R = data;
		break; 
	
	default: ;
	}
}





void UART_TX_String (uint8_t UART_SEL, const char  *str)
{
   while (*str){
		 UART_TX ( UART_SEL, (uint8_t)(*str++));
	 }
}




