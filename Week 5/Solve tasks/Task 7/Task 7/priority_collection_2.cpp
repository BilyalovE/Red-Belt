#include "test_runner.h"
#include "profailer.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <set>
#include <utility>
#include <list>
#include <vector>
#include <random>

using namespace std;

//template <typename T>
//class PriorityCollection {
//public:
//    using It = typename list<T>::iterator;
//    using Id = T*;
//
//  // Добавить объект с нулевым приоритетом
//  // с помощью перемещения и вернуть его идентификатор
//    Id Add(T object){
//        It it = obj_collection.insert(obj_collection.end(), move(object)); //O(1)
//        Id ptr_id = &(*it);
//        priority_collection[ptr_id] = make_pair(it, init_priority);
//        flag_change_status = true;
//        prioritet_id[init_priority].insert(ptr_id);
//        return ptr_id; //copy elision
//    }
//
//  // Добавить все элементы диапазона [range_begin, range_end)
//  // с помощью перемещения, записав выданные им идентификаторы
//  // в диапазон [ids_begin, ...)
//
//  template <typename ObjInputIt, typename IdOutputIt>
//  void Add(ObjInputIt range_begin, ObjInputIt range_end,
//           IdOutputIt ids_begin){
//      // O(N) - максимальная длина за все запросы
//      for(auto item = range_begin; item != range_end; ++item) {
//          It it = obj_collection.insert(obj_collection.end(), move(*item)); //O(1)
//          Id ptr_id = &(*it);
//          priority_collection[ptr_id] = make_pair(it, init_priority);
//          prioritet_id[init_priority].insert(ptr_id);
//          *ids_begin = ptr_id;
//          ++ids_begin;
//          flag_change_status = true;
//      }
//  }
//
//  // Определить, принадлежит ли идентификатор какому-либо
//  // хранящемуся в контейнере объекту
//    bool IsValid(Id id) const {
//        return priority_collection.count(id);    // O(Log(N))
//    }
//
//  // Получить объект по идентификатору
//    const T& Get(Id id) const{
//        //move
//        return  move(*id); // O(Log(N))
//    }
//
//  // Увеличить приоритет объекта на 1
//    void Promote(Id id){
//        auto current_prioritet = priority_collection[id].second;
//        prioritet_id.at(current_prioritet).erase(id);
//        if(prioritet_id[current_prioritet].empty()){
//            prioritet_id.erase(current_prioritet);
//        }
//        ++current_prioritet;
//        prioritet_id[current_prioritet].insert(id);
//        ++priority_collection[id].second;
//    }
//
//  // Получить объект с максимальным приоритетом и его приоритет
//    pair<const T&, int> GetMax() const {
//        if(flag_change_status){
//            SearchIdObjectMaxPriority();
//            flag_change_status = false;
//        }
//        return {move(*max_id), priority_collection.at(max_id).second};
//    }
//
//
//  // Аналогично GetMax, но удаляет элемент из контейнера
//    pair<T, int> PopMax(){
//        if(flag_change_status){
//            SearchIdObjectMaxPriority();
//        }
//        auto object = move(*max_id);
//        auto priority = priority_collection[max_id].second;
//        auto it_max_object = priority_collection[max_id].first;
//        obj_collection.erase(it_max_object);
//        priority_collection.erase(max_id);
//        prioritet_id[priority].erase(max_id);
//        if(prioritet_id[priority].empty()){
//            prioritet_id.erase(priority);
//        }
//        flag_change_status = true;
//        return {move(object), priority};
//    }
//
//private:
//  // Приватные поля и методы
//    map<Id, pair<It, int>> priority_collection;
//    list<T> obj_collection;
//    map<int, set<Id>> prioritet_id;
//    int init_priority = 0;
//    static bool flag_change_status;
//    static Id max_id;
//
//    void SearchIdObjectMaxPriority() const {
//        auto pair_max_priority_ids = prev(prioritet_id.end());
//        auto set_ids = pair_max_priority_ids->second;
//        max_id = *prev(set_ids.end());
//    }
//
//};

template <typename T>
class PriorityCollection {
public:
    using Id = int;
    
  // Добавить объект с нулевым приоритетом
  // с помощью перемещения и вернуть его идентификатор
    Id Add(T object){
        const Id new_id = objects.size();
        objects.push_back({move(object)});
        sorted_objects.insert({0, new_id});
        return new_id;
    }

  // Добавить все элементы диапазона [range_begin, range_end)
  // с помощью перемещения, записав выданные им идентификаторы
  // в диапазон [ids_begin, ...)
    
  template <typename ObjInputIt, typename IdOutputIt>
  void Add(ObjInputIt range_begin, ObjInputIt range_end,
           IdOutputIt ids_begin){
      // O(N) - максимальная длина за все запросы
      while(range_begin != range_end){
          *ids_begin = Add(move(*range_begin));
          range_begin++;
          ids_begin++;
      }
  }

  // Определить, принадлежит ли идентификатор какому-либо
  // хранящемуся в контейнере объекту
    bool IsValid(Id id) const {
        return id >= 0 && id < objects.size() &&
            objects[id].priority != NONE_PRIORITY;
    }

  // Получить объект по идентификатору
    const T& Get(Id id) const{
        return objects[id].object;
    }

  // Увеличить приоритет объекта на 1
    void Promote(Id id){
        auto& item = objects[id];
        auto old_priority = item.priority;
        auto new_priority = ++item.priority;
        sorted_objects.erase({old_priority, id});
        sorted_objects.insert({new_priority, id});
    }

