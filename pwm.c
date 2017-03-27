#include <pic18lf4620.h>

#include"pwm.h"

#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)

void initPWM(){
    TRISCbits.RC1 = 0;
    CCP2CON = 0b00011111;
    T2CON = 0x00;
    PR2 = 0b00110011;
    setDutyCycle(25);
    //dutyCycleClear();
}
void setDutyCycle(unsigned char x){
    CCPR2L = x;
    T2CONbits.TMR2ON = 1;
    PIR1bits.CCP1IF = 0;
    //while(PIR1bits.CCP1IF == 0);
}

void dutyCycleUp(){
    rate = rate + minx;
    rate  = min(49, rate);
    setDutyCycle(rate);
}

void dutyCycleDown(){
    rate = rate - minx;
    rate  = max(0, rate);
    setDutyCycle(rate);
}

void dutyCycleSet(){
    setDutyCycle(rate);
}

void dutyCycleClear(){
    //rate = 0;
    setDutyCycle(0);
}

void moreLight(){
    if (lightStatus == 1){
        dutyCycleUp();
    }
}

void lessLight(){
    if (lightStatus == 1){
        dutyCycleDown();
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