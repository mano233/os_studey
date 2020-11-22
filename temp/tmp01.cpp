//
// Created by mano233 on 2020/11/9.
//
#include "TaskManager.h"
#include <thread>
int main(){
    TaskManager ts;
    for (int i = 0; i < 10; ++i) {
        ts.create("ss___ss__ss",11,400);
    }
    for (int i = 0; i < ts.all_pcb->size(); ++i) {
        ts.ready(i);
    }
    while (true){
        this_thread::sleep_for(chrono::seconds (1));
        ts.dispatch();
    }
    return 0;
}