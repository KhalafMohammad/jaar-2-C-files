



/***********************************************************************
 * Universal startup code structure for new and simple projects
 * 
 * PIC   : 16F1829
 * Board : PICkit 3 Low Pin Count Demo Board (PK3LPCDB) or breadboard
 * Date  : A long time ago, in a galaxy far...far away
 * 
 **********************************************************************/

#include <xc.h>                 // PIC hardware mapping
// This auto-determines (using sub-includes, #pragma's, and IDE-
// controlled data sources) that 
// /opt/microchip/xc8/v<compiler_version>/pic/include/proc/pic16f1829.h
// should be included ...
// As for Windoze, `/opt' is probably somewhere in the user's AppData 
// folder ...

#define _XTAL_FREQ      500000  // Used by the XC8 delay_ms(x) macro

// CONFIG WORD 1 @ flash program memory location 0x8007
// For acceptable values use both datasheet and this file:
// /opt/microchip/xc8/v<compiler_version>/docs/pic_chipinfo.html

#pragma config FOSC     = 0x4   // xor INTOSC (name from IDE database)
#pragma config WDTE     = 0x0   // OFF
#pragma config PWRTE    = 0x1   // OFF
#pragma config MCLRE    = OFF   // etc.
#pragma config CP       = OFF   // text is the most readable option
#pragma config CPD      = OFF
#pragma config BOREN    = ON
#pragma config CLKOUTEN = OFF
#pragma config IESO     = OFF
#pragma config FCMEN    = OFF

// XOR (not recommended)
// #pragma config CONFIG1 = 0b (00)00 1111 1010 0100
// i.e. (don't do this)
// #pragma config CONFIG1 = 0x0FA4

// CONFIG WORD 2 @ flash program memory location 0x8008
#pragma config WRT      = OFF
#pragma config PLLEN    = OFF
#pragma config STVREN   = OFF
#pragma config BORV     = LO
//#pragma config DEBUG    = OFF   // Pre-processor short-circuits !
#pragma config LVP      = OFF

/* Hardware / state naming scheme ------------------------------------*/

// ...

/* End-of hardware / state naming scheme -----------------------------*/

//>>

/* Forward function declarations + main function hereafter -----------*/

#define LED1 LATCbits.LATC0
#define LED2 LATCbits.LATC1
#define LED3 LATCbits.LATC2
#define LED4 LATCbits.LATC3

#define ON 1
#define OFF 0

void pic_init(void);
void init_osc(void);

// ... more init function declarations here, one per each subsystem !

// ... and even more function declarations here, for module behaviors !

void main(void)
{
    
    // Do all initialisation here
    pic_init();
	
    while(1)
    {
        // Main program loop here
        __delay_us(5);                              //wait for ADC charging cap to settle
        GO = 1;
        while (GO) continue;                        //wait for conversion to be finished
        if(ADRESH >> 4)                       //grab the top 4 MSbs
            LED1 = ON;
        else if (ADRESH >> 3)
            LED1 = OFF;
            LED2 = OFF;
            LED3 = OFF;
            LED4 = OFF;
        
        if(ADRESH >> 5)
            LED2 = ON;
        else if (ADRESH >> 4)
            LED3 = OFF;
            LED4 = OFF;
            
        if(ADRESH >> 6)
            LED3 = ON;
        else if (ADRESH >> 5)
            LED4 = OFF;
        
        
        if (ADRESH >> 7)
            LED4 = ON;
        
    }
}

/* End-of function declarations + main function --------------------- */

//>>


/* Init functions hereafter -- may be modularized later --------------*/

void pic_init(void)
{
    OSCCON = 0b00111000;                            //500KHz clock speed
    TRISC = 0;                                      //all LED pins are outputs

                                                    //setup ADC
    TRISAbits.TRISA4 = 1;                           //Potentiamtor is connected to RA4...set as input
    ANSELAbits.ANSA4 = 1;                           //analog
    ADCON0 = 0b00001101;                            //select RA4 as source of ADC and enable the module (AN3)
    ADCON1 = 0b00010000;                            //left justified - FOSC/8 speed - Vref is Vdd
    init_osc();
}

void init_osc(void)
{
    // Do it like this, it's easily compared to the datasheet:
    // System Clock Select (SCS)
    OSCCONbits.SCS      = 0b00;     // Clk determined by FOSC in Conf-1
    // Internal Resistor-Capacitor Frequency select (IRCF)
    OSCCONbits.IRCF     = 0b0111;   // 500 kHz clock speed
    // Software Phase-Locked Loop ENable (SPLLEN)
    OSCCONbits.SPLLEN   = 0b0;      // 4 x Phase-Locked Loop disabled
    // XOR (Don't do this, it's unmaintainable)
    // OSCCON = 0b00111000;
}

