/* 
 * File:   stack.h
 * Author: cap
 *
 * Created on 2017?3?27?, ??4:02
 */

#ifndef STACK_H
#define	STACK_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "system.h"

int my_stack[10], iter;

void initQueue();
void myQueuePush(int x);
int myQueueCheck();



#ifdef	__cplusplus
}
#endif

#endif	/* STACK_H */

