//
//  main.cpp
//  Task 2
//
//  Created by Билялов Эльдар on 24.10.2024.
//

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "leaner.h"
#include "profailer.h"
#include <cstdlib>  // для rand() и srand()
#include <ctime>    // для time()

using namespace std;

//string generateRandomWord(int length) {
//    string alphabet = "abcdefghijklmnopqrstuvwxyz";  // Алфавит
//    string word = "";  // Будем накапливать слово
//
//    for (int i = 0; i < length; ++i) {
//        int randomIndex = rand() % alphabet.size();  // Случайный индекс
//        word += alphabet[randomIndex];  // Добавляем случайный символ
//    }
//    return word;
//}

int main() {
    {
        LOG_DURATION("full program");
        Learner learner;
        string line;
        while (getline(cin, line)) {
            vector<string> words;
            stringstream ss(line);
            string word;
            while (ss >> word) {
              words.push_back(word);
            }
            {
                LOG_DURATION("learner.Learn");
                cout << learner.Learn(words) << "\n";
                //learner.Learn(words);
            }
        }
        cout << "=== known words ===\n";
        {
            LOG_DURATION("learner.KnownWords");
            for (auto word : learner.KnownWords()) {
                cout << word << "\n";
            }
        }
    }
    return 0;
//    const uint wordLength = 10;
//    srand(static_cast<unsigned>(time(0)));  // Инициализация генератора случайных чисел
//
//    ofstream out("newWords.txt");
//    for (int i = 0; i < 100000; ++i){
//        out << generateRandomWord(wordLength) << ' ';
//    }
//    out << '\n';
}
