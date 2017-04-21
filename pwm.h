/* 
 * File:   pwm.h
 * Author: cap
 *
 * Created on 2017?3?27?, ??12:53
 */

#ifndef PWM_H
#define	PWM_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "system.h"

#define minx 20
#define maxn 77
//#define CCP2CON
    
void initPWM();
void setDutyCycle1(unsigned char x);
void setDutyCycle2(unsigned char x);
void dutyCycleUp();
void dutyCycleSet();
void dutyCycleClear();
void dutyCycleDown();
//unsigned char getDutyCycle();
void lessLight();
void moreLight();
void lightSwitch();


unsigned char rate=45;
unsigned char lightStatus = 1;


#ifdef	__cplusplus
}
#endif

#endif	/* PWM_H */

