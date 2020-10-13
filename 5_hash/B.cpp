#include <random>
#include <iostream>
#include <vector>
#include <string>
#include <memory>


class List {
 public:
    ~List();

    void put(const std::string& key, const std::string& value);
    void erase(const std::string& key);
    std::string get(const std::string &key);

 private:
    struct Node {
        std::string key;
        std::string value;

        std::unique_ptr<Node> next;
    };

    std::unique_ptr<Node> head_;
};

List::~List() {
    while (head_) {
        erase(head_->key);
    }
}

void List::put(const std::string& key, const std::string& value) {
    auto node = head_.get();

    while (node != nullptr) {
        if (node->key == key) {
            node->value = value;
            return;
        }
    }

    node = new Node({key, value});
    node->next = std::move(head_);
    head_ = std::unique_ptr<Node>(node);
}

void List::erase(const std::string& key) {
    if (head_) {
        if (head_->next != nullptr) {
            auto node = head_.get();
            while (node->next != nullptr) {

                if (node->next->key == key) {
                    node->next = std::move(node->next->next);
                    return;
                }

                node = node->next.get();
            }
        } else if (head_->key == key) {
            head_ = nullptr;
        }
    }

}

std::string List::get(const std::string& key) {
    auto node = head_.get();
    while (node != nullptr) {

        if (node->key == key) {
            return node->value;
        }

        node = node->next.get();
    }
    return "none";
}


class Map {
 public:
    Map(const size_t map_size) : map_size_(map_size),
    body_(std::vector<Node>(map_size)),
    P(2147483423), A(29) {};

    void put(const std::string& key, const std::string& value);
    void erase(const std::string& key);
    std::string get(const std::string& key);

 private:
    struct Node {
        std::string key;
        std::string value;
        std::unique_ptr<Node> next;
    };

    std::vector<Node> body_;
    const size_t map_size_;

    const int A;
    const int P;

    size_t get_hash(const std::string& key);
};

void Map::put(const std::string& key, const std::string& value) {
    size_t index = get_hash(key);
    if (body_[index].key == "" || body_[index].key == key) {
        body_[index].key = key;
        body_[index].value = value;

    } else {
        Node* node = &body_[index];
        while (node->next != nullptr) {
            if (node->next->key == key) {
                node->next->value = value;
                return;
            }
            node = node->next.get();
        }
        Node* new_node = new Node({key, value});
        node->next = std::unique_ptr<Node>(new_node);
    }
}

void Map::erase(const std::string& key) {
    size_t index = get_hash(key);
    if (body_[index].key == "") {
        return;

    } else if (body_[index].key == key) {
        if (body_[index].next == nullptr) {
            body_[index].key = "";
            body_[index].value = "";
        } else {
            body_[index].key = body_[index].next->key;
            body_[index].value = body_[index].next->value;
            body_[index].next = std::move(body_[index].next->next);
        }

    } else {
        Node* last_node = &body_[index];
        Node* node = body_[index].next.get();
        while (node != nullptr) {
            if (node->key == key) {
                last_node->next = std::move(node->next);
            }
            last_node = node;
            node = node->next.get();
        }
    }
}

std::string Map::get(const std::string& key) {
    size_t index = get_hash(key);
    Node* node = &body_[index];
    while (node != nullptr) {
        if (node->key == key) {
            return node->value;
        }
        node = node->next.get();
    }
    return "none";
}

size_t Map::get_hash(const std::string& key) {
    size_t sum = 0;
    for (char c : key) {
        sum += (sum * A + c) % P;
    }
    return (sum % P) % map_size_;
}


//std::string random_string() {
//    std::string str("abcdefghijklmnopqrstuvwxyz");
//
//    std::random_device rd;
//    std::mt19937 generator(rd());
//
//    std::shuffle(str.begin(), str.end(), generator);
//
//    return str.substr(0, 20);    // assumes 32 < number of characters in str
//}
//
//
//int main() {
//    Map map(100000);
//    for (int i = 0; i < 100000; ++i) {
//        map.put(random_string(), random_string());
//        std::cout << i << '\n';
//    }
//    std::cout << "OK.\n";
//}


int main() {

    const size_t MAP_SIZE = 1e5;
    std::string command;
    std::string key;
    std::string value;
    Map map(MAP_SIZE);

    while (std::cin >> command) {
        if (command == "put") {
            std::cin >> key >> value;
            map.put(key, value);

        } else if (command == "delete") {
            std::cin >> key;
            map.erase(key);

        } else if (command == "get") {
            std::cin >> key;
            std::cout << map.get(key) << '\n';
        }
    }
    return 0;
}
