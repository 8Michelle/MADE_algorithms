#include <vector>
#include <iostream>
#include <string>
#include <algorithm>

void stableCountingTupleSort(std::vector<std::string>& array, int digit) {
    int base = 26;
    std::vector<int> cnt(base);
    std::vector<std::string> result(array.size());
    std::vector<int> p(base);
    for (auto item : array) {
        ++cnt[item[digit] - 'a'];
    }
    p[0] = 0;
    for (int i = 1; i < base; ++i) {
        p[i] = p[i - 1] + cnt[i - 1];
    }
    for (auto item : array) {
        result[p[item[digit] - 'a']++] = item;
    }
    array = result;
}

void radixSort(std::vector<std::string>& array, int m, int k) {
    for (int digit = m - 1; digit >= m - k; --digit) {
        stableCountingTupleSort(array, digit);
    }
}

int main() {
    int n, m, k;
    std::cin >> n >> m >> k;
    std::vector<std::string> array(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> array[i];
    }
    radixSort(array, m, k);
    for (auto item : array) {
        std::cout << item << '\n';
    }
    return 0;
}
