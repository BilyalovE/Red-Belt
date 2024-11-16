#include <cstdint>
#include <cstdlib>
#include <algorithm>
#include <iostream>
using namespace std;

// Реализуйте SimpleVector в этом файле
// и отправьте его на проверку

template <typename T>
class SimpleVector {
public:
    SimpleVector() : size_(0), capacity(0), data(nullptr) { }
    
    //Констутор копирования
    SimpleVector(const SimpleVector<T>& other)
    : size_(other.size_), capacity(other.capacity), data(new T[other.capacity])
    {
        copy(other.data, other.data + size_, data);
        cout << "copy ctor" << endl;
    }
    

    //Констутор перемещения
    SimpleVector(SimpleVector&& other)
    : size_(other.size_), capacity(other.capacity), data(other.data)
    {
        other.data = nullptr;
        other.size_ = other.capacity = 0;
        cout << "move ctor" << endl;
    }
    //Оператор копирования
    void operator=(const SimpleVector<T>& other){
        delete[] data;
        data = new T[other.capacity];
        size_ = other.size_;
        capacity = other.capacity;
        copy(other.data, other.data + size_, data);
        cout << "oper copy" << endl;
    }
    //Оператор перемещения
    void operator=(SimpleVector<T>&& other){
        delete[] data;
        data = other.data;
        size_ = other.size_;
        capacity = other.capacity;
        other.data = nullptr;
        other.size_ = other.capacity = 0;
        cout << "oper move" << endl;
    }
    
    explicit SimpleVector(size_t size)
        : size_(size),
          capacity(size_),
          data(new T[size]) { }
    
    ~SimpleVector(){
        delete[]  data;
    }

    T& operator[](size_t index){
        return data[index];
    }

    T* begin() { return data; }
    T* end() { return data + size_; }
    
    const T* begin() const { return data; }
    const T* end() const { return data + size_; }

    size_t Size() const { return size_; }
    size_t Capacity() const { return capacity; }
    

        
    void PushBack(T&& value){
        if(capacity == 0){
            capacity = 1;
            data = new T[capacity];
        }
        else if(size_ == capacity){
            capacity *= 2;
            T* new_data = new T[capacity];
            move(data, data + size_, new_data);
            delete[] data;
            data = new_data;
        }
        data[size_] = move(value);
        ++size_;
    }
    
    void PushBack(const T& value){
        if(capacity == 0){
            capacity = 1;
            data = new T[capacity];
        }
        else if(size_ == capacity){
            capacity *= 2;
            T* new_data = new T[capacity];
            copy(data, data + size_, new_data);
            delete[] data;
            data = new_data;
        }
        data[size_] = value;
        ++size_;
    }

private:
    T* data;
    size_t size_;
    size_t capacity;
    
    // Добавьте сюда поля
};
