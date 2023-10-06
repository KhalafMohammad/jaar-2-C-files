#include <xc.h> //PIC hardware mapping
#define _XTAL_FREQ 500000                               //Used by the XC8 delay_ms(x) macro

//config bits that are part-specific for the PIC16F1829
__CONFIG(FOSC_INTOSC & WDTE_OFF & PWRTE_OFF & MCLRE_OFF & CP_OFF & CPD_OFF & 
BOREN_ON & CLKOUTEN_OFF & IESO_OFF & FCMEN_OFF);
__CONFIG(WRT_OFF & PLLEN_OFF & STVREN_OFF & LVP_OFF);
//Every program needs a `main` function
void main(void) {
//    unsigned int delay;
    OSCCON = 0b00111000;
    TRISCbits.TRISC0 = 0; //using pin as output
    TRISAbits.TRISA2 = 1; //using pin as input
    LATCbits.LATC0 = 0; //    LATC = 0; //init to zero
    ANSELAbits.ANSA2 = 0;
    #define Knop PORTAbits.RA2 //
//    delay = 11250;
    while(1){
        switch(Knop){
        case 0:
            LATCbits.LATC0 = 1; //turn on the LED by writing to the latch
            __delay_ms(250);
            LATCbits.LATC0 = 0; 
            __delay_ms(250);
            break;
    }
       
    }
    
//    while(1) continue; //sit here forever doing nothing
}
//=================================================================================================



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

void pic_init(void);
void init_osc(void);
void knopie(int count);
// ... more init function declarations here, one per each subsystem !

// ... and even more function declarations here, for module behaviors !

void main(void)
{
    #define Knop PORTAbits.RA2
    // Do all initialisation here
    int counter = 0;
    pic_init();
	
    while(1)
    {
        // Main program loop here
        switch(Knop){
        case 0:
            counter++; // counter encremenen bij elk knop druk
//            
            knopie(counter);
            break;
        }
        if(counter == 10){ //counter reset naar 0 als het 10 beriekt
            counter = 0;
        }
    }
}

/* End-of function declarations + main function --------------------- */

//>>
/* de function knopie pakt the counter die krijgt van de while loop 
 * als argument en op basis van de counter 1 of 2 tot 10 gaat de code in de
 * for loop dat repeaten  */
void knopie(int count){
    int i;
    for(i = 0; i < count; i++){
        LATCbits.LATC0 = 1; //turn on the led by writing to the latch
        __delay_ms(250);
        LATCbits.LATC0 = 0; //turn off the led
        __delay_ms(250);
    
    }
    
}

/* Init functions hereafter -- may be modularized later --------------*/

void pic_init(void)
{
    TRISCbits.TRISC0 = 0; //using led pin as output
    TRISAbits.TRISA2 = 1; //using knop pin as input
    LATCbits.LATC0 = 0; //init to zero
    ANSELAbits.ANSA2 = 0; //0 = Digital I/O. Pin is assigned to port or digital special function
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

//>>
