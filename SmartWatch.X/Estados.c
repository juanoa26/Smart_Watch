/* 
 * File:   Estados.c
 * Author: Arlex Fabian Galindez-Geraldina Ivonne Carlosama-Juan Sebastian Osorio
 *
 * Created on 4 de octubre de 2021, 10:59 AM
 */

#include "Funciones.h"
#include "Melodia.h"
#include "Usart.h"

/*********************************************************************
 * Function:        int Estados()
 *
 * Input:           None
 *
 * Output:          Entero: Devuelve un numero entero positivo dependiendo 
 *                  de cada una de las condiciones
 *
 * Overview:        Permite determinar cada uno de los respectivos casos a usar
 *
 * Note:            None
 ********************************************************************/

int Estados() {
    tempar = ReadADC();
    luz = ReadLUZ();

    //data_in = USART_ReceiveChar();
    if (tempar > 15 && (luz > 0 && luz < 400)) {
        return 1;
    } else if ((tempar >= 12 && tempar <= 15)&&(luz > 400 && luz < 700)) {
        return 2;

    } else if (tempar < 12 && (luz > 700 && luz < 1500)) {
        return 3;
    }
    if(data_in =='1'){
        return 4;
    }
}

/*********************************************************************
 * Function:        void Sunny_State()
 *
 * Input:           None
 *
 * Output:          None
 *
 * Overview:        Imprime la temperatura y apaga los leds (si estan prendidos),
 *                  ademas imprime un emoticon en una pantalla LCD
 *
 * Note:            None
 ********************************************************************/

void Sunny_State() {
    LED_GREEN = OFF;
    LED_GREEN1 = OFF;
    LED_GREEN2 = OFF;
    sprintf(Stemp, "%0.0fC", tempar);
    LCD_String_xy(1, 0, Stemp);
    LCD_Custom_Char(0, character2); /* Write custom character to CGRAM 0x00 memory location */
    LCD_Command(0xc0);
    LCD_Char(0);
    PlayCancion();
    return;
}

/*********************************************************************
 * Function:        void Cloudy_State()
 *
 * Input:           None
 *
 * Output:          None
 *
 * Overview:        Imprime la temperatura y prende dos leds (si estan apagados),
 *                  ademas imprime un emoticon en una pantalla LCD
 *
 * Note:            None
 ********************************************************************/

void Cloudy_State() {
    LED_GREEN = ON;
    LED_GREEN1 = ON;
    LED_GREEN2 = OFF;
    sprintf(Stemp, "%0.0fC", tempar);
    LCD_String_xy(1, 0, Stemp);
    LCD_Custom_Char(0, character3); /* Write custom character to CGRAM 0x00 memory location */
    LCD_Command(0xc0);
    LCD_Char(0);
    return;
}

/*********************************************************************
 * Function:        void Rainy_State()
 *
 * Input:           None
 *
 * Output:          None
 *
 * Overview:        Imprime la temperatura y prende todos leds (si estan apagados),
 *                  ademas imprime un emoticon en una pantalla LCD
 *
 * Note:            None
 ********************************************************************/

void Rainy_State() {
    LED_GREEN = ON;
    LED_GREEN1 = ON;
    LED_GREEN2 = ON;
    sprintf(Stemp, "%0.0fC", tempar);
    LCD_String_xy(1, 0, Stemp);
    LCD_Custom_Char(0, character1); /* Write custom character to CGRAM 0x00 memory location */
    LCD_Command(0xc0);
    LCD_Char(0);
    return;
}

/*********************************************************************
 * Function:        void Alarm_Status(void)
 *
 * Input:           None
 *
 * Output:          None
 *
 * Overview:        Se encarga de hacer sonar la alarma e imprimir un mensaje de buenos dias
 *
 * Note:            None
 ********************************************************************/
void Alarm_Status(void) {
    
    USART_SendString("Buenos Dias");
    PlayCancion();
    return;
}
