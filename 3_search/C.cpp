#include <iostream>
#include <cmath>

double f(double x) {
    return x * x + std::sqrt(x);
}

double binSearch(double c, double left, double right, int iters) {
    for (int i = 0; i < iters; ++i) {
        double medium = (right + left) / 2;
        if (f(medium) < c) {
            left = medium;
        } else {
            right = medium;
        }
    }
    return right;
}

int main() {
    double c;
    std::cin >> c;
    double right = 0.5;
    while (f(right) < c) {
        right *= 2;
    }
    const double LEFT = 0.5;
    const int ITERS = 53;
    std::cout.precision(7);
    std::cout << binSearch(c, LEFT, right, ITERS);
    return 0;
}
