/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#elif defined(__18CXX)
    #include <p18cxxx.h>    /* C18 General Include File */
#endif

#if defined(__XC) || defined(HI_TECH_C)

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */

#endif

#include "user.h"

/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

/* <Initialize variables in user.h and insert code for user algorithms.> */

void InitApp(void)
{
    /* TODO Initialize User Ports/Peripherals/Project here */

    /* Setup analog functionality and port direction */

    /* Initialize peripherals */

    /* Configure the IPEN bit (1=on) in RCON to turn on/off int priorities */

    /* Enable interrupts */
}

void lcdEnable(void){
    lcd_E = 1;
    __delay_us(1);
    lcd_E = 0;
}

void initLCD(void){
    lcd_E = 0;
    lcd_RS = 0;
    __delay_ms(100);
    
    lcd_DB = 0b00000010;
    lcdEnable();
    lcd_DB = 0b00000010;
    lcdEnable();
    lcd_DB = 0b00001111;
    lcdEnable();
    __delay_us(70);
    
    lcd_DB = 0b00000000;
    lcdEnable();
    lcd_DB = 0b00001111;
    lcdEnable();
    __delay_us(70);
    
    lcd_DB = 0b00000000;
    lcdEnable();
    lcd_DB = 0b00000001;
    lcdEnable();
    __delay_ms(10);
    
    lcd_DB = 0b00000000;
    lcdEnable();
    lcd_DB = 0b00000011;
    lcdEnable();
    __delay_ms(30);
    
}

void lcdWriteChar(unsigned char leter){
    lcd_RS = 1;
    __delay_ms(10);
    
    
    lcd_DB = (leter >> 4) & 0b00001111;
    lcdEnable();
    __delay_ms(1);
    
    lcd_DB = leter & 0b00001111;
    lcdEnable();
    __delay_ms(1);
    
}

void lcdWriteString(unsigned char str[]){
    for(int i = 0; str[i]; i++){
        lcdWriteChar(str[i]);
    }
}

void lcdWriteUI(unsigned int num){
    char stack[20];
    int i = 0;
    do {
        stack[i++] = '0' + (num % 10);
        num /= 10;
    }
    while(num != 0);
    while(i != 0){
        lcdWriteChar(stack[--i]);
    }
}

void lcdWriteInt(unsigned char num){
    if(num < 0){
        lcdWriteChar('-');
        num = -num;
    }
    lcdWriteUI((unsigned int) num);
}

void clearDisplay(){
    //*
    
    lcd_RS = 0;
    lcd_DB = 0b00000000;
    lcdEnable();
    __delay_ms(10);
    
    lcd_DB = 0b00000001;
    lcdEnable();
    __delay_ms(10);
}

void ledOn_0(){
    LATB = LATB | 0b00000001;
}
void ledOn_1(){
    LATB = LATB | 0b00000010;
}
void ledOn_2(){
    LATB = LATB | 0b00000100;
}
void ledOn_3(){
    LATB = LATB | 0b00001000;
}

void ledOff_0(){
    LATB = LATB & 0b11111110;
}
void ledOff_1(){
    LATB = LATB & 0b11111101;
}
void ledOff_2(){
    LATB = LATB & 0b11111011;
}
void ledOff_3(){
    LATB = LATB & 0b11110111;
}

