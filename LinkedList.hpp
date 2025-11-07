#pragma once
#include <cstddef>
#include <iostream>
#include <new>
#include <stdexcept>

template<typename T>
class LinkedList {
	struct Node {
		T data;
		Node* prev = nullptr;
		Node* next = nullptr;
	};

    Node* m_head = nullptr;
	Node* m_tail = nullptr;

    void copy(const LinkedList& rhs, Node*& head, Node*& tail) {
        Node* prev = nullptr;

        for (Node* node = rhs.m_head; node; node = node->next) {
            Node* append = new Node{ T{ node->data } };

            if (!prev) {
                head = append;
            } else {
                prev->next = append;
            }

            append->prev = prev;
            prev = append;
        }

        if (prev) {
            prev->next = nullptr;
            tail = prev;
        }
    }

    void destroy() noexcept {
        for (Node* node = m_head; node;) {
            Node* next = node->next;
            delete node;
            node = next;
        }
    }

    public:
        LinkedList() = default;
        LinkedList(const LinkedList& rhs) {
            copy(rhs, m_head, m_tail);
        }
        LinkedList& operator=(const LinkedList& rhs) {
            if (this == &rhs) {
                return *this;
            }

            Node* head;
            Node* tail;
            copy(rhs, head, tail);

            destroy();

            m_head = head;
            m_tail = tail;
            
            return *this;
        }
        LinkedList(LinkedList&& rhs) noexcept : m_head(rhs.m_head), m_tail(rhs.m_tail) {
            rhs.m_head = nullptr;
            rhs.m_tail = nullptr;
        }
        LinkedList& operator=(LinkedList&& rhs) noexcept {
            if (this == &rhs) {
                return *this;
            }

            destroy();

            m_head = rhs.m_head;
            m_tail = rhs.m_tail;
            rhs.m_head = nullptr;
            rhs.m_tail = nullptr;
            
            return *this;
        }
        ~LinkedList() noexcept {
            destroy();
        }

        [[nodiscard]] size_t getSize() const noexcept {
            size_t n = 0;
            for (Node* node = m_head; node; node = node->next) {
                n++;
            }
            return n;
        }

        [[nodiscard]] unsigned int getCount() const noexcept {
            return static_cast<unsigned int>(getSize());
        }

        void pushFront(const T& elem) {
            Node* node = new Node{ T{ elem } };

            if (!m_head) {
                m_head = node;
                m_tail = node;
                return;
            }

            m_head->prev = node;
            node->next = m_head;
            m_head = node;
        }

        void addHead(const T& elem) {
            pushFront(elem);
        }

        void pushBack(const T& elem) {
            Node* node = new Node{ T{ elem } };

            if (!m_head) {
                m_head = node;
                m_tail = node;
                return;
            }

            m_tail->next = node;
            node->prev = m_tail;
            m_tail = node;
        }

        void addTail(const T& elem) {
            pushBack(elem);
        }

        T popFront() {
            if (!m_head) {
                throw std::runtime_error("Cannot dequeue an empty queue");
            }

            T elem = std::move(m_head->data);

            Node* head = m_head->next;
            delete m_head;
            m_head = head;

            if (m_head) {
                m_head->prev = nullptr;
            } else {
                m_tail = nullptr;
            }
            
            return elem;
        }

        bool removeHead() {
            if (!m_head) {
                return false;
            }

            popFront();
            return true;
        }

        T popBack() {
            if (!m_head) {
                throw std::runtime_error("Cannot dequeue an empty queue");
            }

            T elem = std::move(m_tail->data);

            Node* tail = m_tail->prev;
            delete m_tail;
            m_tail = tail;

            if (m_tail) {
                m_tail->next = nullptr;
            } else {
                m_head = nullptr;
            }
            
            return elem;
        }

        bool removeTail() {
            if (!m_head) {
                return false;
            }

            popBack();
            return true;
        }

        // Access
        [[nodiscard]] const T& front() const {
            if (!m_head) {
                throw std::runtime_error("Cannot peek an empty queue");
            }
            
            return m_head->data;
        }

        [[nodiscard]] const T& back() const {
            if (!m_head) {
                throw std::runtime_error("Cannot peek an empty stack");
            }
            
            return m_tail->data;
        }

        Node* getHead() {
            return m_head;
        }

        const Node* getHead() const {
            return m_head;
        }

        Node* getTail() {
            return m_tail;
        }

        const Node* getTail() const {
            return m_tail;
        }

        void clear() {
            destroy();
            m_head = nullptr;
            m_tail = nullptr;
        }

        void printForward() {
            for (Node* node = m_head; node; node = node->next) {
                std::cout << node << '\n';
            }
        }

        void printReverse() {
            for (Node* node = m_tail; node; node = node->prev) {
                std::cout << node << '\n';
            }
        }
};
