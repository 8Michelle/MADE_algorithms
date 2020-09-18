#include <random>
#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> threeWayPartition(std::vector<int>& array,
        int left, int right, int pivot) {
    int medium_right = left;
    int medium_left = left;
    for (int i = left; i < right; ++i) {
        if (array[i] < pivot) {
            std::swap(array[i], array[medium_left]);
            if (medium_left == medium_right) {
                ++medium_right;
            }
            ++medium_left;
        }
        if (array[i] == pivot) {
            std::swap(array[i], array[medium_right]);
            ++medium_right;
        }
    }
    return std::vector<int> {medium_left, medium_right};
}

std::vector<int> threeWayPartitionRandomPivot(std::vector<int>& array,
        int left, int right, std::mt19937* generator) {
    std::uniform_int_distribution<int> dist(left, right - 1);
    int pivot = array[dist(*generator)];
    return threeWayPartition(array, left, right, pivot);
}

void quickSort(std::vector<int>& array,
        int left, int right, std::mt19937* generator) {
    if (right - left > 1) {
        std::vector<int> mediums = threeWayPartitionRandomPivot(array,
                left, right, generator);
        quickSort(array, left, mediums[0], generator);
        quickSort(array, mediums[1], right, generator);
    }
}

int main() {
    int n;
    std::mt19937 generator(42);
    std::cin >> n;
    std::vector<int> array(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> array[i];
    }
    quickSort(array, 0, n, &generator);
    for (int i = 0; i < n; ++i) {
        std::cout << array[i] << ' ';
    }
    return 0;
}
