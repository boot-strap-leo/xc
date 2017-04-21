#include <pic18lf4620.h>

#include"pwm.h"

#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)

void initPWM(){
    PR2 = 0x4F;
    CCPR2L = 40;
    CCP2CON = 0b00011110;
    TRISCbits.RC1 = 0;
    T2CON = 0x03;
    T2CONbits.TMR2ON = 1;
}

/*
void initPWM(){
    TRISCbits.RC1 = 0;
    CCP2CON = 0b00011111;
    T2CON = 0x00;
    PR2 = 0b00011111;
    setDutyCycle2(25);
    //dutyCycleClear();
}
*/

void setDutyCycle(unsigned char x){
    CCPR2L = x;
    T2CONbits.TMR2ON = 1;
    PIR1bits.CCP1IF = 0;
    
    //while(PIR1bits.CCP1IF == 0);
}

void dutyCycleUp(){
    if(maxn - minx > rate)
        rate = rate + minx;
    else
        rate  = maxn;
    setDutyCycle(rate);
}

void dutyCycleDown(){
    if(rate > minx)
        rate = max(rate - minx, minx);
    else
        rate  = minx;
    setDutyCycle(rate);
}

void dutyCycleSet(){
    setDutyCycle(rate);
}

void dutyCycleClear(){
    //rate = 0;
    setDutyCycle(maxn + minx);
}

void moreLight(){
    if (lightStatus == 1){
        dutyCycleDown();
    }
}

void lessLight(){
    if (lightStatus == 1){
        dutyCycleUp();
    }
}

void lightSwitch(){
    if (lightStatus == 0){
        lightStatus = 1;
        dutyCycleSet();
    }
    else{
        lightStatus = 0;
        dutyCycleClear();
    }
    initQueue();
}

