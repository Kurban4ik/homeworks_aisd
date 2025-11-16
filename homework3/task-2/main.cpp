#include <iostream>
#include <fstream>
#include <vector>
#include "ArrayGenerator.h"
#include "SortTester.h"
#include <cmath>
void runExperiments() {
    const int minSize = 500;
    const int maxSize = 100000;
    const int step = 100;
    const int maxVal = 6000;
    
    std::vector<int> randomArray = ArrayGenerator::generateRandomArray(maxSize, 0, maxVal);
    std::vector<int> reverseArray = ArrayGenerator::generateReverseSortedArray(maxSize);
    std::vector<int> almostSortedArray = ArrayGenerator::generateAlmostSortedArray(maxSize, 10);

    std::ofstream standardRandom("standard_random.csv");
    std::ofstream standardReverse("standard_reverse.csv");
    std::ofstream standardAlmost("standard_almost.csv");
    
    std::ofstream hybridRandom("hybrid_random.csv");
    std::ofstream hybridReverse("hybrid_reverse.csv");
    std::ofstream hybridAlmost("hybrid_almost.csv");
    
    standardRandom << "Size,Time\n";
    standardReverse << "Size,Time\n";
    standardAlmost << "Size,Time\n";
    hybridRandom << "Size,Time\n";
    hybridReverse << "Size,Time\n";
    hybridAlmost << "Size,Time\n";
    
    for (int size = minSize; size <= maxSize; size += step) {
        
        std::vector<int> randomSub(randomArray.begin(), randomArray.begin() + size);
        std::vector<int> reverseSub(reverseArray.begin(), reverseArray.begin() + size);
        std::vector<int> almostSub(almostSortedArray.begin(), almostSortedArray.begin() + size);
        
        long long standardRandomTime = SortTester::measureTime(SortTester::mergeSort, randomSub, 0, size - 1);
        long long standardReverseTime = SortTester::measureTime(SortTester::mergeSort, reverseSub, 0, size - 1);
        long long standardAlmostTime = SortTester::measureTime(SortTester::mergeSort, almostSub, 0, size - 1);
        
        long long hybridRandomTime = SortTester::measureTime(SortTester::hybridMergeSort, randomSub, 0, size - 1, 10);
        long long hybridReverseTime = SortTester::measureTime(SortTester::hybridMergeSort, reverseSub, 0, size - 1, 10);
        long long hybridAlmostTime = SortTester::measureTime(SortTester::hybridMergeSort, almostSub, 0, size - 1, 10);
        
        standardRandom << size << "," << standardRandomTime << "\n";
        standardReverse << size << "," << standardReverseTime << "\n";
        standardAlmost << size << "," << standardAlmostTime << "\n";
        
        hybridRandom << size << "," << hybridRandomTime << "\n";
        hybridReverse << size << "," << hybridReverseTime << "\n";
        hybridAlmost << size << "," << hybridAlmostTime << "\n";
        
        standardRandom.flush();
        standardReverse.flush();
        standardAlmost.flush();
        hybridRandom.flush();
        hybridReverse.flush();
        hybridAlmost.flush();
    }
}

void testThresholds() {
    const int testSize = 10000;
    const int numRuns = 10; // Количество запусков для каждого порога
    
    std::vector<int> testArray = ArrayGenerator::generateRandomArray(testSize, 0, 6000);
    
    std::ofstream thresholdFile("threshold_test.csv");
    thresholdFile << "Threshold,Time,MinTime,MaxTime,StdDev\n";
    
    for (int threshold = 5; threshold <= 50; threshold += 5) {
        std::vector<long long> times;
        times.reserve(numRuns);
        
        // Запускаем тест 10 раз для текущего порога
        for (int run = 0; run < numRuns; ++run) {
            std::vector<int> arr = testArray; // Создаем копию для каждого запуска
            
            long long time = SortTester::measureTime(SortTester::hybridMergeSort, arr, 0, testSize - 1, threshold);
            times.push_back(time);
        }
        
        // Вычисляем статистику
        long long sum = 0;
        long long minTime = times[0];
        long long maxTime = times[0];
        
        for (long long time : times) {
            sum += time;
            if (time < minTime) minTime = time;
            if (time > maxTime) maxTime = time;
        }
        
        long long avgTime = sum / numRuns;
        
        long long sumSquares = 0;
        for (long long time : times) {
            long long diff = time - avgTime;
            sumSquares += diff * diff;
        }
        long long stdDev = static_cast<long long>(std::sqrt(sumSquares / numRuns));
        
        thresholdFile << threshold << "," << avgTime << "," << minTime << "," << maxTime << "," << stdDev << "\n";
        thresholdFile.flush();
        
        std::cout << "Threshold " << threshold << ": " 
                  << "avg=" << avgTime << "μs, "
                  << "min=" << minTime << "μs, "
                  << "max=" << maxTime << "μs, "
                  << "stddev=" << stdDev << "μs\n";
    }
}

int main() {
    std::cout << "Starting experiments..." << std::endl;
    runExperiments();
    std::cout << "Testing different thresholds..." << std::endl;
    testThresholds();
    std::cout << "Experiments completed!" << std::endl;
    return 0;
}