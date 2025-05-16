#include"tm4c123gh6pm.h"

//MAECOS
#ifndef BIT_MATHS_H
#define BIT_MATHS_H
#include <stdint.h>

// Set a specific bit in a register
#define SET_BIT(REG, BIT)     ((REG) |=  (1 << (BIT)))

// Clear a specific bit in a register
#define CLR_BIT(REG, BIT)     ((REG) &= ~(1 << (BIT)))

// Toggle a specific bit in a register
#define TOG_BIT(REG, BIT)     ((REG) ^=  (1 << (BIT)))

// Get the value of a specific bit in a register (returns 0 or 1)
#define GET_BIT(REG, BIT)     (((REG) >> (BIT)) & 1)

// Set a register with a specific value
#define SET(REG, VALUE)       ((REG) = (VALUE))

// Clear specific bits in a register using a bitmask
#define CLR(REG, VALUE)       ((REG) &= ~(VALUE))

// Toggle specific bits in a register using a bitmask
#define TOG(REG, VALUE)       ((REG) ^= (VALUE))

// Get specific bits from a register using a bitmask
#define GET(REG, VALUE)       ((REG) & (VALUE))

#endif // BIT_MATHS_H

# define PORTA_ID 0
#define PORTB_ID 1
#define PORTC_ID 2
#define PORTD_ID 3
#define PORTE_ID 4
#define PORTF_ID 5

#define low 0
#define high 1

#define pull_down 0
#define pull_up 1

void MCAL_GPIO_INIT(uint8_t GPIO_SEL)
{
    switch (GPIO_SEL)
    {
        case PORTA_ID:
            // Enable clock for PORTA
            SET_BIT(SYSCTL_RCGCGPIO_R, 0);  // Bit 0
            while ((SYSCTL_PRGPIO_R & 0x01) == 0);
            GPIO_PORTA_LOCK_R = 0x4C4F434B;
            GPIO_PORTA_CR_R = 0xFF;
            break;

        case PORTB_ID:
            SET_BIT(SYSCTL_RCGCGPIO_R, 1);  // Bit 1
            while ((SYSCTL_PRGPIO_R & 0x02) == 0);
            GPIO_PORTB_LOCK_R = 0x4C4F434B;
            GPIO_PORTB_CR_R = 0xFF;
            break;

        case PORTC_ID:
            SET_BIT(SYSCTL_RCGCGPIO_R, 2);  // Bit 2
            while ((SYSCTL_PRGPIO_R & 0x04) == 0);
            // Note: No need to unlock PORTC usually (except PC0–PC3 reserved for JTAG by default)
            GPIO_PORTC_LOCK_R = 0x4C4F434B;
            GPIO_PORTC_CR_R = 0xFF;
            break;

        case PORTD_ID:
            SET_BIT(SYSCTL_RCGCGPIO_R, 3);  // Bit 3
            while ((SYSCTL_PRGPIO_R & 0x08) == 0);
            GPIO_PORTD_LOCK_R = 0x4C4F434B;
            GPIO_PORTD_CR_R = 0xFF;
            break;

        case PORTE_ID:
            SET_BIT(SYSCTL_RCGCGPIO_R, 4);  // Bit 4
            while ((SYSCTL_PRGPIO_R & 0x10) == 0);
            // PORT E doesn't need unlock
            GPIO_PORTE_CR_R = 0xFF;
            break;

        case PORTF_ID:
            SET_BIT(SYSCTL_RCGCGPIO_R, 5);  // Bit 5
            while ((SYSCTL_PRGPIO_R & 0x20) == 0);
            GPIO_PORTF_LOCK_R = 0x4C4F434B;
            GPIO_PORTF_CR_R = 0x1F;
            break;

        default:
            // Handle invalid port selection (optional)
            break;
    }
}



