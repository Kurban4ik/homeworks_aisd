#include <iostream>

int main() {
    int n = 1000;
    int large1 = 0;
    int ar[] = {6, 3, 10, 1, 4, 9, 14, ...} ; // наш предполагаемый массив
    while (2 * large1 + 2 < n) {
        large1 = 2 * large1 + 2;
    }
    
    int large2;
    // Находим индекс второго наибольшего элемента
    if (ar[2 * large1 + 1] != -1) { // предполагаем, что если пустой элемент есть, он обозначен через -1
        large2 = 2 * large1 + 1;
        while (2 * large2 + 2 < n) {
            large2 = 2 * large2 + 2;
        }
    } else {
        large2 = (large1 - 2) / 2;
    }
    
    int large3;
    // Находим индекс третьего наибольшего элемента
    if (ar[2 * large2 + 1] != -1) {
        large3 = 2 * large2 + 1;
        while (2 * large3 + 2 < n) {
            large3 = 2 * large3 + 2;
        }
    } else {
        large3 = (large2 - 2) / 2;
    }

}