  // Получить объект с максимальным приоритетом и его приоритет
    pair<const T&, int> GetMax() const {
        const auto& item = objects[prev(sorted_objects.end())->second];
        return {item.object, item.priority};
    }


  // Аналогично GetMax, но удаляет элемент из контейнера
    pair<T, int> PopMax(){
        const auto sorted_objects_it = prev(sorted_objects.end());
          auto& item = objects[sorted_objects_it->second];
          sorted_objects.erase(sorted_objects_it);
          const int priority = item.priority;
          item.priority = NONE_PRIORITY;
          return {move(item.object), priority};
    }

private:
  // Приватные поля и методы
    struct Object{
        T object;
        int priority = 0;
    };
    static const int NONE_PRIORITY = -1;
    vector<Object> objects;
    set<pair<int, Id>> sorted_objects;
    
};

 
class StringNonCopyable : public string {
public:
  using string::string;  // Позволяет использовать конструкторы строки
  StringNonCopyable(const StringNonCopyable&) = delete;
  StringNonCopyable(StringNonCopyable&&) = default;
  StringNonCopyable& operator=(const StringNonCopyable&) = delete;
  StringNonCopyable& operator=(StringNonCopyable&&) = default;
};

void TestNoCopy() {
    PriorityCollection<StringNonCopyable> strings;
    const auto white_id = strings.Add("white");
    const auto yellow_id = strings.Add("yellow");
    const auto red_id = strings.Add("red");
    
    strings.Promote(yellow_id);
    for (int i = 0; i < 2; ++i) {
        strings.Promote(red_id);
    }
    
    strings.Promote(yellow_id);
    // Получить объект по идентификатору
    {
        ASSERT_EQUAL(strings.Get(white_id), "white");
        ASSERT_EQUAL(strings.Get(yellow_id), "yellow");
        ASSERT_EQUAL(strings.Get(red_id), "red");
    }
    // Определить, принадлежит ли идентификатор какому-либо
    // хранящемуся в контейнере объекту
    {
        auto item = strings.IsValid(white_id );
        ASSERT(item);
        item = strings.IsValid(yellow_id);
        ASSERT(item);
        item = strings.IsValid(red_id);
        ASSERT(item);
    }
    
        {
            const auto item = strings.GetMax();
            ASSERT_EQUAL(item.first, "red");
            ASSERT_EQUAL(item.second, 2);
        }
        {
            const auto item = strings.PopMax();
            ASSERT_EQUAL(item.first, "red");
            ASSERT_EQUAL(item.second, 2);
        }
        {
            const auto item = strings.GetMax();
            ASSERT_EQUAL(item.first, "yellow");
            ASSERT_EQUAL(item.second, 2);
        }
        {
            const auto item = strings.PopMax();
            ASSERT_EQUAL(item.first, "yellow");
            ASSERT_EQUAL(item.second, 2);
        }
        {
            const auto item = strings.GetMax();
            ASSERT_EQUAL(item.first, "white");
            ASSERT_EQUAL(item.second, 0);
        }
        {
            const auto item = strings.PopMax();
            ASSERT_EQUAL(item.first, "white");
            ASSERT_EQUAL(item.second, 0);
        }
    
        // если у всех приоритет 0 и еще проверю, что будет если снова добавить те же самые элементы
        const auto wh_id = strings.Add("white");
        const auto y_id = strings.Add("yellow");
        const auto r_id = strings.Add("red");
        {
            const auto item = strings.GetMax();
            ASSERT_EQUAL(item.first, "red");
            ASSERT_EQUAL(item.second, 0);
        }
        {
            const auto item = strings.PopMax();
            ASSERT_EQUAL(item.first, "red");
            ASSERT_EQUAL(item.second, 0);
        }
        {
            const auto item = strings.GetMax();
            ASSERT_EQUAL(item.first, "yellow");
            ASSERT_EQUAL(item.second, 0);
        }
        {
            const auto item = strings.PopMax();
            ASSERT_EQUAL(item.first, "yellow");
            ASSERT_EQUAL(item.second, 0);
        }
        {
            const auto item = strings.GetMax();
            ASSERT_EQUAL(item.first, "white");
            ASSERT_EQUAL(item.second, 0);
        }
        {
            const auto item = strings.PopMax();
            ASSERT_EQUAL(item.first, "white");
            ASSERT_EQUAL(item.second, 0);
        }
}

void TestAddManyObjs(){
    PriorityCollection<StringNonCopyable> strings;
    const size_t SIZE = 1e6/3;
    vector<StringNonCopyable> unicObjs;
    unicObjs.reserve(SIZE);
    mt19937_64 random_gen; // генератор случайных чисел
    for(int i = 0; i < SIZE; ++i){
        StringNonCopyable str = "var";
        str += to_string(random_gen());
        unicObjs.push_back(move(str));
    }
    vector<int> idObjs;
    idObjs.reserve(SIZE);
    //O(N)
    strings.Add(unicObjs.begin(), unicObjs.end(), idObjs.begin());
    //O(N)
    for(int call = 0; call < SIZE; ++call){
        StringNonCopyable str = "var";
        str += to_string(random_gen());
        const auto item = strings.Add(move(str));
        strings.Promote(item);
        strings.GetMax();
    }
}


int main() {
    TestRunner tr;
    RUN_TEST(tr, TestNoCopy);
    {
        LOG_DURATION("TestAddManyObjs");
        RUN_TEST(tr, TestAddManyObjs);
    }
  return 0;
}
