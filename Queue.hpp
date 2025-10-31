#pragma once
#include <algorithm>
#include <cstddef>

template<typename T, typename B>
class Queue {
    B b;
    
    public:
        [[nodiscard]] size_t size() const noexcept {
            return b.size();
        }

        void enqueue(const T& elem) {
            b.reserve_back();
            new (&b.back()) T{ elem };
        }
        
        T dequeue() {
            T elem = std::move(b.front());
            b.front().~T();

            b.shrink_front();

            return elem;
        }

        [[nodiscard]] const T& peek() const noexcept {
            return b.back();
        }

        [[nodiscard]] auto begin() noexcept { return b.begin(); }
        [[nodiscard]] auto end() noexcept { return b.end(); }

        [[nodiscard]] auto begin() const noexcept { return b.begin(); }
        [[nodiscard]] auto end() const noexcept { return b.end(); }
};
