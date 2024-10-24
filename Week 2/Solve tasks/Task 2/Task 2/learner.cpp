#include "leaner.h"

int Learner::Learn(const vector<string>& words) {
    int newWords = 0;
    for (const auto& word : words) {
      if (lower_bound(dict.begin(), dict.end(), word) == dict.end()) {
        ++newWords;
        dict.push_back(word);
      }
    }
    return newWords;
}

vector<string> Learner::KnownWords() {
    sort(dict.begin(), dict.end());
    dict.erase(unique(dict.begin(), dict.end()), dict.end());
    return dict;
}

