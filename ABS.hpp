#pragma once

#include <cstddef>
#include <stdexcept>
#include <iostream>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABS : public StackInterface<T> {
public:
    ABS() : capacity_(1), curr_size_(0), array_(new T[1]) {}
    explicit ABS(const size_t capacity) : capacity_(capacity), curr_size_(0), array_(new T[capacity]) {}

    ABS(const ABS& other) {
        capacity_ = other.capacity_;
        curr_size_ = other.curr_size_;
        array_ = new T[other.capacity_];
        for (int i = 0; i < curr_size_; i++) {
            array_[i] = other.array_[i];
        }
    }
    ABS& operator=(const ABS& rhs){
        if(*this == rhs){
            return *this;
        }
        capacity_ = rhs.capacity_;
        curr_size_ = rhs.curr_size_;
        array_ = new T[rhs.capacity_];
        for(int i = 0; i<curr_size_; i++){
            array_[i] = rhs.array_[i];
        }
        return *this;
    }

    ABS(ABS&& other) noexcept {
        capacity_ = other.capacity_;
        curr_size_ = other.curr_size_;
        array_ = new T[other.capacity_];
        other.curr_size_ = 0;
        other.capacity_ = 0;
        other.array_ = nullptr;
    }

    ABS& operator=(ABS&& rhs) noexcept {
        if (*this == rhs) return *this;
        delete[] array_;
        capacity_ = rhs.capacity_;
        curr_size_ = rhs.curr_size_;
        array_ = rhs.array_;
        rhs.curr_size_ = 0;
        rhs.capacity_ = 0;
        rhs.array_ = nullptr;
        return *this;
    }

    ~ABS() noexcept override {
        delete[] array_;
        array_ = nullptr;
    }

    [[nodiscard]] size_t getSize() const noexcept override {
        return curr_size_;
    }

    [[nodiscard]] size_t getMaxCapacity() const noexcept {
        return capacity_;
    }

    [[nodiscard]] T* getData() const noexcept {
        return array_;
    }

    void push(const T& data) {
        if (curr_size_ >= capacity_) {
            capacity_ *= scale_factor_;
            T* fix = new T[capacity_];
            for (int i = 0; i < curr_size_; i++) {
                fix[i] = array_[i];
            }
            delete[] array_;
            array_ = fix;
        }
        array_[curr_size_] = data;
        curr_size_++;
    }

    T peek() const override {
        if (curr_size_ != 0) {
            return array_[curr_size_ - 1];
        }
        return 0;
    }

    T pop() override {
        if (curr_size_ != 0) {
            curr_size_--;
            return array_[curr_size_ - 1];
        }
        return 0;
    }
    void PrintForward() const{
        for( int i = 0; i <curr_size_; i++){
            std::cout<<array_[i]<<std::endl;
        }
    }
    void PrintReverse() const{
        for (int i =0; i<curr_size_; i++){
            std::cout<<array_[curr_size_-1-i]<<std::endl;
        }
    }

private:
    size_t capacity_;
    size_t curr_size_;
    T* array_;
    static constexpr size_t scale_factor_ = 2;
};