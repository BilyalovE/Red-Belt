////
////  main.cpp
////  Task E
////
////  Created by Билялов Эльдар on 03.11.2024.
////
//
//#include <iostream>
//#include <vector>
//#include <utility>
//#include <set>
//#include <cmath>
//#include <deque>
//#include <algorithm>
//#include "profailer.h"
//
//using namespace std;
//
//deque<int> getPrimesUpTo(int n) {
//    vector<bool> is_prime(n + 1, true);
//    deque<int> primes;
//
//    // Обработка базовых случаев
//    if (n < 2) return primes;
//
//    // Решето Эратосфена
//    is_prime[0] = is_prime[1] = false; // 0 и 1 не являются простыми числами
//    for (int i = 2; i * i <= n; ++i) {
//        if (is_prime[i]) {
//            for (int j = i * i; j <= n; j += i) {
//                is_prime[j] = false;
//            }
//        }
//    }
//
//    // Сбор простых чисел
//    for (int i = 2; i <= n; ++i) {
//        if (is_prime[i]) {
//            primes.push_back(i);
//        }
//    }
//
//    return primes;
//}
//
//vector<int> find_divisors(int n) {
//    vector<int> divisors;
//    int limit = static_cast<int>(sqrt(n)); // Предел проверки до корня из n
//
//    for (int i = 1; i <= limit; ++i) {
//        if (n % i == 0) {
//            divisors.push_back(i); // Добавляем i как делитель
//            if (i != n / i) {
//                divisors.push_back(n / i); // Добавляем парный делитель n / i, если он отличается
//            }
//        }
//    }
//
//    // Сортируем делители в порядке возрастания
//    sort(divisors.begin(), divisors.end());
//    return divisors;
//}
//
//
//int main(int argc, const char * argv[]) {
//    LOG_DURATION("full_programm");
//    int T = 0;
//    cin >> T;
//    vector<pair<int, int>> nums_pairs(T);
//    int A = 0, B = 0;
//    for (int i = 0; i < T; ++i){
//        cin >> A >> B;
//        nums_pairs[i] = make_pair(A, B);
//    }
//
//    // 1 случай: наибольшие делители двух чисел равны
//    // во множеств храним делители чисел
//    vector<int> dividers_min_num;
//    int counter = 0;
//    for(const auto& p : nums_pairs){
//        ++counter;
//        int max_num = max(p.first, p.second);
//        int min_num = min(p.first, p.second);
//        dividers_min_num = find_divisors(min_num);
//        // самый большой максимальный общий делитель - это большее число
//        // если 1 * на максимальное простое число до большого из чисел,
//        // то потенциально можно получить найибольший общий делитель - большее число,
//        // если простое число - макcимальное число
//        // получаю все простые числа до максимального числа
//        deque<int> simple_nums_to_max_num = getPrimesUpTo(max_num);
//        simple_nums_to_max_num.push_front(1);
//        int max_nod = 1;
//        int potential_max_nod = 1;
//        // максимальный общий делитель надо искать среди делителей большего числа
//        for(const int i : simple_nums_to_max_num){
//            for(int d_min : dividers_min_num){
//                if(max_num % (d_min * i) == 0){
//                    potential_max_nod = d_min * i;
//                    if(potential_max_nod > max_nod){
//                        max_nod = potential_max_nod ;
//                    }
//                }
//            }
//        }
//        if(counter != T){
//            cout << max_nod << "\n";
//        }
//        else{
//            cout << max_nod;
//        }
//    }
//    return 0;
//}

#include <iostream>
#include <vector>
#include <utility>
#include <set>
#include <cmath>
#include <deque>
#include <algorithm>
#include "profailer.h"

using namespace std;

// Функция для нахождения НОД
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Функция для нахождения всех простых чисел до n
deque<int> getPrimesUpTo(int n) {
    vector<bool> is_prime(n + 1, true);
    deque<int> primes;

    // Обработка базовых случаев
    if (n < 2) return primes;

    // Решето Эратосфена
    is_prime[0] = is_prime[1] = false; // 0 и 1 не являются простыми числами
    for (int i = 2; i * i <= n; ++i) {
        if (is_prime[i]) {
            for (int j = i * i; j <= n; j += i) {
                is_prime[j] = false;
            }
        }
    }

    // Сбор простых чисел
    for (int i = 2; i <= n; ++i) {
        if (is_prime[i]) {
            primes.push_back(i);
        }
    }

    return primes;
}

int main(int argc, const char * argv[]) {
    LOG_DURATION("full_programm");
    int T = 0;
    cin >> T;
    vector<pair<int, int>> nums_pairs(T);

    for (int i = 0; i < T; ++i) {
        cin >> nums_pairs[i].first >> nums_pairs[i].second;
    }

    for (const auto& p : nums_pairs) {
        int A = p.first;
        int B = p.second;

        // Находим текущий НОД
        int current_gcd = gcd(A, B);
        int max_gcd = current_gcd;

        // Получаем простые числа до максимального числа из A и B
        deque<int> primes = getPrimesUpTo(max(A, B));

        // Проверяем каждое простое число
        for (int prime : primes) {
            // Проверяем НОД после умножения A на простое
            max_gcd = max(max_gcd, gcd(A * prime, B));
            // Проверяем НОД после умножения B на простое
            max_gcd = max(max_gcd, gcd(A, B * prime));
        }

        cout << max_gcd << endl;
    }

    return 0;
}
