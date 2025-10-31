#pragma once
#include <algorithm>
#include <cstddef>

template<typename T, typename B>
class Stack {
    B b;
    
    public:
        [[nodiscard]] size_t size() const noexcept {
            return b.size();
        }

        void push(const T& elem) {
            b.reserve_back();
            new (&b.back()) T{ elem };
        }
        
        T pop() {
            T elem = std::move(b.back());
            b.back().~T();

            b.shrink_back();

            return elem;
        }

        [[nodiscard]] const T& top() const noexcept {
            return b.back();
        }

        [[nodiscard]] auto begin() noexcept { return b.begin(); }
        [[nodiscard]] auto end() noexcept { return b.end(); }

        [[nodiscard]] auto begin() const noexcept { return b.begin(); }
        [[nodiscard]] auto end() const noexcept { return b.end(); }
};
