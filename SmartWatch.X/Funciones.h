/* 
 * File:  Funciones.h 
 * Author: Arlex Fabian Galindez-Geraldina Ivonne Carlosama-Juan Sebastian Osorio
 * Comments: Liberia que contiene las especificaciones de las variables utilizadas en Temperatura.c,
 *          Sensor_luz.c, asi como la declaracion de funciones, leds y los emoticones que se mostraran
 * Revision history: 
 */
// This is a guard condition so that contents of this file are not included
// more than once.  

#include <xc.h>
#include <pic18f4550.h>  /*Header file PIC18f4550 definitions*/
#include "config.h"
#include "LCD_caracter.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>


#define LED_GREEN LATE0
#define LED_GREEN1 LATE1
#define LED_GREEN2 LATE2
#define ON 1
#define OFF 0

float tempar;
float luz;
char Stemp[20];
char Sluz[20];
uint16_t result;
char i;
char data_in;

unsigned char character1[ 8 ] = {0x0e, 0x1f, 0x1f, 0x0e, 0x00, 0x0a, 0x0a, 0x00}; /*  Value for Rainy day  */
unsigned char character2[ 8 ] = {0x15, 0x0e, 0x11, 0x11, 0x0e, 0x15, 0x00, 0x00}; /*  Value for Sunny day  */
unsigned char character3[ 8 ] = {0x00, 0x08, 0x16, 0x1f, 0x1f, 0x16, 0x08, 0x00}; /*  Value for Cloudy day  */

uint16_t ReadADC(void);/*Lee el sensor de Temperatura*/
uint16_t ReadLUZ(void);/*Lee el sensor de Luz*/
int Estados(void);/*Se encarga de determinar el estado al que se debe ir*/
void Sunny_State(void);/*Estado para dias soleados*/
void Cloudy_State(void);/*Estado para dias nublados*/
void Rainy_State(void);/*Estado de dias lluviosos*/
void Alarm_Status(void);/*Estado para sonar la alarma*/
