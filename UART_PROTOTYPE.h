#ifndef UART_PROTOTYPE
#define UART_PROTOTYPE
#include <stdint.h>
#include "tm4c123gh6pm.h"
void UART_RX_String (uint8_t UART_SEL,char *str, char terminator);
void UART_TX_String (uint8_t UART_SEL, const char  *str);
void UART_INIT(uint8_t UART_SEL, uint32_t baud_rate);
void UART_TX(uint8_t UART_SEL, uint8_t data);
uint8_t UART_RX(uint8_t UART_SEL);
char UART_AVAILABLE (uint8_t UART_SEL);

#endif

