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
    TPQueue();
    ~TPQueue();
    void push(const T&);
    T pop();
    T get() const;
    bool Full() const;
    bool Empty() const;
};

template<typename T>
TPQueue<T>::TPQueue() :
    size(100),
    begin(0), end(0), count(0) {
    arr = new T[size + 1];
}
template<typename T>
TPQueue<T>::~TPQueue() {
    delete[] arr;
}

template<typename T>
void TPQueue<T>::push(const T& item) {
    assert(count < size);
    if (count != 0) {
        for (int i = end - 1; i >= begin; i--) {
            if (arr[i].prior >= item.prior) {
                arr[i + 1] = item;
                break;
            }
            if (arr[i].prior < item.prior) {
                arr[i + 1] = arr[i];
            }
            if (begin == i) {
                arr[i] = item;
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
bool TPQueue<T>::Full() const {
    return count == size;
}
template<typename T>
bool TPQueue<T>::Empty() const {
    return count == 0;
}
struct SYM {
    char ch;
    int  prior;
};

#endif // INCLUDE_TPQUEUE_H_
