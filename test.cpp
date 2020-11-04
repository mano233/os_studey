//
// Created by mano233 on 2020/11/4.
//

#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "CycleQueue.h"

using namespace std;

mutex mtx;
condition_variable produce, consume;  // 条件变量是一种同步机制，要和mutex以及lock一起使用

bool stop_consumer = false;
bool stop_producer = false;

//queue<int> q;     // shared value by producers and consumers, which is the critical section
CycleQueue<int> q(20);
int maxSize = 20;

void consumer() {
    while (!stop_consumer) {
        this_thread::sleep_for(chrono::milliseconds(1000));

        unique_lock<mutex> lck(mtx);                        // RAII，程序运行到此block的外面（进入下一个while循环之前），资源（内存）自动释放
        consume.wait(lck, [] { return !q.isEmpty(); });     // wait(block) consumer until q.size() != 0 is true

        cout << "consumer " << this_thread::get_id() << ": " << endl;
        q.pop();
        produce.notify_all();                               // nodity(wake up) producer when q.size() != maxSize is true
    }
}

void producer(int id) {
    while (!stop_producer) {
        this_thread::sleep_for(chrono::milliseconds(900));      // producer is a little faster than consumer

        unique_lock<mutex> lck(mtx);
        produce.wait(lck,
                     [] { return q.size() != maxSize; });   // wait(block) producer until q.size() != maxSize is true

        cout << "-> producer " << this_thread::get_id() << ": " << endl;
        try {
            q.push(id);
        }
        catch (const char *e) {
            cout << e << endl;
            return;
        }
        consume.notify_all();                                   // notify(wake up) consumer when q.size() != 0 is true
    }
}

int main() {
    thread consumers[2], producers[2];

    // spawn 2 consumers and 2 producers:
    for (int i = 0; i < 2; ++i) {
        //consumers[i] = thread(consumer);
        producers[i] = thread(producer, i + 1);
    }

    // join them back: (in this program, never join...)
    for (int i = 0; i < 2; ++i) {
        producers[i].join();
        //consumers[i].join();
    }

    system("pause");
    return 0;
}