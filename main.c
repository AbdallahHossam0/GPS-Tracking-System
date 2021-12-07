#include "gpio.h"
#include "common_macros.h"
#include "LCD.h"
#include "std_types.h"
#include "uart0.h"
#include <math.h>

#define NUMBER_OF_ITERATIONS_PER_ONE_MILI_SECOND 762

void Delay_MS(unsigned long long n)
{
    volatile unsigned long long count = 0;
    while(count++ < (NUMBER_OF_ITERATIONS_PER_ONE_MILI_SECOND * n) );
}


void SW2_Init(void)
{
    GPIO_PORTF_LOCK_REG   = 0x4C4F434B;   /* Unlock the GPIO_PORTF_CR_REG */
    //GPIO_PORTF_LOCK_REG   = 0x4C4F434B;   /* Unlock the GPIO_PORTF_CR_REG */
    GPIO_PORTF_CR_REG    |= (1<<0);       /* Enable changes on PF0 */
    GPIO_vSetDigitalPin(PORTF, 0);
    GPIO_vPinDirection(PORTF, 0, GPIO_INPUT);
    GPIO_vEnablePinPullUp(PORTF, 0);
}


uint8 incomeFlag = 0;
uint8 incomeData = 0;
float32 totalDistance = 0;

uint8 prevlat = 0;
uint8 prevlong = 0;
uint8 prevDataFlag = 0;


// Utility function for
// converting degrees to radians
long double toRadians(const long double degree)
{
    // cmath library in C++
    // defines the constant
    // M_PI as the value of
    // pi accurate to 1e-30
    long double one_deg = (3.14) / 180;
    return (one_deg * degree);
}

long double distance(long double lat1, long double long1,
                    long double lat2, long double long2)
{
    // Convert the latitudes
    // and longitudes
    // from degree to radians.
    lat1 = toRadians(lat1);
    long1 = toRadians(long1);
    lat2 = toRadians(lat2);
    long2 = toRadians(long2);

    // Haversine Formula
    long double dlong = long2 - long1;
    long double dlat = lat2 - lat1;

    long double ans = pow(sin(dlat / 2), 2) +
                        cos(lat1) * cos(lat2) *
                        pow(sin(dlong / 2), 2);

    ans = 2 * asin(sqrt(ans));

    // Radius of Earth in
    // Kilometers, R = 6371
    // Use R = 3956 for miles
    long double R = 6371;

    // Calculate the result
    ans = ans * R;

    return ans;
}

void onMode(void){



    uint8 latitude = 0;
    uint8 longitude = 0;

    incomeFlag = 0;
    incomeData = 0;

    uint32 lonI = 0;
    uint32 lonF = 0;
    uint32 latI = 0;
    uint32 latF = 0;

    uint8 counter = 0;


   // uint8 incomeData = 0;
    //uint8 incomeFlag = 0;

    float finalLat = 0;
    float finalLon = 0;

    uint8 floatflag = 0;

    clr_screen();
    LCD_send_str("Distance (in M)");
    LCD_move_cursor(2, 5);
    LCD_send_num(0);
    LCD_move_cursor(2, 5);
    while(1){
        if(!(GPIO_PORTF_DATA_REG & (1<<0))){
            while(!(GPIO_PORTF_DATA_REG & (1<<0)));
            break;
        }

        if(incomeFlag == 1){
            if(incomeData == 78){
                floatflag = 0;
                longitude = 1;
                latitude = 0;
            }
            else if(incomeData == 76){
                finalLon = lonI + (((float)(lonF))/(pow(10,counter)));
                lonF = lonI = 0;
                counter = 0;
                floatflag = 0;
                longitude = 0;
                latitude = 1;
            }
            else if(incomeData == 35){
                finalLat = latI + (((float)(latF))/(pow(10,counter)));
                latI = 0;
                latF = 0;
                counter = 0;
                if(prevDataFlag){
                    totalDistance += distance(prevlat, prevlong, finalLat, finalLon);
                    LCD_move_cursor(2, 5);
                    totalDistance *= 1000;
                    LCD_send_num((uint32) totalDistance);
                    prevlat = finalLat;
                    prevlong = finalLon;
                }
                else{
                    prevDataFlag = 1;
                    prevlat = finalLat;
                    prevlong = finalLon;
                }
                finalLat = finalLon = 0;
            }
            else if(longitude == 1){
                if(incomeData == 46){
                    floatflag = 1;
                }
                else if(floatflag == 1){
                    counter++;
                    lonF = lonF * 10 + (int)(incomeData-48);
                }
                else
                    lonI = lonI * 10 + (int)(incomeData-48);
            }
            else if(latitude == 1){
                if(incomeData == 46){
                    floatflag = 1;
                }
                else if(floatflag == 1){
                    counter++;
                    latF = latF * 10 + (int)(incomeData-48);
                }
                else
                    latI = latI * 10 + (int)(incomeData-48);

            }

        }


    }

}

int main(void)
{
    volatile unsigned long delay = 0;
    GPIO_vClkInit(PORTA);
    GPIO_vClkInit(PORTB);
    GPIO_vClkInit(PORTF);
    delay = SYSCTL_REGCGC2_REG;

    GPIO_vSetDigitalPin(PORTA, PIN4);
    GPIO_vPinDirection(PORTA, PIN4, GPIO_OUTPUT);

    SW2_Init();

    UART0_init();

    Delay_MS(350);
    LCD_init();
    LCD_send_str("      Hello");


    while(1)
    {

        if(!(GPIO_PORTF_DATA_REG & (1<<0))){
            while(!(GPIO_PORTF_DATA_REG & (1<<0)));
            onMode();
            clr_screen();
            LCD_send_str("Total D =    M");
            LCD_move_cursor(1, 11);
            LCD_send_num((uint8) totalDistance);
            LCD_move_cursor(2, 1);
            LCD_send_str("Skip after: ");
            LCD_move_cursor(2, 13);
            LCD_send_num(3);
            LCD_move_cursor(2, 13);
            Delay_MS(1000);
            LCD_send_num(2);
            LCD_move_cursor(2, 13);
            Delay_MS(1000);
            LCD_send_num(1);
            LCD_move_cursor(2, 13);
            Delay_MS(1000);
            LCD_send_num(0);
            clr_screen();
            LCD_send_str("      Hello");

            incomeFlag = 0;
            incomeData = 0;
            totalDistance = 0;

            prevlat = 0;
            prevlong = 0;
            prevDataFlag = 0;
        }
        GPIO_vPinOutValue(PORTA, PIN4, 1);
        Delay_MS(150);

        GPIO_vPinOutValue(PORTA, PIN4, 0);
        Delay_MS(150);


    }
}


void UART0_Hndler(void){
    char receivedByte;
    receivedByte = (uint8) UART0DR;
    incomeFlag = 1;
    incomeData = receivedByte;
    UART0_sendChar(receivedByte);

}
