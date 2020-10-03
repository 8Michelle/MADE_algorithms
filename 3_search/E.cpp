#include <iostream>
#include <algorithm>

bool timeTestFunction(int64_t time, int first_time,
                      int second_time, int copies) {
    int min_time = std::min(first_time, second_time);
    int first_copies = (time - min_time) / first_time;
    int second_copies = (time - min_time) / second_time;
    return (1 + first_copies + second_copies) >= copies;
}

int searchTime(int copies, int first_time, int second_time,
               int64_t min_time, int64_t max_time) {
    if (max_time - min_time == 1) {
        return max_time;
    }
    int64_t time = (min_time + max_time) / 2;
    if (timeTestFunction(time, first_time, second_time, copies)) {
        return searchTime(copies, first_time, second_time, min_time, time);
    } else {
        return searchTime(copies, first_time, second_time, time, max_time);
    }
}

int main() {
    int n, x, y;
    std::cin >> n >> x >> y;
    int64_t min_time = std::min(x, y) - 1;
    int64_t max_time = n * std::max(x, y);
    std::cout << searchTime(n, x, y, min_time, max_time);
    return 0;
}
