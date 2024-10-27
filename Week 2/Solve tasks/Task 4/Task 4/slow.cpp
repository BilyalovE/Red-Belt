#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>
#include "profailer.h"
#include <fstream>
#include <cstdlib>  // для rand() и srand()
#include <ctime>    // для time()
#include <map>
#include "test_runner.h"

using namespace std;
// =========================================   №1
//class ReadingManager {
//public:
//  ReadingManager()
//      : user_page_counts_(MAX_USER_COUNT_ + 1, 0),
//        sorted_users_(),
//        user_positions_(MAX_USER_COUNT_ + 1, -1) {}
//
//  void Read(int user_id, int page_count) {
//    if (user_page_counts_[user_id] == 0) {
//      AddUser(user_id);
//    }
//    user_page_counts_[user_id] = page_count;
//    int& position = user_positions_[user_id];
//    while (position > 0 && page_count > user_page_counts_[sorted_users_[position - 1]]) {
//      SwapUsers(position, position - 1);
//    }
//  }
//
//  double Cheer(int user_id) const {
//    if (user_page_counts_[user_id] == 0) {
//      return 0;
//    }
//    const int user_count = GetUserCount();
//    if (user_count == 1) {
//      return 1;
//    }
//    const int page_count = user_page_counts_[user_id];
//    int position = user_positions_[user_id];
//    while (position < user_count &&
//      user_page_counts_[sorted_users_[position]] == page_count) {
//      ++position;
//    }
//    if (position == user_count) {
//        return 0;
//    }
//    // По умолчанию деление целочисленное, поэтому
//    // нужно привести числитель к типу double.
//    // Простой способ сделать это — умножить его на 1.0.
//    return (user_count - position) * 1.0 / (user_count - 1);
//  }
//
//private:
//  // Статическое поле не принадлежит какому-то конкретному
//  // объекту класса. По сути это глобальная переменная,
//  // в данном случае константная.
//  // Будь она публичной, к ней можно было бы обратиться снаружи
//  // следующим образом: ReadingManager::MAX_USER_COUNT.
//  static const int MAX_USER_COUNT_ = 100'000;
//
//  vector<int> user_page_counts_;
//  vector<int> sorted_users_;   // отсортированы по убыванию количества страниц
//  vector<int> user_positions_; // позиции в векторе sorted_users_
//
//  int GetUserCount() const {
//    return sorted_users_.size();
//  }
//  void AddUser(int user_id) {
//    sorted_users_.push_back(user_id);
//    user_positions_[user_id] = sorted_users_.size() - 1;
//
//  }
//  void SwapUsers(int lhs_position, int rhs_position) {
//    const int lhs_id = sorted_users_[lhs_position];
//    const int rhs_id = sorted_users_[rhs_position];
//    swap(sorted_users_[lhs_position], sorted_users_[rhs_position]);
//    swap(user_positions_[lhs_id], user_positions_[rhs_id]);
//  }
//};
//
void QueryGenerator(int query_count, ofstream& out){
    // Инициализация генератора случайных чисел с использованием текущего времени
    srand(static_cast<unsigned>(time(0)));
    // Определение диапазона случайных чисел
    const int MAX_USER = 1e5;
    const int MAX_PAGE = 1e3;
    int user_id = 0, user_page = 0;
    map<int, int> users_statistis;
    out << query_count << '\n';
    for(int i = 0; i < query_count; ++i){
        user_id = rand() % (MAX_USER + 1);
        // Генерация случайного чиcла 0 или 1
        if(rand() % 2 == 0){
            out << "READ" << ' ';
            int MIN_PAGE = 0;
            if (users_statistis.count(user_id)){
                MIN_PAGE = users_statistis[user_id];
            }
            user_page = MIN_PAGE + rand() % (MAX_PAGE - MIN_PAGE + 1);
            users_statistis[user_id] = user_page;
            out << user_id << " " << user_page << "\n";
        }
        else {
            out << "CHEER" << ' ' << user_id << "\n";
        }
    }
}


