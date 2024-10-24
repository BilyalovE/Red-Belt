#pragma once
#include <algorithm>
#include <string>
#include <vector>

using namespace std;
class Learner {
 private:
  vector<string> dict;
 public:
    int Learn(const vector<string>& words);
    vector<string> KnownWords();
};
