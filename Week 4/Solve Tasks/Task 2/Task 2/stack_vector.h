#pragma once

#include <stdexcept>
#include <array>
#include <string>
#include <sstream>
using namespace std;

template <typename T, size_t N>
class StackVector {
public:
    explicit StackVector(size_t a_size = 0){
        if (a_size > capacity){
            string str_error = "Expect invalid_argument for too large size";
            throw invalid_argument(str_error);
        }
        else{
            size_array = a_size;
        }
    }
    typename array<T, N>::iterator GetHead(){
        return stackVector.begin();
    }
    
    T& operator[](size_t index){
        if(index < size_array){
            return stackVector[index];
        }
        else{
            stringstream str_error("Going beyond the boundaries of the vector");
            throw range_error(str_error.str());
        }

    }
    const T& operator[](size_t index) const{
        if(index < size_array){
            return stackVector[index];
        }
        else{
            stringstream str_error("Going beyond the boundaries of the vector");
            throw range_error(str_error.str());
        }
    }
    typename array<T, N>::iterator begin(){
        return stackVector.begin();
    }
    typename array<T, N>::iterator end(){
        return stackVector.begin() + size_array;
    }
    const typename array<T, N>::iterator begin() const {
        return stackVector.begin();
    }
    const typename array<T, N>::iterator end() const {
        return stackVector.begin() + size_array;
    }

    size_t Size() const {
        return size_array;
    }
    size_t Capacity() const{
        return capacity;
    }

    void PushBack(const T& value){
        ++size_array;
        if(size_array <= capacity){
            stackVector[size_array - 1] = value;
        }
        else{
            string str_error = "Expect overflow_error for PushBack in full vector";
            throw overflow_error(str_error);
        }
    }
    
    T PopBack(){
        if(size_array != 0){
            --size_array;
            return stackVector[size_array];
        }
        else{
            stringstream str_error("Expect underflow_error for PopBack from empty vector");
            throw underflow_error(str_error.str());
        }
    }

private:
    const size_t capacity = N;
    size_t size_array;
    array<T, N> stackVector;
};

