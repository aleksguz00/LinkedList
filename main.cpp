#include <iostream>
#include <initializer_list>
#include <memory>

template<class T>
class List;

template <class T>
class ListNode {
private:
    T data_;
    std::shared_ptr<ListNode<T>> next_;
    std::shared_ptr<ListNode<T>> prev_;
public:
    explicit ListNode() = default;
    explicit ListNode(const T data) : data_{ data } {}

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

            while (tail->next_ != nullptr) {
                tail = tail->next_;
            }
        }
    List() : head{ nullptr }, tail{ nullptr } {}

    List(const List& other) {
        std::shared_ptr<ListNode<T>> current = nullptr;

        if (other->head == nullptr) {
            return;
        }

        if (head) {
            Clear();
        }

        while (current) {
            AddEnd(current->data_);
            current = current->next_;
        }

        while (tail->next_) {
            tail = tail->next_;
        }
    }

    List (List&& other) {
        // Add move ctor
    }

    List<T>& operator=(const List& other) {
        if (&other == this) return *this;

        std::shared_ptr<ListNode<T>> current = nullptr;

        if (other.head == nullptr) {
            return *this;
        }

        if (head) {
            Clear();
        }

        current = other.head;

        while (current) {
            AddEnd(current->data_);
            current = current->next_;
        }

        while (tail->next_) {
            tail = tail->next_;
        }

        return *this;      
    }

    List<T>& operator=(List&& other) {
        // Add move assignment operator
    }

    void AddStart(const T n) {
        auto node = std::make_shared<ListNode<T>>(n);

        if (head == nullptr) tail = node;
        else {
            head->prev_ = node;
            node->next_ = head;
        }

        head = node;
    }

    void AddEnd(const T n) {
        auto node = std::make_shared<ListNode<T>>(n);

        if (head == nullptr) {
            head = node;
        }
        else {
            tail->next_ = node;
            node->prev_ = tail;
        }
        
        tail = node;
    }

    void InsertAfter(const T after_n, const T n) {
        auto search_node = LinearSearch_(after_n);

        if (search_node) {
            auto node = std::make_shared<ListNode<T>>(n);

            if (search_node == tail) tail = node;
            if (search_node->next_) search_node->next_->prev_ = node;
            node->next_ = search_node->next_;
            search_node->next_ = node;
            node->prev_ = search_node;
        }
    }

    void PopFront() {
        if (head == nullptr) return;

        head->next_->prev_ = nullptr;
        head = head->next_;
    }

    void PopBack() {
        if (head == nullptr) return;

        tail->prev_->next_ = nullptr;
        tail = tail->prev_;
    }

    void Remove(const T n) {
        auto search_node = LinearSearch_(n);

        if (search_node == tail) return;

        if (search_node == head) {
            search_node->next_->prev_ = nullptr;
            head = search_node->next_;
        }

        if (search_node) {
            search_node->prev_->next_ = search_node->next_;
            search_node->next_->prev_ = search_node->prev_;
        }
    }

    void Clear() {
        std::shared_ptr<ListNode<T>> current = head->next_;

        while (current) {
            current->prev_.reset();
            current = current->next_;
        }

        head.reset();
        tail.reset();
    }

    void Print() const {
        if (head == nullptr) return;

        std::shared_ptr<ListNode<T>> current = head;

        while (current) {
            std::cout << current->data_ << ' ';
            current = current->next_;
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
            current = current->next_;
        }

        return size;
    }

    T& operator[](const size_t index) {
        if (index >= 0 && index < Size()) {
            size_t i = 0;
            std::shared_ptr<ListNode<T>> current = head;

            while (current) {
                if (i == index) return current->data_;
                current = current->next_;
                ++i;
            }
        }
        else {
            throw std::out_of_range("Out of range!\n");
        }
    }

    const T& operator[](const size_t index) const {
        if (index >= 0 && index < Size()) {
            size_t i = 0;
            std::shared_ptr<ListNode<T>> current = head;

            while (current) {
                if (i == index) return current->data_;
                current = current->next_;
                ++i;
            }
        }
        else {
            throw std::out_of_range("Out of range!\n");
        }
    }

private:
    std::shared_ptr<ListNode<T>> head;
    std::shared_ptr<ListNode<T>> tail;

    // Trouble with strings
    std::shared_ptr<ListNode<T>> LinearSearch_(T n) const {
        std::shared_ptr<ListNode<T>> search_node = head;

        while (search_node != nullptr) {
            if (search_node->data_ == n) return search_node;
            search_node = search_node->next_;
        }
        return nullptr;
    }
};

int main() {
    List<int> list1;
    List<int> list2 { 2, 5, 3, 5 };

    std::cout << "List 1 before: ";
    list1.Print();

    std::cout << "List 2 before: ";
    list2.Print();

    list2 = list1;

    list1.AddEnd(111);
    list2.AddStart(222);

    std::cout << "List 1 after: ";
    list1.Print();

    std::cout << "List 2 after: ";
    list2.Print();
}