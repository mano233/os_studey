//
// Created by mano233 on 2020/11/4.
//

#ifndef UNTITLED3_CYCLEQUEUE_H
#define UNTITLED3_CYCLEQUEUE_H

#include <exception>

template<class T>
class CycleQueue {
private:
    unsigned int m_size;
    T *m_data;
public:
    int m_front;
    int m_rear;
    explicit CycleQueue(unsigned size)
            : m_size(size),
              m_front(0),
              m_rear(0) {
        m_data = new T[size];
    }

    ~CycleQueue() {
        delete[] m_data;
    }

    bool isEmpty() {
        return m_front == m_rear;
    }

    bool isFull() {
        return m_front == (m_rear + 1) % m_size;
    }

    void push(T ele) {
        if (isFull()) {
            throw "bad_exception";
        }
        m_data[m_rear] = ele;
        m_rear = (m_rear + 1) % m_size;
    }

    int size() {
        return (m_rear-m_front+m_size)% m_size;
    }

    T pop() {
        if (isEmpty()) {
            throw "bad_exception";
        }
        T tmp = m_data[m_front];
        m_front = (m_front + 1) % m_size;
        return tmp;
    }
};

#endif //UNTITLED3_CYCLEQUEUE_H
