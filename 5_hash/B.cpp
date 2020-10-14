#include <iostream>
#include <vector>
#include <string>
#include <memory>


class Map {
 public:
    Map(const size_t map_size) : map_size_(map_size),
    body_(std::vector<Node>(map_size)),
    P(2147483423), A(29) {}

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
        Node* prev_node = &body_[index];
        Node* node = body_[index].next.get();
        while (node != nullptr) {
            if (node->key == key) {
                prev_node->next = std::move(node->next);
                return;
            }
            prev_node = node;
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
