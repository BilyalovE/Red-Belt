#pragma once

#include <chrono>
#include <iostream>
#include <string>
using namespace std;
using namespace chrono;

class LogDuration{
public:
    explicit LogDuration(const string& msg) :
        message(msg + ": "), start(steady_clock::now()) { }
    
    ~LogDuration (){
        auto finish = steady_clock::now();
        auto duration = finish - start;
        cerr << message << duration_cast<milliseconds>(duration).count() << " ms" << endl;
        
    }
private:
    const string message;
    steady_clock::time_point start;
};

#define g(a) _a_local_var_##a
#define UNIQ_ID(a) g(a)

#define LOG_DURATION(message)  \
    LogDuration UNIQ_ID(__LINE__){message};
