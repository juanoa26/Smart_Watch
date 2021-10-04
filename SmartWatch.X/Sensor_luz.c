/*
 * PIC18F4550 I2C Source File
 * http://www.electronicwings.com
 */

#include "Funciones.h"

/*********************************************************************
 * Function:        uint16_t ReadLUZ(void)
 *
 * Input:           None
 *
 * Output:          uint16_t result: Informacion de la temperatura luego de la 
 *                  conversion
 *
 * Overview:        Funcion que se encarga de tomar la informacion en el sensor de luz
 *
 * Note:            None
 ********************************************************************/

uint16_t ReadLUZ(void) {

    TRISD = 0x00;
    TRISA = 0xFF;

    OSCCONbits.IRCF = 0b111; //Configura oscilador interno (FOSC = 8Mhz)
    OSCCONbits.SCS = 0b10; // Oscilador del sistema = Fosc interno

    //ADC = 10bits, Tad = 1us, Tacq = 4us, Vref = 5v-0v, RA=ANALOG
    ADCON1bits.PCFG = 0b1101; //  Configura el Puerto como Entrada Analógica.
    ADCON1bits.VCFG = 0b00; //  Selecciona Voltajes de Referencia (5v-0v).
    ADCON0bits.CHS = 0b0001; //  Selecciona el Canal Analógico.
    ADCON2bits.ACQT = 0b010; //  Tiempo de Adquisición 4Tad.
    ADCON2bits.ADCS = 0b001; //  Tiempo de Conversión Fosc/8.
    ADCON2bits.ADFM = 1; //  Justificación derecha (modo-10bits).
    ADCON0bits.ADON = 1; //  Habilita el Módulo AD.

    while (1) {
        ADCON0bits.GO_DONE = 1; //Inicia la COnversió AD.
        while (ADCON0bits.GO_DONE); //  Espera a que termine la conversión AD.
        result = ADRESH; //  Lectura de valor AD.
        result = (result << 8) + ADRESL;

        return result;
    }
}


