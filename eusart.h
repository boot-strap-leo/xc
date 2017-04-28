/* 
 * File:   eusart.h
 * Author: cap
 *
 * Created on 2017?4?24?, ??4:28
 */

#ifndef EUSART_H
#define	EUSART_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#define NO_COMMAND              0x00
#define OPEN_DOOR               0x01
#define CLOSE_DOOR              0x02
#define MORE_LIGHT              0x03
#define LESS_LIGHT              0x04
#define OPEN_AIRCONDITION       0x05
#define CLOSE_AIRCONDITION      0x06

unsigned char RC_DATA;
unsigned char RC_FLAG;
unsigned char uart_buffer[105], uart_head = 0, uart_tail = 0;

void initUART();
void uartTX(unsigned char data);

void interrupt isr();
void openAirCondition();
void closeAirCondition();

unsigned char getCommand();

#ifdef	__cplusplus
}
#endif

#endif	/* EUSART_H */

