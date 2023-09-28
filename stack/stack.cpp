#include "stack.h"

#include <stdexcept>

Node::Node(int32_t value, Node* previous) : value(value), previous(previous) {
}

Stack::Stack() : head_(0), size_(0) {
}

Stack::~Stack() {
    Clear();
}

void Stack::Push(int32_t value) {
    auto node = new Node(value, head_);
    head_ = node;
    ++size_;
}

void Stack::Pop() {
    Node* nodelete = head_;
    head_ = nodelete->previous;
    delete nodelete;
    --size_;
}

int32_t Stack::Top() const {
    return head_->value;
}

int32_t Stack::Size() const {
    return size_;
}

void Stack::Clear() {
    while (!Empty()) {
        Pop();
    }
}

bool Stack::Empty() const {
    return head_ == 0;
}