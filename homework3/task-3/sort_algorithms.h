#ifndef SORT_ALGORITHMS_H
#define SORT_ALGORITHMS_H

#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>

class SortAlgorithms {
private:
    // Вспомогательные функции для Heap Sort
    static void heapify(std::vector<int>& arr, int n, int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && arr[left] > arr[largest])
            largest = left;

        if (right < n && arr[right] > arr[largest])
            largest = right;

        if (largest != i) {
            std::swap(arr[i], arr[largest]);
            heapify(arr, n, largest);
        }
    }

    static void buildHeap(std::vector<int>& arr, int n) {
        for (int i = n / 2 - 1; i >= 0; i--)
            heapify(arr, n, i);
    }

    static int partition(std::vector<int>& arr, int low, int high) {
        int randomIndex = low + rand() % (high - low + 1);
        std::swap(arr[randomIndex], arr[high]);
        
        int pivot = arr[high];
        int i = low - 1;

        for (int j = low; j < high; j++) {
            if (arr[j] <= pivot) {
                i++;
                std::swap(arr[i], arr[j]);
            }
        }
        std::swap(arr[i + 1], arr[high]);
        return i + 1;
    }

    static void insertionSort(std::vector<int>& arr, int low, int high) {
        for (int i = low + 1; i <= high; i++) {
            int key = arr[i];
            int j = i - 1;

            while (j >= low && arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
    }

    static void heapSortPartial(std::vector<int>& arr, int low, int high) {
        int n = high - low + 1;
        std::vector<int> temp(n);
        
        for (int i = 0; i < n; i++) {
            temp[i] = arr[low + i];
        }

        buildHeap(temp, n);

        for (int i = n - 1; i >= 0; i--) {
            std::swap(temp[0], temp[i]);
            heapify(temp, i, 0);
        }

        for (int i = 0; i < n; i++) {
            arr[low + i] = temp[i];
        }
    }

    static void quickSortStandardRecursive(std::vector<int>& arr, int low, int high) {
        if (low < high) {
            int pi = partition(arr, low, high);
            quickSortStandardRecursive(arr, low, pi - 1);
            quickSortStandardRecursive(arr, pi + 1, high);
        }
    }

    static void quickSortHybridRecursive(std::vector<int>& arr, int low, int high, int depthLimit) {
        if (high - low < 16) {
            insertionSort(arr, low, high);
            return;
        }

        if (depthLimit == 0) {
            heapSortPartial(arr, low, high);
            return;
        }

        // Обычный Quick Sort
        int pi = partition(arr, low, high);
        quickSortHybridRecursive(arr, low, pi - 1, depthLimit - 1);
        quickSortHybridRecursive(arr, pi + 1, high, depthLimit - 1);
    }

public:
    // Стандартный Quick Sort
    static void quickSortStandard(std::vector<int>& arr) {
        if (arr.size() <= 1) return;
        quickSortStandardRecursive(arr, 0, arr.size() - 1);
    }

    // Гибридный Introsort
    static void quickSortHybrid(std::vector<int>& arr) {
        if (arr.size() <= 1) return;
        
        // Вычисляем максимальную глубину рекурсии: 2 * log2(n)
        int depthLimit = 2 * static_cast<int>(log2(arr.size()));
        quickSortHybridRecursive(arr, 0, arr.size() - 1, depthLimit);
    }

    // Insertion Sort (для сравнения)
    static void insertionSort(std::vector<int>& arr) {
        insertionSort(arr, 0, arr.size() - 1);
    }

    // Heap Sort (для сравнения)
    static void heapSort(std::vector<int>& arr) {
        int n = arr.size();
        if (n <= 1) return;

        buildHeap(arr, n);

        for (int i = n - 1; i > 0; i--) {
            std::swap(arr[0], arr[i]);
            heapify(arr, i, 0);
        }
    }
};

#endif