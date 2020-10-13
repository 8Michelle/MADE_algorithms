#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <utility>


class Heap {
 public:
    Heap();

    void add(int value);
    std::pair<int, int> get_min();
    void remove_min();
    void decrease_key(size_t order, int value);
   
    size_t size();
    void operate();

 private:
    struct Node {
        int value;
        size_t order;
    };

    std::vector<Node> body_;
    size_t counter_;

    void sift_up(size_t index);
    void sift_down(size_t index);

    size_t get_index_by_order(size_t order);
};

Heap::Heap() : counter_(0) {}

void Heap::add(int value) {
    body_.push_back(Node({value, counter_}));
    sift_up(body_.size() - 1);
}

std::pair<int, int> Heap::get_min() {
    return std::pair<int, int>(body_[0].value, body_[0].order);
}

void Heap::remove_min() {
    std::swap(body_[0], body_[body_.size() - 1]);
    body_.erase(body_.end() - 1);
    sift_down(0);
}

void Heap::decrease_key(size_t order, int value) {
    size_t index = get_index_by_order(order);
    body_[index].value = value;
    sift_up(index);
}

void Heap::sift_up(size_t index) {
    while (index != 0 &&
            body_[(index - 1) / 2].value > body_[index].value) {

        std::swap(body_[index], body_[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}

void Heap::sift_down(size_t index) {
    while (2 * index + 1 < body_.size()) {
        size_t left = 2 * index + 1;
        size_t right = 2 * index + 2;

        if (right != body_.size()) {

            if (body_[index].value <= body_[left].value &&
            body_[index].value <= body_[right].value) {
                break;

            } else if (body_[index].value > body_[left].value &&
                       body_[index].value <= body_[right].value) {
                std::swap(body_[index], body_[left]);
                index = left;
                continue;

            } else if (body_[index].value <= body_[left].value &&
            body_[index].value > body_[right].value) {
                std::swap(body_[index], body_[right]);
                index = right;
                continue;

            } else if (body_[index].value > body_[left].value &&
            body_[index].value > body_[right].value) {
                if (body_[left].value < body_[right].value) {
                    std::swap(body_[index], body_[left]);
                    index = left;
                    continue;
                } else {
                    std::swap(body_[index], body_[right]);
                    index = right;
                    continue;
                }
            }

        } else if (body_[index].value > body_[left].value) {
            std::swap(body_[index], body_[left]);
            break;

        } else {
            break;
        }
    }
}

size_t Heap::size() {
    return body_.size();
}

void Heap::operate() {
    ++counter_;
}

size_t Heap::get_index_by_order(size_t order) {
    auto node = std::find_if(body_.begin(), body_.end(),
                          [order](const Node& node) {
        return node.order == order;
    });
    return node - body_.begin();
}


int main() {
    std::string word;
    Heap heap;
    std::pair<int, int> minimum;
    int value;
    size_t key;
    while (std::cin >> word) {
        heap.operate();
        if (word == "push") {
            std::cin >> value;
            heap.add(value);

        } else if (word == "extract-min") {
            if (heap.size()) {
                minimum = heap.get_min();
                heap.remove_min();
                std::cout << minimum.first << ' ' << minimum.second;
            } else {
                std::cout << '*';
            }
            std::cout << '\n';

        } else if ("decrease-key") {
            std::cin >> key >> value;
            heap.decrease_key(key, value);
        }
    }
    return 0;
}
