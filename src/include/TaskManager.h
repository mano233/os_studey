#ifndef UNTITLED3_TASKMANAGER_H
#define UNTITLED3_TASKMANAGER_H

#include <list>
#include <CycleQueue.h>
#include <queue>
#include <stack>
#include <map>
// #include <QObject>
// #include <QDir>
// #include <QTimer>
// #include <QString>

#define PCB_POOL_SIZE 255

using namespace std;

enum STATUS{
    CREATE,
    RUN,
    BLOCK,
    READY,
    S_BLOCK,
    S_READY,
    DEAD,
};
struct PCB{
    int      pid;                 //线程id
    const    char*    name;       //线程名
    unsigned int      cpu_time;   //时间片
    unsigned int      time;
    unsigned int      p;          //优先级
    STATUS state;                 //线程状态
};

class TaskManager {
public:
    explicit TaskManager();
    ~TaskManager();
    void dispatch();
    void create(const char *name, unsigned int p, unsigned int cpu_time);
    void destroy(unsigned _pid);
    void block(unsigned _pid);
    void ready(unsigned _pid);
    void wakeup(unsigned _pid);
    PCB getPcb();
    map<int,PCB> *all_pcb;
    list<PCB*> *ready_queue;
private:
    PCB popInQueue(queue<PCB> *queue,unsigned int _pid);
    int pid=0;

    queue<PCB*> *block_queue{};
    queue<PCB*> *dead_queue;
    queue<PCB*> *wake_queue{};
    PCB *current;
private:

};


#endif //UNTITLED3_TASKMANAGER_H
