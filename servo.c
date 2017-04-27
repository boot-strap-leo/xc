#include "servo.h"
#include "user.h"
#include <pic18lf4620.h>

void startTurning(unsigned char dirct){
    servo_direction = dirct;
    servo_counter = 0;
}

void servoInteruptions(){
    //*
    if(onCounter != 0 || offCounter != 0){
        if(onCounter != 0){
            onCounter--;
            PORTCbits.RC2 = 1;
        }
        else{
            offCounter--;
            PORTCbits.RC2 = 0;
        }
        return;
    }
    if(servo_counter < COUNTLIMIT){
        servo_counter++;
        if(servo_direction == CLOCKWISE){
            onCounter = 5;
            offCounter = 15;
        }
        else    if(servo_direction == EASTERN){
            onCounter = 11;
            offCounter = 9;
        }
        else{
            onCounter = 8;
            offCounter = 12;
        }
    }
    /*
    else{
        servo_counter = 0;
        servo_direction = NOTURNING;
    }
    //*/
}