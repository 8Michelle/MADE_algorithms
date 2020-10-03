#include <iostream>
#include <string>
#include <vector>

bool isAnagramOrLess(const std::vector<int>& cnt_str,
                     const std::vector<int>& cnt_tbl) {
    for (size_t i = 0; i < cnt_str.size(); ++i) {
        if (cnt_str[i] > cnt_tbl[i]) {
            return false;
        }
    }
    return true;
}

int64_t countPermutations(const std::string& str, const std::string& tbl) {
    /* не пересчитываем couning вектор для строки каждый раз, а
     * инкрементируем и декрементируем элементы при сдвиге окна */
    int BASE = 26;
    std::vector<int> cnt_tbl(BASE);
    for (auto item : tbl) {
        ++cnt_tbl[item - 'a'];
    }
    std::vector<int> cnt_str(BASE);
    size_t left = 0;
    size_t right = 0;
    ++cnt_str[str[right++] - 'a']; // создаем окно с первой буквой
    int64_t counter = 0;
    while (right <= str.size()) { // пока не уперлись в правый край строки
        if (isAnagramOrLess(cnt_str, cnt_tbl)) {
            counter += (right - left);
            if (right == str.size()) { // если уперлись в правый край, выходим
                // так как все подстроки слева от left уже учтены, а сейчас посчитали подстроки в окне
                break;
            }
            ++cnt_str[str[right++] - 'a']; // если не уперлись, расширяем окно
        } else {
            --cnt_str[str[left++] - 'a']; // иначе сужаем окно
            if (left == right) {
                if (right == str.size()) {
                    break;
                }
                ++cnt_str[str[right++] - 'a'];
            }
        }
    }
    return counter;
}

int main() {
    int n, m;
    std::cin >> n >> m;
    std::string str;
    std::string tbl;
    std::cin >> str;
    std::cin >> tbl;
    std::cout << countPermutations(str, tbl);
    return 0;
}
