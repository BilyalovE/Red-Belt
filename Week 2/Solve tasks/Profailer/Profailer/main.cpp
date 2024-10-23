//
//  main.cpp
//  Profailer
//
//  Created by Билялов Эльдар on 23.10.2024.
//
#include "profailer.h"
#include <iostream>
#include <fstream>


using namespace std;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    {
        LOG_DURATION("'\\n'");
        for (int i = 0; i < 100000; ++i){
            int x;
            cin >> x;
            cout << x << '\n';
        }
    }
    {
        LOG_DURATION("endl");
        for (int i = 0; i < 100000; ++i){
            int x;
            cin >> x;
            cout << x << endl;
        }
    }
    return 0;
}
