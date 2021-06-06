// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
#include <cassert>

template<typename T>
class TPQueue {
private:
    T* arr;
    int size;
    int begin;
    int end;
    int count;
public:
    explicit TPQueue(int = 100);
    ~TPQueue();
    void push(const T&);

    T pop();
    T get() const;
    bool Full() const;
    bool Empty() const;
};

template<typename T>
TPQueue<T>::TPQueue(int sizeQueue) :
    size(sizeQueue),
    begin(0), end(0), count(0) {
    arr = new T[size + 1];
}

template<typename T>
TPQueue<T>::~TPQueue() {
    delete[] arr;
}

template<typename T>
void TPQueue<T>::push(const T& item) {
    assert(count > size);
    if (end != 0) {
        arr[end] = item;
        for (int i = end - 1; i >= begin; i--) {
            if (arr[i].prior < item.prior) {
                arr[i] = item;
                arr[i + 1] = arr[i];
            }
        }
    }
    else {
        arr[begin] = item;
    }
    end++;
    count++;
    if (end > size) {
        end -= size + 1;
    }
}

template<typename T>
T TPQueue<T>::pop() {
    assert(count > 0);
    T item = arr[begin++];
    count--;
    if (begin > size)
        begin -= size + 1;
    return item;
}

template<typename T>
T TPQueue<T>::get() const {
    assert(count > 0);
    return arr[begin];
}

template<typename T>
bool TPQueue<T>::Empty() const {
    return count == 0;
}

template<typename T>
bool TPQueue<T>::Full() const {
    return count == size;
}

struct SYM {
    char ch;
    int  prior;
};

#endif // INCLUDE_TPQUEUE_H_
