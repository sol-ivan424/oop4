#include <vector>
#include <memory>
#include "houses.h"
#ifndef TABLE_H
#define TABLE_H


struct Shelter {
    bool free;
    int price_usd;
    std::shared_ptr<BaseAppartment> appartment;
};

template<typename T>
struct Node {
    Node* next;
    T data;
};

template<typename T>
class Table {
    private:
        Node<T>* start_node=nullptr;
        Node<T>* end_node=nullptr;
    public:
        Table() =default;
        void add(T data) {
            Node<T>* n = new Node<T> {nullptr, data};

            if (start_node == nullptr) {
                start_node = n;
            } else {
                end_node->next = n;
            }
            end_node = n;
        }

        Node<T>* find(const std::string& address) {
            Node<T>* cur_node = start_node;
            while (cur_node != nullptr) {
                if (cur_node->data.appartment->get_address() == address) {
                    return cur_node;
                }
                cur_node = cur_node->next;
            }

            return nullptr;
        }

        void find_by_address(const std::string& address) {
            Node<Shelter>* n = find(address);
            if (n != nullptr) {
                print_node(n);
            } else {
                std::cout << "Shelter not found\n";
            }
        }

        void print() {
            Node<T>* cur_node = start_node;
            while (cur_node != nullptr) {
                print_node(cur_node);
                cur_node = cur_node->next;
            }
        }

        void print_node(const Node<T>* cur_node) {
            std::cout << *(cur_node->data.appartment);
            std::cout << " * Price per m^2: " << cur_node->data.price_usd << "$\n";
            std::cout << " * Free: " << cur_node->data.free << "\n";
        }

        ~Table() {
            Node<T>* cur_node = start_node;
            while (cur_node != nullptr) {
                Node<T>* temp_node = cur_node;
                cur_node = cur_node->next;
                delete temp_node;
            }
        }
};
#endif //TABLE_H