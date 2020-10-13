#include <iostream>
#include <memory>
#include <algorithm>


class Stack {
 public:
    Stack();
    ~Stack();

    void push_back(int value);
    void pop();
    int get_min();

 private:
    struct Node {
        int value;
        int min_next_value;
        std::unique_ptr<Node> next;
    };

    std::unique_ptr<Node> head_;
};


Stack::Stack() : head_(nullptr) {}


Stack::~Stack() {
    while (head_) {
        pop();
    }
}


void Stack::push_back(int value) {
    Node* node = new Node({value});

    if (head_) {
        node->min_next_value = std::min(value, head_->min_next_value);
        node->next = std::move(head_);

    } else {
        node->min_next_value = value;
    }
    head_ = std::unique_ptr<Node>(node);
}

void Stack::pop() {
    head_ = std::move(head_->next);
}

int Stack::get_min() {
    return head_->min_next_value;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    Stack stack;
    int t, x;
    for (int i = 0; i < n; ++i) {
        std::cin >> t;
        switch (t) {
            case 1:
                std::cin >> x;
                stack.push_back(x);
                break;

            case 2:
                stack.pop();
                break;

            case 3:
                std::cout << stack.get_min() << '\n';
        }
    }
    return 0;
}
