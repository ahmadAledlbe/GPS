#ifndef GPIO_H_
#define GPIO_H_

#include <stdint.h>
#include "tm4c123gh6pm.h"

// ----- Bit Manipulation Macros -----
#define SET_BIT(REG, BIT)     ((REG) |=  (1U << (BIT)))
#define CLR_BIT(REG, BIT)     ((REG) &= ~(1U << (BIT)))
#define TOG_BIT(REG, BIT)     ((REG) ^=  (1U << (BIT)))
#define GET_BIT(REG, BIT)     (((REG) >> (BIT)) & 1U)

#define SET(REG, VALUE)       ((REG) = (VALUE))
#define CLR(REG, VALUE)       ((REG) &= ~(VALUE))
#define TOG(REG, VALUE)       ((REG) ^= (VALUE))
#define GET(REG, VALUE)       ((REG) & (VALUE))
#define GET_REG (REG)         ((REG)& 0xFF)

// ----- Port IDs -----
#define PORTA_ID 0
#define PORTB_ID 1
#define PORTC_ID 2
#define PORTD_ID 3
#define PORTE_ID 4
#define PORTF_ID 5

// ----- Modes and Polarity -----
#define low        0
#define high       1
#define pull_down  0
#define pull_up    1

// ----- Function Prototypes -----
void MCAL_GPIO_INIT(uint8_t GPIO_SEL);
void MCAL_GPIO_DIGITAL_INIT(uint8_t GPIO_SEL, uint8_t pin);
void MCAL_GPIO_DIGITAL_PIN_MODE(uint8_t GPIO_SEL, uint8_t pin, uint8_t Mode, uint8_t Polarity);
void MCAL_GPIO_WRITE_PIN(uint8_t GPIO_SEL, uint8_t pin, uint8_t data);
uint8_t MCAL_GPIO_READ_PIN(uint8_t GPIO_SEL, uint8_t pin);

#endif // GPIO_H_

