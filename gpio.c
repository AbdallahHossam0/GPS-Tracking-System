/* File Comment
 * ---------------------------------------------------------------------------------------------------
 * [FILE NAME]: <gpio.c>
 *
 * [AUTHOR]: Abdallah Hossam-Eldin Hosny
 *
 * [DATE CREATED]: <3 - 12 - 2020>
 *
 * [DESCRIPTION]: <Source code for GPIO driver>
 * ---------------------------------------------------------------------------------------------------
 */


#include "gpio.h"

void GPIO_vClkInit(uint8 port){
    SYSCTL_REGCGC2_REG |= 1 << port;
}

void GPIO_vSetDigitalPin(uint8 port, uint8 pin){
    switch(port){
    case PORTA:
        GPIO_PORTA_AMSEL_REG &= ~(1 << pin);
        GPIO_PORTA_PCTL_REG  &= ~(0xF << pin);
        GPIO_PORTA_AFSEL_REG &= ~(1 << pin);
        GPIO_PORTA_DEN_REG   |=  (1 << pin);
        break;
    case PORTB:
        GPIO_PORTB_AMSEL_REG &= ~(1<<pin);
        GPIO_PORTB_PCTL_REG  &= ~(0xF << pin);
        GPIO_PORTB_AFSEL_REG &= ~(1<<pin);
        GPIO_PORTB_DEN_REG   |=  (1 << pin);
        break;
    case PORTC:
        GPIO_PORTC_AMSEL_REG &= ~(1<<pin);
        GPIO_PORTC_PCTL_REG  &= ~(0xF << pin);
        GPIO_PORTC_AFSEL_REG &= ~(1<<pin);
        GPIO_PORTC_DEN_REG   |=  (1 << pin);
        break;
    case PORTD:
        GPIO_PORTD_AMSEL_REG &= ~(1<<pin);
        GPIO_PORTD_PCTL_REG  &= ~(0xF << pin);
        GPIO_PORTD_AFSEL_REG &= ~(1<<pin);
        GPIO_PORTD_DEN_REG   |=  (1 << pin);
        break;
    case PORTE:
        GPIO_PORTE_AMSEL_REG &= ~(1<<pin);
        GPIO_PORTE_PCTL_REG  &= ~(0xF << pin);
        GPIO_PORTE_AFSEL_REG &= ~(1<<pin);
        GPIO_PORTE_DEN_REG   |=  (1 << pin);
        break;
    case PORTF:
        GPIO_PORTF_AMSEL_REG &= ~(1<<pin);
        GPIO_PORTF_PCTL_REG  &= ~(0xF << pin);
        GPIO_PORTF_AFSEL_REG &= ~(1<<pin);
        GPIO_PORTF_DEN_REG   |=  (1 << pin);
        break;
    }
}

void GPIO_vPinDirection(uint8 port, uint8 pin, uint8 GPIO_dir){
    switch(port){
    case PORTA:
        if(GPIO_dir == GPIO_INPUT){
            GPIO_PORTA_DIR_REG &= ~(1 << pin);
        }
        else if(GPIO_dir == GPIO_OUTPUT){
            GPIO_PORTA_DIR_REG |= 1 << pin;
        }
        break;
    case PORTB:
        if(GPIO_dir == GPIO_INPUT){
            GPIO_PORTB_DIR_REG &= ~(1 << pin);
        }
        else if(GPIO_dir == GPIO_OUTPUT){
            GPIO_PORTB_DIR_REG |= 1 << pin;
        }
        break;
    case PORTC:
        if(GPIO_dir == GPIO_INPUT){
            GPIO_PORTC_DIR_REG &= ~(1 << pin);
        }
        else if(GPIO_dir == GPIO_OUTPUT){
            GPIO_PORTC_DIR_REG |= 1 << pin;
        }
        break;
    case PORTD:
        if(GPIO_dir == GPIO_INPUT){
            GPIO_PORTD_DIR_REG &= ~(1 << pin);
        }
        else if(GPIO_dir == GPIO_OUTPUT){
            GPIO_PORTD_DIR_REG |= 1 << pin;
        }
        break;
    case PORTE:
        if(GPIO_dir == GPIO_INPUT){
            GPIO_PORTE_DIR_REG &= ~(1 << pin);
        }
        else if(GPIO_dir == GPIO_OUTPUT){
            GPIO_PORTE_DIR_REG |= 1 << pin;
        }
        break;
    case PORTF:
        if(GPIO_dir == GPIO_INPUT){
            GPIO_PORTF_DIR_REG &= ~(1 << pin);
        }
        else if(GPIO_dir == GPIO_OUTPUT){
            GPIO_PORTF_DIR_REG |= 1 << pin;
        }
        break;
    default: break;
    }
}

