#include <iostream>
#include "TaskManager.h"
#include <thread>

void TaskManager::dispatch() {
    ready_queue.sort([&](const PCB a,const PCB b){
        return a.p-b.p;
    });
    current = &ready_queue.front();
    // run
    cout<<current->pid<<'['<<current->time<<']'<<current->p<<endl;
    this_thread::sleep_for(chrono::seconds (1));
    current->time--;
    current->p--;
    if(current->time==0||current->p==0){
        ready_queue.pop_front();
        dead_queue.push(*current);
        return;
    }


}

TaskManager::TaskManager(QObject *parent) : QObject(parent) {
    pid=0;
    current= nullptr;
}

void TaskManager::create(const char *name, unsigned int p, unsigned int cpu_time) {
    PCB temp{pid++,name,cpu_time,10,p};
    all_pcb.push_back(temp);
    ready_queue.push_back(temp);
}

TaskManager::~TaskManager() {

}
