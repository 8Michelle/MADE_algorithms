#include <iostream>
#include <vector>
#include <algorithm>

int64_t merge(std::vector<int>& array, int left, int medium, int right) {
    int i = 0;
    int j = 0;
    int64_t counter = 0; // для суммарного учета
    int64_t proxy_counter = 0; // для учета элементов, перенесенных справа
    std::vector<int> buff(right - left);
    while (left + i < medium && medium + j < right) {
        if (array[left + i] <= array[medium + j]) {
            buff[i + j] = array[left + i];
            counter += (proxy_counter * (medium - left - i));
            // "количество элементов перенесенных справа" * "количество инвертированных с ними элементов слева"
            proxy_counter = 0;
            ++i;
        } else {
            buff[i + j] = array[medium + j];
            ++proxy_counter; // инкрементируем количество перенесенных справа элементов
            ++j;
        }
    }
    counter += (proxy_counter * (medium - left - i));
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
    return counter;
}

int64_t countInversions(std::vector<int>& array, int left, int right) {
    int64_t counter = 0;
    if (right - left > 1) {
        int medium = (right + left) / 2;
        counter += countInversions(array, left, medium);
        counter += countInversions(array, medium, right);
        counter += merge(array, left, medium, right);
    }
    return counter;
}

int main() {
    int n;
    std::cin >> n;
    std::vector<int> array(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> array[i];
    }
    std::cout << countInversions(array, 0, n);
    return 0;
}