////=========================================   №2
//class ReadingManager{
//public:
//    void Read(const int user_id, const int page){
//        if(user_count_pages.count(user_id)){ //O(log(Q))
//            auto last_page =  user_count_pages[user_id]; // номер старой страницы, до которой дочитал пользователь
//            pages_count_user[last_page] -= 1; // уменьшилось число пользователей, кто прочитал до старой страницы
//        }
//        user_count_pages[user_id] = page; // пользователь хранит новую страницу
//        pages_count_user[page] += 1; // увеличилось число пользователей, кто прочитал до новой страницы
//    }
//    double Cheer(const int user_id){
//        if(!user_count_pages.count(user_id)){ //O(log(Q))
//            return 0;
//        }
//        // Общее число читателей
//        const size_t total_users = user_count_pages.size();
//        if(total_users == 1){
//            return 1;
//        }
//        const int current_page = user_count_pages.at(user_id); //O(log(N))
//        // Получаю пользователей, которые дочитали до текушей страницы
//        auto it_current_page = pages_count_user.lower_bound(current_page); //O(log(1000))
//        //auto it = pages_count_user.begin();
//        int num_users = 0;
//        for (auto it = pages_count_user.begin(); it != it_current_page; it = next(it)){   // O(1000)
//            num_users += it->second;
//        }
//        return 1.0 * num_users / (total_users - 1);
//    }
//
//private:
//    // ключ - пользователь, значение - число страниц, которое он прочитал
//    map<int, int> user_count_pages;
//    // ключ - страницы из книги, значение - число пользователей,
//    // которые прочитали включительно по данную страницы
//    map<int, int> pages_count_user;
//    map<int, int> rating_users;
//};


// =========================================   №3
//class ReadingManager{
//public:
//    void Read(const int user_id, const int page){
//        if(user_count_pages.count(user_id)){ //O(log(Q))
//            auto last_page =  user_count_pages[user_id]; // номер старой страницы, до которой дочитал пользователь
//            pages_count_users[last_page] -= 1; // уменьшилось число пользователей, кто прочитал до старой страницы
//        }
//        user_count_pages[user_id] = page; // пользователь хранит новую страницу
//        pages_count_users[page] += 1; // увеличилось число пользователей, кто прочитал до новой страницы
//        //Общее число читателей
//        const size_t total_users = user_count_pages.size();
//        int num_users = 0;
//        if(user_count_pages.size() > 1){
//            rating_pages[prev(pages_count_users.end())->first] = 1;
//            for (auto it_1 = pages_count_users.begin(); it_1 != prev(pages_count_users.end()); it_1 = next(it_1)){
//                for(auto it_2 = pages_count_users.begin(); it_2 != it_1; it_2 = next(it_2)){
//                    num_users += it_2->second;
//                }
//                double rating = 1.0 * num_users / (total_users - 1);
//                rating_pages[it_1->first] = rating;
//                num_users = 0;
//            }
//        }
//        else{
//            rating_pages[page] = 1;
//        }
//    }
//    double Cheer(const int user_id){
//        if(!user_count_pages.count(user_id)){ //O(Q*log(M))
//            return 0;
//        }
//        else{
//            auto page = user_count_pages[user_id]; //O(1)
//            return  rating_pages[page];   //O(1)
//        }
//    }
//private:
//    // ключ - пользователь, значение - число страниц, которое он прочитал
//    map<int, int> user_count_pages;
//    // ключ - страницы из книги, значение - число пользователей,
//    // которые прочитали включительно по данную страницы
//    map<int, int> pages_count_users;
//    // рейтинг каждой страницы
//    map<int, double> rating_pages;
//};

//// =========================================   №4
//class ReadingManager{
//public:
//    void Read(const int user_id, const int page){
//        if(user_count_pages.count(user_id)){                                //O(log(M))
//            // номер старой страницы, до которой дочитал пользователь
//            auto last_page =  user_count_pages[user_id];    //O(log(M))
//            // уменьшилось число пользователей,
//            // кто прочитал до старой страницы
//            pages_count_users[last_page] -= 1;  //O(log(M))
//        }
//        // пользователь хранит новую страницу
//        user_count_pages[user_id] = page; //O(log(M))
//        // увеличилось число пользователей,
//        // кто прочитал до новой страницы
//        pages_count_users[page] += 1; //O(log(M))
//        // Для каждой страницы считаем рейтинг
//        int first_page = begin(pages_count_users)->first;  //O(1)
//        rating_pages[first_page] = 0;   //O(log(M))
//        int num_users = 0;  //O(1)
//        //Общее число читателей
//        const size_t total_users = user_count_pages.size();   // O(1)
//        for(auto it = begin(pages_count_users); it != prev(end(pages_count_users)); it = next(it)){    //O(1000)
//            num_users += it->second;
//            rating_pages[next(it)->first] = 1.0 * num_users / (total_users - 1); //O(log(M))
//        }
//        // Расчет рейтинга
//        if(user_count_pages.size() == 1){   //O(1)
//            rating_pages[page] = 1;         //O(1)
//        }
//    }
//
//    double Cheer(const int user_id){
//        if(!user_count_pages.count(user_id)){ //O(log(M))
//            return 0;
//        }
//        else{
//            auto page = user_count_pages[user_id]; //O(log(M))
//            return  rating_pages[page];   //O(1)
//        }
//    }
//private:
//    // ключ - пользователь, значение - число страниц, которое он прочитал
//    map<int, int> user_count_pages;
//    // ключ - страницы из книги, значение - число пользователей,
//    // которые прочитали включительно по данную страницы
//    map<int, int> pages_count_users;
//    // ключ - страницы из книги, значение - число пользователей,
//    // которые прочитали до даной страницы
//    map<int, int> pages_count_less_readers;
//    // рейтинг каждой страницы
//    map<int, double> rating_pages;
//};



