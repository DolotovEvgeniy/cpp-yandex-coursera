#pragma once

#include <stdexcept>
#include <array>

using namespace std;

template <typename T, size_t N>
class StackVector {
public:
    explicit StackVector(size_t a_size = 0)
        : size_(a_size)
    {
        if (size_ > N) {
            throw invalid_argument("Wrong vector size");
        }
    }

    T& operator[](size_t index) {
        if (index >= size_) {
            throw invalid_argument("Wrong index");
        }
        return array_[index];
    }
    const T& operator[](size_t index) const {
        if (index >= size_) {
            throw invalid_argument("Wrong index");
        }
        return array_[index];
    }

    auto begin() { return array_.begin(); };
    auto end() { return array_.begin() + size_; };
    auto begin() const { return array_.cbegin(); };
    auto end() const { return array_.cbegin() + size_; };

    size_t Size() const { return size_; }
    size_t Capacity() const { return N; }

    void PushBack(const T& value) {
        if (size_ >= N) {
            throw overflow_error("Vector is full");
        }
        array_[size_] = value;
        size_++;
    }

    T PopBack() {
       if (0 == size_) {
           throw underflow_error("Empty vector");
       } else {
           size_--;
           return array_[size_];
       }
    }

private:
    size_t size_;
    array<T, N> array_;
};
