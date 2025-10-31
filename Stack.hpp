#pragma once
#include <algorithm>
#include <cstddef>

template<typename T, typename B>
class stack {
    B::ptr end;
    B b;
    
    public:
        stack() {
            end = b.begin();
        }
        ~stack() {
            b.destroy(b.begin(), end);
        }
        stack(const stack<T, B>& rhs) : end(rhs.end), b{rhs.b, rhs.b.begin(), rhs.end} {}
        stack(stack<T, B>&& rhs) noexcept : end(rhs.end), b{std::move(rhs.b)} {
            rhs.end = rhs.b.begin();
        }

        stack<T, B>& operator=(const stack<T, B>& rhs) {
            end = rhs.end;
            b = B{rhs.b, rhs.b.begin(), rhs.end};
        }
        stack<T, B>& operator=(stack<T, B>&& rhs) {
            end = rhs.end;
            b = std::move(rhs.b);
            rhs.end = rhs.b.begin();
        }

        [[nodiscard]] size_t size() const noexcept {
            return b.size(b.begin(), end);
        }

        void push(const T& elem) {
            typename B::ptr new_end = b.increment(end);

            b.reserve(b.begin(), end, b.begin(), new_end);
            new (&b.access(end)) T{ elem };

            end = new_end;
        }
        
        T pop() {
            T elem = std::move(b.access(end));
            b.access(end--).~T();

            return elem;
        }

        [[nodiscard]] const T& peek() const noexcept {
            return b.access(b.decrement(end));
        }
};
