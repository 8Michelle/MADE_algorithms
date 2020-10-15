#include <iostream>
#include <vector>
#include <memory>
#include <string>


class Map {
 public:
    Map(const size_t map_size) : body_(std::vector<Node>(map_size)),
    map_size_(map_size),
    last_added_(nullptr),
    A(29), P(2147483423) {}

    void put(const std::string& key, const std::string& value);
    void erase(const std::string& key);
    std::string get(const std::string& key);

    std::string prev(const std::string& key);
    std::string next(const std::string& key);

 private:
    struct Node {
        std::string key;
        std::string value;
        std::unique_ptr<Node> next;
        Node* next_added;
        Node* prev_added;
    };

    std::vector<Node> body_;
    const size_t map_size_;

    Node* last_added_;

    const int A;
    const int P;

    void delete_from_linking(Node* node);
    Node* find_node(const std::string& key);
    size_t hash(const std::string& key);
};

void Map::put(const std::string& key, const std::string& value) {
    size_t index = hash(key);
    Node* new_node;
    if (body_[index].key == "") {
        body_[index].key = key;
        body_[index].value = value;
        new_node = &body_[index];

    } else if (body_[index].key == key) {
        body_[index].value = value;
        return;

    } else {
        Node* node = &body_[index];
        while (node->next) {
            if (node->next->key == key) {
                node->next->value = value;
                return;
            }
            node = node->next.get();
        }
        new_node = new Node({key, value});
        node->next = std::unique_ptr<Node>(new_node);
    }

    new_node->prev_added = last_added_;
    if (last_added_) {
        last_added_->next_added = new_node;
    }
    last_added_ = new_node;
}

void Map::erase(const std::string& key) {
    size_t index = hash(key);
    if (body_[index].key == "") {
        return;
    }

    if (body_[index].key == key) {
        if (body_[index].next == nullptr) {
            body_[index].key = "";
            body_[index].value = "";
            delete_from_linking(&body_[index]);
            body_[index].next_added = nullptr;
            body_[index].prev_added = nullptr;

        } else {
            delete_from_linking(&body_[index]);

            body_[index].next_added = body_[index].next->next_added;
            body_[index].prev_added = body_[index].next->prev_added;

            body_[index].key = body_[index].next->key;
            body_[index].value = body_[index].next->value;

            if (body_[index].next->prev_added) {
                body_[index].next->prev_added->next_added = &body_[index];
            }
            if (body_[index].next->next_added) {
                body_[index].next->next_added->prev_added = &body_[index];
            }

            if (body_[index].next->next) {
                body_[index].next = std::move(body_[index].next->next);
            } else {
                body_[index].next = nullptr;
            }
        }

    } else {
        Node* prev_node = &body_[index];
        Node* node = body_[index].next.get();
        while (node) {
            if (node->key == key) {
                delete_from_linking(node);
                prev_node->next = std::move(node->next);
                break;
            }
            prev_node = node;
            node = node->next.get();
        }
    }
}

std::string Map::get(const std::string& key) {
    Node* node = find_node(key);
    if (node) {
        return node->value;
    } else {
        return "none";
    }
}

std::string Map::prev(const std::string &key) {
    Node* node = find_node(key);
    if (node) {
        if (node->prev_added) {
            return node->prev_added->value;
        }
    }
    return "none";
}

std::string Map::next(const std::string &key) {
    Node* node = find_node(key);
    if (node) {
        if (node->next_added) {
            return node->next_added->value;
        }
    }
    return "none";
}

size_t Map::hash(const std::string& key) {
    size_t sum = 0;
    for (char c : key) {
        sum += (sum * A + c) % P;
    }
    return (sum % P) % map_size_;
}

void Map::delete_from_linking(Node* node) {
    if (node->prev_added) {
        node->prev_added->next_added = node->next_added;
    }

    if (node->next_added) {
        node->next_added->prev_added = node->prev_added;
    }

    if (node == last_added_) {
        last_added_ = node->prev_added;
    }
}

Map::Node* Map::find_node(const std::string &key) {
    size_t index = hash(key);
    Node* node = &body_[index];
    while (node != nullptr) {
        if (node->key == key) {
            return node;
        }
        node = node->next.get();
    }
    return nullptr;
}


int main() {
    const size_t MAP_SIZE = 1e5;
    std::string command;
    std::string key;
    std::string value;
    Map map(MAP_SIZE);

    while (std::cin >> command >> key) {
        if (command == "put") {
            std::cin >> value;
            map.put(key, value);

        } else if (command == "delete") {
            map.erase(key);

        } else if (command == "get") {
            std::cout << map.get(key) << '\n';

        } else if (command == "prev") {
            std::cout << map.prev(key) << '\n';

        } else if (command == "next") {
            std::cout << map.next(key) << '\n';
        }
    }
}
