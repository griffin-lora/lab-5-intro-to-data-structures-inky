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
        stack(const stack<T, B>& rhs) : end(rhs.end), b(B{ rhs.b, rhs.b.begin(), rhs.end }) {}
        stack(stack<T, B>&& rhs) noexcept : end(rhs.end), b(std::move(rhs.b)) {
            rhs.end = rhs.b.begin();
        }

        stack<T, B>& operator=(const stack<T, B>& rhs) {
            if (this == &rhs) {
                return *this;
            }

            b.assign(b.begin(), end, rhs, rhs.b.begin(), rhs.end);
            end = rhs.end;

            return *this;
        }
        stack<T, B>& operator=(stack<T, B>&& rhs) {
            if (this == &rhs) {
                return *this;
            }

            b.assign(b.begin(), end, std::move(rhs));
            end = rhs.end;
            rhs.end = rhs.b.begin();

            return *this;
        }

        [[nodiscard]] size_t size() const noexcept {
            return b.size(b.begin(), end);
        }

        void push(const T& elem) {
            typename B::ptr new_end = b.increment(end);

            b.reserve(b.begin(), end, b.begin(), new_end);
            new (&b.access_end(new_end)) T{ elem };

            end = new_end;
        }
        
        T pop() {
            T elem = std::move(b.access_end(end));
            b.access_end(end).~T();

            end = b.decrement(end);

            return elem;
        }

        [[nodiscard]] const T& peek() const noexcept {
            return b.access_end(end);
        }
};
