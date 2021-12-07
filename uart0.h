/*
 * uart0.h
 *
 *  Created on: Dec 7, 2021
 *      Author: abdal
 */

#ifndef UART0_H_
#define UART0_H_

#include "std_types.h"
#include "common_macros.h"


// Macros to enable and disable Global interrupts
#define ENABLE_INTERRUPTS() __asm(" CPSIE I")
#define DISABLE_INTERRUPTS() __asm(" CPSID I")


/*******************************************************************
 ************** Register Addresses Macros **************************
 *******************************************************************/
#define RCGCUART                (*((volatile uint32 *) 0x400FE618))
#define RCGCGPIO                (*((volatile uint32 *) 0x400FE608))
#define GPIOAFSEL_PORTA         (*((volatile uint32 *) 0x40004420))
#define GPIOPCTL_PORTA          (*((volatile uint32 *) 0x4000452C))
#define GPIODEN_PORTA           (*((volatile uint32 *) 0x4000451C))
#define UART0CTL                (*((volatile uint32 *) 0x4000C030))
#define UART0IBRD               (*((volatile uint32 *) 0x4000C024))
#define UART0FBRD               (*((volatile uint32 *) 0x4000C028))
#define UART0LCRH               (*((volatile uint32 *) 0x4000C02C))
#define UART0CC                 (*((volatile uint32 *) 0x4000CFC8))
#define UART0FR                 (*((volatile uint32 *) 0x4000C018))
#define UART0DR                 (*((volatile uint32 *) 0x4000C000))
#define UART0IM                 (*((volatile uint32 *) 0x4000C038))
#define UART0ICR                (*((volatile uint32 *) 0x4000C044))
#define NVICEN0                 (*((volatile uint32 *) 0xE000E100))
#define NVICPRI5                (*((volatile uint32 *) 0xE000E414))
#define UART0FR                 (*((volatile uint32 *) 0x4000C018))
#define RCGCGPIO                (*((volatile uint32 *) 0x400FE608))


void UART0_init(void);
void UART0_sendChar(uint8 c);
void UART0_sendtString(uint8 *string);
uint8 UART0_receiveChar(void);

#endif /* UART0_H_ */
