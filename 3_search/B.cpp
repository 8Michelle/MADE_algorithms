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

int countBetween(const std::vector<int>& array, int left, int right) {
    int lower_bound = lowerBound(array, left, -1, array.size());
    int upper_bound = lowerBound(array, right + 1, -1, array.size());
    return upper_bound - lower_bound;
}

int main() {
    int n;
    std::cin >> n;
    std::vector<int> array(n);
    for (int i = 0; i < array.size(); ++i) {
        std::cin >> array[i];
    }
    std::sort(array.begin(), array.end());
    int k;
    std::cin >> k;
    int l, r;
    for (int i = 0; i < k; ++i) {
        std::cin >> l >> r;
        std::cout << countBetween(array, l, r) << ' ';
    }
}
