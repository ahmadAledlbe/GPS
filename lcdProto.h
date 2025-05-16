#ifndef LCD_I2C_H
#define LCD_I2C_H

#include "tm4c123gh6pm.h"
#include <stdint.h>
#include <stdbool.h>

// ==== I2C LCD Pin Definitions ====
#define I2C_SCL     (1 << 3)  // PB3
#define I2C_SDA     (1 << 2)  // PB2
#define I2C_PORT    GPIO_PORTB_DATA_R

// ==== LCD Command Bits ====
#define LCD_BACKLIGHT   0x08
#define LCD_ENABLE      0x04
#define LCD_RW          0x02
#define LCD_RS          0x01

#define LCD_ADDR        0x27  // Adjust if needed

// ==== Function Prototypes ====

// Delay functions
void delay_us(int n);
void delayMs(int n);

// I2C bit-bang GPIO
void I2C_Init(void);
void I2C_SDA_HIGH(void);
void I2C_SDA_LOW(void);
void I2C_SCL_HIGH(void);
void I2C_SCL_LOW(void);
void I2C_Start(void);
void I2C_Stop(void);
void I2C_WriteBit(uint8_t bit);
void I2C_WriteByte(uint8_t byte);

// LCD control
void LCD_I2C_Write(uint8_t data);
void LCD_I2C_Strobe(uint8_t data);
void LCD_I2C_SendByte(uint8_t data, uint8_t mode);
void LCD_I2C_Command(uint8_t cmd);
void LCD_I2C_Data(uint8_t data);
void LCD_I2C_Init(void);
void LCD_I2C_Print(char *str);
void LCD_I2C_SetCursor(uint8_t col, uint8_t row) ;

#endif // LCD_I2C_H
