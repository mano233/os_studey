//
// Created by mano233 on 2020/11/5.
//

#ifndef UNTITLED3_PRODCONSSERVICE2_H
#define UNTITLED3_PRODCONSSERVICE2_H

#include <QObject>
#include <QtGui/QColor>
#include <thread>
#include <mutex>
#include <iostream>
#include "CycleQueue.h"

using namespace std;

class ProdConsService2 : public QObject {
Q_OBJECT
    Q_PROPERTY(int front READ front NOTIFY frontChanged)
    Q_PROPERTY(int real READ rear NOTIFY realChanged)

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
    Q_INVOKABLE void stop();
    ~ProdConsService2() override;
public slots:
    int front(){
        return q->m_front;
    }
    int rear(){
        return q->m_rear;
    }
signals:
    void frontChanged(int front);
    void realChanged(int real);
private:
    mutex mtx;
    // 条件变量是一种同步机制，要和mutex以及lock一起使用
    condition_variable produce, consume;
    bool stop_consumer = false;
    bool quit = false;
    bool stop_producer = false;
    CycleQueue<int> *q;
    int maxSize = 10;
    std::thread consumers[2], producers[2];
};

#endif //UNTITLED3_PRODCONSSERVICE2_H
