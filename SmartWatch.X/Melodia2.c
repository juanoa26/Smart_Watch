/*
 * File:   Melodia2.c
 * Author: User
 *
 * Created on 22 de septiembre de 2021, 09:28 AM
 */


#include <pic18f4550.h>  /*Header file PIC18f4550 definitions*/
#include "config.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "LCD_caracter.h"
#define _XTAL_FREQ 4000000 

void conf_CLK(void);
void conf_IO(void);
void conf_TA1(void);


/**
 *  \brief     void conf_CLK (void)
 *  \details   Configura los relojes disponibles
 *                  - Reloj Principal: INTERNO 8 MHz.
 *
 *  \author    Manuel Caballero
 *  \version   0.0
 *  \date      17/3/2015
 */

void PlayCancion( void ) {

    uint8_t var3seg     =   0;  /**< Variable contador que junto al Timer1 nos permite contabilizar 3 s */
    uint8_t var3beep    =   0;  /**< Variable contador que junto al Timer1 nos permite realizar tres Beep */


    conf_CLK    ();     // Configura Relojes
    conf_IO     ();     // Configura I/O
    conf_TA1    ();     // Configura Timer1

    
    INTCONbits.PEIE     =   1;      // Peripheral Interrupt Enable
    ei  ();                         // enable interrupts


    do{
        SLEEP();                    // uC modo IDLE

        if ( var3seg == 60 && var3beep < 6 )
        {
        // Tres Beep cada 3 segundos
            LATDbits.LD2       =   ~LATDbits.LD2;
            var3beep++;
            return;
        }
        else
        {
            if ( var3beep > 5 )
            {
            // Reset variables ( vuelta a empezar! )
                var3beep    =   0;
                var3seg     =   0;
                return;
            }

            var3seg++;
        }
    } while ( 1 );
}

void conf_CLK(void) {
    OSCCONbits.IRCF0 = 1; // Internal clock...
    OSCCONbits.IRCF1 = 1;
    OSCCONbits.IRCF2 = 1; //...8 MHz.

    OSCCONbits.SCS = 0b10; // Internal oscillator

    OSCCONbits.IDLEN = 1; // SLEEP() == Idle mode


    //OSCCONbits.IOFS     =   1;      // Frequency is stable
    //OSCCONbits.OSTS     =   1;      // Device is running from the primary system clock
}

/**
 *  \brief     void conf_IO (void)
 *  \details   Configura los pines del MCU a usar en este proyecto.
 *                  - Puerto D: Buzzer.
 *  			- RD2:	Salida.	  ( Serie Resistor 220 Ohms con Base Transistor NPN )
 *
 *  \author    Manuel Caballero
 *  \version   0.0
 *  \date      13/3/2015
 */
void conf_IO(void) {
    ADCON1bits.PCFG = 0b1111; // All Port Digital

    TRISDbits.RD2 = 0; // RD2 OUTPUT

    LATDbits.LD2 = 0; // reset pin
}

/**
 *  \brief     void conf_TA1 (void)
 *  \details   Configura el Timer1 como 16-bit timer.
 *
 *             El Timer1 será el encargado de ejecutar las acciones requeridas:
 *
 *                  1. Cuenta de 3 segundos.
 *                  2. Tres Beep por el Buzzer.
 *
 *             Se realizará todo el proceso cada, aproximadamente 3 segundos.
 *
 *           Teniendo en cuenta la expresión del Timer1:
 *
 *                  Interrupt_Timer1 = ( 1/( f_OSC/4 ) )·( 65536 - TMR1 )·Prescaler
 *
 *            Tenemos que:
 *
 *                  50 ms = ( 1/( 8MHz/4 ) )·( 65536 - TMR1 )·8
 *
 *                  TMR1 = 65536 - 12500 = 53036 ( 0xCF2C )
 *
 *
 *  \pre       El reloj debe ser 8 MHz.
 *  \author    Manuel Caballero
 *  \version   0.0
 *  \date      14/3/2015
 */
void conf_TA1(void) {
    T1CONbits.T1CKPS0 = 1; // 1:8 Prescale value
    T1CONbits.T1CKPS1 = 1; // 1:8 Prescale value

    TMR1H = 0xCF;
    TMR1L = 0x2C;

    PIR1bits.TMR1IF = 0; // Reset flag
    PIE1bits.TMR1IE = 1; // TA1 interrupt ON

    T1CONbits.TMR1ON = 1; // TA1 enabled
}

void __interrupt() ISR ( void )
{
    if ( PIR1bits.TMR1IF == 1 )                 // Timer1 Interrupt
    {
                     

        TMR1H               =   0xCF;
        TMR1L               =   0x2C;
        
        PIR1bits.TMR1IF     =   0; 
    }
}