#ifndef UNTITLED3_TASKMANAGER_H
#define UNTITLED3_TASKMANAGER_H

#include <list>
#include <queue>

using namespace std;

struct PCB{
    unsigned        pid;
    const char*     name;
    unsigned        cpu_time;
    unsigned        time;
    unsigned        p;
};

class PCBPool{
private:
    queue<PCB> pool;
public:
    explicit PCBPool(size_t size){
        for(unsigned i=0;i<size;++i)
            pool.push(PCB{i});
    }
    PCB get(){
        PCB temp = pool.front();
        pool.pop();
        return temp;
    }
    PCB set(PCB temp);
};

class TaskManager {
public:
    explicit TaskManager(int id);
    ~TaskManager();
    void dispatch();
    void create(const char* name,size_t p,size_t cpu_time);
    void destroy(unsigned pid);
    void block(unsigned pid);
    void ready(unsigned pid);
    void wakeup(unsigned pid);
private:
    PCBPool *pcbPool;
    list<PCB> all_pcb;
    list<PCB> ready_queue;
    queue<PCB> block_queue;
    queue<PCB> dead_queue;
    queue<PCB> wake_queue;
    PCB current{};
private:

};


#endif //UNTITLED3_TASKMANAGER_H
