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



void play(int nota, int octava, int duracion){
     int fn;
     int mS_Transcurridos=0;
     int CiclosL=0;
    
     fn=FreqNota[nota];         // Define los retardos para generar
                                // la frecuencia de cada nota
     fn>>=(octava);             // Adapta la frecuencia
                            // a la octava actual
   
    do{
        
        TRISDbits . TRISD2 =  0;   // Genera la frecuancia
        LATDbits . LATD2 =  1 ;
        MSdelay(fn);;           // con los retardos mientras
        CiclosL+=(fn);          // aumenta el contador de
                            // ciclos transcurridos
        LATDbits . LATD2 =  0 ;    // en dos partes para repartir el
         MSdelay(fn);           // trabajo entre estado alto y bajo.
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
        MSdelay (50);
        play (nMI   ,4,150);
        MSdelay (150);
        play (nMI   ,4,150);
        MSdelay (200);

        play (nDO   ,4,125);
        MSdelay (50);
        play (nMI   ,4,125);
        MSdelay (150);
        play (nSOL   ,4,200);
        MSdelay (400);
        play (nSOL   ,3,350);
        MSdelay (300);
        
        for(int i=0;i<2;i++){
        play (nDO   ,4,200);
        MSdelay (200);
        play (nSOL   ,3,150);
        MSdelay (200);
        play (nMI   ,3,200);
        MSdelay (150);
        play (nLA   ,3,200);
        MSdelay (150);
        play (nSI   ,3,150);
        MSdelay (50);
        play (nLA_   ,3,100);
        MSdelay (40);
        play (nLA   ,3,100);
        MSdelay (60);
        play (nSOL   ,3,120);
        MSdelay (100);
        
        play (nMI   ,4,110);
        MSdelay (100);
        play (nSOL   ,4,110);
        MSdelay (110);
        play (nLA   ,4,150);
        MSdelay (100);
        play (nFA   ,4,110);
        MSdelay (100);
        play (nSOL   ,4,110);
        MSdelay (150);
        play (nMI   ,4,110);
        MSdelay (100);
        play (nDO   ,4,110);
        MSdelay (50);
        play (nRE   ,4,125);
        MSdelay (50);
        play (nSI   ,3,125);
        MSdelay (200);
        }
        
        for(int i=0;i<2;i++){
        MSdelay (100);
        play (nSOL   ,4,150);
        MSdelay (120);
        play (nFA_   ,4,125);
        MSdelay (50);
        play (nFA   ,4,125);
        MSdelay (50);
        play (nRE_   ,4,125);
        MSdelay (100);
        play (nMI   ,4,150);
        MSdelay (100);
        
        play (nSOL_   ,3,125);
        MSdelay (100);
        play (nLA   ,3,125);
        MSdelay (100);
        play (nDO   ,4,150);
        MSdelay (150);
        
        play (nLA   ,3,125);
        MSdelay (100);
        play (nDO   ,4,125);
        MSdelay (100);
        play (nRE   ,4,150);
        MSdelay (150);
        
        play (nSOL   ,4,150);
        MSdelay (120);
        play (nFA_   ,4,125);
        MSdelay (50);
        play (nFA   ,4,125);
        MSdelay (50);
        play (nRE_   ,4,125);
        MSdelay (100);
        play (nMI   ,4,150);
        MSdelay (100);
        
        play (nDO   ,5,200);
        MSdelay (50);
        play (nDO   ,5,150);
        MSdelay (50);
        play (nDO   ,5,150);
        MSdelay (300);
        
        play (nSOL   ,4,150);
        MSdelay (120);
        play (nFA_   ,4,125);
        MSdelay (50);
        play (nFA   ,4,125);
        MSdelay (50);
        play (nRE_   ,4,125);
        MSdelay (100);
        play (nMI   ,4,150);
        MSdelay (100);
        
        play (nSOL_   ,3,125);
        MSdelay (100);
        play (nLA   ,3,125);
        MSdelay (100);
        play (nDO   ,4,150);
        MSdelay (150);
        
        play (nLA   ,3,125);
        MSdelay (100);
        play (nDO   ,4,125);
        MSdelay (100);
        play (nRE   ,4,150);
        MSdelay (200);
        
        play (nRE_   ,4,200);
        MSdelay (150);
        play (nRE   ,4,200);
        MSdelay (150);
        play (nDO   ,4,200);
        MSdelay (250);
        }
        
        play (nDO   ,4,130);
        MSdelay (50);
        play (nDO   ,4,130);
        MSdelay (100);
        play (nDO   ,4,200);
        MSdelay (130);
        play (nDO   ,4,150);
        MSdelay (100);
        play (nRE   ,4,130);
        MSdelay (50);
        play (nMI   ,4,150);
        MSdelay (50);
        play (nDO   ,4,125);
        MSdelay (50);
        play (nLA   ,3,125);
        MSdelay (100);
        play (nSOL   ,3,200);
        MSdelay (200);
        play (nDO   ,4,130);
        MSdelay (50);
        
        play (nDO   ,4,130);
        MSdelay (100);
        play (nDO   ,4,200);
        MSdelay (100);
        play (nDO   ,4,125);
        MSdelay (100);
        play (nRE   ,4,125);
        MSdelay (100);
        play (nMI   ,4,200);
        MSdelay (400);

        play (nDO   ,4,130);
        MSdelay (50);
        play (nDO   ,4,130);
        MSdelay (100);
        play (nDO   ,4,200);
        MSdelay (130);
        play (nDO   ,4,150);
        MSdelay (100);
        play (nRE   ,4,130);
        MSdelay (50);
        play (nMI   ,4,150);
        MSdelay (50);
        play (nDO   ,4,125);
        MSdelay (50);
        play (nLA   ,3,125);
        MSdelay (100);
        play (nSOL   ,3,200);
        MSdelay (200);
        
        play (nMI   ,4,150);
        MSdelay (50);
        play (nMI   ,4,150);
        MSdelay (150);
        play (nMI   ,4,150);
        MSdelay (200);
        play (nDO   ,4,125);
        MSdelay (50);
        play (nMI   ,4,125);
        MSdelay (150);
        play (nSOL   ,4,200);
        MSdelay (400);
        
        for(int i=0;i<2;i++){
        play (nDO   ,4,200);
        MSdelay (200);
        play (nSOL   ,3,150);
        MSdelay (200);
        play (nMI   ,3,200);
        MSdelay (150);
        play (nLA   ,3,200);
        MSdelay (150);
        play (nSI   ,3,150);
        MSdelay (50);
        play (nLA_   ,3,100);
        MSdelay (40);
        play (nLA   ,3,100);
        MSdelay (60);
        play (nSOL   ,3,120);
        MSdelay (100);
        
        play (nMI   ,4,110);
        MSdelay (100);
        play (nSOL   ,4,110);
        MSdelay (110);
        play (nLA   ,4,150);
        MSdelay (100);
        play (nFA   ,4,110);
        MSdelay (100);
        play (nSOL   ,4,110);
        MSdelay (150);
        play (nMI   ,4,110);
        MSdelay (100);
        play (nDO   ,4,110);
        MSdelay (50);
        play (nRE   ,4,125);
        MSdelay (50);
        play (nSI   ,3,125);
        MSdelay (200);
        }
        
        play (nMI   ,4,125);
        MSdelay (50);
        play (nDO   ,4,125);
        MSdelay (70);
        play (nSOL   ,3,230);
        MSdelay (150);
        play (nSOL_   ,3,150);
        MSdelay (150);
        play (nLA   ,3,125);
        MSdelay (50);
        play (nFA   ,4,125);
        MSdelay (50);
        play (nFA   ,4,125);
        MSdelay (50);
        play (nLA   ,3,200);
        MSdelay (100);
        play (nSI   ,3,220);
        MSdelay (100);
        play (nLA   ,4,150);
        MSdelay (100);
        play (nLA   ,4,150);
        MSdelay (100);
        play (nLA   ,4,150);
        MSdelay (50);
        play (nSOL   ,4,125);
        MSdelay (50);
        play (nFA   ,4,150);
        MSdelay (100);
        play (nMI   ,4,200);
        MSdelay (100);
        play (nDO   ,4,150);
        MSdelay (100);
        play (nLA   ,3,125);
        MSdelay (65);
        play (nSOL   ,3,200);
        MSdelay (200);
        
        
        play (nMI   ,4,125);
        MSdelay (50);
        play (nDO   ,4,125);
        MSdelay (70);
        play (nSOL   ,3,230);
        MSdelay (150);
        play (nSOL_   ,3,150);
        MSdelay (150);
        play (nLA   ,3,125);
        MSdelay (50);
        play (nFA   ,4,125);
        MSdelay (50);
        play (nFA   ,4,125);
        MSdelay (50);
        play (nLA   ,3,200);
        MSdelay (100);
        play (nSI   ,3,220);
        MSdelay (100);
        play (nFA   ,4,150);
        MSdelay (100);
        play (nFA   ,4,150);
        MSdelay (100);
        play (nFA   ,4,150);
        MSdelay (50);
        play (nMI   ,4,150);
        MSdelay (100);
        play (nRE   ,4,125);
        MSdelay (65);
        play (nDO   ,4,200);
        MSdelay (200);
        
        
        play (nDO   ,4,130);
        MSdelay (50);
        play (nDO   ,4,130);
        MSdelay (100);
        play (nDO   ,4,200);
        MSdelay (130);
        play (nDO   ,4,150);
        MSdelay (100);
        play (nRE   ,4,130);
        MSdelay (50);
        play (nMI   ,4,150);
        MSdelay (50);
        play (nDO   ,4,125);
        MSdelay (50);
        play (nLA   ,3,125);
        MSdelay (100);
        play (nSOL   ,3,200);
        MSdelay (200);
        play (nDO   ,4,130);
        MSdelay (50);
        
        play (nDO   ,4,130);
        MSdelay (100);
        play (nDO   ,4,200);
        MSdelay (100);
        play (nDO   ,4,125);
        MSdelay (100);
        play (nRE   ,4,125);
        MSdelay (100);
        play (nMI   ,4,200);
        MSdelay (400);

        play (nDO   ,4,130);
        MSdelay (50);
        play (nDO   ,4,130);
        MSdelay (100);
        play (nDO   ,4,200);
        MSdelay (130);
        play (nDO   ,4,150);
        MSdelay (100);
        play (nRE   ,4,130);
        MSdelay (50);
        play (nMI   ,4,150);
        MSdelay (50);
        play (nDO   ,4,125);
        MSdelay (50);
        play (nLA   ,3,125);
        MSdelay (100);
        play (nSOL   ,3,200);
        MSdelay (200);
        
        play (nMI   ,4,150);
        MSdelay (50);
        play (nMI   ,4,150);
        MSdelay (150);
        play (nMI   ,4,150);
        MSdelay (200);
        play (nDO   ,4,125);
        MSdelay (50);
        play (nMI   ,4,125);
        MSdelay (150);
        play (nSOL   ,4,200);
        MSdelay (400);
        
        
    
}