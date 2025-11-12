#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include <utility>
#include <iostream>
//https://www.geeksforgeeks.org/dsa/implementation-deque-using-circular-array/
template <typename T>
class ABDQ : public DequeInterface<T> {
private:
    T* data_;                 // underlying dynamic array
    std::size_t capacity_;    // total allocated capacity
    std::size_t size_;        // number of stored elements
    std::size_t front_;       // index of front element
    std::size_t back_;        // index after the last element (circular)

    static constexpr std::size_t SCALE_FACTOR = 2;

public:
    // Big 5
    ABDQ() : data_(new T[1]), capacity_(1), size_(0), front_(0), back_(0){} 
    explicit ABDQ(std::size_t capacity): data_(new T[capacity]), capacity_(capacity), size_(0), front_(0), back_(0){}
    ABDQ(const ABDQ& other){
        data_ = new T[other.capacity_];
        capacity_ = other.capacity_;
        size_ = other.size_;
        front_ = 0;
        back_ = other.size_;
        for(int i=0; i<size_; i++){
            data_[i] = other.data_[(other.front_ + i) % other.capacity_];
        }
    }
    ABDQ(ABDQ&& other) noexcept{
        data_ = other.data_;
        capacity_ = other.capacity_;
        size_ = other.size_;
        front_ = other.front_;
        back_ = other.back_;
        other.data_ = nullptr;
        other.capacity_ = 0;
        other.size_ = 0;
        other.front_ = 0;
        other.back_ = 0;
    }
    ABDQ& operator=(const ABDQ& other){
        if(this == &other) return *this;
        delete[] data_;
        capacity_ = other.capacity_;
        size_ = other.size_;
        data_ = new T[capacity_];
        for (int i = 0; i<size_; i++){
            data_[i] = other.data_[(other.front_+i)% other.capacity_];
        }
        front_ = 0;
        back_ = size_;
        return *this;
    }
    ABDQ& operator=(ABDQ&& other) noexcept{
        if (this == &other) return *this;
        delete[] data_;
        data_ = other.data_;
        capacity_ = other.capacity_;
        size_ = other.size_;
        front_ = other.front_;
        back_ = other.back_;
        other.data_ = nullptr;
        other.capacity_ = 0;
        other.size_ = 0;
        other.front_ = 0;
        other.back_ = 0;
        return *this;
    }
    ~ABDQ() override{
        delete[] data_;
        data_ = nullptr;
    }
    void ensureCapacity(){
        if (size_ < capacity_) return;
        int newSize = capacity_ * SCALE_FACTOR;
        T* fix = new T[newSize];
        for (int i = 0; i<size_; i++){
            fix[i] = data_[(front_ + i) % capacity_];
        }
        delete[] data_;
        data_ = fix;
        capacity_ = newSize;
        front_ = 0;
        back_ = size_;

    }
    // Insertion
    void pushFront(const T& item) override{
        ensureCapacity();
        front_ = (front_==0) ? capacity_-1 : front_-1;
        data_[front_] = item;
        size_++;
    }
    void pushBack(const T& item) override{
        ensureCapacity();
        data_[back_] = item;
        back_ = (back_ + 1 == capacity_) ? 0 : back_ + 1;
        size_++;
    }

    // Deletion
    T popFront() override{
        if(size_==0){
            throw std::runtime_error("error");
        }
        T val = data_[front_];
        front_ = (front_ + 1)% capacity_;
        size_--;
        return val;
    }
    T popBack() override{
        if(size_==0){
            throw std::runtime_error("error");
        }
        back_ = (back_ + capacity_ -1) % capacity_;
        T val = data_[back_];
        --size_;
        return val;
    }

    // Access
    const T& front() const override{
        if(size_==0){
            throw std::runtime_error("error");
        }
        return data_[front_];
    }

    const T& back() const override{
        if(size_==0){
            throw std::runtime_error("error");
        }
    std::size_t idx = (back_ + capacity_ - 1) % capacity_;
    return data_[idx];

    }

    // Getters
    std::size_t getSize() const noexcept override{
        return size_;
    }

    void printForward() const {
        for (int i = 0; i< size_; i++){
            std::cout<<data_[(front_ + i) % capacity_] << std::endl;
        }
    }
    void printReverse() const {
        for (int i = 0; i<size_; i++){
            std::cout << data_[(back_ + capacity_ - 1 - i) % capacity_] <<std::endl;
        }
    }
};
