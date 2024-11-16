#include "simple_vector.h"
#include "test_runner.h"

#include <numeric>
#include <vector>
#include <tuple>

using namespace std;

template <typename T>
void PrintVector(const SimpleVector<T>& vec){
    for (const auto& v : vec){
        cout << v << " ";
    }
    cout << "\n";
}

void TestCopyCtor() {
  SimpleVector<int> numbers(10);
  iota(numbers.begin(), numbers.end(), 1);

  SimpleVector<int> dest = numbers;
  ASSERT_EQUAL(dest.Size(), 10u);
  ASSERT_EQUAL(dest.Size(), numbers.Size());
  ASSERT(dest.Capacity() >= dest.Size());
  ASSERT(equal(dest.begin(), dest.end(), numbers.begin()));
}


void TestCopyAssignment() {
  SimpleVector<int> numbers(10);
  iota(numbers.begin(), numbers.end(), 1);

  SimpleVector<int> dest;
  ASSERT_EQUAL(dest.Size(), 0u);

  dest = numbers;
  ASSERT_EQUAL(dest.Size(), numbers.Size());
  ASSERT(dest.Capacity() >= dest.Size());
  ASSERT(equal(dest.begin(), dest.end(), numbers.begin()));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestCopyCtor);
  RUN_TEST(tr, TestCopyAssignment);
    SimpleVector<int> source(1);
    SimpleVector<int> target;
    target = move(source);
    cout << source.Size() << target.Size() << "\n";
}
