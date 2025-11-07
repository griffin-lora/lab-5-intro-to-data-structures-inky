#pragma once
#include "LinkedList.hpp"

template<typename T>
class LLS {
    LinkedList<T> ll;

    public:
        LLS() = default;

        [[nodiscard]] size_t getSize() const noexcept {
            return ll.getSize();
        }

        void push(const T& elem) {
            ll.pushBack(elem);
        }

        [[nodiscard]] const T& peek() const {
            return ll.back();
        }

        T pop() {
            return ll.popBack();
        }
};
