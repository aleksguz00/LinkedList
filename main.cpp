#include <iostream>

template <class T>
class ListNode {
public:
    T data_;
    ListNode* next;
    ListNode* prev;

    explicit ListNode() = default;
    explicit ListNode(T data) : data_{ data } {}
};

template <class T>
class List {
public:
    void AddStart(T n) {
        ListNode* node = new ListNode{ n };

        if (head == nullptr) tail = node;
        else {
            head->prev = node;
            node->next = head;
        }

        head = node;
    }

    void AddEnd(T n) {
        ListNode* node = new ListNode{ n };

        if (head == nullptr) {
            head = node;
        }
        else {
            tail->next = node;
            node->prev = tail;
        }
        
        tail = node;
    }

    void InsertAfter(T after_n, T n) {
        ListNode* search_node = LinearSearch_(after_n);

        if (search_node) {
            ListNode* node = new ListNode{ n };

            if (search_node == tail) tail = node;
            if (search_node->next) search_node->next->prev = node;
            node->next = search_node->next;
            search_node->next = node;
            node.prev = search_node;
        }
    }

    // Need to use smart pointers
    void PopFront(T n) {
        if (head == nullptr) return;

        head->next->prev = nullptr;
        head = head.next;
    }

    void PopBack(T n) {
        if (head == nullptr) return;

        tail->prev->next = nullptr;
        tail = tail->prev;
    }

private:
    ListNode* head;
    ListNode* tail;

    // Trouble with strings
    ListNode* LinearSearch_(T n) {
        ListNode* search_node = head;

        while (search_node != nullptr) {
            if (search_node->data == n) return search_node;
            search_node = search_node->next;
        }
        return nullptr;
    }
};

int main() {

}