//// =========================================   №5(4)
//class ReadingManager{
//public:
//    ReadingManager() : pages_count_users(MAX_PAGE + 1),
//                       rating_pages(MAX_PAGE + 1){
//    }
//    void Read(const int user_id, const int page){
//        if(user_count_pages.count(user_id)){                                //O(log(M))
//            // номер старой страницы, до которой дочитал пользователь
//            auto last_page =  user_count_pages[user_id];      //O(log(M))
//            // уменьшилось число пользователей,
//            // кто прочитал до старой страницы
//            pages_count_users[last_page] -= 1;  //O(1)
//        }
//        // пользователь хранит новую страницу
//        user_count_pages[user_id] = page; //O(log(M))
//        // увеличилось число пользователей, кто прочитал до новой страницы
//        pages_count_users[page] += 1; //O(1)
//        // Для каждой страницы считаем ее рейтинг
//        int num_users = 0;  //O(1)
//        //Общее число читателей
//        const size_t total_users = user_count_pages.size();   // O(1)
//        for(int i = 1; i < pages_count_users.size(); ++i){    //O(1000)
//            num_users += pages_count_users[i];   // О(1)
//            rating_pages[i + 1] = 1.0 * num_users / (total_users - 1);   // О(1)
//        }
//        // Расчет рейтинга
//        if(user_count_pages.size() == 1){   //O(1)
//            rating_pages[page] = 1;         //O(1)
//        }
//        else{
//            rating_pages[1] = 0;           //O(1)
//        }
//    }
//
//    double Cheer(const int user_id){
//        if(!user_count_pages.count(user_id)){ //O(log(M))
//            return 0;
//        }
//        else{
//            auto page = user_count_pages[user_id]; //O(log(M))
//            return  rating_pages[page];   //O(1)
//        }
//    }
//private:
//    // ключ - пользователь, значение - число страниц, которое он прочитал
//    map<int, int> user_count_pages;
//    // индекс - страницы из книги, значение - число пользователей,
//    // которые прочитали включительно по данную страницы
//    vector<int> pages_count_users;
//    // индекс - страница, значение - рейтинг страницы
//    vector<double> rating_pages;
//    static const int MAX_PAGE = 1000;
//};

//////=========================================   №6 (2)
//class ReadingManager{
//public:
//    ReadingManager(): pages_count_user(MAX_PAGE + 1, 0),
//                      sum_count_user(MAX_PAGE + 1, 0){}
//    void Read(const int user_id, const int page){
//        if(user_count_pages.count(user_id)){ //O(log(M))
//            // номер старой страницы, до которой дочитал пользователь
//            auto last_page =  user_count_pages[user_id]; //O(log(M))
//            // уменьшилось число пользователей, кто прочитал до старой страницы
//            pages_count_user[last_page] -= 1;  //O(1)
//        }
//        // пользователь хранит новую страницу
//        user_count_pages[user_id] = page;  //O(log(M))
//        // увеличилось число пользователей, кто прочитал до новой страницы
//        pages_count_user[page] += 1;   //O(1)
//        int buffer = 0;
//        for(int i = page; i < pages_count_user.size(); ++i){    //O(1000)
//            int num = buffer + sum_count_user[i-1] + pages_count_user[i-1];
//            if(pages_count_user[i] == 0){
//                buffer = num ;
//            }
//            else{
//                sum_count_user[i] = num;
//                buffer = 0;
//            }
//        }
//
//    }
//
//    double Cheer(const int user_id){
//        if(!user_count_pages.count(user_id)){ //O(log(M))
//            return 0;
//        }
//        // Общее число читателей
//        const size_t total_users = user_count_pages.size();      //O(1)
//        if(total_users == 1){
//            return 1;
//        }
//        const int page = user_count_pages.at(user_id); //O(log(M))
//        int num_users = sum_count_user[page];
//
//        return 1.0 * num_users / (total_users - 1);
//    }
//
//private:
//    // ключ - пользователь, значение - число страниц, которое он прочитал
//    map<int, int> user_count_pages;
//    // ключ - страницы из книги, значение - число пользователей,
//    // которые прочитали включительно по данную страницы
//    vector<int> pages_count_user;
//    vector<int> sum_count_user;
//    static const int MAX_PAGE = 1000;
//};
//
class ReadingManager
{
public:
    ReadingManager() :
    people(MAX_USER_COUNT_ + 1, -1),
    pages(MAX_PAGE_COUNT_ + 1, 0) {}

