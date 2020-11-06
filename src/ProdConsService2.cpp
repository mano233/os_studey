#include "ProdConsService2.h"
 void consumer_worker(ProdConsService2 *ts) {
    while (!ts->quit) {
        this_thread::sleep_for(chrono::seconds (2));
        // RAII，程序运行到此block的外面（进入下一个while循环之前），资源（内存）自动释放
        unique_lock<mutex> lck(ts->mtx);
        // wait(block) consumer until q.size() != 0 is true
        ts->consume.wait(lck, [&] { return !ts->stop_consumer; });
        cout << "consumer " << this_thread::get_id() << ": " << endl;
        ts->q->pop();
        emit ts->frontChanged(ts->q->m_front);
        // nodity(wake up) producer when q.size() != maxSize is true
        ts->produce.notify_all();
    }
}

void producer_worker(ProdConsService2 *ts, int id) {
    while (!ts->quit) {
        // producer is a little faster than consumer
        this_thread::sleep_for(chrono::seconds (1));
        unique_lock<mutex> lck(ts->mtx);
        // wait(block) producer until q.size() != maxSize is true
        ts->produce.wait(lck, [&] { return !ts->stop_producer && !ts->q->isFull(); });

        cout << "-> producer " << this_thread::get_id() << ": " << "  front:" << ts->q->m_front << "rear:"
             << ts->q->m_rear
             << endl;
        ts->q->push(id);
        emit ts->realChanged(ts->q->m_rear);
        // notify(wake up) consumer when q.size() != 0 is true
        ts->consume.notify_all();
        lck.unlock();
    }
}

ProdConsService2::ProdConsService2(QObject *parent) : QObject(parent) {
    q = new CycleQueue<int>(maxSize);
    mtx.lock();
}

ProdConsService2::~ProdConsService2() {
    delete q;
}

void ProdConsService2::lock_producer() {
    stop_producer = true;
}

void ProdConsService2::unlock_producer() {
    stop_producer = false;
}

void ProdConsService2::start() {
    if(isStart){
        return;
    }
    isStart = true;
    // spawn 2 consumers and 2 producers:
    for (int i = 0; i < 1; ++i) {
        consumers[i] = std::thread(consumer_worker, this);
        producers[i] = std::thread(producer_worker, this, i + 1);
    }
    // join them back: (in this program, never join...)
    for (int i = 0; i < 1; ++i) {
        producers[i].detach();
        consumers[i].detach();
    }
    mtx.unlock();
}

void ProdConsService2::lock_consumer() {
    stop_consumer = true;
}

void ProdConsService2::unlock_consumer() {
    stop_consumer = false;
}

void ProdConsService2::stop() {
    quit = true;

}



