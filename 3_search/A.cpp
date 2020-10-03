#include <iostream>
#include <vector>

int approxBinSearch(const std::vector<int>& array,
                    int request, int left, int right) {
    if (right - left == 1) {
        if (array[left] == request) {
            return array[left];
        } else {
            return request - array[left] <= array[left + 1] - request ?
                   array[left] : array[left + 1];
        }
    }
    int medium = (right + left) / 2;
    if (request < array[medium]) {
        return approxBinSearch(array, request, left, medium);
    } else {
        return approxBinSearch(array, request, medium, right);
    }
}

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<int> array(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> array[i];
    }
    int request;
    for (int i = 0; i < m; ++i) {
        std::cin >> request;
        if (request > array[n - 1]) {
            std::cout << array[n - 1];
        } else if (request < array[0]) {
            std::cout << array[0];
        } else {
            std::cout << approxBinSearch(array, request, 0, n);
        }
        std::cout << '\n';
    }
    return 0;
}
