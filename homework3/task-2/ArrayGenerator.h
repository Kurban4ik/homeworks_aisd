#ifndef ARRAY_GENERATOR_H
#define ARRAY_GENERATOR_H

#include <vector>

class ArrayGenerator {
public:
    static std::vector<int> generateRandomArray(int size, int minVal, int maxVal);
    static std::vector<int> generateReverseSortedArray(int size);
    static std::vector<int> generateAlmostSortedArray(int size, int swapsCount);
};

#endif