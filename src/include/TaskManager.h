#ifndef UNTITLED3_TASKMANAGER_H
#define UNTITLED3_TASKMANAGER_H

#include <list>
#include <CycleQueue.h>
#include <queue>
#include <QObject>
#include <QDir>
#include <QTimer>
#include <QString>
using namespace std;

struct PCB{
    unsigned int      pid;        //线程id
    const    char*    name;       //线程名
    unsigned int      cpu_time;   //时间片
    unsigned int      time;
    unsigned int      p;          //优先级
};

class TaskManager: public QObject {
Q_OBJECT
signals:
    void update();
public:
    explicit TaskManager(QObject *parent = nullptr);
    ~TaskManager() override;
    void dispatch();
    void create(const char *name, unsigned int p, unsigned int cpu_time);
    void destroy(unsigned pid);
    void block(unsigned pid);
    void ready(unsigned pid);
    void wakeup(unsigned pid);
private:
    unsigned int pid;
    list<PCB> all_pcb;
    list<PCB> ready_queue;
    queue<PCB> block_queue;
    queue<PCB> dead_queue;
    queue<PCB> wake_queue;
    PCB *current;
private:

};


#endif //UNTITLED3_TASKMANAGER_H
