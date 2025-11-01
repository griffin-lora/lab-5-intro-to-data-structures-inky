#pragma once
#include <algorithm>
#include <cstddef>

template<typename T, typename B>
class stack {
    using ptr = B::ptr;
    
    ptr end;
    B b;
    
    public:
        stack() {
            b.create();
            end = b.begin();
        }
        ~stack() {
            b.destroy(b.begin(), end);
        }
        stack(const stack<T, B>& rhs) {
            ptr begin;
            b.create(begin, end, rhs.b, rhs.b.begin(), rhs.end);
        }
        stack(stack<T, B>&& rhs) noexcept : end(rhs.end) {
            b.create(std::move(rhs.b));
            rhs.end = rhs.b.begin();
        }

        stack<T, B>& operator=(const stack<T, B>& rhs) {
            if (this == &rhs) {
                return *this;
            }

            ptr begin = b.begin();
            b.assign(begin, end, rhs.b, rhs.b.begin(), rhs.end);

            return *this;
        }
        stack<T, B>& operator=(stack<T, B>&& rhs) noexcept {
            if (this == &rhs) {
                return *this;
            }

            b.assign(b.begin(), end, std::move(rhs.b));
            end = rhs.end;
            rhs.end = rhs.b.begin();

            return *this;
        }

        [[nodiscard]] size_t size() const noexcept {
            return b.size(b.begin(), end);
        }

        void push(const T& elem) {
            ptr new_end = b.grow_increment(b.begin(), end, end);
            new (&b.access_end(new_end)) T{ elem };

            end = new_end;
        }
        
        T pop() {
            T elem = std::move(b.access_end(end));
            b.access_end(end).~T();

            end = b.shrink_decrement(b.begin(), end, end);

            return elem;
        }

        [[nodiscard]] const T& peek() const noexcept {
            return b.access_end(end);
        }
};
