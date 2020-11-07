#include <iostream>
#include "TaskManager.h"

TaskManager::~TaskManager() = default;
void TaskManager::dispatch() {
    for(int i=0;i<10;++i){
        PCB temp{};
        temp.p = i;
        ready_queue.push_back( temp);
    }
    ready_queue.sort([](PCB const &a,PCB const &b){
        return a.p-b.p;
    });
    current = ready_queue.front();
    ready_queue.pop_front();
    std::cout<<current.p<<'\n';
}

TaskManager::TaskManager(int id) {
    pcbPool = new PCBPool(20);
    PCB temp = pcbPool->get();
    temp.p = 11231;
}

void TaskManager::create(const char *name, size_t p, size_t cpu_time) {
}
