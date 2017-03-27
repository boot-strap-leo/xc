#include"lpque.h"

void initQueue(){
    for (int i = 0; i < 10; i++)
        my_stack[i] = 101;
}

void myQueuePush(int x){
    iter = (iter + 1) % 10;
    my_stack[iter] = x;
}
int myQueueCheck(){
    for (int i = 10; i  > 7; i--){
        //if (my_stack[(iter + i) % 10] - my_stack[(iter + i - 1) % 10] < my_stack[(iter + i) % 10] / 20)
        //    return 0;
        if (my_stack[(iter + i) % 10] > 20)
            return 0;
    }
    return 1;
}
