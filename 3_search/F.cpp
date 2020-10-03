#include <iostream>
#include <cmath>

double travelTime(double pointOfEntry, int p_velocity, int f_velocity,
                  double border) {
    double p_time = (1 - border) * (1 - border) + pointOfEntry * pointOfEntry;
    double v_time = (1 - pointOfEntry) * (1 - pointOfEntry) + border * border;
    p_time = std::sqrt(p_time) / p_velocity;
    v_time = std::sqrt(v_time) / f_velocity;
    return p_time + v_time;
}

double searchPoint(int p_velocity, int f_velocity, double border,
                double left, double right, int iters) {
    for (int i = 0; i < iters; ++i) {
        double medium_first = left + (right - left) / 3;
        double medium_second = right - (right - left) / 3;
        if (travelTime(medium_first, p_velocity, f_velocity,
                       border) < travelTime(medium_second, p_velocity,
                                                        f_velocity, border)) {
            right = medium_second;
        } else {
            left = medium_first;
        }
    }
    return right;
}

int main() {
    int vp, vf;
    std::cin >> vp >> vf;
    double a;
    std::cin >> a;
    const double LEFT = 0;
    const double RIGHT = 1;
    const int ITERS = 23;
    std::cout.precision(5);
    std::cout << searchPoint(vp, vf, a, LEFT, RIGHT, ITERS);
    return 0;
}
