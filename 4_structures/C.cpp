#include <iostream>
#include <memory>

class CyclicArray {
 public:
    CyclicArray();

    void push_back(int value);
    void pop_front();
    int operator[](size_t index);
    size_t size();

 private:
    std::unique_ptr<int> body_;

    size_t begin_;
    size_t end_;

    size_t capacity_;
    size_t size_;

    void change_capacity(size_t new_capacity);
};

CyclicArray::CyclicArray() : body_(new int[1]),
begin_(0), end_(0), capacity_(1), size_(0) {}

void CyclicArray::push_back(int value) {
    if (size_ == capacity_) {
        change_capacity(capacity_ * 2);
    }
    body_.get()[end_] = value;
    end_ = (end_ + 1) % capacity_;
    ++size_;
}

void CyclicArray::pop_front() {
    begin_ = (begin_ + 1) % capacity_;
    --size_;
    if (size_ <= capacity_ / 4 && capacity_ / 2 > 0) {
        change_capacity(capacity_ / 2);
    }
}

int CyclicArray::operator[](size_t index) {
    return body_.get()[(begin_ + index) % capacity_];
}

void CyclicArray::change_capacity(size_t new_capacity) {
    int* new_body = new int[new_capacity];
    for (size_t i = 0; i < size_; ++i) {
        new_body[i] = body_.get()[(begin_ + i) % capacity_];
    }
    body_ = std::unique_ptr<int>(new_body);
    capacity_ = new_capacity;
    begin_ = 0;
    end_ = size_;
}


class Queue {
 public:
    void push(int value);
    void pop();
    int front();

 private:
    CyclicArray body_;
};

void Queue::push(int value) {
    body_.push_back(value);
}

void Queue::pop() {
    body_.pop_front();
}

int Queue::front() {
    return body_[0];
}


int main() {
    int n;
    std::cin >> n;
    Queue queue;
    int operand;
    char command;
    for (int i = 0; i < n; ++i) {
        std::cin >> command;

        if (command == '+') {
            std::cin >> operand;
            queue.push(operand);

        } else if (command == '-') {
            std::cout << queue.front() << '\n';
            queue.pop();
        }
    }
    return 0;
}
