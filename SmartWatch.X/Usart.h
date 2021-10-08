/* 
 * File:   Estados.c
 * Author: Arlex Fabian Galindez-Geraldina Ivonne Carlosama-Juan Sebastian Osorio
 *
 * Created on 4 de octubre de 2021, 10:59 AM
 */


// This is a guard condition so that contents of this file are not included
// more than once.  
void USART_Init(long);/*Inicializa el Bluetooth*/
void USART_TransmitChar(char);/*Trasnmite los datos*/
void USART_SendString(const char *);/*Envia el mensaje a imprimir*/
char USART_ReceiveChar(void);/*Recibe los datos*/