void MCAL_GPIO_DIGITAL_INIT(uint8_t GPIO_SEL, uint8_t pin)
{
    switch (GPIO_SEL)
    {
        case PORTA_ID:
            SET_BIT(GPIO_PORTA_CR_R, pin);               // Unlock pin
            SET_BIT(GPIO_PORTA_DEN_R, pin);              // Enable digital function
            CLR_BIT(GPIO_PORTA_AMSEL_R, pin);            // Disable analog
            CLR_BIT(GPIO_PORTA_AFSEL_R, pin);            // Disable alternate function
            GPIO_PORTA_PCTL_R &= ~(0xF << (pin * 4));    // Clear PCTL
            break;

        case PORTB_ID:
            SET_BIT(GPIO_PORTB_CR_R, pin);
            SET_BIT(GPIO_PORTB_DEN_R, pin);
            CLR_BIT(GPIO_PORTB_AMSEL_R, pin);
            CLR_BIT(GPIO_PORTB_AFSEL_R, pin);
            GPIO_PORTB_PCTL_R &= ~(0xF << (pin * 4));
            break;

        case PORTC_ID:
            SET_BIT(GPIO_PORTC_CR_R, pin);
            SET_BIT(GPIO_PORTC_DEN_R, pin);
            CLR_BIT(GPIO_PORTC_AMSEL_R, pin);
            CLR_BIT(GPIO_PORTC_AFSEL_R, pin);
            GPIO_PORTC_PCTL_R &= ~(0xF << (pin * 4));
            break;

        case PORTD_ID:
            SET_BIT(GPIO_PORTD_CR_R, pin);
            SET_BIT(GPIO_PORTD_DEN_R, pin);
            CLR_BIT(GPIO_PORTD_AMSEL_R, pin);
            CLR_BIT(GPIO_PORTD_AFSEL_R, pin);
            GPIO_PORTD_PCTL_R &= ~(0xF << (pin * 4));
            break;

        case PORTE_ID:
            SET_BIT(GPIO_PORTE_CR_R, pin);
            SET_BIT(GPIO_PORTE_DEN_R, pin);
            CLR_BIT(GPIO_PORTE_AMSEL_R, pin);
            CLR_BIT(GPIO_PORTE_AFSEL_R, pin);
            GPIO_PORTE_PCTL_R &= ~(0xF << (pin * 4));
            break;

        case PORTF_ID:
            SET_BIT(GPIO_PORTF_CR_R, pin);
            SET_BIT(GPIO_PORTF_DEN_R, pin);
            CLR_BIT(GPIO_PORTF_AMSEL_R, pin);
            CLR_BIT(GPIO_PORTF_AFSEL_R, pin);
            GPIO_PORTF_PCTL_R &= ~(0xF << (pin * 4));
            break;

        default:
            // Invalid port, ???? ???? error handler ??? ?? ????
            break;
    }
}



void MCAL_GPIO_DIGITAL_PIN_MODE(uint8_t GPIO_SEL, uint8_t pin, uint8_t Mode, uint8_t Polarity) {
    switch (GPIO_SEL) {
        case PORTA_ID:
            if (Mode == high) {
                SET_BIT(GPIO_PORTA_DIR_R, pin);
            } else {
                CLR_BIT(GPIO_PORTA_DIR_R, pin);
                switch (Polarity) {
                    case high: // Pull-up
                        SET_BIT(GPIO_PORTA_PUR_R, pin);
                        CLR_BIT(GPIO_PORTA_PDR_R, pin);
                        break;
                    case low: // Pull-down
                        SET_BIT(GPIO_PORTA_PDR_R, pin);
                        CLR_BIT(GPIO_PORTA_PUR_R, pin);
                        break;
                    default: // Floating
                        CLR_BIT(GPIO_PORTA_PUR_R, pin);
                        CLR_BIT(GPIO_PORTA_PDR_R, pin);
                        break;
                }
            }
            break;

        case PORTB_ID:
            if (Mode == high) {
                SET_BIT(GPIO_PORTB_DIR_R, pin);
            } else {
                CLR_BIT(GPIO_PORTB_DIR_R, pin);
                switch (Polarity) {
                    case high:
                        SET_BIT(GPIO_PORTB_PUR_R, pin);
                        CLR_BIT(GPIO_PORTB_PDR_R, pin);
                        break;
                    case low:
                        SET_BIT(GPIO_PORTB_PDR_R, pin);
                        CLR_BIT(GPIO_PORTB_PUR_R, pin);
                        break;
                    default:
                        CLR_BIT(GPIO_PORTB_PUR_R, pin);
                        CLR_BIT(GPIO_PORTB_PDR_R, pin);
                        break;
                }
            }
            break;

        case PORTC_ID:
            if (Mode == high) {
                SET_BIT(GPIO_PORTC_DIR_R, pin);
            } else {
                CLR_BIT(GPIO_PORTC_DIR_R, pin);
                switch (Polarity) {
                    case high:
                        SET_BIT(GPIO_PORTC_PUR_R, pin);
                        CLR_BIT(GPIO_PORTC_PDR_R, pin);
                        break;
                    case low:
                        SET_BIT(GPIO_PORTC_PDR_R, pin);
                        CLR_BIT(GPIO_PORTC_PUR_R, pin);
                        break;
                    default:
                        CLR_BIT(GPIO_PORTC_PUR_R, pin);
                        CLR_BIT(GPIO_PORTC_PDR_R, pin);
                        break;
                }
            }
            break;

        case PORTD_ID:
            if (Mode == high) {
                SET_BIT(GPIO_PORTD_DIR_R, pin);
            } else {
                CLR_BIT(GPIO_PORTD_DIR_R, pin);
                switch (Polarity) {
                    case high:
                        SET_BIT(GPIO_PORTD_PUR_R, pin);
                        CLR_BIT(GPIO_PORTD_PDR_R, pin);
                        break;
                    case low:
                        SET_BIT(GPIO_PORTD_PDR_R, pin);
                        CLR_BIT(GPIO_PORTD_PUR_R, pin);
                        break;
                    default:
                        CLR_BIT(GPIO_PORTD_PUR_R, pin);
                        CLR_BIT(GPIO_PORTD_PDR_R, pin);
                        break;
                }
            }
            break;

        case PORTE_ID:
            if (Mode == high) {
                SET_BIT(GPIO_PORTE_DIR_R, pin);
            } else {
                CLR_BIT(GPIO_PORTE_DIR_R, pin);
                switch (Polarity) {
                    case high:
                        SET_BIT(GPIO_PORTE_PUR_R, pin);
                        CLR_BIT(GPIO_PORTE_PDR_R, pin);
                        break;
                    case low:
                        SET_BIT(GPIO_PORTE_PDR_R, pin);
                        CLR_BIT(GPIO_PORTE_PUR_R, pin);
                        break;
                    default:
                        CLR_BIT(GPIO_PORTE_PUR_R, pin);
                        CLR_BIT(GPIO_PORTE_PDR_R, pin);
                        break;
                }
            }
            break;

        case PORTF_ID:
            if (Mode == high) {
                SET_BIT(GPIO_PORTF_DIR_R, pin);
            } else {
                CLR_BIT(GPIO_PORTF_DIR_R, pin);
                switch (Polarity) {
                    case pull_up:
                        SET_BIT(GPIO_PORTF_PUR_R, pin);
                        CLR_BIT(GPIO_PORTF_PDR_R, pin);
                        break;
                    case pull_down:
                        SET_BIT(GPIO_PORTF_PDR_R, pin);
                        CLR_BIT(GPIO_PORTF_PUR_R, pin);
                        break;
                    default:
                        CLR_BIT(GPIO_PORTF_PUR_R, pin);
                        CLR_BIT(GPIO_PORTF_PDR_R, pin);
                        break;
                }
            }
            break;
    }
}


