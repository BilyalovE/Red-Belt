//#include "test_runner.h"
//#include <algorithm>
//#include <iostream>
//#include <string>
//#include <queue>
//#include <stdexcept>
//#include <set>
//
//
//using namespace std;
//
//
//
//template <class T>
//class ObjectPool {
//public:
//    T* Allocate(){
//        if(!deallocate_objs.empty()){
//            auto it = deallocate_objs.begin();
//            T* obj = *it;
//            deallocate_objs.erase(obj);
//        }
//        else{
//            T* ptr_obj = new T;
//            set_allocate_objs.insert(ptr_obj);
//            return ptr_obj;
//        }
//        auto obj = allocate_objs.front();
//        allocate_objs.pop();
//        return obj;
//    }
//
//    T* TryAllocate(){
//        if(!deallocate_objs.empty()){
//            auto it = deallocate_objs.begin();
//            T* obj = *it;
//            deallocate_objs.erase(obj);
//        }
//        else{
//            return nullptr;
//        }
//        auto obj = allocate_objs.front();
//        allocate_objs.pop();
//        return obj;
//    }
//
//    void Deallocate(T* object){
//        if (set_allocate_objs.count(object)){
//            set_allocate_objs.erase(object);
//            deallocate_objs.insert(object);
//            allocate_objs.push(object);
//        }
//        else{
//            throw invalid_argument("Переданный объект не содержится в множестве выделенных");
//        }
//    }
//
//    ~ObjectPool(){
//        while (!allocate_objs.empty()){
//            delete allocate_objs.front();
//            allocate_objs.pop();
//        }
//        while (!set_allocate_objs.empty()){
//            auto it = set_allocate_objs.begin();
//            delete *it;
//            set_allocate_objs.erase(it);
//        }
//        while (!deallocate_objs.empty()){
//            auto it = deallocate_objs.begin();
//            delete *it;
//            deallocate_objs.erase(it);
//        }
//    }
//
//private:
//    queue<T*> allocate_objs;
//    set<T*> set_allocate_objs;
//    set<T*> deallocate_objs;
//};
//
//void TestObjectPool() {
//  ObjectPool<string> pool;
//
//  auto p1 = pool.Allocate();
//  auto p2 = pool.Allocate();
//  auto p3 = pool.Allocate();
//
//  *p1 = "first";
//  *p2 = "second";
//  *p3 = "third";
//
//  pool.Deallocate(p2);
//  ASSERT_EQUAL(*pool.Allocate(), "second");
//
//  pool.Deallocate(p3);
//  pool.Deallocate(p1);
//  ASSERT_EQUAL(*pool.Allocate(), "third");
//  ASSERT_EQUAL(*pool.Allocate(), "first");
//
//  //pool.Deallocate(p1);
//}
//
//int main() {
//  TestRunner tr;
//  RUN_TEST(tr, TestObjectPool);
//  return 0;
//}

#include "test_runner.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>

using namespace std;

template <class T>
class ObjectPool {
public:
    T* Allocate() {
        if (!deallocate_objs.empty()) {
            // Извлекаем объект из освобождённых объектов
            T* obj = deallocate_objs.front();
            deallocate_objs.pop(); // Удаляем его из очереди освобождённых
            set_allocate_objs.insert(obj); // Добавляем в выделенные объекты
            return obj; // Возвращаем указатель на выделенный объект
        } else {
            // Создаём новый объект, если освобождённых нет
            T* ptr_obj = new T;
            set_allocate_objs.insert(ptr_obj);
            return ptr_obj; // Возвращаем указатель на новый объект
        }
    }

    T* TryAllocate() {
        if (!deallocate_objs.empty()) {
            // Аналогично Allocate, но возвращаем указатель на освобождённый объект
            T* obj = deallocate_objs.front();
            deallocate_objs.pop();
            set_allocate_objs.insert(obj);
            return obj; // Возвращаем указатель на выделенный объект
        }
        return nullptr; // Возвращаем nullptr, если освобождённых объектов нет
    }

    void Deallocate(T* object) {
        // Проверяем, что объект находится в выделенных
        if (set_allocate_objs.count(object)) {
            set_allocate_objs.erase(object); // Удаляем из выделенных объектов
            deallocate_objs.push(object); // Добавляем в очередь освобождённых
        } else {
            throw invalid_argument("Переданный объект не содержится в множестве выделенных");
        }
    }

    ~ObjectPool() {
        // Удаляем все объекты из множества выделенных
        for (auto obj : set_allocate_objs) {
            delete obj;
        }
        set_allocate_objs.clear(); // Очищаем множество выделенных объектов

        // Удаляем освобождённые объекты
        while (!deallocate_objs.empty()) {
            delete deallocate_objs.front();
            deallocate_objs.pop(); // Удаляем освобождённые объекты
        }
    }

private:
    queue<T*> deallocate_objs; // Очередь освобождённых объектов
    set<T*> set_allocate_objs;  // Множество выделенных объектов
};

void TestObjectPool() {
    ObjectPool<string> pool;

    auto p1 = pool.Allocate();
    auto p2 = pool.Allocate();
    auto p3 = pool.Allocate();

    *p1 = "first";
    *p2 = "second";
    *p3 = "third";

    pool.Deallocate(p2);
    ASSERT_EQUAL(*pool.Allocate(), "second"); // Проверяем, что вернулся p2

    pool.Deallocate(p3);
    pool.Deallocate(p1);
    ASSERT_EQUAL(*pool.Allocate(), "third"); // Проверяем, что вернулся p3
    ASSERT_EQUAL(*pool.Allocate(), "first");  // Проверяем, что вернулся p1

    // pool.Deallocate(p1); // Проверка на двойное освобождение
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestObjectPool);
    return 0;
}
