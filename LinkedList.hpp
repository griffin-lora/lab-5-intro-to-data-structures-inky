#pragma once
#include <algorithm>
#include <cstddef>

template<typename T>
class linked_list {
	struct node {
		T elem;
		node* next;
	};

    node* head;
	node* tail;
    public:
        using ptr = node*;

        linked_list() = default;

        void destroy(ptr begin, ptr end) {
            for (node* n = begin; n != end; n = n->next) {
				::operator delete(node);
			}

            for (node* n = head; n != nullptr; n = n->next) {
				::operator delete(node);
			}
        }

        linked_list(const linked_list<T>& rhs) = delete;

        linked_list(const linked_list<T>& rhs, ptr rhs_begin, ptr rhs_end) : capacity(rhs.capacity), data(static_cast<T*>(::operator new[](rhs.capacity))) {
            for (size_t i = 0; i < rhs_end - rhs_begin; i++) {
                new (&data[i]) T{ rhs.data[rhs_begin + i] };
            }
        }

        array(array<T>&& rhs) noexcept : capacity(rhs.capacity), data(rhs.data) {
            rhs.capacity = 0;
            rhs.data = nullptr;
        }

        array<T>& operator=(const array<T>& rhs) = delete;
        array<T>& operator=(array<T>&& rhs) = delete;

        array<T>& assign(ptr begin, ptr end, const array<T>& rhs, ptr rhs_begin, ptr rhs_end) {
            if (this == &rhs) {
                return *this;
            }

            T* new_data = static_cast<T*>(::operator new[](rhs.capacity));
            
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

        void reserve(ptr begin, ptr end, ptr new_begin, ptr new_end) {
            if (new_end - new_begin <= capacity) {
                return;
            }

            size_t new_capacity = capacity == 0 ? 1 : capacity * 2;

            T* new_data = static_cast<T*>(::operator new[](new_capacity));

            for (size_t i = begin; i < end; i++) {
                new (&new_data[(i - begin) + new_begin]) T{ std::move(data[i]) };
            }

            ::operator delete[](data);
            
            data = new_data;
            capacity = new_capacity;
        }

        T& access(ptr p) noexcept {
            return data[p];
        }

        const T& access(ptr p) const noexcept {
            return data[p];
        }

        ptr begin() const noexcept {
            return 0;
        }

        ptr end() const noexcept {
            return capacity;
        }

        ptr increment(ptr p) const noexcept {
            return p + 1;
        }

        ptr decrement(ptr p) const noexcept {
            return p - 1;
        }

        size_t size(ptr begin, ptr end) const noexcept {
            return end - begin;
        }

        // array_forward_iterator<T> begin() noexcept { return data; }
        // array_forward_iterator<T> end() noexcept { return data + size; }

        // array_forward_iterator<const T> begin() const noexcept { return data; }
        // array_forward_iterator<const T> end() const noexcept { return data + size; }
};