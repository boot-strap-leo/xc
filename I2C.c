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

void I2CStop() 
{ 

    SDA=0;
    __delay_ms(2);
    SCL=1; 
    __delay_ms(5);
    SDA=1; 
    __delay_ms(5);
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
    SDA=1;
    __delay_ms(3);
    SCL=1; 
    __delay_ms(5);
    SDA=0;
    __delay_ms(5);
    SCL=0; 
    __delay_ms(3);
} 

void sendByte(unsigned char c){
    //if (c != 0x21)
    //    c = 0x08;
    __delay_ms(5);
    unsigned char bit_count; 
    for (bit_count = 0; bit_count < 8; bit_count++) 
    { 
        if (c & (0x80 >> bit_count)){
            SDA = 1;
        } 
        else {
            SDA = 0;
        } 
        __delay_ms(5);
        SCL = 1; 
        __delay_ms(5);
        SCL = 0; 
        __delay_ms(6);
    } 
    __delay_ms(3);
    SDA = 1; 
    __delay_ms(3);
    SCL = 1; 
    __delay_ms(5);
    if (SDA == 1){
        ack = 0; 
        I2CSendError();
    }
    else
        ack = 1;
    __delay_ms(2);
    SCL = 0;
    __delay_ms(3); 
    SDA = 1;
    __delay_ms(3); 
} 

unsigned char receiveByte(){ 
    unsigned char retc, bit_count; 
    retc = 0; 
    SDA = 1; 
    __delay_ms(5);
    for (bit_count = 0; bit_count < 8; bit_count++) 
    { 
        __delay_ms(1);
        SCL = 0; 
        __delay_ms(5); 
        SCL = 1; 
        __delay_ms(2);
        retc = retc << 1; 
        if (SDA == 1)
            retc = retc + 1; 
        __delay_ms(2);
    } 
    SCL = 0; 
    __delay_ms(2);
    /*
    SDA = 0;
    __delay_ms(2);
    SCL = 1;
    __delay_ms(2);
    SCL = 0; 
    __delay_ms(2);
    */
    return retc; 
} 



void writeDataByte(unsigned char reg, unsigned char val){
    _addr &= 0b11111110;
    sendByte(_addr);
    sendByte(reg);
    sendByte(val);
}

unsigned char readDataByte(unsigned char reg){
    sendByte(reg);
    _addr |= 0b00000001;
    sendByte(_addr);
    //__delay_ms(10);
    //////!!!!!!!!!!!!!!!!!!FIXME
    /*/
        clearDisplay();
        initLCD();
        __delay_ms(3);
                lcdWriteString("reg: ");
                lcdWriteUI(reg);
                
        I2CStop();
        __delay_ms(500);
    //*/
    //////////////////////////////
    //__delay_ms(10);
    //reg = 0x08;
    unsigned char c;
    c = receiveByte();
    return c;
}


unsigned char readX(){
    unsigned char x_pos;
    x_pos = readDataByte(ZX_XPOS);
    
    if (ack == 0 || x_pos > MAX_X){
        I2CReceiveError();
        return ZX_ERROR;
    }
    else{
        return x_pos;
    }
}

unsigned char readZ(){
    unsigned char z_pos;
    z_pos = readDataByte(ZX_ZPOS);
    
    if (ack == 0 || z_pos > MAX_Z){
        I2CReceiveError();
        return ZX_ERROR;
    }
    else{
        return z_pos;
    }
}

bool positionAvailable(){
    unsigned char status;
    status = readDataByte(ZX_STATUS);
    if(ack == 0 || (status & 0b00000001) == 0){
        return false;
    }
    else{
        return true;
    }
}

bool gestureAvailable(){
    unsigned char status;
    status = readDataByte(ZX_STATUS);
    if(ack == 0 || (status & 0b00011100) == 0){
        return false;
    }
    else{
        return true;
    }
}

GestureType readGesture(){
    unsigned char gesture;
    gesture = readDataByte(ZX_GESTURE);
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
    speed = readDataByte(ZX_GSPEED);
    if (ack == 0){
        return ZX_ERROR;
    }
    else{
        return speed;
    }
}
