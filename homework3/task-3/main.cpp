#include <iostream>
#include <vector>
#include <string>
#include "sort_tester.h"

void runPerformanceAnalysis() {
    SortTester tester;
    
    // Размеры массивов для тестирования
    std::vector<int> sizes = {100, 500, 1000, 5000, 10000, 25000, 50000, 100000};
    
    std::cout << "=== PERFORMANCE ANALYSIS: STANDARD vs HYBRID QUICKSORT ===" << std::endl;
    std::cout << "Test sizes: ";
    for (int size : sizes) {
        std::cout << size << " ";
    }
    std::cout << std::endl << std::endl;
    
    // Запуск всех тестов
    tester.runAllTests(sizes);
    
    // Сохранение результатов
    tester.saveResultsToCSV("sorting_performance_results.csv");
    
    // Вывод сводки
    tester.printSummary();
}

void demoSmallExample() {
    std::cout << "\n=== DEMONSTRATION ON SMALL EXAMPLE ===" << std::endl;
    
    // Создаем тестовый массив
    std::vector<int> testArray = {64, 34, 25, 12, 22, 11, 90, 5, 77, 30};
    std::vector<int> copy1 = testArray;
    std::vector<int> copy2 = testArray;
    
    std::cout << "Original array: ";
    for (int num : testArray) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    // Тестируем стандартный Quick Sort
    SortAlgorithms::quickSortStandard(copy1);
    std::cout << "Standard QuickSort: ";
    for (int num : copy1) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    // Тестируем гибридный Introsort
    SortAlgorithms::quickSortHybrid(copy2);
    std::cout << "Hybrid Introsort: ";
    for (int num : copy2) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

int main() {
    // Инициализация генератора случайных чисел
    srand(static_cast<unsigned int>(time(nullptr)));
    
    // Демонстрация на маленьком примере
    demoSmallExample();
    
    // Полный анализ производительности
    runPerformanceAnalysis();
    
    std::cout << "\n=== ANALYSIS COMPLETE ===" << std::endl;
    std::cout << "Results saved to 'sorting_performance_results.csv'" << std::endl;
    std::cout << "Use the Python script to visualize the results." << std::endl;
    
    return 0;
}