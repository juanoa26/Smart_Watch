#include <xc.h>
#include <pic18f4550.h>  /*Header file PIC18f4550 definitions*/
#include "config.h"
#include "LCD_caracter.h"
#include "I2C_Master_File.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>



//#define _User_
#ifdef _User_
#define DELAY(a) MSdelay(a);
#else 
#define DELAY(a) __delay_ms(a);
#endif

#define LED_GREEN LATE0
#define LED_GREEN1 LATE1
#define LED_GREEN2 LATE2
#define ON 1
#define OFF 0

float tempar;
float luz;
char Stemp[20];
char Sluz[20];

char i;
uint16_t ReadADC(void);
uint16_t ReadLUZ(void);
void PlayCancion();


unsigned char character1[ 8 ] = {0x0e, 0x1f, 0x1f, 0x0e, 0x00, 0x0a, 0x0a, 0x00}; /*  Value for Rainy day  */
unsigned char character2[ 8 ] = {0x15, 0x0e, 0x11, 0x11, 0x0e, 0x15, 0x00, 0x00}; /*  Value for Sunny day  */
unsigned char character3[ 8 ] = {0x00, 0x08, 0x16, 0x1f, 0x1f, 0x16, 0x08, 0x00}; /*  Value for Cloudy day  */

void main() {
    OSCCON = 0x72; /* Use internal oscillator of 8MHz Frequency */
    TRISE = 0x00; /* Set direction of PORTB as OUTPUT to which LED is connected */


    I2C_Init();
    LCD_Init(); /*Initialize LCD to 5*8 matrix in 4-bit mode*/
    LCD_String_xy(1, 0, " Buenos Dias "); /* Display string for respective symbol */
    LCD_Clear();

    while (1) {
        tempar = ReadADC();
        luz = ReadLUZ();
        RTC_Calendario();
        MSdelay(10);

        if (tempar > 15 && (luz > 0 && luz < 400)) {
            LED_GREEN = OFF;
            LED_GREEN1 = OFF;
            LED_GREEN2 = OFF;
            sprintf(Stemp, "%0.0fC", tempar);
            LCD_String_xy(1, 0, Stemp);
            LCD_Custom_Char(0, character2); /* Write custom character to CGRAM 0x00 memory location */
            LCD_Command(0xc0);
            LCD_Char(0);
            PlayCancion();
        }
        if ((tempar >= 12 && tempar <= 15)&&(luz > 400 && luz < 700)) {
            LED_GREEN = ON;
            LED_GREEN1 = ON;
            LED_GREEN2 = OFF;
            sprintf(Stemp, "%0.0fC", tempar);
            LCD_String_xy(1, 0, Stemp);
            LCD_Custom_Char(0, character3); /* Write custom character to CGRAM 0x00 memory location */
            LCD_Command(0xc0);
            LCD_Char(0);
            
        }
        if (tempar < 12 && (luz > 700 && luz < 1500)) {
            LED_GREEN = ON;
            LED_GREEN1 = ON;
            LED_GREEN2 = ON;
            sprintf(Stemp, "%0.0fC", tempar);
            LCD_String_xy(1, 0, Stemp);
            LCD_Custom_Char(0, character1); /* Write custom character to CGRAM 0x00 memory location */
            LCD_Command(0xc0);
            LCD_Char(0);

            //Calendario();
        }
        MSdelay(3000);
        LCD_Clear();
    };

}





