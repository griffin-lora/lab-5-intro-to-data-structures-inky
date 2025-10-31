#pragma once
#include <algorithm>
#include <cstddef>

template<typename T>
struct array_forward_iterator {
    using difference_type = std::ptrdiff_t;
    using value_type = T;

    T* ptr;

    array_forward_iterator(T* ptr) : ptr(ptr) {}
    T& operator*() const { return *ptr; }
    array_forward_iterator<T>& operator++() { ptr++; return *this; }
    bool operator==(const array_forward_iterator<T>& rhs) const { return ptr == rhs.ptr; }
};

template<typename T>
class array {
    size_t capacity = 0;
    T* data = nullptr;
    public:
        using ptr = size_t;

        array() = default;
        array(const array<T>& rhs, ptr rhs_begin, ptr rhs_end) : capacity(rhs.capacity), data(::operator new[](rhs.capacity)) {
            for (size_t i = 0; i < rhs_end - rhs_begin; i++) {
                new (&data[i]) T{ rhs.data[rhs_begin + i] };
            }
        }

        array<T>& operator=(const array<T>& rhs) = delete;
        array<T>& operator=(array<T>&& rhs) = delete;

        array(array<T>&& rhs) noexcept : capacity(rhs.capacity), data(rhs.data) {
            rhs.capacity = 0;
            rhs.data = nullptr;
        }

        array<T>& assign(ptr begin, ptr end, const array<T>& rhs, ptr rhs_begin, ptr rhs_end) {
            if (this == &rhs) {
                return *this;
            }

            T* new_data = ::operator new[](rhs.capacity);
            
            for (size_t i = begin; i < end; i++) {
                data[i].~T();
            }

            ::operator delete[](data);

            capacity = rhs.capacity;
            data = new_data;

            for (size_t i = 0; i < rhs_end - rhs_begin; i++) {
                new (&data[i]) T{ rhs.data[rhs_begin + i] };
            }
        }

        array<T>& assign(ptr begin, ptr end, array<T>&& rhs) noexcept {
            if (this == &rhs) {
                return *this;
            }

            for (size_t i = begin; i < end; i++) {
                data[i].~T();
            }

            ::operator delete[](data);

            capacity = rhs.capacity;
            data = rhs.data;

            rhs.capacity = 0;
            rhs.size = 0;
            rhs.data = nullptr;
        }

        void reserve(ptr begin, ptr end, size_t new_capacity, ptr new_begin, ptr new_end) {
            (void) new_end;
        }

        void reserve(ptr begin, ptr end, ptr new_begin, ptr new_end) {
            if (new_end - new_begin <= capacity) {
                return;
            }

            size_t new_capacity = capacity == 0 ? 1 : capacity * 2;

            T* new_data = ::operator new[](new_capacity);

            for (size_t i = begin; i < end; i++) {
                new (&new_data[(i - begin) + new_begin]) T{ std::move(data[i]) };
            }

            ::operator delete[](data);
            
            data = new_data;
            capacity = new_capacity;
        }

        T& front(ptr begin, ptr end) noexcept {
            (void) end;

            return data[begin];
        }

        T& back(ptr begin, ptr end) noexcept {
            (void) begin;

            return data[end];
        }

        // array_forward_iterator<T> begin() noexcept { return data; }
        // array_forward_iterator<T> end() noexcept { return data + size; }

        // array_forward_iterator<const T> begin() const noexcept { return data; }
        // array_forward_iterator<const T> end() const noexcept { return data + size; }
};