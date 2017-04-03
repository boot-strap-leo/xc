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

#define minx 8
#define maxn 50
//#define CCP2CON
    
void initPWM();
void setDutyCycle(unsigned char x);
void dutyCycleUp();
void dutyCycleSet();
void dutyCycleClear();
void dutyCycleDown();
//unsigned char getDutyCycle();
void lessLight();
void moreLight();
void lightSwitch();

unsigned char rate=20;
unsigned char lightStatus = 1;


#ifdef	__cplusplus
}
#endif

#endif	/* PWM_H */