/* End-of Init functions -------------------------------------------- */

//>>

/* Utility functions per module hereafter -- may be modularized later!*/

// ...

/* End-of utility functions per module -------------------------------*/

//>>

/* Interrupt Service Routine (ISR) hereafter -- keep with main module!*/

void __interrupt() isr();

/* End-of Interrupt Service Routine (ISR) ----------------------------*/

// =========================================================================================

/**
 *******************************************************************
 * Lesson 4 - "Analog to Digital"
 *
 * This shows how to read the A2D converter and display the
 * High order parts on the 4 bit LED display.
 * The pot on the Low Pin Count Demo board varies the voltage
 * coming in on in A0.
 *
 * The A2D is referenced to the same Vdd as the device, which
 * is nominally is 5V.  The A2D returns the ratio of the voltage
 * on Pin RA0 to 5V.  The A2D has a resolution of 10 bits, with 1023 
 * representing 5V and 0 representing 0V.
 *
 *
 * The top four MSbs of the ADC are mirrored onto the LEDs. Rotate the potentiometer
 * to change the display.
 *
 *  PIC: 16F1829
 *  Compiler: XC8 v1.00
 *  IDE: MPLABX v1.10
 *
 *  Board: PICkit 3 Low Pin Count Demo Board
 *  Date: 6.1.2012
 *
 * *******************************************************************
 * See Low Pin Count Demo Board User's Guide for Lesson Information*
 * ******************************************************************
 */

#include <xc.h>                                    //PIC hardware mapping
#define _XTAL_FREQ 500000                           //Used by the XC8 delay_ms(x) macro

//config bits that are part-specific for the PIC16F1829
__CONFIG(FOSC_INTOSC & WDTE_OFF & PWRTE_OFF & MCLRE_OFF & CP_OFF & CPD_OFF & BOREN_ON & CLKOUTEN_OFF & IESO_OFF & FCMEN_OFF);
__CONFIG(WRT_OFF & PLLEN_OFF & STVREN_OFF & LVP_OFF);

    /* -------------------LATC-----------------
     * Bit#:  -7---6---5---4---3---2---1---0---
     * LED:   ---------------|DS4|DS3|DS2|DS1|-
     *-----------------------------------------
     */
#define LED1 LATCbits.LATC0
#define LED2 LATCbits.LATC1
#define LED3 LATCbits.LATC2
#define LED4 LATCbits.LATC3

#define ON 1
#define OFF 0



void main(void) {
    OSCCON = 0b00111000;                            //500KHz clock speed
    TRISC = 0;                                      //all LED pins are outputs

                                                    //setup ADC
    TRISAbits.TRISA4 = 1;                           //Potentiamtor is connected to RA4...set as input
    ANSELAbits.ANSA4 = 1;                           //analog
    ADCON0 = 0b00001101;                            //select RA4 as source of ADC and enable the module (AN3)
    ADCON1 = 0b00010000;                            //left justified - FOSC/8 speed - Vref is Vdd

    while (1) {
        __delay_us(5);                              //wait for ADC charging cap to settle
        GO = 1;
        while (GO) continue;                        //wait for conversion to be finished
        if(ADRESH >> 4)                       //grab the top 4 MSbs
            LED1 = ON;
        else if (ADRESH >> 3)
            LED1 = OFF;
            LED2 = OFF;
            LED3 = OFF;
            LED4 = OFF;
        
        if(ADRESH >> 5)
            LED2 = ON;
        else if (ADRESH >> 4)
            LED3 = OFF;
            LED4 = OFF;
            
        if(ADRESH >> 6)
            LED3 = ON;
        else if (ADRESH >> 5)
            LED4 = OFF;
        
        
        if (ADRESH >> 7)
            LED4 = ON;
        
            
            
            
        
        
        
        
        
//        if (ADRES >= 300)
//            LED1 = ON;
//        else if (ADRES <= 500)
//            LED1 = OFF;
//        
//        if (ADRES >= 16100)
//            LED2 = ON;
//        else if (ADRES <= 16300)
//            LED2 = OFF;
//        
//        if (ADRES >= 32200)
//            LED3 = ON;
//        else if (ADRES <= 32400)
//            LED3 = OFF;
//        
//        if (ADRES >= 64800)
//            LED4 = ON;
//        else if (ADRES <= 70000)
//            LED4 = OFF;
        
    }



}