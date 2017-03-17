/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>        /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>       /* HiTech General Include File */
#elif defined(__18CXX)
    #include <p18cxxx.h>   /* C18 General Include File */
#endif

#if defined(__XC) || defined(HI_TECH_C)

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */

#endif

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp */

#include "I2C.h"

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/

/* i.e. uint8_t <variable_name>; */

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/


extern unsigned char valuePort;
extern unsigned int myCount;

//void interrupt myIsr(void){
//}

int main(void)
{
    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize I/O and Peripherals for application */
    InitApp();

    TRISB=0X00;
    TRISA=0XFF;
    TRISD = 0x00;
    TRISC = 0b00000000;
    PORTB=0X00;
    
    T0CON = 0b10001000;
    INTCONbits.TMR0IE = 1;
    //ei();
    
    __delay_ms(70);
    initLCD();
    unsigned char str[15] = "HELLO WORLD";
    lcdWriteString(str);
    __delay_ms(500);
    clearDisplay();
    initLCD();
    lcdWriteInt(123);
    __delay_ms(500);
    //*/
    unsigned char xpos;
    
    _addr = 0x20;
    
    //*
    while(1){
        clearDisplay();
        initLCD();
        I2CStart();
        if (positionAvailable()){
            xpos = readZ();
            if (xpos != ZX_ERROR){
                lcdWriteString("X POS: ");
                lcdWriteInt(xpos);
            }
            else{
                lcdWriteString("ZX_ERROR");
            }
        }
        //else{
        //    lcdWriteString("not available");
        //}
        I2CStop();
        __delay_ms(300);
    }
    //*/
    return 0;
}

