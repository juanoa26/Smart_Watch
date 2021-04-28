#include <xc.h>
#include <pic18f4550.h>  /*Header file PIC18f4550 definitions*/
#include "config.h"
#include "utils.h"

//#define _User_
#ifdef _User_
#define DELAY(a) MSdelay(a);
#else 
#define DELAY(a) __delay_ms(a);
#endif

#define LED_GREEN LATE
#define ON 1
#define OFF 0


void main()
{
    OSCCON=0x72;        /* Use internal oscillator of 8MHz Frequency */
    TRISE=0x00;         /* Set direction of PORTB as OUTPUT to which LED is connected */
    
    LED_GREEN = ON;
    DELAY(500);
    LED_GREEN = OFF;
    DELAY(500);
    
}

