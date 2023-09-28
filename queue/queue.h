#pragma once

#include <cstdint>
#include <iostream>

struct Node {
    int32_t value;
    Node* next;
    explicit Node(int32_t value, Node* next = 0) : value(value), next(next) {
    }
};

class Queue {
private:
    Node* front_;
    Node* tail_;
    int32_t size_;

public:
    Queue() : front_(0), tail_(0), size_(0) {
    }

    ~Queue() {
        while (!Empty()) {
            Pop();
        }
    }

    void Push(int32_t value) {
        Node* new_node = new Node(value);
        if (Empty()) {
            front_ = new_node;
            tail_ = new_node;
        } else {
            (*tail_).next = new_node;
            tail_ = new_node;
        }
        ++size_;
    }

    void Pop() {
        if (!Empty()) {
            Node* temp = front_;
            front_ = (*front_).next;
            delete temp;
            --size_;
            if (Empty()) {
                tail_ = 0;
            }
        }
    }

    int32_t Front() const {
        return (*front_).value;
    }

    int32_t Size() const {
        return size_;
    }

    bool Empty() const {
        return size_ == 0;
    }

    void Clear() {
        while (!Empty()) {
            Pop();
        }
    }
};