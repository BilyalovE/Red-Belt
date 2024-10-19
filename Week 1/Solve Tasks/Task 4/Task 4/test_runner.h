#pragma once
#include "airline_ticket.h"
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

bool operator<(const Time& lhs, const Time& rhs){
    return make_tuple(lhs.hours, lhs.minutes) <
           make_tuple(rhs.hours, rhs.minutes);
}

bool operator<(const Date& lhs, const Date& rhs){
    return make_tuple(lhs.year, lhs.month, lhs.day) <
           make_tuple(lhs.year, lhs.month, lhs.day);
}

bool operator==(const Date& lhs, const Date& rhs){
    return make_tuple(lhs.year, lhs.month, lhs.day) ==
           make_tuple(lhs.year, lhs.month, lhs.day);
}

bool operator==(const Time& lhs, const Time& rhs){
    return make_tuple(lhs.hours, lhs.minutes) ==
           make_tuple(rhs.hours, rhs.minutes);
}

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
  os << "{";
  bool first = true;
  for (const auto& kv : m) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << kv.first << ": " << kv.second;
  }
  return os << "}";
}

ostream& operator << (ostream& os, const Date& date) {
    os << date.year << "."
       << date.month << "."
       << date.day;
    return os;
}

ostream& operator << (ostream& os, const Time& time) {
    os << time.hours << ":"
       << time.minutes;
    return os;
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
  if (!(t == u)) {
    ostringstream os;
    os << "Assertion failed: " << t << " != " << u;
    if (!hint.empty()) {
       os << " hint: " << hint;
    }
    throw runtime_error(os.str());
  }
}

inline void Assert(bool b, const string& hint) {
  AssertEqual(b, true, hint);
}

class TestRunner {
public:
  template <class TestFunc>
  void RunTest(TestFunc func, const string& test_name) {
    try {
      func();
      cerr << test_name << " OK" << endl;
    } catch (exception& e) {
      ++fail_count;
      cerr << test_name << " fail: " << e.what() << endl;
    } catch (...) {
      ++fail_count;
      cerr << "Unknown exception caught" << endl;
    }
  }

  ~TestRunner() {
    if (fail_count > 0) {
      cerr << fail_count << " unit tests failed. Terminate" << endl;
      exit(1);
    }
  }

private:
  int fail_count = 0;
};

#define RUN_TEST(tr, func) \
tr.RunTest(func, #func)

#define ASSERT_EQUAL(x, y) {            \
    ostringstream os;                   \
    os << #x << " != " << #y << ",  "   \
       << __FILE__ << ": " << __LINE__; \
    AssertEqual(x, y, os.str());        \
}

#define ASSERT(x, y) {                  \
    ostringstream os;                   \
    os << #x << "is false, "            \
       << __FILE__ << ": " << __LINE__; \
    AssertEqual(x, y, os.str());        \
}

