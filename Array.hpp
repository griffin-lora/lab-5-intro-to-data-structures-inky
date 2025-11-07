#pragma once
#include <cstddef>
#include <new>
#include <stdexcept>

template<typename T>
class Array {
    size_t m_capacity = 1;
    size_t m_size = 0;
    T* m_data = nullptr;

    void set_capacity(size_t new_capacity) {
        T* new_data = static_cast<T*>(::operator new[](sizeof(T) * new_capacity));
        for (size_t i = 0; i < m_size; i++) {
            new (&new_data[i]) T{ std::move(m_data[i]) };
            m_data[i].~T();
        }

        ::operator delete[](m_data);

        m_capacity = new_capacity;
        m_data = new_data;
    }

    void reserve() {
        set_capacity(m_capacity * 2);
    }

    void shrink() {
        set_capacity(m_capacity == 1 ? 1 : m_capacity / 2);
    }

    public:
        Array() : m_data(static_cast<T*>(::operator new[](sizeof(T)))) {}
        explicit Array(const size_t capacity) : m_capacity(capacity), m_data(static_cast<T*>(::operator new[](sizeof(T) * capacity))) {}
        Array(const Array& rhs) : m_capacity(rhs.m_capacity), m_size(rhs.m_size), m_data(static_cast<T*>(::operator new[](sizeof(T) * rhs.m_capacity))) {
            for (size_t i = 0; i < rhs.m_size; i++) {
                new (&m_data[i]) T{ rhs.m_data[i] };
            }
        }
        Array& operator=(const Array& rhs) {
            if (this == &rhs) {
                return *this;
            }

            T* new_data = static_cast<T*>(::operator new[](sizeof(T) * rhs.m_capacity));
            for (size_t i = 0; i < rhs.m_size; i++) {
                new (&new_data[i]) T{ rhs.m_data[i] };
            }
            
            for (size_t i = 0; i < m_size; i++) {
                m_data[i].~T();
            }

            ::operator delete[](m_data);

            m_capacity = rhs.m_capacity;
            m_size = rhs.m_size;
            m_data = new_data;
            
            return *this;
        }
        Array(Array&& rhs) noexcept : m_capacity(rhs.m_capacity), m_size(rhs.m_size), m_data(rhs.m_data) {
            rhs.m_capacity = 1;
            rhs.m_size = 0;
            rhs.m_data = nullptr;
        }
        Array& operator=(Array&& rhs) noexcept {
            if (this == &rhs) {
                return *this;
            }

            for (size_t i = 0; i < m_size; i++) {
                m_data[i].~T();
            }

            ::operator delete[](m_data);

            m_capacity = rhs.m_capacity;
            m_size = rhs.m_size;
            m_data = rhs.m_data;

            rhs.m_capacity = 1;
            rhs.m_size = 0;
            rhs.m_data = nullptr;
            
            return *this;
        }
        ~Array() noexcept {
            for (size_t i = 0; i < m_size; i++) {
                m_data[i].~T();
            }

            ::operator delete[](m_data);
        }

        [[nodiscard]] size_t getSize() const noexcept {
            return m_size;
        }

        [[nodiscard]] size_t getMaxCapacity() const noexcept {
            return m_capacity;
        }

        [[nodiscard]] T* getData() const {
            return m_data;
        }

        void pushFront(const T& elem) {
            if (m_size == m_capacity) {
                reserve();
            }
            
            if (m_size > 0) {
                new (&m_data[m_size]) T{};
            }

            // Move everything forward one
            for (size_t i = m_size; i > 0; i--) {
                m_data[i] = std::move(m_data[i - 1]);
            }

            m_data[0] = elem;
            m_size++;
        }

        void pushBack(const T& elem) {
            if (m_size == m_capacity) {
                reserve();
            }

            new (&m_data[m_size]) T{ elem };
            m_size++;
        }

        T popFront() {
            if (m_size == 0) {
                throw std::runtime_error("Cannot dequeue an empty queue");
            }

            T elem = std::move(m_data[0]);

            // Move everything back one
            for (size_t i = 1; i < m_size; i++) {
                m_data[i - 1] = std::move(m_data[i]);
            }

            m_data[m_size - 1].~T();

            m_size--;

            if (m_size < m_capacity / 2) {
                shrink();
            }

            return elem;
        }

        T popBack() {
            if (m_size == 0) {
                throw std::runtime_error("Cannot pop an empty stack");
            }

            T elem = std::move(m_data[m_size - 1]);
            m_data[m_size - 1].~T();
            m_size--;

            if (m_size < m_capacity / 2) {
                shrink();
            }

            return elem;
        }

        // Access
        [[nodiscard]] const T& front() const {
            if (m_size == 0) {
                throw std::runtime_error("Cannot peek an empty queue");
            }
            
            return m_data[0];
        }

        [[nodiscard]] const T& back() const {
            if (m_size == 0) {
                throw std::runtime_error("Cannot peek an empty stack");
            }
            
            return m_data[m_size - 1];
        }
};
