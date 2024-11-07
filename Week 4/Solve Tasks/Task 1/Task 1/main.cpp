//
//  main.cpp
//  Task 1
//
//  Created by Билялов Эльдар on 06.11.2024.
//

#include <iostream>
#include <vector>
#include <list>

using namespace::std;
int main() {
    int n = 0;  // n <= 100000
    cin >> n;
    const int MAX_NUM_PLAYERS = 100000;
    list<int> queue;
    vector<list<int>::iterator> positions(MAX_NUM_PLAYERS, queue.end());
    int new_player = 0, next_player = 0;
    for (int i = 0; i < n; ++i) {   // O (N)
        cin >> new_player >> next_player;
        positions[new_player] = queue.insert(positions[next_player], new_player);
    }
    for(const auto q : queue){
        cout << q << "\n";
    }
    cout << "\n";
    return 0;
}
