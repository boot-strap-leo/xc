/* 
 * File:   servo.h
 * Author: cap
 *
 * Created on 2017?4?20?, ??4:59
 */

#ifndef SERVO_H
#define	SERVO_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include "system.h"

#define EASTERN 1
#define GOMIDDLE 2
#define CLOCKWISE 3
#define NOTURNING 0
#define COUNTLIMIT 30

unsigned servo_direction;

unsigned onCounter;
unsigned offCounter;
unsigned servo_counter;

void servoInteruptions();
void startTurning(unsigned dirct);

#ifdef	__cplusplus
}
#endif

#endif	/* SERVO_H */

