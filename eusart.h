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

unsigned char RC_DATA;
unsigned char RC_FLAG;
unsigned char uart_buffer[105], uart_head = 0, uart_tail = 0;

void initUART();
void uartTX(unsigned char data);

void interrupt isr();


#ifdef	__cplusplus
}
#endif

#endif	/* EUSART_H */

