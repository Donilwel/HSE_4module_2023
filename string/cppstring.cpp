#include "cppstring.h"
String operator+(const String& first, const String& second) {
    String tmp(first);
    for (size_t i = 0; i < second.Size(); ++i) {
        tmp.PushBack(second[i]);
    }
    return tmp;
}
std::ostream& operator<<(std::ostream& stream, const String& string) {
    for (size_t i = 0; i < string.Size(); ++i) {
        stream << string[i];
    }
    return stream;
}
bool operator==(const String& first, const String& second) {
    return first >= second && second >= first;
}
bool operator!=(const String& first, const String& second) {
    return !(first == second);
}
bool operator>(const String& first, const String& second) {
    size_t size = std::min(first.Size(), second.Size());
    for (size_t i = 0; i < size; ++i) {
        if (first[i] > second[i]) {
            return true;
        }
        if (second[i] > first[i]) {
            return false;
        }
    }
    return first.Size() > second.Size();
}
bool operator<(const String& first, const String& second) {
    return second > first;
}
bool operator>=(const String& first, const String& second) {
    return !(first < second);
}
bool operator<=(const String& first, const String& second) {
    return !(first > second);
}
void SafeCpy(char* dest, const char* src, size_t len) {
    for (size_t i = 0; i < len; ++i) {
        dest[i] = src[i];
    }
}
String::String() {
    size_ = 0;
    capacity_ = 0;
    data_ = nullptr;
}
String::String(size_t size, char symbol) : String() {
    size_ = size;
    capacity_ = 2 * size;
    if (size_ != 0) {
        data_ = new char[capacity_];
    }
    for (size_t i = 0; i < size; ++i) {
        data_[i] = symbol;
    }
}
String::String(const char* src) {
    size_ = 0;
    while (src[size_] != '\0') {
        ++size_;
    }
    capacity_ = 2 * size_;
    data_ = new char[capacity_];
    for (size_t i = 0; i < size_; ++i) {
        data_[i] = src[i];
    }
}
String::String(const char* src, size_t size) {
    size_ = size;
    capacity_ = size;
    data_ = new char[capacity_];
    for (size_t i = 0; i < size; ++i) {
        data_[i] = src[i];
    }
}
String::~String() {
    delete[] data_;
}
String& String::operator=(const String& other) {
    if (data_ != other.data_) {
        if (capacity_ < other.capacity_) {
            delete[] data_;
            data_ = new char[other.capacity_];
        }
        size_ = other.size_;
        for (size_t i = 0; i != size_; ++i) {
            data_[i] = other[i];
        }
        capacity_ = other.capacity_;
    }
    return *this;
}
String::String(const String& other) {
    size_ = other.size_;
    capacity_ = other.capacity_;
    if (other.data_ == nullptr) {
        data_ = nullptr;
    } else {
        data_ = new char[capacity_];
    }
    for (size_t i = 0; i != size_; ++i) {
        data_[i] = other[i];
    }
}
const char& String::operator[](size_t idx) const {
    return *(data_ + idx);
}
char& String::operator[](size_t idx) {
    return *(data_ + idx);
}
const char& String::At(size_t idx) const {
    if (idx >= size_) {
        throw StringOutOfRange{};
    }
    return *(data_ + idx);
}
const char* String::Data() const {
    return data_;
}
char* String::Data() {
    return data_;
}
const char* String::CStr() const {
    return data_;
}
char& String::At(size_t idx) {
    if (idx >= size_) {
        throw StringOutOfRange{};
    }
    return *(data_ + idx);
}
const char& String::Front() const {
    return (*this).At(0);
}
char& String::Front() {
    return (*this).At(0);
}
const char& String::Back() const {
    return (*this).At(size_ - 1);
}
char& String::Back() {
    return (*this).At(size_ - 1);
}
char* String::CStr() {
    return data_;
}
bool String::Empty() const {
    return size_ == 0;
}
void String::Clear() {
    size_ = 0;
}
void String::Swap(String& other) {
    std::swap(other, *this);
}
void String::PopBack() {
    --size_;
}
size_t String::Size() const {
    return size_;
}
size_t String::Length() const {
    return size_;
}
size_t String::Capacity() const {
    return capacity_;
}
void String::PushBack(char c) {
    if (size_ + 1 >= capacity_) {
        if (capacity_ == 0) {
            capacity_ = 1;
        }
        Reserve(capacity_ * 2);
    }
    data_[size_] = c;
    ++size_;
}
void String::Resize(size_t new_size, char symbol) {
    if (new_size > size_) {
        if (new_size > capacity_) {
            Reserve(2 * (new_size + size_));
        }
        for (size_t i = 0; i < new_size; ++i) {
            PushBack(symbol);
        }
    }
    size_ = new_size;
}
void String::Reserve(size_t new_capacity) {
    if (new_capacity <= capacity_) {
        return;
    }
    auto tmp = new char[new_capacity];
    if (!(!data_)) {
        for (size_t i = 0; i < size_; ++i) {
            tmp[i] = data_[i];
        }
    }
    delete[] data_;
    data_ = tmp;
    capacity_ = new_capacity;
}
void String::ShrinkToFit() {
    capacity_ = size_;
}
int String::Compare(const String& other) const {
    if (*this > other) {
        return 1;
    }
    if (*this < other) {
        return -1;
    } else {
        return 0;
    }
}
String& String::operator+=(const String& other) {
    for (size_t i = 0; i != other.Size(); ++i) {
        PushBack(other[i]);
    }
    return *(this);
}