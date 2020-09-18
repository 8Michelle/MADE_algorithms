#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

class King {
  public:
    King(const std::string& name, const std::string& roman_number);

    std::string name;
    std::string roman_number;
    int number;
  private:
    void roman2decimal();

    std::map<char, int> roman2value = {
            {'I', 1},
            {'V', 5},
            {'X', 10},
            {'L', 50}
    };
};

King::King(const std::string& name, const std::string& roman_number)
    : name(name), roman_number(roman_number) {
    roman2decimal();
}

void King::roman2decimal() {
    number = 0;
    int first = 0;
    int second = 0;
    for (int i = 0; i < roman_number.size(); ++i) {
        first = roman2value[roman_number[i]];
        second = 0;
        if (i + 1 < roman_number.size()) {
            second = roman2value[roman_number[i + 1]];
            if (first >= second) {
                number += first;
            } else {
                number += (second - first);
                ++i;
            }
        } else {
            number += first;
        }
    }
}

void kingSort(std::vector<King>& kings) {
    std::sort(kings.begin(), kings.end(), [](King first, King second) {
        if (first.name != second.name) {
            return first.name < second.name;
        } else {
            return first.number < second.number;
        }
    });
}

int main() {
    int n;
    std::string name, roman_number;
    std::cin >> n;
    std::vector<King> kings;
    for (int i = 0; i < n; ++i) {
        std::cin >> name >> roman_number;
        kings.push_back(King(name, roman_number));
    }
    kingSort(kings);
    for (auto king : kings) {
        std::cout << king.name << ' ' << king.roman_number << '\n';
    }
    return 0;
}
