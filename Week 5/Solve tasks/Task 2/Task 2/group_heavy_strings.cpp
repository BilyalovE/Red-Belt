#include "test_runner.h"
#include "profailer.h"
#include <utility>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

// Объявляем Group<String> для произвольного типа String
// синонимом vector<String>.
// Благодаря этому в качестве возвращаемого значения
// функции можно указать не малопонятный вектор векторов,
// а вектор групп — vector<Group<String>>.
template <typename String>
using Group = vector<String>;

// Ещё один шаблонный синоним типа
// позволяет вместо громоздкого typename String::value_type
// использовать Char<String>
template <typename String>
using Char = typename String::value_type;



template <typename String>
vector<Group<String>> GroupHeavyStrings(vector<String> strings) { //O(N*M*K) = 10ˆ9
  // Напишите реализацию функции,
  // использовав не более 1 копирования каждого символа
    map<set<Char<String>>, Group<String>> map_groups;
    set<Char<String>> group_in_word;
    for(auto& word : strings){  //O(N) N = 100000
        group_in_word.clear();
        for (auto Ch : word){    //O(M) M = 100
            group_in_word.insert(Ch); //O(K)  K = 100
         }
        map_groups[move(group_in_word)].push_back(move(word));
    }
    vector<Group<String>> res_group;
    res_group.reserve(map_groups.size());
    for(auto group : map_groups){   //O(N) N = 100000
        res_group.push_back(move(group.second));
    }
    return res_group;
}



void TestGroupingABC() {
  vector<string> strings = {"caab", "abc", "cccc", "bacc", "c"};
  auto groups = GroupHeavyStrings(strings);
  ASSERT_EQUAL(groups.size(), 2);
  sort(begin(groups), end(groups));  // Порядок групп не имеет значения
  ASSERT_EQUAL(groups[0], vector<string>({"caab", "abc", "bacc"}));
  ASSERT_EQUAL(groups[1], vector<string>({"cccc", "c"}));
}

void TestGroupingReal() {
  vector<string> strings = {"law", "port", "top", "laptop", "pot", "paloalto", "wall", "awl"};
  auto groups = GroupHeavyStrings(strings);
  ASSERT_EQUAL(groups.size(), 4);
  sort(begin(groups), end(groups));  // Порядок групп не имеет значения
  ASSERT_EQUAL(groups[0], vector<string>({"laptop", "paloalto"}));
  ASSERT_EQUAL(groups[1], vector<string>({"law", "wall", "awl"}));
  ASSERT_EQUAL(groups[2], vector<string>({"port"}));
  ASSERT_EQUAL(groups[3], vector<string>({"top", "pot"}));
}

vector<string> HeavyVector(){
    const int MAX_VEC_SIZE = 100000;
    const int MAX_WORD_SIZE = 100;
    vector<string> heavy_vector;
    heavy_vector.reserve(MAX_VEC_SIZE);
    for(int i = 0; i < MAX_VEC_SIZE; ++i){
        heavy_vector.push_back(string(MAX_WORD_SIZE, 'a'));
    }
    return heavy_vector;
}

int main() {
      TestRunner tr;
      RUN_TEST(tr, TestGroupingABC);
      RUN_TEST(tr, TestGroupingReal);
    {
        LOG_DURATION("TestGroupingWithoutCopy");
        auto groups = GroupHeavyStrings(HeavyVector());
    }
  return 0;
}
