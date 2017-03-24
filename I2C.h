/* 
 * File:   I2C.h
 * Author: cap
 *
 * Created on March 13, 2017, 3:47 PM
 */

#ifndef I2C_H
#define	I2C_H

#ifdef	__cplusplus
extern "C" {
#endif

    
#include "system.h"

unsigned char ack;

#define nop() asm("nop")
#define SCL LATC3 
#define SDA LATC4

/* Acceptable ZX Sensor version */
#define ZX_MODEL_VER        0x01

/* Acceptable ZX Sensor register map */
#define ZX_REG_MAP_VER      0x01

/* ZX Sensor register addresses */
#define ZX_STATUS           0x00
#define ZX_DRE              0x01
#define ZX_DRCFG            0x02
#define ZX_GESTURE          0x04
#define ZX_GSPEED           0x05
#define ZX_DCM              0x06
#define ZX_XPOS             0x08
#define ZX_ZPOS             0x0A
#define ZX_LRNG             0x0C
#define ZX_RRNG             0x0E
#define ZX_REGVER           0xFE
#define ZX_MODEL            0xFF

/* ZX Sensor bit names */
#define DRE_RNG             0
#define DRE_CRD             1
#define DRE_SWP             2
#define DRE_HOVER           3
#define DRE_HVG             4
#define DRE_EDGE            5
#define DRCFG_POLARITY      0
#define DRCFG_EDGE          1
#define DRCFG_FORCE         6
#define DRCFG_EN            7

/* ZX Sensor UART message headers */
#define ZX_UART_END         0xFF
#define ZX_UART_RANGES      0xFE
#define ZX_UART_X           0xFA
#define ZX_UART_Z           0xFB
#define ZX_UART_GESTURE     0xFC
#define ZX_UART_ID          0xF1

/* Constants */
#define ZX_ERROR            0xFF
#define MAX_X               240
#define MAX_Z               240

/* Enumeration for possible gestures */
typedef enum GestureType {
    RIGHT_SWIPE = 0x01,
    LEFT_SWIPE = 0x02,
    UP_SWIPE = 0x03,
    NO_GESTURE = 0xFF
} GestureType;

/* Enumeration for possible interrupt enables */
typedef enum InterruptType {
    NO_INTERRUPTS = 0x00,
    POSITION_INTERRUPTS = 0x01,
    GESTURE_INTERRUPTS = 0x02,
    ALL_INTERRUPTS = 0x03
} InterruptType;

void I2CStop();
void I2CStart();
void I2CShowError();
void sendByte(unsigned char c);
unsigned char receiveByte();
unsigned char readX();
void writeDataByte(unsigned char addr, unsigned char reg);
unsigned char readDataByte(unsigned char addr, unsigned char reg);
unsigned char readX();
unsigned char readZ();
bool positionAvailable();
bool gestureAvailable();
GestureType readGesture();
unsigned char readGestureSpeed();

unsigned char _addr;

#ifdef	__cplusplus
}
#endif

#endif	/* I2C_H */

