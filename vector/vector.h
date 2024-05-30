#pragma once
#include <algorithm>
#include <iostream>
template <class T>
class Vector {
public:
    Vector() {
        size_ = 0;
        capacity_ = 0;
        arr_ = nullptr;
    }

    explicit Vector(size_t size) : Vector() {
        size_ = size;
        capacity_ = size;
        if (size_) {
            arr_ = new T[capacity_];
            for (size_t i = 0; i < size; ++i) {
                arr_[i] = 0;
            }
        }
    }
    Vector(std::initializer_list<T> list) : Vector() {
        size_ = list.size();
        capacity_ = size_;
        if (size_) {
            arr_ = new T[capacity_];
            size_t idx = 0;
            for (auto& el : list) {
                arr_[idx++] = el;
            }
        }
    }
    Vector(const Vector& other) {
        size_ = other.size_;
        capacity_ = other.capacity_;
        arr_ = new T[capacity_];
        for (size_t i = 0; i < size_; ++i) {
            arr_[i] = other.arr_[i];
        }
    }
    Vector(Vector&& other) {
        size_ = other.size_;
        capacity_ = other.capacity_;
        arr_ = other.arr_;
        other.size_ = 0;
        other.capacity_ = 0;
        other.arr_ = nullptr;
    }
    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] arr_;
            size_ = other.size_;
            capacity_ = other.capacity_;
            arr_ = new T[capacity_];
            for (size_t i = 0; i < size_; ++i) {
                arr_[i] = other.arr_[i];
            }
        }
        return *this;
    }
    Vector& operator=(Vector&& other) noexcept {
        if (this != &other) {
            Swap(other);
        }
        return *this;
    }
    ~Vector() {
        delete[] arr_;
    }
    void Swap(Vector& other) {
        std::swap(arr_, other.arr_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
    }
    T& operator[](size_t idx) {
        return *(arr_ + idx);
    }
    const T& operator[](size_t idx) const {
        return *(arr_ + idx);
    }
    size_t Size() const {
        return size_;
    }
    size_t Capacity() const {
        return capacity_;
    }
    void Reserve(size_t new_capacity) {
        if (new_capacity <= capacity_) {
            return;
        }
        auto tmp = new T[new_capacity];
        if (arr_) {
            std::copy(arr_, arr_ + size_, tmp);
        }
        delete[] arr_;
        arr_ = tmp;
        capacity_ = new_capacity;
    }
    void PopBack() {
        --size_;
    }
    void Clear() {
        size_ = 0;
    }
    void PushBack(T el) {
        if (size_ == capacity_) {
            Reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        }
        arr_[size_] = el;
        ++size_;
    }
    struct Iterator : std::iterator<std::random_access_iterator_tag, int> {
        explicit Iterator(int* ptr = nullptr) : ptr_(ptr){};

        int& operator*() {
            return *ptr_;
        }

        int* operator->() {
            return ptr_;
        }

        Iterator& operator++() {
            ++ptr_;
            return *this;
        }

        Iterator operator++(int) {
            Iterator tmp = *this;
            ++ptr_;
            return tmp;
        }
        Iterator& operator--() {
            --ptr_;
            return *this;
        }

        Iterator operator--(int) {
            Iterator tmp = *this;
            --ptr_;
            return tmp;
        }
        Iterator& operator+=(int n) {
            ptr_ += n;
            return *this;
        }
        Iterator& operator-=(int n) {
            ptr_ -= n;
            return *this;
        }
        friend Iterator operator+(Iterator it, int n) {
            it += n;
            return it;
        }
        friend Iterator operator-(Iterator it, int n) {
            it -= n;
            return it;
        }
        friend size_t operator-(Iterator it_1, Iterator it_2) {
            return it_1.ptr_ - it_2.ptr_;
        }
        friend bool operator==(const Iterator& a, const Iterator& b) {
            return (a.ptr_ == b.ptr_);
        }
        friend bool operator!=(const Iterator& a, const Iterator& b) {
            return (a.ptr_ != b.ptr_);
        }

    private:
        int* ptr_;
    };

    Iterator Begin() {
        return Iterator(&arr_[0]);
    }

    Iterator End() {
        return Iterator(&arr_[size_]);
    }
    Iterator begin() {  // NOLINT
        return Iterator(&arr_[0]);
    }

    Iterator end() {  // NOLINT
        return Iterator(&arr_[size_]);
    }

private:
    T* arr_;
    size_t size_;
    size_t capacity_;
};
