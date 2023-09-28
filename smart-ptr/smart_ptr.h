#pragma once

#include <string>

struct Counter {
    size_t strong_count = 0;
    size_t weak_count = 0;

    Counter() {
    }
};

template <class T>
class WeakPtr;

template <class T>
class SharedPtr {
private:
    T *ptr_;

public:
    explicit SharedPtr(const WeakPtr<T> &rhs);

    SharedPtr() {
        counter_ = new Counter();
        ptr_ = nullptr;
    }

    explicit SharedPtr(T *x) {
        counter_ = new Counter();
        if (x != nullptr) {
            counter_->strong_count++;
        }
        ptr_ = x;
    }

    SharedPtr(const SharedPtr &x) {
        if (x.ptr_ != nullptr) {
            counter_ = x.counter_;
            counter_->strong_count++;
        } else {
            counter_ = new Counter;
        }
        ptr_ = x.ptr_;
    }

    SharedPtr(SharedPtr &&x) {
        counter_ = x.counter_;
        ptr_ = x.ptr_;
        x.counter_ = new Counter();
        x.ptr_ = nullptr;
    }

    SharedPtr &operator=(const SharedPtr &x) {
        if (counter_->strong_count != 0) {
            counter_->strong_count--;
        }
        if (counter_->strong_count == 0 && counter_->weak_count == 0) {
            delete counter_;
            delete ptr_;
        } else if (counter_->strong_count == 0) {
            delete ptr_;
        }

        if (x.ptr_ != nullptr) {
            counter_ = x.counter_;
            counter_->strong_count++;
        } else {
            counter_ = new Counter;
        }
        ptr_ = x.ptr_;
        return *this;
    }

    SharedPtr &operator=(SharedPtr &&x) {
        if (counter_->strong_count != 0) {
            counter_->strong_count--;
        }
        if (counter_->strong_count == 0 && counter_->weak_count == 0) {
            delete counter_;
            delete ptr_;
        } else if (counter_->strong_count == 0) {
            delete ptr_;
        }

        counter_ = x.counter_;
        ptr_ = x.ptr_;
        x.counter_ = new Counter();
        x.ptr_ = nullptr;
        return *this;
    }

    T *Get() {
        return ptr_;
    }

    T &operator*() {
        return *ptr_;
    }

    ~SharedPtr() {
        if (counter_->strong_count != 0) {
            counter_->strong_count--;
        }
        if (counter_->strong_count == 0 && counter_->weak_count == 0) {
            delete counter_;
            delete ptr_;
        } else if (counter_->strong_count == 0) {
            delete ptr_;
        }
    }

    void Reset(T *object) {
        counter_->strong_count--;
        if (counter_->strong_count == 0 && counter_->weak_count == 0) {
            delete counter_;
            delete ptr_;
        } else if (counter_->strong_count == 0) {
            delete ptr_;
        }
        counter_ = new Counter;
        if (object != nullptr) {
            counter_->strong_count++;
        }
        ptr_ = object;
    }

    Counter *counter_;
};

template <class T>
class WeakPtr {
private:
    T *ptr_;
    Counter *counter_;

public:
    SharedPtr<T> *shared;

    WeakPtr() {
        ptr_ = nullptr;
        counter_ = nullptr;
        shared = nullptr;
    }

    WeakPtr(const WeakPtr &x) {
        if (x.ptr_ != nullptr) {
            counter_ = x.counter_;
            counter_->weak_count++;
        } else {
            counter_ = nullptr;
        }
        shared = x.shared;
        ptr_ = x.ptr_;
    }

    explicit WeakPtr(SharedPtr<T> &x) {
        if (x.Get() != nullptr) {
            counter_ = x.counter_;
            counter_->weak_count++;
        } else {
            counter_ = nullptr;
        }
        shared = &x;
        ptr_ = x.Get();
    }

    WeakPtr(WeakPtr &&x) {
        if (x.ptr_ != nullptr) {
            counter_ = x.counter_;
        } else {
            counter_ = nullptr;
        }
        shared = x.shared;
        ptr_ = x.ptr_;
        x.ptr_ = nullptr;
    }

    WeakPtr &operator=(const WeakPtr &x) {
        if (counter_ != nullptr && counter_->weak_count != 0) {
            counter_->weak_count--;
        }
        if (counter_ != nullptr && counter_->strong_count == 0 && counter_->weak_count == 0) {
            delete counter_;
        }
        if (x.ptr_ != nullptr) {
            counter_ = x.counter_;
            counter_->weak_count++;
        } else {
            counter_ = nullptr;
        }
        shared = x.shared;
        ptr_ = x.ptr_;
        return *this;
    }

    WeakPtr &operator=(WeakPtr &&x) {
        if (counter_ != nullptr && counter_->weak_count != 0) {
            counter_->weak_count--;
        }
        if (counter_ != 0 && (*counter_).strong_count == 0 && counter_weak_count == 0) {
            delete counter_;
        }
        if (x.counter_ != 0) {
            counter_ = x.counter_;
        } else {
            counter_ = 0;
        }
        shared = x.shared;
        ptr_ = x.ptr_;
        x.ptr_ = 0;
        return *this;
    }

    ~WeakPtr() {
        if (counter_ != nullptr && counter_->weak_count != 0) {
            counter_->weak_count--;
        }
        if (counter_ != nullptr && counter_->strong_count == 0 && counter_->weak_count == 0) {
            delete counter_;
        }
    }

    bool IsExpired() const {
        return ptr_ == nullptr || counter_ == NULL || counter_->strong_count == 0;
    }

    SharedPtr<T> Lock() {
        if (IsExpired()) {
            return SharedPtr<T>();
        }
        return SharedPtr<T>(*this);
    }
};

template <class T>
SharedPtr<T>::SharedPtr(const WeakPtr<T> &rhs) {
    if (rhs.shared != nullptr && not(rhs.IsExpired())) {
        counter_ = rhs.shared->counter_;
        (*counter_).strong_count++;
        ptr_ = rhs.shared->ptr_;
    } else if (rhs.IsExpired()) {
        ptr_ = nullptr;
        counter_ = new Counter;
    } else {
        ptr_ = (*rhs.shared).ptr_;
        counter_ = new Counter;
    }
}
