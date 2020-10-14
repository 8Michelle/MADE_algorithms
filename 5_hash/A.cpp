#include <iostream>
#include <vector>
#include <string>
#include <algorithm>


class Set {
 public:
    Set(size_t set_size) : set_size_(set_size),
    P(2147483423), A(1e9), NONE(1e9 + 1) {
        body_ = std::vector<int>(set_size, NONE);
    }

    void put(int key);
    bool contains(int key);
    void erase(int key);

 private:
    std::vector<int> body_;
    const size_t set_size_;

    const int A;
    const int P;
    const int NONE;

    size_t hash(int key);
};

void Set::put(int key) {
    size_t index = hash(key);
    for (int i = 0; i < set_size_; ++i) {
        if (body_[index] == NONE || body_[index] == key) {
            body_[index] = key;
            break;
        }
        index = (index + 1) % set_size_;
    }
}

bool Set::contains(int key) {
    size_t index = hash(key);
    for (int i = 0; i < set_size_; ++i) {
        if (body_[index] == key) {
            return true;

        } else if (body_[index] == NONE) {
            return false;
        }
        index = (index + 1) % set_size_;
    }
    return false;
}

void Set::erase(int key) {
    size_t index = hash(key);
    size_t index_swap;
    size_t index_counter = 0;
    bool beyond;

    while (body_[index] != NONE && index_counter++ < set_size_) {
        if (body_[index] == key) {
            body_[index] = NONE;
            index_swap = (index + 1) % set_size_;

            while (body_[index_swap] != NONE) {
                beyond = (index_swap < index);

                if ((hash(body_[index_swap]) <= index && !beyond) ||
                (hash(body_[index_swap]) <= index && hash(body_[index_swap]) > index_swap && beyond)) {

                    std::swap(body_[index_swap], body_[index]);
                    index = index_swap;
                }
                index_swap = (index_swap + 1) % set_size_;
            }
            break;
        }
        index = (index + 1) % set_size_;
    }
}

size_t Set::hash(int key) {
    return ((A * key) % P) % set_size_;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    const size_t SET_SIZE = 1e6;
    std::string command;
    int key;
    Set set(SET_SIZE);

    while (std::cin >> command >> key) {
        if (command == "insert") {
            set.put(key);

        } else if (command == "delete") {
            set.erase(key);

        } else if (command == "exists") {
            std::cout << (set.contains(key) ? "true" : "false") << '\n';
        }
    }
}
