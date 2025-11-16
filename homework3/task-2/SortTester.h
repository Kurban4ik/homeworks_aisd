#ifndef SORT_TESTER_H
#define SORT_TESTER_H

#include <vector>
#include <chrono>
#include <functional>

class SortTester {
public:
    static void mergeSort(std::vector<int>& arr, int l, int r);
    static void hybridMergeSort(std::vector<int>& arr, int l, int r, int threshold);
    
    template<typename Func, typename... Args>
    static long long measureTime(Func sortFunc, std::vector<int> arr, Args... args);
    
private:
    static void insertionSort(std::vector<int>& arr, int l, int r);
    static void merge(std::vector<int>& arr, int l, int m, int r);
};

template<typename Func, typename... Args>
long long SortTester::measureTime(Func sortFunc, std::vector<int> arr, Args... args) {
    auto start = std::chrono::high_resolution_clock::now();
    sortFunc(arr, args...);
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    return std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
}

#endif