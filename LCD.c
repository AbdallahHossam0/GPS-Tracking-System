/*
 * LCD.c
 *
 * Created: 26-Jul-20 1:06:56 PM
 *  Author: Hatem
 */ 


#include "LCD.h"
#include "common_macros.h"
#include "std_types.h"
#include "gpio.h"
#include "stdlib.h"
#define NUMBER_OF_ITERATIONS_PER_ONE_MILI_SECOND 762
void _Delay_MS(unsigned long long n)
{
    volatile unsigned long long count = 0;
    while(count++ < (NUMBER_OF_ITERATIONS_PER_ONE_MILI_SECOND * n) );
}


void swap(char *str1, char *str2)
{
    char *temp = str1;
    str1 = str2;
    str2 = temp;
}

void reverse(char str[], int length)
{
    int start = 0;
    int end = length -1;
    while (start < end)
    {
        swap((str+start), (str+end));
        start++;
        end--;
    }
}

// Implementation of itoa()
char* itoa(int num, char* str, int base)
{
    int i = 0;
    bool isNegative = FALSE;

    /* Handle 0 explicitly, otherwise empty string is printed for 0 */
    if (num == 0)
    {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }

    // In standard itoa(), negative numbers are handled only with
    // base 10. Otherwise numbers are considered unsigned.
    if (num < 0 && base == 10)
    {
        isNegative = TRUE;
        num = -num;
    }

    // Process individual digits
    while (num != 0)
    {
        int rem = num % base;
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
        num = num/base;
    }

    // If number is negative, append '-'
    if (isNegative)
        str[i++] = '-';

    str[i] = '\0'; // Append string terminator

    // Reverse the string
    reverse(str, i);

    return str;
}

void LCD_init(void){

    GPIO_vSetDigitalPin(PORTB, PIN0);
    GPIO_vSetDigitalPin(PORTB, PIN1);
    GPIO_vSetDigitalPin(PORTB, PIN2);
    GPIO_vSetDigitalPin(PORTB, PIN3);
    GPIO_vSetDigitalPin(PORTB, PIN4);
    GPIO_vSetDigitalPin(PORTB, PIN5);
    GPIO_vSetDigitalPin(PORTB, PIN6);
    GPIO_vSetDigitalPin(PORTB, PIN7);
    GPIO_vSetDigitalPin(PORTA, RS);
    GPIO_vSetDigitalPin(PORTA, RW);
    GPIO_vSetDigitalPin(PORTA, EN);
#if defined eight_bits_mode
    SET_BIT(DATA_DIR,0);
    SET_BIT(DATA_DIR,1);
    SET_BIT(DATA_DIR,2);
    SET_BIT(DATA_DIR,3);
    SET_BIT(DATA_DIR,4);
    SET_BIT(DATA_DIR,5);
    SET_BIT(DATA_DIR,6);
    SET_BIT(DATA_DIR,7);

    SET_BIT(CTRL_DIR,RS);
    SET_BIT(CTRL_DIR,RW);
    SET_BIT(CTRL_DIR,EN);

    CLEAR_BIT(CTRL_PORT,RW);

    LCD_send_cmd(EIGHT_BITS);
    _Delay_MS(2);
    LCD_send_cmd(cursor_off_display_on);
    _Delay_MS(2);
    LCD_send_cmd(clear_screen);
    _Delay_MS(10);
    LCD_send_cmd(entry_mode);
    _Delay_MS(2);

#elif defined four_bits_mode
    SET_BIT(DATA_DIR,4);
    SET_BIT(DATA_DIR,5);
    SET_BIT(DATA_DIR,6);
    SET_BIT(DATA_DIR,7);

    SET_BIT(CTRL_DIR,RS);
    SET_BIT(CTRL_DIR,RW);
    SET_BIT(CTRL_DIR,EN);

    SET_BIT(CTRL_PORT,RW);

    LCD_send_cmd(FOUR_BITS);
    Delay_MS(1);
    LCD_send_cmd(cursor_on_display_on);
    Delay_MS(1);
    LCD_send_cmd(clr_screen);
    Delay_MS(5);
    LCD_send_cmd(entry_mode);
    Delay_MS(1);

#endif

}

void send_falling_edge(void){
    SET_BIT(CTRL_PORT,EN);
    _Delay_MS(2);
    CLEAR_BIT(CTRL_PORT,EN);
    _Delay_MS(2);
}

void LCD_send_cmd(char cmd){
#if defined eight_bits_mode
    DATA_PORT=cmd;
    CLEAR_BIT(CTRL_PORT,RS);
    send_falling_edge();

#elif defined four_bits_mode
    char high_nibble=(cmd>>4);
    char low_nibble=(cmd&0x0F);

    DATA_PORT = (DATA_PORT&0x0F)&(high_nibble<<4);
    CLEAR_BIT(CTRL_PORT,RS);
    send_falling_edge();

    DATA_PORT = (DATA_PORT&0x0F)&(low_nibble<<4);
    CLEAR_BIT(CTRL_PORT,RS);
    send_falling_edge();
    Delay_MS(1);

#endif

}

void LCD_send_char(char data){
#if defined eight_bits_mode
    DATA_PORT = data;
    SET_BIT(CTRL_PORT,RS);
    send_falling_edge();

#elif defined four_bits_mode
    char high_nibble=(data>>4);
    char low_nibble=(data&0x0F);

    DATA_PORT = (DATA_PORT&0x0F)&(high_nibble<<4);
    SET_BIT(CTRL_PORT,RS);
    send_falling_edge();

    DATA_PORT = (DATA_PORT&0x0F)&(low_nibble<<4);
    SET_BIT(CTRL_PORT,RS);
    send_falling_edge();
    Delay_MS(1);

#endif

}

void clr_screen(){
    LCD_send_cmd(clear_screen);
    _Delay_MS(10);
}

void LCD_send_str(char* data){
    while((*data)!='\0'){
        LCD_send_char(*data);
        data+=1;
    }
}

void LCD_send_num(int data){
    char buffer[16];
    int reverse = 0, rem = 0;
    while(data!=0)
    {
        rem=data%10;
        reverse=reverse*10+rem;
        data/=10;
    }
    itoa(reverse,buffer,10);
    LCD_send_str(buffer);
}

void LCD_move_cursor(char row,char col){
    char data;

    if(row>2||row<1||col>16||col<1){
        data=0x80;
    }
    else if(row==1){
        data=0x80+col-1;
    }
    else{
        data=0xC0+col-1;
    }

    LCD_send_cmd(data);
    _Delay_MS(1);
}
