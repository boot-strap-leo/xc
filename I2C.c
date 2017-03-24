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

#include "I2C.h"
#include "user.h"

void I2CInit(){
    SSPCON1bits.SSPM0 = 0;
    SSPCON1bits.SSPM1 = 0;
    SSPCON1bits.SSPM2 = 0;
    SSPCON1bits.SSPM3 = 1;// I2C Master mode ,clock=Fosc/(4*(SSPxADD+1))
    //SSPADD1 = 0x9f;
    SSPCON1bits.SSPEN = 1;
}

void I2CStop() 
{ 
    SSPCON2bits.PEN = 1;//Stop condition
} 

void I2CSendError () 
{ 
    unsigned char i; 
    for (i=0;i<1;i++) 
    {
        ledOn_0();
        __delay_ms(60);
        ledOff_0();
        __delay_ms(60); 
    }
}

void I2CReceiveError () 
{ 
    unsigned char i; 
    for (i=0;i<1;i++) 
    {
        ledOn_1(); 
        __delay_ms(60);
        ledOff_1();
        __delay_ms(60); 
    }
}


void I2CStart() 
{ 
    SSPCON2bits.SEN = 1;;//Start condition
    while(SSPCON2bits.SEN == 1);//waiting for Start condition completed.
} 

void I2CRestart(){
    SSPCON2bits.RSEN = 1;;//Start condition
    while(SSPCON2bits.RSEN == 1);//waiting for Restart condition completed.
}

void sendByte(unsigned char c){
    PIR1bits.SSPIF = 0;
    SSPBUF = c;
    while(PIR1bits.SSPIF == 0);
} 

unsigned char receiveByte(){ 
    SSPCON2bits.RCEN = 1;
    PIR1bits.SSPIF = 0;
    while(PIR1bits.SSPIF == 0);
    unsigned char retc = SSPBUF;
    return retc;
} 



void writeDataByte(unsigned char addr, unsigned char reg){
    I2CInit();
    I2CStart();
    sendByte(addr);
    sendByte(reg);
}

unsigned char readDataByte(unsigned char addr, unsigned char reg){
    writeDataByte(addr, reg);
    I2CRestart();
    sendByte(addr | 0x01);
    unsigned char retc = receiveByte();
    return retc;
}


unsigned char readX(){
    unsigned char x_pos;
    x_pos = readDataByte(_addr, ZX_XPOS);
    
    return x_pos;
    /*
    if (ack == 0 || x_pos > MAX_X){
        I2CReceiveError();
        return ZX_ERROR;
    }
    else{
        return x_pos;
    }
    //*/
}

unsigned char readZ(){
    unsigned char z_pos;
    z_pos = readDataByte(_addr, ZX_ZPOS);
    return z_pos;
    /*/
    if (ack == 0 || z_pos > MAX_Z){
        I2CReceiveError();
        return ZX_ERROR;
    }
    else{
        return z_pos;
    }
    //*/
}

bool positionAvailable(){
    unsigned char status;
    status = readDataByte(_addr, ZX_STATUS);
    if(ack == 0 || (status & 0b00000001) == 0){
        return false;
    }
    else{
        return true;
    }
}

bool gestureAvailable(){
    unsigned char status;
    status = readDataByte(_addr, ZX_STATUS);
    if(ack == 0 || (status & 0b00011100) == 0){
        return false;
    }
    else{
        return true;
    }
}

GestureType readGesture(){
    unsigned char gesture;
    gesture = readDataByte(_addr, ZX_GESTURE);
    if (ack == 0){
        return NO_GESTURE;
    }
    switch (gesture){
        case RIGHT_SWIPE:
            return RIGHT_SWIPE;
        case LEFT_SWIPE:
            return LEFT_SWIPE;
        case UP_SWIPE:
            return UP_SWIPE;
        default:
            return NO_GESTURE;
    }
}

unsigned char readGestureSpeed(){
    unsigned char speed;
    speed = readDataByte(_addr, ZX_GSPEED);
    if (ack == 0){
        return ZX_ERROR;
    }
    else{
        return speed;
    }
}
