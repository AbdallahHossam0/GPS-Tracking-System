/* File Comment
 * ---------------------------------------------------------------------------------------------------
 * [FILE NAME]: <LCD.h>
 *
 * [AUTHOR]: Abdallah Hossam-Eldin Hosny
 *
 * [DATE CREATED]: <7 - 12 - 2021>
 *
 * [DESCRIPTION]: <header file for LCD program>
 * ---------------------------------------------------------------------------------------------------
 */


#ifndef LCD_H_
#define LCD_H_

#include "tm4c123gh6pm_registers.h"

//Choose mode please "eight_bits_mode" or "four_bits_mode"
#define eight_bits_mode

#define clear_screen 0x01
#define cursor_on_display_on 0x0F
#define cursor_off_display_on 0b00001100
#define return_home 0x02
#define entry_mode 0x06

#if defined four_bits_mode
#define DATA_DIR GPIO_PORTB_DIR_REG
#define DATA_PORT GPIO_PORTB_DATA_REG
#define CTRL_DIR GPIO_PORTA_DIR_REG
#define CTRL_PORT GPIO_PORTA_DATA_REG
#define RS 5
#define RW 6
#define EN 7
#define FOUR_BITS 0x28

#elif defined eight_bits_mode
#define DATA_DIR GPIO_PORTB_DIR_REG
#define DATA_PORT GPIO_PORTB_DATA_REG
#define CTRL_DIR GPIO_PORTA_DIR_REG
#define CTRL_PORT GPIO_PORTA_DATA_REG
#define RS 5
#define RW 6
#define EN 7
#define EIGHT_BITS 0x38

#endif

void LCD_init(void);
void send_falling_edge(void);
void LCD_send_cmd(char cmd);
void LCD_send_char(char data);
void LCD_send_num(int data);
void LCD_send_str(char* data);
void LCD_clr_screen();
void LCD_move_cursor(char row,char col);

#endif /* LCD_H_ */
