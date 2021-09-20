#include <xc.h>
#include <pic18f4550.h>  /*Header file PIC18f4550 definitions*/
#include "config.h"
#include "LCD_caracter.h"
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
uint16_t ReadADC(void);
uint16_t ReadLUZ(void);

unsigned  char  character1[ 8 ] = { 0x0e ,  0x1f ,  0x1f ,  0x0e ,  0x00 ,  0x0a ,  0x0a ,  0x00 };  /*  Value for Pi  */ 
unsigned  char  character2[ 8 ] = { 0x15 ,  0x0e ,  0x11 ,  0x11 ,  0x0e ,  0x15 ,  0x00 ,  0x00 };  /*  Value for Diode  */ 
unsigned  char  character3[ 8 ] = { 0x00 ,  0x00 ,  0x0e ,  0x1f ,  0x0e ,  0x00 ,  0x00 ,  0x00 };  /*  Value for Transistor  */ 


void main()
{
    OSCCON=0x72;        /* Use internal oscillator of 8MHz Frequency */
    TRISE=0x00;         /* Set direction of PORTB as OUTPUT to which LED is connected */

    
	LCD_Init();  /*Initialize LCD to 5*8 matrix in 4-bit mode*/   
	LCD_String_xy ( 1 , 0 , " Buenos Dias " ); /* Display string for respective symbol */
    LCD_Clear();
    
 
   
  
    //for (i= 0 ;i< 5 ;i++) 
    //{     
     //   LCD_Command ( 0xc0 |(i* 3 ));      // Display characters from c0(2nd row) location  */ 
      //  LCD_Char (i);                  // To display custom character send address as data to point stored  
                                       //character   
    //}   
        
    while ( 1 ){
        tempar = ReadADC();
        luz = ReadLUZ();
        if(tempar >20&&(luz>0&&luz<200)){
            sprintf(Stemp, "%0.1f C", tempar);
            LCD_String_xy(1, 0, Stemp);
            sprintf(Sluz, "%0.1f", luz);
            LCD_String_xy(1, 6, Sluz);
            LCD_Custom_Char ( 0 ,character2);         /* Write custom character to CGRAM 0x00 memory location */ 
            LCD_Command ( 0xc0);
            LCD_Char (0);
            LED_GREEN = OFF;
            LED_GREEN1 = OFF;
            LED_GREEN2 = OFF;
        }
        if((tempar >10||tempar<=20)&&(luz>200&&luz<500)){
            sprintf(Stemp, "%0.1f C", tempar);
            LCD_String_xy(1, 0, Stemp);
            sprintf(Sluz, "%0.1f", luz);
            LCD_String_xy(1, 6, Sluz);
            LCD_Custom_Char ( 0 ,character1);         /* Write custom character to CGRAM 0x00 memory location */ 
            LCD_Command ( 0xc0);
            LCD_Char (0);
            LED_GREEN = ON;
            LED_GREEN1 = ON;
            LED_GREEN2 = OFF;
        }
        if(tempar <10&&(luz>500&&luz<1500)){
            sprintf(Stemp, "%0.1f C", tempar);
            LCD_String_xy(1, 0, Stemp);
            sprintf(Sluz, "%0.1f", luz);
            LCD_String_xy(1, 6, Sluz);
            LCD_Custom_Char ( 0 ,character1);         /* Write custom character to CGRAM 0x00 memory location */ 
            LCD_Command ( 0xc0);
            LCD_Char (0);
            LED_GREEN = ON;
            LED_GREEN1 = ON;
            LED_GREEN2 = ON;
        }
        LCD_Clear();
    };	
   
}