void GPIO_vPinOutValue(uint8 port, uint8 pin, uint8 pinValue){
    switch(port){
    case PORTA:
        if(pinValue == 0){
            GPIO_PORTA_DATA_REG &= ~(1 << pin);
        }
        else if(pinValue == 1){
            GPIO_PORTA_DATA_REG |= 1 << pin;
        }
        break;
    case PORTB:
        if(pinValue == 0){
            GPIO_PORTB_DATA_REG &= ~(1 << pin);
        }
        else if(pinValue == 1){
            GPIO_PORTB_DATA_REG |= 1 << pin;
        }
        break;
    case PORTC:
        if(pinValue == 0){
            GPIO_PORTC_DATA_REG &= ~(1 << pin);
        }
        else if(pinValue == 1){
            GPIO_PORTC_DATA_REG |= 1 << pin;
        }
        break;
    case PORTD:
        if(pinValue == 0){
            GPIO_PORTD_DATA_REG &= ~(1 << pin);
        }
        else if(pinValue == 1){
            GPIO_PORTD_DATA_REG |= 1 << pin;
        }
        break;
    case PORTE:
        if(pinValue == 0){
            GPIO_PORTE_DATA_REG &= ~(1 << pin);
        }
        else if(pinValue == 1){
            GPIO_PORTE_DATA_REG |= 1 << pin;
        }
        break;

    case PORTF:
        if(pinValue == 0){
            GPIO_PORTF_DATA_REG &= ~(1 << pin);
        }
        else if(pinValue == 1){
            GPIO_PORTF_DATA_REG |= 1 << pin;
        }
        break;

    }
}

uint8 GPIO_u8PinInValue(uint8 port, uint8 pin){
    switch(port){
    case PORTA:
        if(BIT_IS_SET(GPIO_PORTA_DATA_REG, pin)){
            return 1;
        }
        else if(BIT_IS_CLEAR(GPIO_PORTA_DATA_REG, pin)){
            return 0;
        }
        break;
    case PORTB:
        if(BIT_IS_SET(GPIO_PORTB_DATA_REG, pin)){
            return 1;
        }
        else if(BIT_IS_CLEAR(GPIO_PORTB_DATA_REG, pin)){
            return 0;
        }
        break;

    case PORTC:
        if(BIT_IS_SET(GPIO_PORTC_DATA_REG, pin)){
            return 1;
        }
        else if(BIT_IS_CLEAR(GPIO_PORTC_DATA_REG, pin)){
            return 0;
        }
        break;

    case PORTD:
        if(BIT_IS_SET(GPIO_PORTD_DATA_REG, pin)){
            return 1;
        }
        else if(BIT_IS_CLEAR(GPIO_PORTD_DATA_REG, pin)){
            return 0;
        }
        break;
    case PORTE:
        if(BIT_IS_SET(GPIO_PORTE_DATA_REG, pin)){
            return 1;
        }
        else if(BIT_IS_CLEAR(GPIO_PORTE_DATA_REG, pin)){
            return 0;
        }
        break;
    case PORTF:
        if(BIT_IS_SET(GPIO_PORTF_DATA_REG, pin)){
            return 1;
        }
        else if(BIT_IS_CLEAR(GPIO_PORTF_DATA_REG, pin)){
            return 0;
        }
        break;
    }
    return 0;
}

void GPIO_vEnablePinPullUp(uint8 port, uint8 pin){
    switch(port){
    case PORTA:
        GPIO_PORTA_PUR_REG |= 1 << pin;
        break;
    case PORTB:
        GPIO_PORTB_PUR_REG |= 1 << pin;
        break;
    case PORTC:
        GPIO_PORTC_PUR_REG |= 1 << pin;
        break;
    case PORTD:
        GPIO_PORTD_PUR_REG |= 1 << pin;
        break;
    case PORTE:
        GPIO_PORTE_PUR_REG |= 1 << pin;
        break;
    case PORTF:
        GPIO_PORTF_PUR_REG |= 1 << pin;
        break;
    }
}
