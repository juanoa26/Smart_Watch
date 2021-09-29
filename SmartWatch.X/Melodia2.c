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




#ifndef  MUSIC_NOTES
#define  MUSIC_NOTES

//            NOTE                 FREQUENCY
//                     Octave0  Octave1  Octave2  Octave3
const long C_NOTE[4] = {262, 523, 1047, 2093};
const long Db_NOTE[4] = {277, 554, 1109, 2217};
const long D_NOTE[4] = {294, 587, 1175, 2349};
const long Eb_NOTE[4] = {311, 622, 1245, 2489};
const long E_NOTE[4] = {330, 659, 1329, 2637};
const long F_NOTE[4] = {349, 698, 1397, 2794};
const long Gb_NOTE[4] = {370, 740, 1480, 2960};
const long G_NOTE[4] = {392, 784, 1568, 3136};
const long Ab_NOTE[4] = {415, 831, 1661, 3322};
const long A_NOTE[4] = {440, 880, 1760, 3520};
const long Bb_NOTE[4] = {466, 923, 1865, 3729};
const long B_NOTE[4] = {494, 988, 1976, 3951};
#endif

int FreqNota[12] = {// retardos entre estado alto
    // y bajo para generar las notas
    15289, // DO
    14430, // DO#
    13620, // RE
    12856, // RE#
    12134, // MI
    11453, // FA
    10810, // FA#
    10204, // SOL
    9631, // SOL#
    9090, // LA
    8580, // LA#
    8099 // SI
};


void Play(int nota, int octava, int duracion);
void PlayCancion();
void delay_ms(int x);
void delay_us(int x);

void do_delay(int ms_delay, int num_ms, int us_delay, int num_us) {
    int i;

    for (i = 0; i < num_ms; i++) {
        delay_us(250);
        delay_us(ms_delay);
    }

    for (i = 0; i < num_us; i++) {
        delay_ms(250);
        delay_ms(us_delay);
    }

}

void delay_ms(int x) {
    for (int i = 0; i < x; i++) {
        __delay_ms(1);
    }
}

void delay_us(int x) {
    for (int i = 0; i < x; i++) {
        __delay_us(1);
    }
}

void play(long frequency, long duration) {
    long total_delay_time; // in microseconds
    long total_ms_delay_time, total_us_delay_time;
    int num_us_delays, num_ms_delays, ms_delay_time, us_delay_time;
    long num_periods;

    total_delay_time = (1000000 / frequency) / 2 - 10; // calculate total delay time (10 for error)

    total_ms_delay_time = total_delay_time / 1000; // total delay time of ms
    num_ms_delays = total_ms_delay_time / 250; // number of 250ms delays needed
    ms_delay_time = total_ms_delay_time % 250; // left over ms delay time needed

    total_us_delay_time = total_delay_time % 1000; // total delay time of us (ms already acounted for)
    num_us_delays = total_us_delay_time / 250; // number of 250us delays needed
    us_delay_time = total_us_delay_time % 250; // left over us delay time needed

    num_periods = ((long) duration * 1000) / (1000000 / frequency);

    while ((num_periods--) != 0) {
        do_delay(ms_delay_time, num_ms_delays, us_delay_time, num_us_delays);
        TRISCbits . TRISC1 = 0; // Genera la frecuancia
        LATCbits . LATC1 = 1;
        do_delay(ms_delay_time, num_ms_delays, us_delay_time, num_us_delays);
        LATCbits . LATC1 = 0;
    }

    return;
}

void PlayCancion() {

    play(C_NOTE[0], 1000);
    play(D_NOTE[0], 1000);
    play(E_NOTE[0], 1000);
    play(F_NOTE[0], 1000);
    play(G_NOTE[0], 1000);
    play(A_NOTE[0], 1000);
    play(B_NOTE[0], 1000);

    play(B_NOTE[0], 800);
    play(C_NOTE[1], 600);
    play(D_NOTE[1], 500);
    play(D_NOTE[1], 500);
    play(C_NOTE[1], 500);
    play(B_NOTE[0], 500);

    play(A_NOTE[0], 500);
    play(G_NOTE[0], 500);
    play(G_NOTE[0], 500);
    play(A_NOTE[0], 600);
    play(B_NOTE[0], 500);
    play(B_NOTE[0], 700);
    play(A_NOTE[0], 400);
    play(A_NOTE[0], 600);


    play(B_NOTE[0], 800);
    play(C_NOTE[1], 600);
    play(D_NOTE[1], 500);
    play(D_NOTE[1], 500);
    play(C_NOTE[1], 500);
    play(B_NOTE[0], 500);

    play(A_NOTE[0], 500);
    play(G_NOTE[0], 500);
    play(G_NOTE[0], 500);
    play(A_NOTE[0], 600);
    play(B_NOTE[0], 500);
    play(A_NOTE[0], 700);
    play(G_NOTE[0], 400);
    play(G_NOTE[0], 600);



    //delay_ms(100);

    play(A_NOTE[0], 800);
    play(B_NOTE[0], 500);
    play(G_NOTE[0], 500);
    play(A_NOTE[0], 800);
    play(B_NOTE[0], 300);
    play(C_NOTE[1], 300);
    play(B_NOTE[0], 300);
    play(G_NOTE[0], 400);

    play(A_NOTE[0], 500);
    play(B_NOTE[0], 300);
    play(C_NOTE[1], 300);
    play(B_NOTE[0], 300);
    play(A_NOTE[0], 500);
    play(G_NOTE[0], 500);
    play(A_NOTE[0], 500);
    play(D_NOTE[0], 500);



    //delay_ms(100);

    play(B_NOTE[0], 800);
    play(C_NOTE[1], 700);
    play(D_NOTE[1], 500);
    play(D_NOTE[1], 500);
    play(C_NOTE[1], 500);
    play(B_NOTE[0], 500);

    play(A_NOTE[0], 500);
    play(G_NOTE[0], 500);
    play(G_NOTE[0], 500);
    play(A_NOTE[0], 600);
    play(B_NOTE[0], 500);
    play(A_NOTE[0], 700);
    play(G_NOTE[0], 300);
    play(G_NOTE[0], 600);


    delay_ms(2000);



}