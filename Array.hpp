#pragma once
#include <algorithm>
#include <cstddef>

template<typename T>
struct ArrayForwardIterator {
    using difference_type = std::ptrdiff_t;
    using value_type = T;

    T* ptr;

    ArrayForwardIterator(T* ptr) : ptr(ptr) {}
    T& operator*() const { return *ptr; }
    ArrayForwardIterator<T>& operator++() { ptr++; return *this; }
    bool operator==(const ArrayForwardIterator<T>& rhs) const { return ptr == rhs.ptr; }
};

template<typename T>
class Array {
    size_t capacity = 0;
    size_t size = 0;
    T* data = nullptr;

    void reserve(size_t new_capacity) {
        if (new_capacity <= capacity) {
            return;
        }

        T* new_data = ::operator new[](new_capacity);

        for (size_t i = 0; i < size; i++) {
            new (&new_data[i]) T{ std::move(data[i]) };
        }

        ::operator delete[](data);
        
        data = new_data;
        capacity = new_capacity;
    }
    public:
        Array() = default;
        ~Array() {
            for (size_t i = 0; i < size; i++) {
                data[i].~T();
            }

            ::operator delete[](data);
        }
        Array(const Array<T>& rhs) : capacity(rhs.capacity), size(rhs.size), data(::operator new[](rhs.capacity)) {
            for (size_t i = 0; i < size; i++) {
                new (&data[i]) T{ rhs.data[i] };
            }
        }
        Array(Array<T>&& rhs) noexcept : capacity(rhs.capacity), size(rhs.size), data(rhs.data) {
            rhs.capacity = 0;
            rhs.size = 0;
            rhs.data = nullptr;
        }
        Array<T>& operator=(const Array<T>& rhs) {
            if (this == &rhs) {
                return *this;
            }

            T* new_data = ::operator new[](rhs.capacity);
            
            for (size_t i = 0; i < size; i++) {
                data[i].~T();
            }

            ::operator delete[](data);

            capacity = rhs.capacity;
            size = rhs.size;
            data = new_data;

            for (size_t i = 0; i < size; i++) {
                new (&data[i]) T{ rhs.data[i] };
            }
        }
        Array<T>& operator=(Array<T>&& rhs) noexcept {
            if (this == &rhs) {
                return *this;
            }

            for (size_t i = 0; i < size; i++) {
                data[i].~T();
            }

            ::operator delete[](data);

            capacity = rhs.capacity;
            size = rhs.size;
            data = rhs.data;

            rhs.capacity = 0;
            rhs.size = 0;
            rhs.data = nullptr;
        }

        void reserve_back() {
            size++;
            if (size > capacity) {
                reserve(capacity == 0 ? 1 : capacity * 2);
            }
        }

        void shrink_back() noexcept {
            size--;
        }

        T& back() noexcept {
            return data[size - 1];
        }

        void resize(size_t new_size) {
            if (new_size <= size) {
                return;
            }

            if (new_size > capacity) {
                reserve(capacity == 0 ? 1 : capacity * 2);
                for (size_t i = size; i < new_size; i++) {
                    new (&data[i]) T{};
                }
            }

            size = new_size;
        }

        ArrayForwardIterator<T> begin() noexcept { return data; }
        ArrayForwardIterator<T> end() noexcept { return data + size; }

        ArrayForwardIterator<const T> begin() const noexcept { return data; }
        ArrayForwardIterator<const T> end() const noexcept { return data + size; }
};