#pragma once
#include "Array.hpp"

template<typename T>
class ABQ {
    Array<T> arr;

    public:
        ABQ() = default;
        explicit ABQ(const size_t capacity) : arr(capacity) {}

        [[nodiscard]] size_t getSize() const noexcept {
            return arr.getSize();
        }

        [[nodiscard]] size_t getMaxCapacity() const noexcept {
            return arr.getMaxCapacity();
        }

        [[nodiscard]] T* getData() const {
            return arr.getData();
        }

        void enqueue(const T& elem) {
            arr.pushBack(elem);
        }

        [[nodiscard]] const T& peek() const {
            return arr.front();
        }

        T dequeue() {
            return arr.popFront();
        }
};
