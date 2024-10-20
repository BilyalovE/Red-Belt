#include "test_runner.h"
#include <iostream>
#include <utility>
using namespace std;

template <typename  T>
class Table {
public:
    Table(const size_t num_rows_, const size_t num_columns_)
    {
        Resize(num_rows_, num_columns_);
    }
    
    vector<T>& operator[](const size_t index) {
        return table[index];
    }
    
    const vector<T>& operator[](const size_t index) const {
        return table[index];
    }
    
    void Resize(const size_t new_num_rows_,
                const size_t new_num_columns_){
        num_rows = new_num_rows_;
        num_columns = new_num_columns_;
        const T default_value = 1;
        table.resize(num_rows);
        for (auto& row : table){
            row.resize(num_columns, default_value);
        }
    };
    auto Size() const{
        return make_pair(num_rows, num_columns);
    }
    
private:
    
    size_t num_rows = 0, num_columns = 0;
    vector <vector<T>> table;
};

void TestTable() {
  Table<int> t(1, 1);
  ASSERT_EQUAL(t.Size().first, 1u);
  ASSERT_EQUAL(t.Size().second, 1u);
  t[0][0] = 42;
  ASSERT_EQUAL(t[0][0], 42);
  t.Resize(3, 4);
  ASSERT_EQUAL(t.Size().first, 3u);
  ASSERT_EQUAL(t.Size().second, 4u);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestTable);
  return 0;
}
