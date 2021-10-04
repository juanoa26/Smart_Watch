//	4.3.4. Creación de melodías
//	Autores: Jesús María Corres, Carlos Ruiz Zamarreño y Cándido Bariáin
//	Pamplona, Agosto 2016

// ARCHIVOS DE DEFINICIONES

#include "Funciones.h"
#include "LCD_caracter.h"
#include "Melodia.h"

/*********************************************************************
 * Function:        void delay_us(int nota)
 *
 * Input:           int nota: Entero que determina la duracion del retardo
 *
 * Output:          None
 *
 * Overview:        Determina la duracion del retardo en funcion del 
 *                  entero recibido
 *
 * Note:            None
 ********************************************************************/

void delay_us(int nota){
    for(int i=0; i<=nota;i++ ){
        __delay_us(1);
    }
}

/*********************************************************************
 * Function:        void play(int nota, int octava, int duracion)
 *
 * Input:           int nota: Entero que determina la duracion del retardo
 *                  int octava: Entero para determinar la nota a tocar
 *                  int duracion: El tiempo que se tocara la nota determinada
 *
 * Output:          None
 *
 * Overview:        Se encarga de configurar el parlante donde sonara la melodia
 *                  ademas de determinar la frecuencia y duracion de la misma
 *
 * Note:            None
 ********************************************************************/


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

/*********************************************************************
 * Function:        void PlayCancion(
 *
 * Input:           None
 *
 * Output:          None
 *
 * Overview:        Contiene la melodia que se va a tocar
 *
 * Note:            None
 ********************************************************************/

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