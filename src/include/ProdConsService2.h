//
// Created by mano233 on 2020/11/5.
//

#ifndef UNTITLED3_PRODCONSSERVICE2_H
#define UNTITLED3_PRODCONSSERVICE2_H

#include <QObject>
#include <QtGui/QColor>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <iostream>
#include "CycleQueue.h"

using namespace std;
class ProdConsService2 : public QObject {
Q_OBJECT
    friend void consumer_worker(ProdConsService2 *ts);

    friend void producer_worker(ProdConsService2 *ts, int id);
    friend int main(int argc, char* argv[]);
public:
    explicit ProdConsService2(QObject *parent = nullptr);
    Q_INVOKABLE void lock_producer();
    Q_INVOKABLE void unlock_producer();
    Q_INVOKABLE void lock_consumer();
    Q_INVOKABLE void unlock_consumer();
    Q_INVOKABLE void start();
    Q_INVOKABLE void quit();
    ~ProdConsService2() override;
signals:
    void consumed(int front);
    void produced(int real);
    void readyConsume(int index);
    void readyProduce(int index);
    void log(QString str);
private:
    mutex mtx;
    // 条件变量是一种同步机制，要和mutex以及lock一起使用
    condition_variable produce, consume;
    bool stop_consumer = false;
    bool _quit = false;
    bool stop_producer = false;
    CycleQueue<int> *q = nullptr;
    int maxSize = 10;
    bool isStart = false;
    std::thread consumers[2], producers[2];
};

#endif //UNTITLED3_PRODCONSSERVICE2_H
