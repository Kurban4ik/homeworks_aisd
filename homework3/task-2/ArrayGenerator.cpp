#include "ArrayGenerator.h"
#include <random>
#include <algorithm>

std::vector<int> ArrayGenerator::generateRandomArray(int size, int minVal, int maxVal) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(minVal, maxVal);
    
    std::vector<int> arr(size);
    for (int i = 0; i < size; ++i) {
        arr[i] = dist(gen);
    }
    return arr;
}

std::vector<int> ArrayGenerator::generateReverseSortedArray(int size) {
    std::vector<int> arr(size);
    for (int i = 0; i < size; ++i) {
        arr[i] = size - i;
    }
    return arr;
}

std::vector<int> ArrayGenerator::generateAlmostSortedArray(int size, int swapsCount) {
    std::vector<int> arr(size);
    for (int i = 0; i < size; ++i) {
        arr[i] = i + 1;
    }
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, size - 1);
    
    for (int i = 0; i < swapsCount; ++i) {
        int idx1 = dist(gen);
        int idx2 = dist(gen);
        std::swap(arr[idx1], arr[idx2]);
    }
    return arr;
}