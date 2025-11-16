#ifndef DATA_GENERATOR_H
#define DATA_GENERATOR_H

#include <vector>
#include <algorithm>
#include <random>
#include <functional>

class DataGenerator {
public:
    enum DataType {
        RANDOM,
        SORTED,
        REVERSED,
        NEARLY_SORTED,
        FEW_UNIQUE
    };

    static std::vector<int> generateData(int size, DataType type) {
        std::vector<int> data(size);
        
        switch (type) {
            case RANDOM:
                generateRandom(data);
                break;
            case SORTED:
                generateSorted(data);
                break;
            case REVERSED:
                generateReversed(data);
                break;
            case NEARLY_SORTED:
                generateNearlySorted(data);
                break;
            case FEW_UNIQUE:
                generateFewUnique(data);
                break;
        }
        
        return data;
    }

private:
    static void generateRandom(std::vector<int>& data) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(1, data.size() * 10);
        
        for (int i = 0; i < data.size(); i++) {
            data[i] = dist(gen);
        }
    }

    static void generateSorted(std::vector<int>& data) {
        for (int i = 0; i < data.size(); i++) {
            data[i] = i + 1;
        }
    }

    static void generateReversed(std::vector<int>& data) {
        for (int i = 0; i < data.size(); i++) {
            data[i] = data.size() - i;
        }
    }

    static void generateNearlySorted(std::vector<int>& data) {
        // Сначала создаем отсортированный массив
        generateSorted(data);
        
        // Затем делаем несколько случайных перестановок
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(0, data.size() - 1);
        
        int swapCount = data.size() / 10; // 10% перестановок
        for (int i = 0; i < swapCount; i++) {
            int idx1 = dist(gen);
            int idx2 = dist(gen);
            std::swap(data[idx1], data[idx2]);
        }
    }

    static void generateFewUnique(std::vector<int>& data) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(1, 10); // Только 10 уникальных значений
        
        for (int i = 0; i < data.size(); i++) {
            data[i] = dist(gen);
        }
    }
};

#endif