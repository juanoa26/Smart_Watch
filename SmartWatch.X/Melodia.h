/* 
 * File:  Melodia.h 
 * Author: Arlex Fabian Galindez-Geraldina Ivonne Carlosama-Juan Sebastian Osorio
 * Comments: Liberia que contiene las especificaciones de las notas musicales 
 *            y la declaracion de las funciones
 * Revision history: 
 */

#define nDO     0    // DO
#define nDO_    1    // DO#
#define nRE     2    // RE
#define nRE_    3    // RE#
#define nMI     4    // MI
#define nFA     5    // FA
#define nFA_    6    // FA#
#define nSOL    7    // SOL
#define nSOL_   8    // SOL#
#define nLA     9    // LA
#define nLA_    10   // LA#
#define nSI     11   // SI

int FreqNota[12]={  // retardos entre estado alto
                            // y bajo para generar las notas
15289, // DO
14430, // DO#
13620, // RE
12856, // RE#
12134, // MI
11453, // FA
10810, // FA#
10204, // SOL
9631,  // SOL#
9090,  // LA
8580,  // LA#
8099   // SI
};

void Play(int nota,int octava,int duracion);
void PlayCancion(void);
void delay_us(int nota);