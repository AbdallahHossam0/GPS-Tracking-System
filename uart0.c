/*
 * uart0.c
 *
 *  Created on: Dec 7, 2021
 *      Author: abdal
 */




#include "uart0.h"




void UART0_init(void){
    /* Enable the clock Gating Control for UART 0 */
        RCGCUART |= (1U << 0);

        /* Enable the clock Gating Control for Port A which is UART0 connected to it */
        RCGCGPIO |= (1U << 0);
        uint32 delay = RCGCGPIO;

        /* to select the alternative function for pin 0 and pin 1*/
        GPIOAFSEL_PORTA |= (1U << 0);
        GPIOAFSEL_PORTA |= (1U << 1);

        /* to select which alternative function for this pin */
        GPIOPCTL_PORTA |= (1U << 0); // set RX0 for PIN 0
        GPIOPCTL_PORTA |= (1U << 4); // set TX0 for PIN 1

        /* Enable the Digital function for pin 0 and pin 1 */
        GPIODEN_PORTA |= (1U << 0);
        GPIODEN_PORTA |= (1U << 1);


        /*      "To set the  baud rate"
         * 1. Disable the UART by clearing the UARTEN bit in the UARTCTL register.
         * 2. Write the integer portion of the BRD to the UARTIBRD register.
         * 3. Write the fractional portion of the BRD to the UARTFBRD register.
         * 4. Write the desired serial parameters to the UARTLCRH register.
         * 5. Configure the UART clock source by writing to the UARTCC register.
         * 6. Optionally, configure the DMA channel (see “Micro Direct Memory Access (DMA)” on page 585) and enable the DMA option(s) in the UARTDMACTL register.
         * 7. Enable the UART by setting the UARTEN bit in the UARTCTL register.
         * */

        /* Disable the UART */
        UART0CTL &= ~(1U << 0);

        /*
         * BRD = BRDI + BRDF = UARTSysClk / (ClkDiv * Baud Rate)
         *  BDR = 16 000 000 / (16 * 9600) =  104.1666666666667
         * UARTFBRD[DIVFRAC] = integer(BRDF * 64 + 0.5)
         *                   =  11
         */
        UART0IBRD = 104U;
        UART0FBRD = 11U;

        /*
         * UART serial configurations:
         *   - no parity.
         *   - 1 stop bit.
         *   - Word length = 8 bit.
         */
        UART0LCRH = (UART0LCRH &~ (0x00000060)) | (UART0LCRH | (0x00000060));

        /* to set the system clock to the UART0 */
        UART0CC &= ~(0x0000000F);

        /* Enable the UART, TX and RX*/
        UART0CTL |= (1 << 8);
        UART0CTL |= (1 << 9);
        UART0CTL |= (1 << 0);

        // Enable Global Interrupts
        ENABLE_INTERRUPTS();

        // Enable UART0 Peripheral Interrupt
        UART0IM |= 1 << 4;

        // Enable The Interrupt for UART0 in NVIC
        NVICEN0 |= 1 << 5;

}







/* Function Comment
 * ---------------------------------------------------------------------------------------------------
 * [FUNCTION NAME]:     UART0_sendChar
 *
 * [DESCRIPTION]:       Function to send a character by UART
 *
 * [Args]:              char c
 *
 * [IN]:                char c (the character you want to send)
 *
 * [OUT]:               None
 *
 * [IN / OUT]:          None
 *
 * [RETURNS]:           None
 * ---------------------------------------------------------------------------------------------------
 */
void UART0_sendChar(uint8 c){
    while((UART0FR & (1 << 5)));
    UART0DR = c;
}


/* Function Comment
 * ---------------------------------------------------------------------------------------------------
 * [FUNCTION NAME]:     UART0_sendtString
 *
 * [DESCRIPTION]:       Function to send a character by UART
 *
 * [Args]:              char* string
 *
 * [IN]:                char* string (the array of characters you want to send)
 *
 * [OUT]:               None
 *
 * [IN / OUT]:          None
 *
 * [RETURNS]:           None
 * ---------------------------------------------------------------------------------------------------
 */
void UART0_sendtString(uint8 *string){
    while(*string != '\0'){
        UART0_sendChar(*string);
        string++;
    }
}




/* Function Comment
 * ---------------------------------------------------------------------------------------------------
 * [FUNCTION NAME]:         UART0_receiveChar
 *
 * [DESCRIPTION]:           Function to receive a byte from the UART (by polling)
 *
 * [Args]:                  None
 *
 * [IN]:                    None
 *
 * [OUT]:                   None
 *
 * [IN / OUT]:              None
 *
 * [RETURNS]:               uint8 (the received byte)
 * ---------------------------------------------------------------------------------------------------
 */
uint8 UART0_receiveChar(void){
    char receivedByte;
    while(UART0FR & (1 << 4));
    receivedByte = (uint8) UART0DR;
    return receivedByte;
}
