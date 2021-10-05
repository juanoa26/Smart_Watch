/* 
 * File:   smart_main.c
 * Author: Arlex Fabian Galindez-Geraldina Ivonne Carlosama-Juan Sebastian Osorio
 *
 * Created on 4 de octubre de 2021, 10:59 AM
 */

#include "LCD_caracter.h"
#include "I2C_Master_File.h"
#include "Funciones.h"

/*********************************************************************
 * Function:        void main()
 *
 * Input:           None
 *
 * Output:          None
 *
 * Overview:        Funcion pricipal que se encarga del funcionamiento
 *                  del programa
 *
 * Note:            None
 ********************************************************************/

void main() {
    OSCCON = 0x72; /* Use internal oscillator of 8MHz Frequency */
    TRISE = 0x00; /* Set direction of PORTB as OUTPUT to which LED is connected */


    I2C_Init();/*Initialize the I2C protocol*/
    LCD_Init(); /*Initialize LCD to 5*8 matrix in 4-bit mode*/

    while (1) {
        RTC_Calendario();
        int caso = Estados();
        switch(caso){
            case 1:
                Sunny_State();
                break;
             
            case 2:
                Cloudy_State();
                break;
                
            case 3:
                Rainy_State();
                break;
            
            default:
                break;
                    
        }
        LCD_MSdelay(3000);
        LCD_Clear();
    };

}





