/* код для тестов
 *
 * читать нельзя копировать */

void writeArray(std::vector<int>& array) {
    std::ofstream outfile("/Users/michelle/Desktop/CLionProjects/MADE_algorithms/2_sort/array.txt");
    for (int i = 0; i < array.size(); ++i) {
        outfile << array[i] << ' ';
    }
    outfile.close();
}

std::vector<int> GenRandomArray(std::mt19937 *gen, size_t count, int from, int to) {
    std::uniform_int_distribution<int> dist(from, to - 1);
    std::vector<int> data(count);
    for (int& cur : data) {
        cur = dist(*gen);
    }
    return data;
}

int main() {
    int N = 1000;
    int count = 0;
    int naive = 0;
    int ans = 0;
    int MAX = 1000 * 1000 * 1000;
    int first, second;
    int left, right;
    int k;
    std::uniform_int_distribution<int> dist(0, MAX);
    std::vector<int> array;
    std::mt19937 generator(42);
    for (;;) {
        ++count;
        array = GenRandomArray(&generator, N, 0, MAX);
        std::uniform_int_distribution<int> lr_dist(0, N - 1);
        first = lr_dist(generator);
        second = lr_dist(generator);
        left = std::min(first, second);
        right = std::max(first, second);
//        std::cout << left << ' ' << right << '\n';
        std::uniform_int_distribution<int> k_dist(0, std::max(right - left - 1, 0));
        k = k_dist(generator);
        naive = naiveKOrderStatistic(array, left, right, k, &generator);
        ans = kOrderStatistic(array, left, right, k + left, &generator);
        if (naive != ans) {
            writeArray(array);
            std::ofstream outfile("/Users/michelle/Desktop/CLionProjects/MADE_algorithms/2_sort/params.txt");
            outfile << left << ' ' << right << ' ' << k;
            outfile.close();
            std::cout << count << " test failed.\n";
            break;
        }

        if (count % 1000 == 0) {
            std::cout << count << '\n';
        }
    }
    return 0;
}