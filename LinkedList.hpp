#pragma once
#include <algorithm>
#include <cstddef>

template<typename T>
class linked_list {
	struct node {
		T elem;
		node* next;
	};

    node* head = nullptr;
    public:
        using ptr = node*;

        linked_list() = default;

        void destroy(ptr begin, ptr end) {
            for (node* n = begin; n != end; n = n->next) {
				n->elem.~T();
			}

            for (node* n = head; n != nullptr; n = n->next) {
				::operator delete(n);
			}
        }

        linked_list(const linked_list<T>& rhs) = delete;

        linked_list(const linked_list<T>& rhs, ptr rhs_begin, ptr rhs_end) {
            (void) rhs;

            node* prev = nullptr;

            for (node* n = rhs_begin; n != rhs_end; n = n->next) {
                node* append = ::operator new(sizeof(node));
                new (&append->elem) T{ n->elem };

                if (n == rhs_begin) {
                    head = append;
                } else {
                    prev->next = append;
                }

                prev = append;
            }
        }

        linked_list(linked_list<T>&& rhs) noexcept : head(rhs.head) {
            rhs.head = nullptr;
        }

        linked_list<T>& operator=(const linked_list<T>& rhs) = delete;
        linked_list<T>& operator=(linked_list<T>&& rhs) = delete;

        linked_list<T>& assign(ptr begin, ptr end, const linked_list<T>& rhs, ptr rhs_begin, ptr rhs_end) {
            if (this == &rhs) {
                return *this;
            }

            node* new_head = nullptr;
            node* prev = nullptr;

            for (node* n = rhs_begin; n != rhs_end; n = n->next) {
                node* append = ::operator new(sizeof(node));

                if (n == rhs_begin) {
                    new_head = append;
                } else {
                    prev->next = append;
                }

                prev = append;
            }

            for (node* n = begin; n != end; n = n->next) {
				n->elem.~T();
			}

            for (node* n = head; n != nullptr; n = n->next) {
				::operator delete(n);
			}

            head = new_head;

            node* new_n = head;
            for (node* n = rhs_begin; n != rhs_end; n = n->next) {
                new (&new_n->elem) T{ n->elem };
                new_n = new_n->next;
            }

            return *this;
        }

        linked_list<T>& assign(ptr begin, ptr end, linked_list<T>&& rhs) noexcept {
            if (this == &rhs) {
                return *this;
            }

            for (node* n = begin; n != end; n = n->next) {
				n->elem.~T();
			}

            for (node* n = head; n != nullptr; n = n->next) {
				::operator delete(n);
			}
            
            head = rhs.head;

            rhs.head = nullptr;

            return *this;
        }

        void reserve(ptr begin, ptr end, ptr new_begin, ptr new_end) {
            if (new_end - new_begin <= capacity) {
                return;
            }

            size_t new_capacity = capacity == 0 ? 1 : capacity * 2;

            T* new_data = static_cast<T*>(::operator new[](sizeof(T) * new_capacity));

            for (size_t i = begin; i < end; i++) {
                new (&new_data[(i - begin) + new_begin]) T{ std::move(data[i]) };
                data[i].~T();
            }

            ::operator delete[](data);
            
            capacity = new_capacity;
            data = new_data;
        }

        T& access_begin(ptr p) noexcept {
            return p->elem;
        }

        const T& access_begin(ptr p) const noexcept {
            return p->elem;
        }

        T& access_end(ptr p) noexcept {
            return p->elem;
        }

        const T& access_end(ptr p) const noexcept {
            return p->elem;
        }

        ptr begin() const noexcept {
            return head;
        }

        ptr end() const noexcept {
            const node* n = head;
            for (; n != nullptr; n = n->next) {

            }
            return n;
        }

        ptr increment(ptr p) const noexcept {
            return &p->next;
        }

        ptr decrement(ptr p) const noexcept {
            for (const node* n = head; n != nullptr; n = n->next) {
                if (&n->next == p) {
                    return n;
                }
            }
            return nullptr;
        }

        size_t size(ptr begin, ptr end) const noexcept {
            size_t s = 0;
            for (node* n = begin; n != end; n = n->next) {
				s++;
			}
            return s;
        }
};