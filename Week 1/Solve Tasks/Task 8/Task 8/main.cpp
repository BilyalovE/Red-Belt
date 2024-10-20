//
//  main.cpp
//  Task 8
//
//  Created by Билялов Эльдар on 20.10.2024.
//

#include <iostream>
#include <vector>
#include <deque>
#include <stdexcept>
#include <sstream>

#define VALIDATE_DEQUE_INDEX(index)               \
    if (index >= Size()){                         \
        stringstream s;                           \
        s << "Выход за границы диапазона";        \
        throw out_of_range(s.str());              \
    }                                             \
    else{                                         \
        if (index < Size() / 2){                  \
            return v_front[index];                \
        }                                         \
        else {                                    \
            return v_back[index - Size() / 2];    \
        }                                         \
    }

#define GET_DEQUE_ITEM(index)                 \
    if (index < Size() / 2){                  \
        return v_front[index];                \
    }                                         \
    else {                                    \
        return v_back[index - Size() / 2];    \
    }                                         \



using namespace std;


template <typename T>
class Deque {
public:
    // конструтор по умолчанию - конструткор копирования
    Deque() {}
    // конструтор, задающий размер дека
    Deque(const size_t n) : size(n){
        v_front.resize(size/2);
        v_back.resize(size/2);
    }
    // конструтор, задающий размер дека и его инициализацимю по умолчанию
    Deque(const size_t n, const T& def_value) : size(n){
        v_front.resize(size/2, def_value);
        v_back.resize(size/2, def_value);
    }

    bool  Empty() const{
        return v_front.empty() && v_back.empty();
    }

    size_t Size() const {
        return v_front.size() + v_back.size();
    }

    T& operator[](size_t index) {
        GET_DEQUE_ITEM(index)
    }

    const T& operator[](size_t index) const {
        GET_DEQUE_ITEM(index)
    }
    T& At(size_t index){
        VALIDATE_DEQUE_INDEX(index)
    }
    const T& At(size_t index) const {
        VALIDATE_DEQUE_INDEX(index)
    }
    
    T& Front(){
        if (v_front.empty()) throw std::out_of_range("Deque is empty");
          return v_front.back();
    };
     
    const T& Front() const {
        if (v_front.empty()) throw std::out_of_range("Deque is empty");
          return v_front.back();
    };

    T& Back(){
        if (v_back.empty()) throw std::out_of_range("Deque is empty");
            return v_back.back();
    }
    
    const T& Back() const {
        if (v_back.empty()) throw std::out_of_range("Deque is empty");
            return v_back.back();
    }

    void PushFront(const T& new_value) {
        v_front.push_back(new_value);
    }
    
    void PushBack(const T& new_value) {
        v_back.push_back(new_value);
    }
private:
    size_t size;
    vector <T> v_front, v_back;
};


int main(int argc, const char * argv[]) {
    Deque<int> Deq1(10, 10);
    cout << "size = " << Deq1.Size() << endl;
    cout << "empty = " << Deq1.Empty() << endl;
    Deq1[5] = 5;
    cout << "Deq1[5] = " << Deq1[5] << endl;
    Deq1.At(9) = 9;
    cout << "Deq1[9] = " << Deq1.At(9) << endl;
    Deq1.Front() = 0;
    cout << "Front Deq1 = " << Deq1.Front() << endl;
    Deq1.Back() = 10;
    cout << "Back Deq1 = " << Deq1.Back() << endl;
    Deq1.PushFront(1111);
    cout << "PushFront = " << Deq1.Front() << endl;
    Deq1.PushBack(9999);
    cout << "PushFront = " << Deq1.Back() << endl;
    deque<int> deq2 = {1, 2, 3, 4};
    cout << deq2[1] << endl;
    cout << Deq1[22] << endl;
    cout << Deq1.At(22) << endl;
    return 0;
}

