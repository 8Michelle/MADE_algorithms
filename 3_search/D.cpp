#include <iostream>
#include <vector>
#include <algorithm>

int lowerBound(const std::vector<int>& array, int request,
               int left, int right) {
    if (right - left == 1) {
        return right;
    }
    int medium = (left + right) / 2;
    if (request <= array[medium]) {
        return lowerBound(array, request, left, medium);
    } else {
        return lowerBound(array, request, medium, right);
    }
}

bool testFunction(int length, int houses, std::vector<int> length_array) {
    int index = lowerBound(length_array, length, -1, length_array.size());
    for (int i = 0; i < houses; ++i) {
        if (index < length_array.size()) {
            length_array[index] -= length;
            if (length_array[index] < length) {
                ++index;
            }
        } else {
            return false;
        }
    }
    return true;
}

int searchLength(const std::vector<int>& length_array,
                 int houses, int left, int right) {
    if (right - left == 1) {
        return left;
    }
    int length = (right + left) / 2;
    if (!testFunction(length, houses, length_array)) {
        return searchLength(length_array, houses, left, length);
    } else {
        return searchLength(length_array, houses, length, right);
    }
}

int main() {
    int n, k;
    std::cin >> n >> k;
    std::vector<int> length_array(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> length_array[i];
    }
    std::sort(length_array.begin(), length_array.end());
    int right = length_array[n - 1] + 1;
    const int LEFT = 0;
    std::cout << searchLength(length_array, k, LEFT, right);
    return 0;
}
