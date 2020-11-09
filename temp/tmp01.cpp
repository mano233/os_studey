//
// Created by mano233 on 2020/11/9.
//
#include "TaskManager.h"
int main(){
    TaskManager ts;
    for (int i = 0; i < 10; ++i) {
        ts.create("ss",11,400);
    }
    for (int i = 0; i < 100; ++i) {
        ts.dispatch();
    }
    return 0;
}