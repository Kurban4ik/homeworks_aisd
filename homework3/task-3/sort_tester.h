#ifndef SORT_TESTER_H
#define SORT_TESTER_H

#include <vector>
#include <chrono>
#include <string>
#include <fstream>
#include <iostream>
#include "sort_algorithms.h"
#include "data_generator.h"

class SortTester {
private:
    struct TestResult {
        std::string algorithm;
        std::string dataType;
        int size;
        double timeMs;
        bool sortedCorrectly;
    };

    std::vector<TestResult> results;

    static bool isSorted(const std::vector<int>& arr) {
        for (size_t i = 1; i < arr.size(); i++) {
            if (arr[i] < arr[i - 1]) {
                return false;
            }
        }
        return true;
    }

    static std::vector<int> copyArray(const std::vector<int>& original) {
        return std::vector<int>(original);
    }

public:
    template<typename SortFunction>
    TestResult testAlgorithm(SortFunction sortFunc, const std::string& algoName, 
                           const std::vector<int>& originalData, const std::string& dataType) {
        TestResult result;
        result.algorithm = algoName;
        result.dataType = dataType;
        result.size = originalData.size();

        std::vector<int> testData = copyArray(originalData);

        auto start = std::chrono::high_resolution_clock::now();
        
        sortFunc(testData);
        
        auto end = std::chrono::high_resolution_clock::now();
        
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        result.timeMs = duration.count() / 1000.0;
        
        result.sortedCorrectly = isSorted(testData);

        return result;
    }

    // Запуск всех тестов
    void runAllTests(const std::vector<int>& sizes = {100, 500, 1000, 5000, 10000, 50000, 100000}) {
        std::cout << "Starting performance tests..." << std::endl;
        
        std::vector<DataGenerator::DataType> dataTypes = {
            DataGenerator::RANDOM,
            DataGenerator::SORTED, 
            DataGenerator::REVERSED,
            DataGenerator::NEARLY_SORTED,
            DataGenerator::FEW_UNIQUE
        };

        std::vector<std::string> dataTypeNames = {
            "RANDOM", "SORTED", "REVERSED", "NEARLY_SORTED", "FEW_UNIQUE"
        };

        for (int size : sizes) {
            std::cout << "Testing size: " << size << std::endl;
            
            for (size_t i = 0; i < dataTypes.size(); i++) {
                // Генерируем тестовые данные
                std::vector<int> testData = DataGenerator::generateData(size, dataTypes[i]);
                
                // Тестируем стандартный Quick Sort
                auto result1 = testAlgorithm(
                    [](std::vector<int>& arr) { SortAlgorithms::quickSortStandard(arr); },
                    "QuickSort_Standard",
                    testData,
                    dataTypeNames[i]
                );
                results.push_back(result1);

                // Тестируем гибридный Introsort
                auto result2 = testAlgorithm(
                    [](std::vector<int>& arr) { SortAlgorithms::quickSortHybrid(arr); },
                    "QuickSort_Hybrid", 
                    testData,
                    dataTypeNames[i]
                );
                results.push_back(result2);

                std::cout << "  " << dataTypeNames[i] 
                          << " - Standard: " << result1.timeMs << "ms"
                          << ", Hybrid: " << result2.timeMs << "ms"
                          << std::endl;
            }
        }
    }

    void saveResultsToCSV(const std::string& filename) {
        std::ofstream file(filename);
        file << "Algorithm,DataType,Size,TimeMs,Correct\n";
        
        for (const auto& result : results) {
            file << result.algorithm << ","
                 << result.dataType << ","
                 << result.size << ","
                 << result.timeMs << ","
                 << (result.sortedCorrectly ? "true" : "false") << "\n";
        }
        
        file.close();
        std::cout << "Results saved to: " << filename << std::endl;
    }

    // Вывод сводки результатов
    void printSummary() {
        std::cout << "\n=== TEST RESULTS SUMMARY ===" << std::endl;
        
        for (const auto& result : results) {
            std::cout << result.algorithm << " - " << result.dataType 
                      << " (n=" << result.size << "): " 
                      << result.timeMs << "ms - "
                      << (result.sortedCorrectly ? "PASS" : "FAIL") << std::endl;
        }
    }

    const std::vector<TestResult>& getResults() const {
        return results;
    }
};

#endif