#pragma once
#include <cstddef>
#include <new>
#include <stdexcept>

template<typename T>
class ABS {
    size_t m_capacity = 0;
    size_t m_size = 0;
    T* m_data = nullptr;
    public:
        ABS() = default;
        explicit ABS(const size_t capacity) : m_capacity(capacity), m_data(static_cast<T*>(::operator new[](sizeof(T) * capacity))) {}
        ABS(const ABS& rhs) : m_capacity(rhs.m_capacity), m_size(rhs.m_size), m_data(static_cast<T*>(::operator new[](sizeof(T) * rhs.m_capacity))) {
            for (size_t i = 0; i < rhs.m_size; i++) {
                new (&m_data[i]) T{ rhs.m_data[i] };
            }
        }
        ABS& operator=(const ABS& rhs) {
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
        ABS(ABS&& rhs) noexcept : m_capacity(rhs.m_capacity), m_size(rhs.m_size), m_data(rhs.m_data) {
            rhs.m_capacity = 0;
            rhs.m_size = 0;
            rhs.m_data = nullptr;
        }
        ABS& operator=(ABS&& rhs) noexcept {
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
        ~ABS() noexcept {
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

        void push(const T& elem) {
            // If at max capacity, then reserve new memory
            if (m_size == m_capacity) {
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

            new (&m_data[m_size]) T{ elem };
            m_size++;
        }

        T peek() const {
            if (m_size == 0) {
                throw std::out_of_range("Cannot peek an empty stack");
            }
            
            return m_data[m_size - 1];
        }

        T pop() {
            if (m_size == 0) {
                throw std::out_of_range("Cannot pop an empty stack");
            }

            T elem = std::move(m_data[m_size - 1]);
            m_data[m_size - 1].~T();
            m_size--;

            return elem;
        }
};