void MCAL_GPIO_WRITE_PIN(uint8_t GPIO_SEL, uint8_t pin, uint8_t data)
{
    switch (GPIO_SEL)
    {
        case PORTA_ID:
            if (data == high)
                SET_BIT(GPIO_PORTA_DATA_R, pin);
            else
                CLR_BIT(GPIO_PORTA_DATA_R, pin);
            break;

        case PORTB_ID:
            if (data == high)
                SET_BIT(GPIO_PORTB_DATA_R, pin);
            else
                CLR_BIT(GPIO_PORTB_DATA_R, pin);
            break;

        case PORTC_ID:
            if (data == high)
                SET_BIT(GPIO_PORTC_DATA_R, pin);
            else
                CLR_BIT(GPIO_PORTC_DATA_R, pin);
            break;

        case PORTD_ID:
            if (data == high)
                SET_BIT(GPIO_PORTD_DATA_R, pin);
            else
                CLR_BIT(GPIO_PORTD_DATA_R, pin);
            break;

        case PORTE_ID:
            if (data == high)
                SET_BIT(GPIO_PORTE_DATA_R, pin);
            else
                CLR_BIT(GPIO_PORTE_DATA_R, pin);
            break;

        case PORTF_ID:
            if (data == high)
                SET_BIT(GPIO_PORTF_DATA_R, pin);
            else
                CLR_BIT(GPIO_PORTF_DATA_R, pin);
            break;

        default:
            // Invalid port
            break;
    }
}


uint8_t MCAL_GPIO_READ_PIN(uint8_t GPIO_SEL, uint8_t pin)
{
    switch (GPIO_SEL)
    {
        case PORTA_ID:
            return GET_BIT(GPIO_PORTA_DATA_R, pin);

        case PORTB_ID:
            return GET_BIT(GPIO_PORTB_DATA_R, pin);

        case PORTC_ID:
            return GET_BIT(GPIO_PORTC_DATA_R, pin);

        case PORTD_ID:
            return GET_BIT(GPIO_PORTD_DATA_R, pin);

        case PORTE_ID:
            return GET_BIT(GPIO_PORTE_DATA_R, pin);

        case PORTF_ID:
            return GET_BIT(GPIO_PORTF_DATA_R, pin);

        default:
            return 0;
    }
}



