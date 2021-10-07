/*!
\file   bluetooth.c
\date   2020-11-23
\author Fulvio Vivas <fulvio.vivas@unicauca.edu.co>
\brief  Example bluetooth HC-05.
\par Copyright
Information contained herein is proprietary to and constitutes valuable
confidential trade secrets of unicauca, and
is subject to restrictions on use and disclosure.
\par
Copyright (c) unicauca 2020. All rights reserved.
\par
The copyright notices above do not evidence any actual or
intended publication of this material.
 ******************************************************************************
 */

#include "Funciones.h"
#include "Usart.h"

#define F_CPU 8000000/64
//#define Baud_value(baud_rate) (((float)(F_CPU)/(float)baud_rate)-1)
#define Baud_value (((float)(F_CPU)/(float)baud_rate)-1)


/*********************************************************************
 * Function:        void USART_Init(long baud_rate)
 *
 * Input:           long baud_rate: Valor de frecuencia
 *
 * Output:          None
 *
 * Overview:        Iniciliza la comunicacion con el bluetooth
 *
 * Note:            None
 ********************************************************************/
void USART_Init(long baud_rate) {
    float temp;
    TRISC6 = 0; /*Make Tx pin as output*/
    TRISC7 = 1; /*Make Rx pin as input*/
    temp = Baud_value;
    SPBRG = (int) temp; /*baud rate=9600, SPBRG = (F_CPU /(64*9600))-1*/
    TXSTA = 0x20; /*Transmit Enable(TX) enable*/
    RCSTA = 0x90; /*Receive Enable(RX) enable and serial port enable */
    return;
}

/*********************************************************************
 * Function:        void USART_TransmitChar(char out)
 *
 * Input:           char out: El dato que se recibe
 *
 * Output:          None
 *
 * Overview:        Transminete los datos 
 *
 * Note:            None
 ********************************************************************/
void USART_TransmitChar(char out) {
    while (TXIF == 0); /*wait for transmit interrupt flag*/
    TXREG = out; /*wait for transmit interrupt flag to set which indicates TXREG is ready
                                    for another transmission*/
}

/*********************************************************************
 * Function:        char USART_ReceiveChar()
 *
 * Input:           None
 *
 * Output:          char RCREG: Regresa el dato en el registro RCREG
 *
 * Overview:        Envia los datos recibidos y los regresa an menu principal
 *
 * Note:            None
 ********************************************************************/
char USART_ReceiveChar() {

    while (RCIF == 0); /*wait for receive interrupt flag*/
    return (RCREG); /*receive data is stored in RCREG register and return to main program */
}

/*********************************************************************
 * Function:        void USART_SendString(const char *out)
 *
 * Input:           const char *out: Envia el mensaje a imprimir
 *
 * Output:          None
 *
 * Overview:        Envia el mensaje a imprimir
 *
 * Note:            None
 ********************************************************************/
void USART_SendString(const char *out) {
    while (*out != '\0') {
        USART_TransmitChar(*out);
        out++;
    }
}