    void Read(int user_id, int page_count)
    {
        for (int i = people[user_id] + 1; i <= page_count; i++)
        {
            ++pages[i];
        }
        people[user_id] = page_count;
    }

    double Cheer(int user_id) const
    {
        if (people[user_id] == -1)
        {
            return 0;
        }

        if (pages[0] == 1)
        {
            return 1;
        }
        return static_cast<double>(pages[0] - pages[people[user_id]]) / static_cast<double>(pages[0] - 1);
    }
private:
    static const int MAX_USER_COUNT_ = 100'000;
    static const int MAX_PAGE_COUNT_ = 1'000;

    std::vector<int> people;
    std::vector<int> pages;
};

void TestReadPage()
{
    {
        ReadingManager manager;
        ASSERT_EQUAL(manager.Cheer(1), 0.0);
        manager.Read(1, 1);
        ASSERT_EQUAL(manager.Cheer(1), 1.0);
    }
    {
        ReadingManager manager;
        ASSERT_EQUAL(manager.Cheer(1), 0.0);
        manager.Read(1, 1);
        ASSERT_EQUAL(manager.Cheer(2), 0.0);
    }
    {
        ReadingManager manager;
        manager.Read(1, 1);
        ASSERT_EQUAL(manager.Cheer(1), 1.0);
        manager.Read(1, 2);
        ASSERT_EQUAL(manager.Cheer(1), 1.0);
    }
    {
        ReadingManager manager;
        manager.Read(1, 1);
        manager.Read(2, 2);
        manager.Read(3, 3);
        ASSERT_EQUAL(manager.Cheer(2), 0.5);
        manager.Read(4, 4);
        ASSERT_EQUAL(manager.Cheer(2), 1.0 / 3.0);
    }
    {
        ReadingManager manager;
        manager.Read(1, 1);
        manager.Read(2, 2);
        manager.Read(3, 3);
        ASSERT_EQUAL(manager.Cheer(2), 0.5);
        manager.Read(4, 4);
        ASSERT_EQUAL(manager.Cheer(3), 2.0 / 3.0);
    }
    {
        ReadingManager manager;
        manager.Read(1, 0);
        manager.Read(2, 0);
        manager.Read(3, 1);
        manager.Read(4, 2);
        ASSERT_EQUAL(manager.Cheer(3), 2.0 / 3.0);
    }
    {
        ReadingManager manager;
        manager.Read(1, 5);
        manager.Read(2, 5);
        manager.Read(3, 5);
        manager.Read(4, 5);
        ASSERT_EQUAL(manager.Cheer(3), 0.0);
    }
    {
        ReadingManager manager;
        manager.Read(4, 5);
        manager.Read(3, 4);
        manager.Read(2, 3);
        manager.Read(1, 2);
        ASSERT_EQUAL(manager.Cheer(3), 2.0 / 3.0);
    }
    {
        ReadingManager manager;
        manager.Read(4, 5);
        manager.Read(3, 4);
        manager.Read(4, 6);
        manager.Read(3, 5);
        ASSERT_EQUAL(manager.Cheer(4), 1.0);
        ASSERT_EQUAL(manager.Cheer(3), 0.0);
        manager.Read(10, 2);
        ASSERT_EQUAL(manager.Cheer(3), 0.5);
        ASSERT_EQUAL(manager.Cheer(10000000), 1.0);
    }
    {
        ReadingManager manager;
        manager.Read(4, 5);
        ASSERT_EQUAL(manager.Cheer(4), 1.0);
        manager.Read(4, 6);
        ASSERT_EQUAL(manager.Cheer(4), 1.0);
        manager.Read(4, 100);
        ASSERT_EQUAL(manager.Cheer(4), 1.0);
        ASSERT_EQUAL(manager.Cheer(3), 0.0);
        ASSERT_EQUAL(manager.Cheer(5), 0.0);
    }
    {// ten users
        ReadingManager manager;
        manager.Read(1, 1);
        manager.Read(2, 2);
        manager.Read(3, 3);
        manager.Read(4, 4);
        manager.Read(5, 5);
        manager.Read(6, 6);
        manager.Read(7, 7);
        manager.Read(8, 8);
        manager.Read(9, 9);
        manager.Read(100, 10);
        manager.Read(111, 11);

        ASSERT_EQUAL(manager.Cheer(1), 0.0);
        ASSERT_EQUAL(manager.Cheer(2), 0.1);
        ASSERT_EQUAL(manager.Cheer(3), 0.2);
        ASSERT_EQUAL(manager.Cheer(4), 0.3);
        ASSERT_EQUAL(manager.Cheer(5), 0.4);
        ASSERT_EQUAL(manager.Cheer(6), 0.5);
        ASSERT_EQUAL(manager.Cheer(7), 0.6);
        ASSERT_EQUAL(manager.Cheer(8), 0.7);
        ASSERT_EQUAL(manager.Cheer(9), 0.8);
        ASSERT_EQUAL(manager.Cheer(100), 0.9);
        ASSERT_EQUAL(manager.Cheer(111), 1.0);
        ASSERT_EQUAL(manager.Cheer(12), 0.0);
    }
    {
        ReadingManager manager;

        ASSERT_EQUAL(manager.Cheer(1), 0.0);
        ASSERT_EQUAL(manager.Cheer(1), 0.0);
        manager.Read(1, 1);
        ASSERT_EQUAL(manager.Cheer(1), 1.0);
        ASSERT_EQUAL(manager.Cheer(1), 1.0);

        ASSERT_EQUAL(manager.Cheer(2), 0);
    }
    {
        const int MAX_USER_COUNT = 100'000;
        ReadingManager manager;
        ASSERT_EQUAL(manager.Cheer(MAX_USER_COUNT), 0.0);
        manager.Read(MAX_USER_COUNT, 1);
        ASSERT_EQUAL(manager.Cheer(MAX_USER_COUNT), 1.0);
    }
    {
        ReadingManager manager;
        ASSERT_EQUAL(manager.Cheer(1), 0.0);
        manager.Read(1, 1000);
        ASSERT_EQUAL(manager.Cheer(1), 1.0);
    }
    {
        const int MAX_USER_COUNT = 100'000;
        ReadingManager manager;
        ASSERT_EQUAL(manager.Cheer(MAX_USER_COUNT), 0.0);
        manager.Read(MAX_USER_COUNT, 1000);
        ASSERT_EQUAL(manager.Cheer(MAX_USER_COUNT), 1.0);
    }
    {
        ReadingManager manager;
        ASSERT_EQUAL(manager.Cheer(0), 0.0);
        manager.Read(0, 1000);
        ASSERT_EQUAL(manager.Cheer(0), 1.0);
    }
    {
        ReadingManager manager;
        manager.Read(1, 1);
        manager.Read(1, 3);
        manager.Read(2, 2);
        ASSERT_EQUAL(manager.Cheer(1), 1.0);
        ASSERT_EQUAL(manager.Cheer(10000), 0.0);
    }
}

int main() {
//    int query_count = 1e6;
//    ofstream os("queries.txt");
//    QueryGenerator(query_count, os);
//   Для ускорения чтения данных отключается синхронизация
//   cin и cout с stdio,
//   а также выполняется отвязка cin от cout
  
      TestRunner tr;
      RUN_TEST(tr, TestReadPage);
   {
      LOG_DURATION("Full_program 7");
      ios::sync_with_stdio(false);
      cin.tie(nullptr);

      ReadingManager manager;

      int query_count;
      cin >> query_count;

      for (int query_id = 0; query_id < query_count; ++query_id) {
        string query_type;
        cin >> query_type;
        int user_id;
        cin >> user_id;

        if (query_type == "READ") {
          int page_count;
          cin >> page_count;
          manager.Read(user_id, page_count);
        } else if (query_type == "CHEER") {
          cout << setprecision(6) << manager.Cheer(user_id) << "\n";
        }
      }
  }

  return 0;
}
