#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

void countingSort(std::vector<int>& array) {
    int max = *std::max_element(array.begin(), array.end());
    std::vector<int> cnt(max + 1);
    for (auto i : array) {
        ++cnt[i];
    }
    int j = 0;
    for (int i = 0; i <= max; ++i) {
        while (cnt[i] > 0) {
            array[j++] = i;
            --cnt[i];
        }
    }
}

int main() {
    std::vector<int> array;
    std::string line;
    std::getline(std::cin, line);
    std::istringstream iss(line);
    int n;
    while (iss >> n) {
        array.push_back(n);
    }
    countingSort(array);
    for (auto i : array) {
        std::cout << i << ' ';
    }
    return 0;
}
