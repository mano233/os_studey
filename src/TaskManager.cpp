//
// Created by mano233 on 2020/10/25.
//
#include <iostream>
#include "TaskManager.h"
#include "ProducerConsumer.h"
#include "PC.h"

TaskManager::~TaskManager() = default;
BoundedBuffer g_buffer(2);
std::mutex g_io_mutex;
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
void Producer() {
    int n = 0;
    while (n < 100000) {
        g_buffer.Produce(n);
        if ((n % 10000) == 0) {
            std::unique_lock<std::mutex> lock(g_io_mutex);
            std::cout << "Produce: " << n << std::endl;
        }
        ++n;
    }

    g_buffer.Produce(-1);
}
void Consumer() {
    std::thread::id thread_id = std::this_thread::get_id();

    int n = 0;
    do {
        n = g_buffer.Consume();
        if ((n % 10000) == 0) {
            std::unique_lock<std::mutex> lock(g_io_mutex);
            std::cout << "Consume: " << n <<'\t'<< " (" << thread_id << ")" << std::endl;
        }
    } while (n != -1);  // -1 表示缓冲已达末尾。

    // 往缓冲里再放一个 -1，这样其他消费者才能结束。
    g_buffer.Produce(-1);
}
void TaskManager::create(const char *name, size_t p, size_t cpu_time) {
    // test();
    std::vector<std::thread> threads;
    threads.emplace_back(&Producer);
    threads.emplace_back(&Consumer);
    threads.emplace_back(&Consumer);
    threads.emplace_back(&Consumer);
    for (auto& t : threads) {
        t.join();
    }
}
