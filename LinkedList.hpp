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

            for (node* n = head; n;) {
                node* next = n->next;
				::operator delete(n);
                n = next;
			}
        }

        linked_list(const linked_list<T>& rhs) = delete;

        linked_list(ptr& begin, ptr& end, const linked_list<T>& rhs, ptr rhs_begin, ptr rhs_end) {
            (void) begin;
            (void) end;
            (void) rhs;

            for (node* n = rhs_begin; n != rhs_end; n = n->next) {
                
            }
        }

        linked_list(linked_list<T>&& rhs) noexcept : head(rhs.head) {
            rhs.head = nullptr;
        }

        linked_list<T>& operator=(const linked_list<T>& rhs) = delete;
        linked_list<T>& operator=(linked_list<T>&& rhs) = delete;

        linked_list<T>& assign(ptr& begin, ptr& end, const linked_list<T>& rhs, ptr rhs_begin, ptr rhs_end) {
            if (this == &rhs) {
                return *this;
            }

            node* new_head = nullptr;
            node* prev = nullptr;

            for (node* n = rhs_begin; n != rhs_end; n = n->next) {
                node* append = static_cast<node*>(::operator new(sizeof(node)));
                append->next = nullptr;

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

            for (node* n = head; n;) {
                node* next = n->next;
				::operator delete(n);
                n = next;
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

            for (node* n = head; n; n = n->next) {
				::operator delete(n);
			}
            
            head = rhs.head;

            rhs.head = nullptr;

            return *this;
        }

        ptr grow_increment(ptr begin, ptr end, ptr p) {
            (void) begin; (void) end;

            if (!head) {
                head = static_cast<node*>(::operator new(sizeof(node)));
                head->next = nullptr;

                return head;
            }

            if (p->next) {
                return increment(p);
            }

            p->next = static_cast<node*>(::operator new(sizeof(node)));
            p->next->next = nullptr;

            return increment(p);
        }

        ptr shrink_decrement(ptr begin, ptr end, ptr p) {
            (void) begin; (void) end;

            return decrement(p);
        }

        ptr increment(ptr p) noexcept {
            return p->next;
        }

        ptr increment(ptr p) const noexcept {
            return p->next;
        }

        ptr decrement(ptr p) noexcept {
            for (node* n = head; n; n = n->next) {
                if (n->next == p) {
                    return n;
                }
            }
            return nullptr;
        }

        ptr decrement(ptr p) const noexcept {
            for (const node* n = head; n; n = n->next) {
                if (n->next == p) {
                    return n;
                }
            }
            return nullptr;
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

        ptr begin() noexcept {
            return head;
        }

        ptr begin() const noexcept {
            return head;
        }

        ptr end() noexcept {
            node* n = head;
            for (; n; n = n->next);
            return n;
        }

        ptr end() const noexcept {
            const node* n = head;
            for (; n; n = n->next);
            return n;
        }

        size_t size(ptr begin, ptr end) const noexcept {
            if (!end) {
                return 0;
            }

            size_t s = 1;
            for (const node* n = begin; n != end; n = n->next) {
				s++;
			}
            return s;
        }
};