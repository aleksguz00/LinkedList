#include <iostream>
#include <initializer_list>

template <class T>
class ListNode {
public:
    T data_;
    ListNode<T>* next;
    ListNode<T>* prev;

    explicit ListNode() = default;
    explicit ListNode(T data) : data_{ data } {}
};

template <class T>
class List {
public:
    List(std::initializer_list<T> init_list) : 
        head{ new ListNode<T>(*init_list.begin()) }, tail{ head } {
            for (auto it = init_list.begin() + 1; it != init_list.end(); ++it) {
                AddEnd(*it);
            }

            while (tail->next != nullptr) {
                tail = tail->next;
            }
        }
    List() : head{ nullptr }, tail{ nullptr } {}

    void AddStart(T n) {
        ListNode<T>* node = new ListNode{ n };

        if (head == nullptr) tail = node;
        else {
            head->prev = node;
            node->next = head;
        }

        head = node;
    }

    void AddEnd(T n) {
        ListNode<T>* node = new ListNode{ n };

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
        ListNode<T>* search_node = LinearSearch_(after_n);

        if (search_node) {
            ListNode<T>* node = new ListNode{ n };

            if (search_node == tail) tail = node;
            if (search_node->next) search_node->next->prev = node;
            node->next = search_node->next;
            search_node->next = node;
            node->prev = search_node;
        }
    }

    // Need to use smart pointers
    void PopFront() {
        if (head == nullptr) return;

        head->next->prev = nullptr;
        head = head->next;
    }

    void PopBack() {
        if (head == nullptr) return;

        tail->prev->next = nullptr;
        tail = tail->prev;
    }

    void Remove(T n) {
        ListNode<T>* search_node = LinearSearch_(n);

        if (search_node == tail) return;

        if (search_node == head) {
            search_node->next->prev = nullptr;
            head = search_node->next;
        }

        if (search_node) {
            search_node->prev->next = search_node->next;
            search_node->next->prev = search_node->prev;
        }
    }

    void Print() const {
        if (head == nullptr) return;

        ListNode<T>* current = head;

        while (current) {
            std::cout << current->data_ << ' ';
            current = current->next;
        }
        std::cout << '\n';
    }

    size_t Size() const {
        size_t size = 0;

        if (head == nullptr) return 0;
        if (head == tail) return 1;

        ListNode<T>* current = head;

        while (current) {
            ++size;
            current = current->next;
        }

        return size;
    }

private:
    ListNode<T>* head;
    ListNode<T>* tail;

    // Trouble with strings
    ListNode<T>* LinearSearch_(T n) {
        ListNode<T>* search_node = head;

        while (search_node != nullptr) {
            if (search_node->data_ == n) return search_node;
            search_node = search_node->next;
        }
        return nullptr;
    }
};

int main() {
    List<int> list1 { 1, 2, 3, 4, 5, 6 };

    list1.Print();

    std::cout << list1.Size() << '\n';
}