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
#include "pwm.h"
#include "lpque.h"
#include "servo.h"
#include "eusart.h"

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/

/* i.e. uint8_t <variable_name>; */

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/


unsigned char valuePort;
unsigned int myCount;

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
    TRISC = 0b00011000;
    PORTB=0X00;
    
    TRISCbits.RC2 = 0;
    T0CON = 0b10001000;
    INTCONbits.TMR0IE = 1;
    ei();
    
    
    __delay_ms(70);
    initLCD();
    //unsigned char str[15] = "PROGRAM BEGIN";
    //lcdWriteString(str);
    __delay_ms(500);
    
    initPWM();
    initUART();
    
    unsigned char pos;
    _addr = 0x20;
    initQueue();
        
    //setDutyCycle1(15);
        
    //*/
    while(1){
        //clearDisplay();
        //initLCD();
        //
        if(RC_FLAG == 1){
            while(uart_head != uart_tail){
                lcdWriteChar(uart_buffer[uart_head]);
                uart_head = (1 + uart_head) % 100;
            }
            RC_FLAG = 0;
        }
        pos = readZ();
        lcdWriteString(" ");
        lcdWriteInt(pos);
        myQueuePush((int)pos);
        //pos = readX();
        
        if (myQueueCheck() == 1){
            lightSwitch();
            lcdWriteString("LIGHT_SWITCH");
            __delay_ms(500);
        }
        
        // gesture sensor
        GestureType ges = readGesture();
        switch (ges){
            case RIGHT_SWIPE:
                //lcdWriteString("RIGHT_SWIPE");
                moreLight();
                break;
            case LEFT_SWIPE:
                //lcdWriteString("LEFT_SWIPE");
                lessLight();
                break;
            case UP_SWIPE:
                //lcdWriteString("UP_SWIPE");
                //lightSwitch();
                break;
            default:
                //lcdWriteString("NO_GESTURE");
                break;
        }
        
        // receive some data from uart
        if(RC_FLAG == 1){
            while(uart_head != uart_tail){
                lcdWriteChar(uart_buffer[uart_head]);
                uart_head = (1 + uart_head) % 100;
            }
            RC_FLAG = 0;
        }
        __delay_ms(80);
    }
    /*/
    /*
    // check the servo 
    while(1){
        startTurning(CLOCKWISE);
        __delay_ms(600);
        startTurning(GOMIDDLE);
        __delay_ms(600);
        startTurning(EASTERN);
        __delay_ms(600);
        startTurning(GOMIDDLE);
        __delay_ms(600);
    }
    //*/
    return 0;
}

