#include "eusart.h"
#include <pic18lf4620.h>

void initUART(){
    TRISCbits.RC7 = 1;
    TRISCbits.RC6 = 1;
    
    TXSTAbits.BRGH = 1; //low speed
    BAUDCONbits.BRG16 = 1; //8bit Baud rate Generator is used
    TXSTAbits.SYNC =0; //Asynchronous mode
    
    // frequency
    // 9600 = 32M/[4(n+1)], so n = 52.08333
    SPBRGH = 0x00;//
    SPBRG = 0x07;// Baud rate 00
        
    //interruptions
    PIE1bits.RCIE = 1; //enables the USART Receive interrupt
    INTCONbits.PEIE = 1;
    INTCONbits.GIE  = 1;

    
    RCSTAbits.CREN = 1; //Enables receiver
    TXSTAbits.TXEN = 1; //Transmit enabled
    RCSTAbits.SPEN = 1; //serial port enable
    
}

void uartTX(unsigned char data){
    TXREG = data;
    while(TRMT==0);// loop
}

unsigned char getCommand(){
    unsigned char ret = NO_COMMAND;
    if (uart_buffer[uart_head] == 'o' || uart_buffer[uart_head] == 'O'){
        uart_head = (uart_head + 1) % 100;
        if (uart_buffer[uart_head] == 'd' || uart_buffer[uart_head] == 'D')
            ret = OPEN_DOOR;
        if (uart_buffer[uart_head] == 'a' || uart_buffer[uart_head] == 'A')
            ret = OPEN_AIRCONDITION;
    }
    else if (uart_buffer[uart_head] == 'c' || uart_buffer[uart_head] == 'C'){
        uart_head = (uart_head + 1) % 100;
        if (uart_buffer[uart_head] == 'd' || uart_buffer[uart_head] == 'D')
            ret = CLOSE_DOOR;
        if (uart_buffer[uart_head] == 'a' || uart_buffer[uart_head] == 'A')
            ret = CLOSE_AIRCONDITION;
    }
    else{
        if (uart_buffer[uart_head] == 'm' || uart_buffer[uart_head] == 'M')
            ret = MORE_LIGHT;
        if (uart_buffer[uart_head] == 'l' || uart_buffer[uart_head] == 'L')
            ret = LESS_LIGHT;
        uart_head = (uart_head + 1) % 100;
        if (uart_buffer[uart_head] != 'l' && uart_buffer[uart_head] == 'L')
            ret = NO_COMMAND;
    }
    uart_head = (uart_head + 1) % 100;
    return ret;
}


void openAirCondition(){
    PORTBbits.RB7 = 1;
}

void closeAirCondition(){
    PORTBbits.RB7 = 0;
}

//*/
//*/