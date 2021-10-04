
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
    LCD_Clear();

    while (1) {
        RTC_Calendario();
        int caso = Estados();
        switch(caso){
            case 1:
                Estado_Soleado();
                break;
             
            case 2:
                Estado_Nublado();
                break;
                
            case 3:
                Estado_Lluvioso();
                break;
            
            default:
                break;
                    
        }
        LCD_MSdelay(3000);
        LCD_Clear();
    };

}





