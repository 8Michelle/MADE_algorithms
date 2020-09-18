#include <iostream>
#include <vector>

void merge(std::vector<int>& array, int left, int medium, int right) {
    int i = 0;
    int j = 0;
    std::vector<int> buff(right - left);
    while (left + i < medium && medium + j < right) {
        if (array[left + i] < array[medium + j]) {
            buff[i + j] = array[left + i];
            ++i;
        } else {
            buff[i + j] = array[medium + j];
            ++j;
        }
    }
    while (left + i < medium) {
        buff[i + j] = array[left + i];
        ++i;
    }
    while (medium + j < right) {
        buff[i + j] = array[medium + j];
        ++j;
    }
    for (int i = 0; i < buff.size(); ++i) {
        array[left + i] = buff[i];
    }
}

void mergeSort(std::vector<int>& array, int left, int right) {
    if (right - left > 1) {
        int medium = (left + right) / 2;
        mergeSort(array, left, medium);
        mergeSort(array, medium, right);
        merge(array, left, medium, right);
    }
}

int main() {
    int n;
    std::cin >> n;
    std::vector<int> array(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> array[i];
    }
    mergeSort(array, 0, n);
    for (int i = 0; i < n; ++i) {
        std::cout << array[i] << ' ';
    }
    return 0;
}
