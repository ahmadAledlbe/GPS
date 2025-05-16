#ifndef LCD_INTERFACE_H
#define LCD_INTERFACE_H

#include <stdint.h>

void LCD_I2C_Init(void);
void LCD_I2C_Print(char *str);
void LCD_I2C_Clear(void);

#endif // LCD_INTERFACE_H
