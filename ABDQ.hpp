#pragma once
#include <cstddef>
#include <new>
#include <stdexcept>

template<typename T>
class ABDQ {
    size_t m_capacity = 0;
    size_t m_size = 0;
    T* m_data = nullptr;

    void reserve() {
        size_t new_capacity = m_capacity == 0 ? 1 : m_capacity * 2;

        T* new_data = static_cast<T*>(::operator new[](sizeof(T) * new_capacity));
        for (size_t i = 0; i < m_size; i++) {
            new (&new_data[i]) T{ std::move(m_data[i]) };
            m_data[i].~T();
        }

        ::operator delete[](m_data);

        m_capacity = new_capacity;
        m_data = new_data;
    }

    public:
        ABDQ() = default;
        explicit ABDQ(const size_t capacity) : m_capacity(capacity), m_data(static_cast<T*>(::operator new[](sizeof(T) * capacity))) {}
        ABDQ(const ABDQ& rhs) : m_capacity(rhs.m_capacity), m_size(rhs.m_size), m_data(static_cast<T*>(::operator new[](sizeof(T) * rhs.m_capacity))) {
            for (size_t i = 0; i < rhs.m_size; i++) {
                new (&m_data[i]) T{ rhs.m_data[i] };
            }
        }
        ABDQ& operator=(const ABDQ& rhs) {
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
        ABDQ(ABDQ&& rhs) noexcept : m_capacity(rhs.m_capacity), m_size(rhs.m_size), m_data(rhs.m_data) {
            rhs.m_capacity = 0;
            rhs.m_size = 0;
            rhs.m_data = nullptr;
        }
        ABDQ& operator=(ABDQ&& rhs) noexcept {
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

            rhs.m_capacity = 0;
            rhs.m_size = 0;
            rhs.m_data = nullptr;
            
            return *this;
        }
        ~ABDQ() noexcept {
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

            // Move everything front one
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
                throw std::out_of_range("Cannot dequeue an empty queue");
            }

            T elem = std::move(m_data[0]);

            // Move everything back one
            for (size_t i = 1; i < m_size; i++) {
                m_data[i - 1] = std::move(m_data[i]);
            }

            m_data[m_size - 1].~T();

            m_size--;

            return elem;
        }

        T popBack() {
            if (m_size == 0) {
                throw std::out_of_range("Cannot pop an empty stack");
            }

            T elem = std::move(m_data[m_size - 1]);
            m_data[m_size - 1].~T();
            m_size--;

            return elem;
        }

        // Access
        [[nodiscard]] const T& front() const {
            if (m_size == 0) {
                throw std::out_of_range("Cannot peek an empty queue");
            }
            
            return m_data[0];
        }

        [[nodiscard]] const T& back() const {
            if (m_size == 0) {
                throw std::out_of_range("Cannot peek an empty stack");
            }
            
            return m_data[m_size - 1];
        }
};
