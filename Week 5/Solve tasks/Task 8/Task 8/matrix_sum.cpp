//
//  main.cpp
//  Matrix
//
//  Created by Билялов Эльдар on 21.11.2024.
//

#include <iostream>
#include <vector>
#include "test_runner.h"
#include "profailer.h"
#include <future>
#include <numeric>

using namespace std;

template <typename Iterator>
class IteratorRange{
public:
    IteratorRange(Iterator first_, Iterator last_) :
            first(first_), last(last_) { }
    Iterator begin() const { return first; }
    Iterator end() const { return last; }
    size_t size() const {return last - first;}
private:
    Iterator first, last;
};

template <typename Iterator>
class Paginator {
public:
    Paginator(Iterator first_, Iterator last_,
              size_t page_size_) :
    first(first_), last(last_), page_size(page_size_) {
        size_t num_all_app = last - first;
        auto begin_iterator_range = first;
        while (num_all_app > 0) {
            IteratorRange vec_app = Head(begin_iterator_range, num_all_app);
            v_page.push_back(vec_app);
            size_t size_vec_app = vec_app.size();
            num_all_app -= size_vec_app;
            begin_iterator_range = next(begin_iterator_range, page_size);
        }
    }
    
    
    auto begin() const {
        return v_page.begin() ;
    }
    auto end() const { return  v_page.end() ; }
    
    size_t size() const { return  v_page.size(); }
    
private:
    
    auto Head(Iterator it, size_t num_all_app){
        return IteratorRange{it, next(it, min(page_size,  num_all_app))};
    }
    
    Iterator first, last;
    size_t page_size;
    vector<IteratorRange<Iterator>> v_page;
};

template <typename Container>
auto Paginate(Container& c, size_t page_size) {
    return Paginator {c.begin(), c.end(), page_size};
}

template <typename ContainerOfVectors>
void GenerateMatrixSingleThread(ContainerOfVectors& result,
                                size_t first_row,
                                size_t column_size){
    for(auto& row : result){
        row.reserve(column_size);
        for(size_t column = 0; column < column_size; ++column ){
            row.push_back(column ^ first_row);
        }
        ++first_row;
    }
}


vector<vector<int>>  GenerateMatrixSingleThread(const size_t size){
    vector<vector<int>> result(size);
    GenerateMatrixSingleThread(result, 0, size);
    return result;
}

vector<vector<int>>  GenerateMatrixMultiThread(const size_t size, const size_t page_size){
    vector<vector<int>> result(size);
    vector<future<void>> futures;
    size_t first_row = 0;
    for (auto page : Paginate(result, page_size)){
        futures.push_back(
            async([page, first_row, size](){
                GenerateMatrixSingleThread(page, first_row, size);
            })
        );
        first_row += page_size;
    }
    return result;
}

template <typename ContainerOfVectors>
int64_t SumMatrixSingleThread(const ContainerOfVectors& matrix){
    int64_t sum = 0;
    for(const auto& row : matrix){
        for(auto item : row){
            sum += item;
        }
    }
    return sum;
}

template <typename ContainerOfVectors>
int64_t SumMatrixMultiThread(const ContainerOfVectors& matrix){
    int page_size = 2000;
    int64_t sum = 0;
    vector<future<int64_t>> futures;
    for(const auto page : Paginate(matrix, page_size)){
        futures.push_back(
            async([=](){
               return SumMatrixSingleThread(page);
            })
        );
    }
    for(auto& item : futures){
        sum += item.get();
    }
    return sum;
}

int main(int argc, const char * argv[]) {
    LOG_DURATION("Total");
    vector<vector<int>> matrix;
    const size_t SIZE = 7000;
    {
        LOG_DURATION("GenerateMatrixSingleThread")
        matrix = GenerateMatrixSingleThread(SIZE);
    }
    {
        LOG_DURATION("GenerateMatrixMultiThread")
        matrix = GenerateMatrixMultiThread(SIZE, 2000);
    }
    {
        LOG_DURATION("SumMatrixSingleThread");
        cout <<  SumMatrixSingleThread(matrix) << "\n ";
    }
    {
        LOG_DURATION("SumMatrixMultiThread");
        cout << SumMatrixMultiThread(matrix) << "\n ";
    }
    
    return 0;
}

