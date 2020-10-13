#include <iostream>
#include <string>
#include <sstream>


class Vector {
 public:
    Vector();
    ~Vector();

    void push_back(int value);
    void pop_back();
    int operator[](size_t index);
    size_t size();

 private:
    int* body_;
    size_t size_;
    size_t capacity_;

    void change_capacity(size_t new_capacity);
};

Vector::Vector() : body_(new int[0]), size_(0), capacity_(0) {}

Vector::~Vector() {
    delete[] body_;
}

void Vector::push_back(int value) {
    if (size_ == capacity_) {
        if (capacity_ == 0) {
            change_capacity(1);
        } else {
            change_capacity(capacity_ * 2);
        }
    }
    body_[size_++] = value;
}

void Vector::pop_back() {
    size_--;
    if (size_ <= capacity_ / 4 && capacity_ / 2 > 0) {
        change_capacity(capacity_ / 2);
    }
}

int Vector::operator[](size_t index) {
    return body_[index];
}

size_t Vector::size() {
    return size_;
}

void Vector::change_capacity(size_t new_capacity) {
    int* new_body = new int[new_capacity];
    for (size_t i = 0; i < size_; ++i) {
        new_body[i] = body_[i];
    }
    delete[] body_;
    body_ = new_body;
    capacity_ = new_capacity;
}


class CallStack {
 public:
    void push(int value);
    int back();
    void pop();

 private:
    Vector body_;
};

void CallStack::push(int value) {
    body_.push_back(value);
}

int CallStack::back() {
    return body_[body_.size() - 1];
}

void CallStack::pop() {
    body_.pop_back();
}


std::pair<int, int> get_operands(CallStack& callStack) {
    int first = callStack.back();
    callStack.pop();
    int second = callStack.back();
    callStack.pop();

    std::pair<int, int> operands = {first, second};
    return operands;
}


int main() {
    std::string line;
    std::getline(std::cin, line);
    std::istringstream iss(line);
    std::string word;
    CallStack callStack;
    std::pair<int, int> operands;
    while (iss >> word) {
        if (word == "*") {
            operands = get_operands(callStack);
            callStack.push(operands.first * operands.second);

        } else if (word == "+") {
            operands = get_operands(callStack);
            callStack.push(operands.first + operands.second);

        } else if (word == "-") {
            operands = get_operands(callStack);
            callStack.push(operands.second - operands.first);

        } else {
            callStack.push(std::stoi(word));
        }
    }

    std::cout << callStack.back();
    return 0;
}
