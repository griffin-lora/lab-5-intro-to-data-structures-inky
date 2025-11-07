#pragma once
#include "LinkedList.hpp"

template<typename T>
class LLQ {
    LinkedList<T> ll;

    public:
        LLQ() = default;

        [[nodiscard]] size_t getSize() const noexcept {
            return ll.getSize();
        }

        void enqueue(const T& elem) {
            ll.pushBack(elem);
        }

        [[nodiscard]] const T& peek() const {
            return ll.front();
        }

        T dequeue() {
            return ll.popFront();
        }
};
