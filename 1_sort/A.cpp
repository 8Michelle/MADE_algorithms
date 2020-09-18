#include <iostream>

int sum(int first, int second) {
    return first + second;
}

int main() {
    int n, first, second;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::cin >> first >> second;
        std::cout << sum(first, second) << '\n';
    }
    return 0;
}
