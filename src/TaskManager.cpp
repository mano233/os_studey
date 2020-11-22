#include <iostream>
#include "TaskManager.h"
#include <thread>

void TaskManager::dispatch() {
    if (ready_queue->empty()) {
        return;
    }
    // 选择一个最小的
    ready_queue->sort([](PCB *a, PCB *b) {
        return a->p - b->p;
    });
    current = ready_queue->front();
    // run
    cout << "id:" << current->pid << '[' << current->time << ']' << "优先级:" << current->p << endl;
    this_thread::sleep_for(chrono::seconds(1));
    current->time--;
    current->p--;
    if (current->time == 0 || current->p == 0) {
        cout << "id:" << current->pid << "dead" << endl;
        ready_queue->pop_front();
        dead_queue->push(current);
        return;
    }
}

TaskManager::TaskManager() {
    pid = 0;
    current = nullptr;
    all_pcb = new map<int, PCB>;
    ready_queue = new list<PCB *>;
    dead_queue = new queue<PCB *>;
}

void TaskManager::create(const char *name, unsigned int p, unsigned int cpu_time) {
    PCB temp{};
    temp.pid = pid++;
    temp.state = CREATE;
    temp.cpu_time = cpu_time;
    temp.name = name;
    temp.p = p;
    temp.time = 10;
    // 加入到所有队列中
    all_pcb->insert(map<int, PCB>::value_type(temp.pid, temp));
}

TaskManager::~TaskManager() {

}

PCB TaskManager::getPcb() {
    return {};
}

void TaskManager::destroy(unsigned int pid) {
}

PCB TaskManager::popInQueue(queue<PCB> *queue, unsigned int _pid) {
    int index = 0;
    while (true) {
        if (index == queue->size()) {
            throw "not found in this queue";
        }
        PCB temp = queue->front();
        queue->pop();
        if (temp.pid == _pid) {
            return temp;
        }
        queue->push(temp);
        index++;
    }
}

void TaskManager::ready(unsigned int _pid) {
    PCB *temp = &all_pcb->find(_pid)->second;
    switch (temp->state) {
        case CREATE:
            temp->state = READY;
            ready_queue->push_back(temp);
            break;
        default:
            break;
    }
}
