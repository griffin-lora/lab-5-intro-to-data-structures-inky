#pragma once
#include "Array.hpp"
#include <cstddef>
#include <new>
#include <stdexcept>

template<typename T>
class ABS {
    Array<T> arr;

    public:
        ABS() = default;
        explicit ABS(const size_t capacity) : arr(capacity) {}

        [[nodiscard]] size_t getSize() const noexcept {
            return arr.getSize();
        }

        [[nodiscard]] size_t getMaxCapacity() const noexcept {
            return arr.getMaxCapacity();
        }

        [[nodiscard]] T* getData() const {
            return arr.getData();
        }

        void push(const T& elem) {
            arr.pushBack(elem);
        }

        [[nodiscard]] const T& peek() const {
            return arr.back();
        }

        T pop() {
            return arr.popBack();
        }
};
