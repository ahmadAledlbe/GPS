#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "GPIO.h"

/* typedef enum {
  GPS_NO_DATA,
  GPS_VALID_DATA,
  GPS_INVALID_DATA
} GPS_Status_t;

uint8_t UART_stdErrorReceiveByte(uint8_t *pu8Data) {
  if ((UART1_FR_R & 0x10) != 0) return 1; // RXFE = FIFO empty
  *pu8Data = UART1_DR_R & 0xFF;
  return 0;
} */
void UART_INIT(uint8_t UART_SEL, uint32_t baud_rate) {
    uint32_t BDR;

    switch (UART_SEL) {
        case 0:   //0,A0,1
            SET_BIT(SYSCTL_RCGCUART_R, 0);   // Enable UART0
            SET_BIT(SYSCTL_RCGCGPIO_R, 0);   // Enable GPIOA

				    while (!GET_BIT(SYSCTL_PRUART_R, 0));
            while (!GET_BIT(SYSCTL_PRGPIO_R, 0));
            

            CLR_BIT(UART0_CTL_R, 0);         // Disable UART0

            BDR = 16000000 / (16 * baud_rate);
            UART0_IBRD_R = BDR;
            UART0_FBRD_R = (uint32_t)((16000000 / (16.0 * baud_rate) - BDR) * 64 + 0.5);
            UART0_LCRH_R = 0x70;             // 8-bit, no parity, 1 stop bit , FIFO
            UART0_CTL_R = 0x301;             // Enable UART, RXE, TXE

            GPIO_PORTA_AFSEL_R |= 0x03;      // PA0, PA1
            GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R & ~0xFF) | 0x11;
            GPIO_PORTA_AMSEL_R &= ~0x03;
            GPIO_PORTA_DEN_R |= 0x03;
            break;

        
				case 1 : //1,B0,1
					  SET_BIT(SYSCTL_RCGCUART_R, 1);   // Enable UART1
            SET_BIT(SYSCTL_RCGCGPIO_R, 1);   // GPIO port c (number 3)
            
				    while (!GET_BIT(SYSCTL_PRUART_R, 1));
            while (!GET_BIT(SYSCTL_PRGPIO_R, 1));
       
	
          
	
            CLR_BIT(UART1_CTL_R, 0);         

            BDR = 16000000 / (16 * baud_rate);
            UART1_IBRD_R = BDR;
            UART1_FBRD_R = (uint32_t)((16000000 / (16.0 * baud_rate) - BDR) * 64 + 0.5);
            UART1_LCRH_R = 0x70;
            UART1_CTL_R = 0x301;

            GPIO_PORTB_AFSEL_R |= 0x03;       
            GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R & ~0x00FF0000) | 0x00000011;
            GPIO_PORTB_AMSEL_R &= ~0x03;
            GPIO_PORTB_DEN_R |= 0x03;
            break;
							
				case 2 : //2,D6,7
					  SET_BIT(SYSCTL_RCGCUART_R, 2);   // Enable UART1
            SET_BIT(SYSCTL_RCGCGPIO_R, 3);   // GPIO port c (number 3)

            while (!GET_BIT(SYSCTL_PRUART_R, 2));
				    while (!GET_BIT(SYSCTL_PRGPIO_R, 3));
            
	
           
	
            CLR_BIT(UART1_CTL_R, 0);         // Disable UART6

            BDR = 16000000 / (16 * baud_rate);
            UART2_IBRD_R = BDR;
            UART2_FBRD_R = (uint32_t)((16000000 / (16.0 * baud_rate) - BDR) * 64 + 0.5);
            UART2_LCRH_R = 0x70;
            UART2_CTL_R = 0x301;

            GPIO_PORTD_AFSEL_R |= 0xC0;       // PD4, PD5
            GPIO_PORTD_PCTL_R = (GPIO_PORTD_PCTL_R & ~0x00FF0000) | 0x11000000;
            GPIO_PORTD_AMSEL_R &= ~0xC0;
            GPIO_PORTD_DEN_R |= 0xC0;
            break;
							
				case 3 : //3,C6,7
					  SET_BIT(SYSCTL_RCGCUART_R, 3);   // Enable UART1
            SET_BIT(SYSCTL_RCGCGPIO_R, 2);   // GPIO port c (number 3)

            while (!GET_BIT(SYSCTL_PRUART_R, 3));
				    while (!GET_BIT(SYSCTL_PRGPIO_R, 2));
           
	
           
	
            CLR_BIT(UART1_CTL_R, 0);         // Disable UART6

            BDR = 16000000 / (16 * baud_rate);
            UART3_IBRD_R = BDR;
            UART3_FBRD_R = (uint32_t)((16000000 / (16.0 * baud_rate) - BDR) * 64 + 0.5);
            UART3_LCRH_R = 0x70;
            UART3_CTL_R = 0x301;

            GPIO_PORTC_AFSEL_R |= 0xC0;       // PD4, PD5
            GPIO_PORTC_PCTL_R = (GPIO_PORTC_PCTL_R & ~0x00FF0000) | 0x11000000;
            GPIO_PORTC_AMSEL_R &= ~0xC0;
            GPIO_PORTC_DEN_R |= 0xC0;
            break;
							
				case 4 : //4,C4,5
					  SET_BIT(SYSCTL_RCGCUART_R, 4);   // Enable UART1
            SET_BIT(SYSCTL_RCGCGPIO_R, 2);   // GPIO port c (number 3)

            while (!GET_BIT(SYSCTL_PRUART_R, 4));
				    while (!GET_BIT(SYSCTL_PRGPIO_R, 2));
           
	
            
	
            CLR_BIT(UART1_CTL_R, 0);         // Disable UART6

            BDR = 16000000 / (16 * baud_rate);
            UART4_IBRD_R = BDR;
            UART4_FBRD_R = (uint32_t)((16000000 / (16.0 * baud_rate) - BDR) * 64 + 0.5);
            UART4_LCRH_R = 0x70;
            UART4_CTL_R = 0x301;

            GPIO_PORTC_AFSEL_R |= 0x30;       // PD4, PD5
            GPIO_PORTC_PCTL_R = (GPIO_PORTC_PCTL_R & ~0x00FF0000) | 0x00110000;
            GPIO_PORTC_AMSEL_R &= ~0x30;
            GPIO_PORTC_DEN_R |= 0x30;
            break;
							
				case 5 : //5,E4,5
					  SET_BIT(SYSCTL_RCGCUART_R, 5);   // Enable UART1
            SET_BIT(SYSCTL_RCGCGPIO_R, 4);   // GPIO port c (number 3)

				    while (!GET_BIT(SYSCTL_PRUART_R, 5));
            while (!GET_BIT(SYSCTL_PRGPIO_R, 4));
	
           
	
            CLR_BIT(UART1_CTL_R, 0);         // Disable UART6

            BDR = 16000000 / (16 * baud_rate);
            UART5_IBRD_R = BDR;
            UART5_FBRD_R = (uint32_t)((16000000 / (16.0 * baud_rate) - BDR) * 64 + 0.5);
            UART5_LCRH_R = 0x70;
            UART5_CTL_R = 0x301;

            GPIO_PORTE_AFSEL_R |= 0x30;       // PD4, PD5
            GPIO_PORTE_PCTL_R = (GPIO_PORTE_PCTL_R & ~0x00FF0000) | 0x00110000;
            GPIO_PORTE_AMSEL_R &= ~0x30;
            GPIO_PORTE_DEN_R |= 0x30;
            break;
							
				case 6:  //6,D4,5
            SET_BIT(SYSCTL_RCGCUART_R, 6);   // Enable UART6
            SET_BIT(SYSCTL_RCGCGPIO_R, 3);   // GPIO port D (number 3)

            while (!GET_BIT(SYSCTL_PRUART_R, 6));
				    while (!GET_BIT(SYSCTL_PRGPIO_R, 3));
            

            CLR_BIT(UART6_CTL_R, 0);         // Disable UART6

            BDR = 16000000 / (16 * baud_rate);
            UART6_IBRD_R = BDR;
            UART6_FBRD_R = (uint32_t)((16000000 / (16.0 * baud_rate) - BDR) * 64 + 0.5);
            UART6_LCRH_R = 0x70;
            UART6_CTL_R = 0x301;

            GPIO_PORTD_AFSEL_R |= 0x30;       // PD4, PD5
            GPIO_PORTD_PCTL_R = (GPIO_PORTD_PCTL_R & ~0x00FF0000) | 0x00110000;
            GPIO_PORTD_AMSEL_R &= ~0x30;
            GPIO_PORTD_DEN_R |= 0x30;
            break;
				
							
				case 7 : //7,E0,1
					  SET_BIT(SYSCTL_RCGCUART_R, 7);   // Enable UART1
            SET_BIT(SYSCTL_RCGCGPIO_R, 4);   // GPIO port c (number 3)

            while (!GET_BIT(SYSCTL_PRUART_R, 7));
				    while (!GET_BIT(SYSCTL_PRGPIO_R, 4));
            
	
         
	
            CLR_BIT(UART1_CTL_R, 0);         // Disable UART6

            BDR = 16000000 / (16 * baud_rate);
            UART7_IBRD_R = BDR;
            UART7_FBRD_R = (uint32_t)((16000000 / (16.0 * baud_rate) - BDR) * 64 + 0.5);
            UART7_LCRH_R = 0x70;
            UART7_CTL_R = 0x301;

            GPIO_PORTE_AFSEL_R |= 0x03;       // PD4, PD5
            GPIO_PORTE_PCTL_R = (GPIO_PORTE_PCTL_R & ~0x00FF0000) | 0x00000011;
            GPIO_PORTE_AMSEL_R &= ~0x03;
            GPIO_PORTE_DEN_R |= 0x03;
            break;
	}
    }

char UART_AVAILABLE (uint8_t UART_SEL){
    switch (UART_SEL){
			case 0 :
				return ((UART0_FR_R & UART_FR_RXFE)==UART_FR_RXFE);
			  break;
			case 1:
				return ((UART1_FR_R & UART_FR_RXFE)==UART_FR_RXFE);
        break;
			case 2:
				return ((UART2_FR_R & UART_FR_RXFE)==UART_FR_RXFE);
			  break;
			case 3: 
				return ((UART3_FR_R & UART_FR_RXFE)==UART_FR_RXFE);
			  break;
			case 4:
				return ((UART4_FR_R & UART_FR_RXFE)==UART_FR_RXFE);
			  break;
			case 5:
				return ((UART5_FR_R & UART_FR_RXFE)==UART_FR_RXFE);
			  break;
			case 6:
				return ((UART6_FR_R & UART_FR_RXFE)==UART_FR_RXFE);
			  break;
			case 7:
				return ((UART7_FR_R & UART_FR_RXFE)==UART_FR_RXFE);
			  break;
		}
			
   return 0;
}
