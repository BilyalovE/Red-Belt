//#pragma once
//#include <sstream>
//#include <stdexcept>
//#include <iostream>
//#include <map>
//#include <set>
//#include <string>
//#include <vector>
//
//using namespace std;
//
//
//template <class T>
//ostream& operator << (ostream& os, const vector<T>& s) {
//  os << "{";
//  bool first = true;
//  for (const auto& x : s) {
//    if (!first) {
//      os << ", ";
//    }
//    first = false;
//    os << x;
//  }
//  return os << "}";
//}
//
//template <class T>
//ostream& operator << (ostream& os, const set<T>& s) {
//  os << "{";
//  bool first = true;
//  for (const auto& x : s) {
//    if (!first) {
//      os << ", ";
//    }
//    first = false;
//    os << x;
//  }
//  return os << "}";
//}
//
//template <class K, class V>
//ostream& operator << (ostream& os, const map<K, V>& m) {
//  os << "{";
//  bool first = true;
//  for (const auto& kv : m) {
//    if (!first) {
//      os << ", ";
//    }
//    first = false;
//    os << kv.first << ": " << kv.second;
//  }
//  return os << "}";
//}
//
//
//
//
//template<class T, class U>
//void AssertEqual(const T& t, const U& u, const string& hint = {}) {
//  if (!(t == u)) {
//    ostringstream os;
//    os << "Assertion failed: " << t << " != " << u;
//    if (!hint.empty()) {
//       os << " hint: " << hint;
//    }
//    throw runtime_error(os.str());
//  }
//}
//
//inline void Assert(bool b, const string& hint) {
//  AssertEqual(b, true, hint);
//}
//
//class TestRunner {
//public:
//  template <class TestFunc>
//  void RunTest(TestFunc func, const string& test_name) {
//    try {
//      func();
//      cerr << test_name << " OK" << endl;
//    } catch (exception& e) {
//      ++fail_count;
//      cerr << test_name << " fail: " << e.what() << endl;
//    } catch (...) {
//      ++fail_count;
//      cerr << "Unknown exception caught" << endl;
//    }
//  }
//
//  ~TestRunner() {
//    if (fail_count > 0) {
//      cerr << fail_count << " unit tests failed. Terminate" << endl;
//      exit(1);
//    }
//  }
//
//private:
//  int fail_count = 0;
//};
//
//#define RUN_TEST(tr, func) \
//tr.RunTest(func, #func)
//
//#define ASSERT_EQUAL(x, y) {            \
//    ostringstream os;                   \
//    os << #x << " != " << #y << ",  "   \
//       << __FILE__ << ": " << __LINE__; \
//    AssertEqual(x, y, os.str());        \
//}
//
//#define ASSERT(x, y) {                  \
//    ostringstream os;                   \
//    os << #x << "is false, "            \
//       << __FILE__ << ": " << __LINE__; \
//    AssertEqual(x, y, os.str());        \
//}
//

#pragma once

#ifndef _TEST_RUNNER_H_
#define _TEST_RUNNER_H_

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <set>
#include <map>

//-------------------------------------------------------------------------------------------------
class TestRunner
{
public:
    template <typename test_func>
    void RunTest(test_func func, const std::string& test_name);
    
    TestRunner() = default;
    ~TestRunner();
private:
    int fail_count = 0;
};
//-------------------------------------------------------------------------------------------------
template <typename test_func>
void TestRunner::RunTest(test_func func, const std::string& test_name)
{
    try
    {
        func();
        std::cerr << "PASSED: " << test_name << std::endl;
    }
    catch (const std::runtime_error & e)
    {
        ++fail_count;
        std::cerr << "FAIL: " << test_name << e.what() << std::endl;
    }
}
//-------------------------------------------------------------------------------------------------
template <typename T>
std::ostream& operator << (std::ostream& os, const std::set<T>& s)
{
    os << "{";
    bool first = true;
    for (const auto& x : s)
    {
        if (!first)
        {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}
//-------------------------------------------------------------------------------------------------
template <typename Key, typename Value>
std::ostream& operator << (std::ostream& os, const std::map<Key, Value>& map)
{
    os << "{";
    bool first = true;
    for (const auto& kv : map)
    {
        if (!first)
        {
            os << ", ";
        }
        first = false;
        os << kv.first << ": " << kv.second;
    }
    return os << "}";
}
//-------------------------------------------------------------------------------------------------
template <typename T>
std::ostream& operator << (std::ostream& os, const std::vector<T>& s)
{
    os << "{";
    bool first = true;
    for (const auto& x : s)
    {
        if (!first)
        {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}
//-------------------------------------------------------------------------------------------------
void Assert(bool b, const std::string& hint);
//-------------------------------------------------------------------------------------------------
template<typename T, typename U>
void AssertEqual(const T& t, const U& u, const std::string& hint)
{
    if (t != u)
    {
        std::ostringstream os;
        os << " Assertion failed: " << std::endl;
        os << t << " != " << u << " hint: " << hint;
        throw std::runtime_error(os.str());
    }
}

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

//----------------------------------------------------------------------------------------------------
void Assert(bool b, const std::string& hint)
{
    AssertEqual(b, true, hint);
}
//----------------------------------------------------------------------------------------------------
TestRunner::~TestRunner()
{
    if (fail_count > 0)
    {
        std::cerr << "========================================" << std::endl;
        std::cerr << "FAILED (failures = " << fail_count << ")" << std::endl;
        std::cerr << "========================================" << std::endl;
        exit(1);
    }
    else
    {
        std::cerr << "========================================" << std::endl;
        std::cerr << "OK" << std::endl;
        std::cerr << "========================================" << std::endl;
    }
}
//-------------------------------------------------------------------------------------------------
#endif // _TEST_RUNNER_H_
