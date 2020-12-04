#include "ProdConsService2.h"

void consumer_worker(ProdConsService2* ts) {
    while (!ts->_quit) {
        this_thread::sleep_for(chrono::seconds(3));
        unique_lock<mutex> lck(ts->mtx);
        ts->consume.wait(
            lck, [&] { return !ts->stop_consumer && !ts->q->isEmpty(); });
        cout << "consumer " << this_thread::get_id() << ": " << endl;
        int index = ts->q->m_front;
        emit ts->readyConsume(index);
        this_thread::sleep_for(chrono::milliseconds(1000));
        ts->q->pop();
        emit ts->consumed(index);
        ts->produce.notify_all();
    }
}

void producer_worker(ProdConsService2* ts, int id) {
    while (!ts->_quit) {
        this_thread::sleep_for(chrono::seconds(1));
        unique_lock lck(ts->mtx);
        ts->produce.wait(
            lck, [&] { return !ts->stop_producer && !ts->q->isFull(); });
        // cout << "-> producer " << this_thread::get_id() << ": " << "  front:"
        // << ts->q->m_front << "rear:"
        //      << ts->q->m_rear
        //      << endl;
        cout << "-> producer " << this_thread::get_id()
             << "size:" << ts->q->size() << endl;
        int index = ts->q->m_rear;
        emit ts->readyProduce(index);
        ts->q->push(id);
        this_thread::sleep_for(chrono::milliseconds(1000));
        emit ts->produced(index);
        ts->consume.notify_all();
    }
}

ProdConsService2::ProdConsService2(QObject* parent) : QObject(parent) {
    q = new CycleQueue<int>(maxSize);
    mtx.lock();
}

ProdConsService2::~ProdConsService2() {
    delete q;
    mtx.unlock();
}

void ProdConsService2::lock_producer() {
    stop_producer = true;
}

void ProdConsService2::unlock_producer() {
    stop_producer = false;
    produce.notify_all();
}

void ProdConsService2::lock_consumer() {
    stop_consumer = true;
}

void ProdConsService2::unlock_consumer() {
    stop_consumer = false;
    consume.notify_all();
}

void ProdConsService2::start() {
    if (isStart) {
        return;
    }
    isStart = true;
    for (int i = 0; i < 2; ++i) {
        consumers[i] = std::thread(consumer_worker, this);
        producers[i] = std::thread(producer_worker, this, i + 1);
    }
    for (int i = 0; i < 2; ++i) {
        producers[i].detach();
        consumers[i].detach();
    }
    mtx.unlock();
}

void ProdConsService2::quit() {
    _quit = true;
}
