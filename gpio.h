/* File Comment
 * ---------------------------------------------------------------------------------------------------
 * [FILE NAME]: <gpio.h>
 *
 * [AUTHOR]: Abdallah Hossam-Eldin Hosny
 *
 * [DATE CREATED]: <3 - 12 - 2021>
 *
 * [DESCRIPTION]: <Header file for GPIO driver for TM4C123GH6PM>
 * ---------------------------------------------------------------------------------------------------
 */



#ifndef GPIO_H_
#define GPIO_H_

#include "std_types.h"
#include "common_macros.h"
#include "tm4c123gh6pm_registers.h"

/*---------------- Function Prototypes -------------------*/
void GPIO_vClkInit(uint8 port);
void GPIO_vPinDirection(uint8 port, uint8 pin, uint8 GPIO_dir);
void GPIO_vPinOutValue(uint8 port, uint8 pin, uint8 pinValue);
uint8 GPIO_u8PinInValue(uint8 port, uint8 pin);
void GPIO_vEnablePinPullUp(uint8 port, uint8 pin);


// TM4C123GH6PM has 6 Ports (43 Pins).
// 1. PORTA has 8 pins.
// 2. PORTB has 8 pins.
// 3. PORTC has 8 pins.
// 4. PORTD has 8 pins.
// 5. PORTE has 6 pins.
// 6. PORTF has 5 pins.



/*---------------- PORT Number Macros -------------------*/

#define PORTA               (0)
#define PORTB               (1)
#define PORTC               (2)
#define PORTD               (3)
#define PORTE               (4)
#define PORTF               (5)


/*---------------- PIN Number Macros -------------------*/

#define PIN0                (0)
#define PIN1                (1)
#define PIN2                (2)
#define PIN3                (3)
#define PIN4                (4)
#define PIN5                (5)
#define PIN6                (6)
#define PIN7                (7)


/*---------------- Direction Select -------------------*/
/*----------------  uint8 GPIO_dir  -------------------*/
#define GPIO_INPUT          (0)
#define GPIO_OUTPUT         (1)


#endif /* GPIO_H_ */
