#include "UART_PROTOTYPE.h"
#include <stdint.h>
#include <math.h>
#include "GPS_Interface.h"
#include "STD_TYPES.h"
#include "lcdProto.h"
#define M_PI 3.14159265358979323846


#define EPSILON 0.0001


#include "tm4c123gh6pm.h"
#include "GPS_Interface.h"
#include "LCD_Interface.h"




// ??????? ??????? (????)
#include "tm4c123gh6pm.h"
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

// I2C LCD pin definitions (bit-bang on PB2 for SDA, PB3 for SCL)
#define I2C_SCL     (1 << 3)  // PB3
#define I2C_SDA     (1 << 2)  // PB2
#define I2C_PORT    GPIO_PORTB_DATA_R

#define LCD_BACKLIGHT   0x08
#define LCD_ENABLE      0x04
#define LCD_RW          0x02
#define LCD_RS          0x01

#define LCD_ADDR        0x27  // Change to 0x3F if needed

void delay_us(int n) {
    int i;
    for (i = 0; i < n * 3; i++) __nop();  // 1us delay at 16MHz
}

void delayMs(int n) {
    int i, j;
    for(i = 0; i < n; i++)
        for(j = 0; j < 3180; j++) {}
}

void LCD_I2C_SetCursor(uint8_t col, uint8_t row) {
    uint8_t row_offsets[] = {0x00, 0x40};  // ????? ?????: 0x80? ????? ??????: 0xC0
    if (row > 1) row = 1;  // ??? ????? ?? 16x2
    LCD_I2C_Command(0x80 | (col + row_offsets[row]));
}


// ==== GPIO Bit-Bang I2C ====
void I2C_Init(void) {
    SYSCTL_RCGCGPIO_R |= 0x02;
    while ((SYSCTL_PRGPIO_R & 0x02) == 0);

    GPIO_PORTB_DIR_R |= I2C_SCL | I2C_SDA;
    GPIO_PORTB_DEN_R |= I2C_SCL | I2C_SDA;

    I2C_PORT |= I2C_SCL | I2C_SDA;
}

void I2C_SDA_HIGH(void) { I2C_PORT |= I2C_SDA; }
void I2C_SDA_LOW(void)  { I2C_PORT &= ~I2C_SDA; }
void I2C_SCL_HIGH(void) { I2C_PORT |= I2C_SCL; }
void I2C_SCL_LOW(void)  { I2C_PORT &= ~I2C_SCL; }

void I2C_Start(void) {
    I2C_SDA_HIGH(); I2C_SCL_HIGH(); delay_us(5);
    I2C_SDA_LOW(); delay_us(5);
    I2C_SCL_LOW(); delay_us(5);
}

void I2C_Stop(void) {
    I2C_SDA_LOW(); I2C_SCL_HIGH(); delay_us(5);
    I2C_SDA_HIGH(); delay_us(5);
}

void I2C_WriteBit(uint8_t bit) {
    if (bit) I2C_SDA_HIGH(); else I2C_SDA_LOW();
    delay_us(1);
    I2C_SCL_HIGH(); delay_us(5);
    I2C_SCL_LOW(); delay_us(5);
}

void I2C_WriteByte(uint8_t byte) {
	int i;
    for (i = 0; i < 8; i++) {
        I2C_WriteBit(byte & 0x80);
        byte <<= 1;
    }
    // ACK
    I2C_SDA_HIGH(); delay_us(100);
    I2C_SCL_HIGH(); delay_us(50);
    I2C_SCL_LOW(); delay_us(50);
}

// ==== I2C LCD ====
void LCD_I2C_Write(uint8_t data) {
    I2C_Start();
    I2C_WriteByte(LCD_ADDR << 1);  // Write mode
    I2C_WriteByte(data);
    I2C_Stop();
}

void LCD_I2C_Strobe(uint8_t data) {
    LCD_I2C_Write(data | LCD_ENABLE | LCD_BACKLIGHT);
    delay_us(1);
    LCD_I2C_Write((data & ~LCD_ENABLE) | LCD_BACKLIGHT);
    delay_us(50);
}

void LCD_I2C_SendByte(uint8_t data, uint8_t mode) {
    uint8_t highNib = (data & 0xF0) | mode;
    uint8_t lowNib  = ((data << 4) & 0xF0) | mode;

    LCD_I2C_Strobe(highNib);
    LCD_I2C_Strobe(lowNib);
}

void LCD_I2C_Command(uint8_t cmd) {
    LCD_I2C_SendByte(cmd, 0x00);
}

void LCD_I2C_Data(uint8_t data) {
    LCD_I2C_SendByte(data, LCD_RS);
}

void LCD_I2C_Init(void) {
    delayMs(50);
    LCD_I2C_Command(0x33); // Init
    LCD_I2C_Command(0x32); // 4-bit
    LCD_I2C_Command(0x28); // 2-line
    LCD_I2C_Command(0x0C); // Display on, cursor off
    LCD_I2C_Command(0x06); // Entry mode
    LCD_I2C_Command(0x01); // Clear display
    delayMs(2);
}

void LCD_I2C_Print(char *str) {
    while (*str) LCD_I2C_Data(*str++);
}

