#pragma once
#include <algorithm>
#include <cstddef>
#include <cstdint>

template<typename T>
class linked_list {
	struct node {
		T elem;
		node* next;
	};

    node* head;
    public:
        using ptr = node*;

        linked_list() = default;
        linked_list(const linked_list<T>& rhs) = delete;
        linked_list(linked_list<T>&& rhs) = delete;
        linked_list<T>& operator=(const linked_list<T>& rhs) = delete;
        linked_list<T>& operator=(linked_list<T>&& rhs) = delete;

        void create() noexcept {
            head = nullptr;
        }

        void destroy(ptr begin, ptr end) {
            for (const node* n = begin; n; n = n->next) {
				n->elem.~T();
                if (n == end) {
                    break;
                }
            }

            for (node* n = head; n;) {
                node* next = n->next;
				::operator delete(n);
                n = next;
			}
        }

        void create(ptr& begin, ptr& end, const linked_list<T>& rhs, ptr rhs_begin, ptr rhs_end) {
            (void) rhs;

            if (!rhs_begin) {
                head = begin = end = nullptr;
                return;
            }

            uint8_t start_buf[sizeof(node)];
            node* prev = reinterpret_cast<node*>(start_buf);

            for (const node* rhs_n = rhs_begin;; rhs_n = rhs_n->next) {
                node* n = static_cast<node*>(::operator new(sizeof(node)));
                new (&n->elem) T{ rhs_n->elem };
                
                prev->next = n;
                prev = n;

                if (rhs_n == rhs_end) {
                    break;
                }
            }
            
            head = begin = reinterpret_cast<node*>(start_buf)->next;
            prev->next = nullptr;
            end = prev;
        }

        void create(linked_list<T>&& rhs) noexcept {
            head = rhs.head;
            rhs.head = nullptr;
        }

        void assign(ptr& begin, ptr& end, const linked_list<T>& rhs, ptr rhs_begin, ptr rhs_end) {
            if (this == &rhs) {
                return;
            }

            if (!rhs_begin) {
                head = begin = end = nullptr;
                return;
            }

            uint8_t start_buf[sizeof(node)];
            node* prev = reinterpret_cast<node*>(start_buf);

            for (const node* rhs_n = rhs_begin;; rhs_n = rhs_n->next) {
                node* n = static_cast<node*>(::operator new(sizeof(node)));
                new (&n->elem) T{ rhs_n->elem };
                
                prev->next = n;
                prev = n;

                if (rhs_n == rhs_end) {
                    break;
                }
            }

            for (node* n = begin; n; n = n->next) {
				n->elem.~T();

                if (n == end) {
                    break;
                }
			}

            for (node* n = head; n;) {
                node* next = n->next;
				::operator delete(n);
                n = next;
			}

            head = begin = reinterpret_cast<node*>(start_buf)->next;
            prev->next = nullptr;
            end = prev;

            return;
        }

        void assign(ptr begin, ptr end, linked_list<T>&& rhs) noexcept {
            if (this == &rhs) {
                return;
            }

            for (node* n = begin; n; n = n->next) {
				n->elem.~T();

                if (n == end) {
                    break;
                }
			}

            for (node* n = head; n;) {
                node* next = n->next;
				::operator delete(n);
                n = next;
			}
            
            head = rhs.head;

            rhs.head = nullptr;

            return;
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
            if (!begin) {
                return 0;
            }
            
            size_t s = 0;
            for (const node* n = begin;; n = n->next) {
                s++;
                if (n == end) {
                    break;
                }
            }

            return s;
        }
};