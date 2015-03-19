/* 
 * File:   newmain.c
 * Author: Hikaru
 *
 * Created on 2015/02/21, 16:16
 */

#include <stdio.h>
#include <stdlib.h>
#include <htc.h>

// CONFIG
#pragma config FOSC = INTOSCCLK // Oscillator Selection bits (INTOSC oscillator: CLKOUT function on RA4/OSC2/CLKOUT pin, I/O function on RA5/OSC1/CLKIN)
#pragma config WDTE = ON        // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select bit (MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown Out Detect (BOR enabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)

 #define _XTAL_FREQ 8000000

/***********************************
      ????
***********************************/
void ini_set(){
    GIE = 1;  
    PEIE = 1;  

    OSCCON = 0b01110000; 

    TRISIO = 0b00010101; //
}

/**************************************
 ?????PWM?Duty???
***************************************/
//void set_duty(unsigned int duty){
void set_duty(void){

    //CCPR1L =  duty >> 2;
    //CCP1CON = (duty << 4) | 0x0C;
    
    CCPR1L = 26;
    CCP1CON |= 0b00000000;
}
/***************************************
    PWM?????
***************************************/
void pwm_start(void){
    
    CCP1CON |= 0b00001100; 
    PR2 = 51 ;//Žü”g”
    T2CON =0b00000100;  

    while(!TMR2IF);
    TRISIO2 = 0;
}

int main(int argc, char** argv) {

     ini_set();
     pwm_start();
      set_duty();

    // TRISIO0 = 0;
     //TRISIO5 = 0;
     GP2 = 1;


    while(1){
       TRISIO2 = 0;
       GP2 = 1;

        __delay_ms(25);
        //GP0 = 0;
        TRISIO2 = 1;
        GP2 = 0;

        __delay_ms(25);

    }
    return (EXIT_SUCCESS);
}

