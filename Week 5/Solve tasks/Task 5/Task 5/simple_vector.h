#pragma once

#include <cstdlib>
#include <algorithm>

// Реализуйте шаблон SimpleVector
template <typename T>
class SimpleVector {
public:
    SimpleVector() : size_(0), begin_(nullptr),
    end_(nullptr), capacity_(0) { }

    explicit SimpleVector(size_t size)
    : size_(size), begin_(new T[size]), end_(begin_ + size),
    capacity_(size) { }

    ~SimpleVector(){
        delete [] begin_;
    }

    T& operator[](size_t index){
        return begin_[index];
    }


    T* begin() { return begin_; }
    T* end()  { return end_; }

    const T* begin() const { return begin_; }
    const T* end() const { return end_; }

    size_t Size() const{ return size_;}

    size_t Capacity() const{
        return size_ * 2;
    }
    void PushBack(const T& value){
        if(size_ == 0){
            begin_ = new T;
            capacity_ = 1;
            end_ = begin_ + size_ + 1;
        }
        if(size_ == capacity_){
            auto new_copacity_ = 2 * capacity_;
            T* new_begin_ = new T[new_copacity_];
            std::copy(begin_, end_, new_begin_);
            delete[] begin_;
            begin_ = new_begin_;
        }
        end_ = begin_ + size_ + 1;
        begin_[size_] = value;
        ++size_;
    }

private:
    size_t capacity_;
    T* begin_;
    T* end_;
    size_t size_;
};

