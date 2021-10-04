//	4.3.4. Creación de melodías
//	Autores: Jesús María Corres, Carlos Ruiz Zamarreño y Cándido Bariáin
//	Pamplona, Agosto 2016

// ARCHIVOS DE DEFINICIONES

#include <pic18f4550.h>  /*Header file PIC18f4550 definitions*/
#include "config.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "LCD_caracter.h"



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
void PlayCancion();
void delay_us(int nota);


void delay_us(int nota){
    for(int i=0; i<=nota;i++ ){
        __delay_us(1);
    }
}


void play(int nota, int octava, int duracion){
     int fn;
     int mS_Transcurridos=0;
     int CiclosL=0;
    
     fn=FreqNota[nota];         // Define los retardos para generar
                                // la frecuencia de cada nota
     fn>>=(octava);             // Adapta la frecuencia
                            // a la octava actual
   
    do{
        
        TRISCbits . TRISC1 =  0;   // Genera la frecuancia
        LATCbits . LATC1 =  1 ;
        delay_us(fn);;           // con los retardos mientras
        CiclosL+=(fn);          // aumenta el contador de
                            // ciclos transcurridos
        LATCbits . LATC1 =  0 ;    // en dos partes para repartir el
         delay_us(fn);           // trabajo entre estado alto y bajo.
        CiclosL+=(fn);          //
        CiclosL+=25;            // Compensador.
       
        while(CiclosL>999){     // Se queda en el bucle mientras
                                // CiclosL sea menor a 1000 (1 mS)
           CiclosL-=1000;       // Le resta 1000 a CiclosL
           mS_Transcurridos++;  // y le suma 1 a mS_Transcurridos.
           CiclosL+=25;         // Compensador.
        }
     }while (duracion>mS_Transcurridos); // Repite el bucle hasta
                                         // que haya pasado el
                                         // tiempo indicado.
    
  
}

void PlayCancion(){

   
        play (nMI   ,4,150);
        __delay_ms (50);
        play (nMI   ,4,150);
        __delay_ms (150);
        play (nMI   ,4,150);
        __delay_ms (200);

        play (nDO   ,4,125);
        __delay_ms (50);
        play (nMI   ,4,125);
        __delay_ms (150);
        play (nSOL   ,4,200);
        __delay_ms (400);
        play (nSOL   ,3,350);
        __delay_ms (300);
        
        return;
}