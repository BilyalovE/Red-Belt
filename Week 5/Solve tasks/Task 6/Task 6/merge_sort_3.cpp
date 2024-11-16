#include "test_runner.h"
#include <algorithm>
#include <memory>
#include <vector>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
  // Напишите реализацию функции,
  // не копируя сортируемые элементы
    if(range_end - range_begin < 2){
        return;
    }
    using type = typename RandomIt::value_type;
    vector<type> vec(make_move_iterator(range_begin), make_move_iterator(range_end));
    //разбить вектор на 3 равные части
    size_t len = vec.size() / 3;
    vector<vector<type>> groups(3);
    size_t j = -1;
    for(int i = 0; i < vec.size(); ++i){
        if(i % len == 0) { ++j; }
        groups[j].push_back(move(vec[i]));
    }
    for(auto& v : groups) { MergeSort(v.begin(), v.end()); }
    vector<typename RandomIt::value_type> temp_merge_nums;
    merge(make_move_iterator(begin(groups[0])), make_move_iterator(end(groups[0])),
          make_move_iterator(begin(groups[1])), make_move_iterator(end(groups[1])),
          back_inserter(temp_merge_nums));
    vector<typename RandomIt::value_type> merge_nums;
    merge(make_move_iterator(begin(temp_merge_nums)), make_move_iterator(end(temp_merge_nums)),
          make_move_iterator(begin(groups[2])), make_move_iterator(end(groups[2])),
          back_inserter(merge_nums));
    // Копируем отсортированный результат обратно в исходный диапазон
    move(merge_nums.begin(), merge_nums.end(), range_begin);
}

void TestIntVector() {
  vector<int> numbers = {6, 1, 3, 9, 1, 9, 8, 12, 1};
  MergeSort(begin(numbers), end(numbers));
  ASSERT(is_sorted(begin(numbers), end(numbers)));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestIntVector);
  return 0;
}
