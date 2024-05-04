#include <iostream>
#include <initializer_list>
#include <memory>

template<class T>
class List;

template <class T>
class ListNode {
private:
    T data_;
    std::shared_ptr<ListNode<T>> next;
    std::shared_ptr<ListNode<T>> prev;
public:
    explicit ListNode() = default;
    explicit ListNode(T data) : data_{ data } {}

    friend List<T>;
};

template <class T>
class List {
public:
    List(std::initializer_list<T> init_list) : 
        head{ std::make_shared<ListNode<T>>(*init_list.begin()) }, tail{ head } {
            for (auto it = init_list.begin() + 1; it != init_list.end(); ++it) {
                AddEnd(*it);
            }

            while (tail->next != nullptr) {
                tail = tail->next;
            }
        }
    List() : head{ nullptr }, tail{ nullptr } {}

    void AddStart(T n) {
        auto node = std::make_shared<ListNode<T>>(n);

        if (head == nullptr) tail = node;
        else {
            head->prev = node;
            node->next = head;
        }

        head = node;
    }

    void AddEnd(T n) {
        auto node = std::make_shared<ListNode<T>>(n);

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
        auto search_node = LinearSearch_(after_n);

        if (search_node) {
            auto node = std::make_shared<ListNode<T>>(n);

            if (search_node == tail) tail = node;
            if (search_node->next) search_node->next->prev = node;
            node->next = search_node->next;
            search_node->next = node;
            node->prev = search_node;
        }
    }

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
        auto search_node = LinearSearch_(n);

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

        std::shared_ptr<ListNode<T>> current = head;

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

        std::shared_ptr<ListNode<T>> current = head;

        while (current) {
            ++size;
            current = current->next;
        }

        return size;
    }

private:
    std::shared_ptr<ListNode<T>> head;
    std::shared_ptr<ListNode<T>> tail;

    // Trouble with strings
    std::shared_ptr<ListNode<T>> LinearSearch_(T n) const {
        std::shared_ptr<ListNode<T>> search_node = head;

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

    list1.Remove(4);

    list1.Print();
    std::cout << list1.Size() << '\n';
}