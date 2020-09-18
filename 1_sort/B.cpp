#include <iostream>
#include <vector>

void insertionSort(std::vector<int>& array) {
    for (int i = 0; i < array.size(); ++i) {
        int key = array[i];
        int j = i - 1;
        while (j >= 0 && array[j] > key) {
            array[j + 1] = array[j];
            --j;
        }
        array[j + 1] = key;
    }
}

int main() {
    int n;
    std::cin >> n;
    std::vector<int> array(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> array[i];
    }
    insertionSort(array);
    for (int i = 0; i < n; ++i) {
        std::cout << array[i] << " ";
    }
    return 0;
}
