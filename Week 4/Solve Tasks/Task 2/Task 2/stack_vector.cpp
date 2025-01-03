#include "stack_vector.h"

#include "test_runner.h"
#include "profailer.h"

#include <random>
#include <stdexcept>
#include <sstream>
using namespace std;

template <typename T, size_t N>
void Print(const StackVector<T, N>& v){
    for (auto it = v.begin(); it != v.end(); ++it){
        cout << *it << " ";
    }
    cout << "\n";
}



void TestConstruction() {
  StackVector<int, 10> v;
  ASSERT_EQUAL(v.Size(), 0u);
  ASSERT_EQUAL(v.Capacity(), 10u);

  StackVector<int, 8> u(5);
  ASSERT_EQUAL(u.Size(), 5u);
  ASSERT_EQUAL(u.Capacity(), 8u);

  try {
    StackVector<int, 10> u(50);
    Assert(false, "Expect invalid_argument for too large size");
  }
    catch (invalid_argument&) {
  } catch (...) {
    Assert(false, "Unexpected exception for too large size");
  }
}

void TestPushBack() {
    StackVector<int, 5> v;
    for (size_t i = 0; i < v.Capacity(); ++i) {
        v.PushBack(i);
    }
    ostringstream array;
    for (size_t i = 0; i < v.Capacity(); ++i) {
        array << v[i];
    }
    stringstream expected_array("01234");
    ASSERT_EQUAL(array.str(), expected_array.str());
    try {
        v.PushBack(0);
        Assert(false, "Expect overflow_error for PushBack in full vector");
    } catch (overflow_error&) {
    } catch (...) {
        Assert(false, "Unexpected exception for PushBack in full vector");
    }
}

void TestPopBack() {
    StackVector<int, 5> v;
    for (size_t i = 1; i <= v.Capacity(); ++i) {
        v.PushBack(i);
    }
    ostringstream array;
    for (size_t i = 0; i < v.Capacity(); ++i) {
        array << v[i];
    }
    stringstream expected_array("12345");
    ASSERT_EQUAL(array.str(), expected_array.str());
    
    for (int i = v.Size(); i > 0; --i) {
        ASSERT_EQUAL(v.PopBack(), i);
    }
    try {
        v.PopBack();
        Assert(false, "Expect underflow_error for PopBack from empty vector");
    } catch (underflow_error&) {
    } catch (...) {
        Assert(false, "Unexpected exception for PopBack from empty vector");
    }
}

int main() {
    StackVector<int, 5> v;
    for (size_t i = 1; i <= v.Capacity(); ++i) {
        v.PushBack(i);
    }
    
    Print(v);
    {
        TestRunner tr;
        RUN_TEST(tr, TestConstruction);
        RUN_TEST(tr, TestPushBack);
        RUN_TEST(tr, TestPopBack);
    }

    cerr << "Running benchmark..." << endl;
    const size_t max_size = 2500;

    default_random_engine re;
    uniform_int_distribution<int> value_gen(1, max_size);

    vector<vector<int>> test_data(50000);
    for (auto& cur_vec : test_data) {
        cur_vec.resize(value_gen(re));
        for (int& x : cur_vec) {
            x = value_gen(re);
        }
    }

    {
        LOG_DURATION("vector w/o reserve");
        for (auto& cur_vec : test_data) {
            vector<int> v;
            for (int x : cur_vec) {
                v.push_back(x);
            }
        }
    }
    {
    LOG_DURATION("vector with reserve");
        for (auto& cur_vec : test_data) {
            vector<int> v;
            v.reserve(cur_vec.size());
            for (int x : cur_vec) {
                v.push_back(x);
            }
        }
    }
    {
        LOG_DURATION("StackVector");
        for (auto& cur_vec : test_data) {
            StackVector<int, max_size> v;
            for (int x : cur_vec) {
                v.PushBack(x);
            }
        }
    }
    cerr << "Done" << endl;
}
