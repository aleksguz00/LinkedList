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
        head_{ std::make_shared<ListNode<T>>(*init_list.begin()) }, tail_{ head_ } {
            for (auto it = init_list.begin() + 1; it != init_list.end(); ++it) {
                AddEnd(*it);
            }

            while (tail_->next_ != nullptr) {
                tail_ = tail_->next_;
            }
        }
    List() : head_{ nullptr }, tail_{ nullptr } {}

    List(const List& other) {
        std::shared_ptr<ListNode<T>> current = nullptr;

        if (other->head_ == nullptr) {
            return;
        }

        if (head_) {
            Clear();
        }

        while (current) {
            AddEnd(current->data_);
            current = current->next_;
        }

        while (tail_->next_) {
            tail_ = tail_->next_;
        }
    }

    List (List&& other) {
        if (other.head_ == nullptr) return;
        if (head_) Clear();

        head_ = other.head_;
        other.head_.reset();

        tail_ = other.tail_;
        other.tail_.reset();
    }

    List<T>& operator=(const List& other) {
        if (&other == this) return *this;

        std::shared_ptr<ListNode<T>> current = nullptr;

        if (other.head_ == nullptr) return *this;
        

        if (head_) Clear();

        current = other.head_;

        while (current) {
            AddEnd(current->data_);
            current = current->next_;
        }

        while (tail_->next_) {
            tail_ = tail_->next_;
        }

        return *this;      
    }

    List<T>& operator=(List&& other) {
        if (&other == this) return *this;

        if (other.head_ == nullptr) return *this;
        if (head_) Clear();

        head_ = other.head_;
        other.head_.reset();

        tail_ = other.tail_;
        other.tail_.reset();

        return *this;
    }

    void AddStart(const T n) {
        auto node = std::make_shared<ListNode<T>>(n);

        if (head_ == nullptr) tail_ = node;
        else {
            head_->prev_ = node;
            node->next_ = head_;
        }

        head_ = node;
    }

    void AddEnd(const T n) {
        auto node = std::make_shared<ListNode<T>>(n);

        if (head_ == nullptr) {
            head_ = node;
        }
        else {
            tail_->next_ = node;
            node->prev_ = tail_;
        }
        
        tail_ = node;
    }

    void InsertAfter(const T after_n, const T n) {
        auto search_node = LinearSearch_(after_n);

        if (search_node) {
            auto node = std::make_shared<ListNode<T>>(n);

            if (search_node == tail_) tail_ = node;
            if (search_node->next_) search_node->next_->prev_ = node;
            node->next_ = search_node->next_;
            search_node->next_ = node;
            node->prev_ = search_node;
        }
    }

    void PopFront() {
        if (head_ == nullptr) return;

        head_->next_->prev_ = nullptr;
        head_ = head_->next_;
    }

    void PopBack() {
        if (head_ == nullptr) return;

        tail_->prev_->next_ = nullptr;
        tail_ = tail_->prev_;
    }

    void Remove(const T n) {
        auto search_node = LinearSearch_(n);

        if (search_node == tail_) {
            search_node->prev_->next_ = nullptr;
            tail_ = search_node->prev_;
            return;
        }

        if (search_node == head_) {
            search_node->next_->prev_ = nullptr;
            head_ = search_node->next_;
            return;
        }

        if (search_node) {
            search_node->prev_->next_ = search_node->next_;
            search_node->next_->prev_ = search_node->prev_;
        }
    }

    void Clear() {
        std::shared_ptr<ListNode<T>> current = head_->next_;

        while (current) {
            current->prev_.reset();
            current = current->next_;
        }

        head_.reset();
        tail_.reset();
    }

    void Print() const {
        if (head_ == nullptr) return;

        std::shared_ptr<ListNode<T>> current = head_;

        while (current) {
            std::cout << current->data_ << ' ';
            current = current->next_;
        }
        std::cout << '\n';
    }

    size_t Size() const {
        size_t size = 0;

        if (head_ == nullptr) return 0;
        if (head_ == tail_) return 1;

        std::shared_ptr<ListNode<T>> current = head_;

        while (current) {
            ++size;
            current = current->next_;
        }

        return size;
    }

    T& operator[](const size_t index) {
        if (index >= 0 && index < Size()) {
            size_t i = 0;
            std::shared_ptr<ListNode<T>> current = head_;

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
            std::shared_ptr<ListNode<T>> current = head_;

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
    std::shared_ptr<ListNode<T>> head_;
    std::shared_ptr<ListNode<T>> tail_;

    std::shared_ptr<ListNode<T>> LinearSearch_(T n) const {
        std::shared_ptr<ListNode<T>> search_node = head_;

        while (search_node != nullptr) {
            if (search_node->data_ == n) return search_node;
            search_node = search_node->next_;
        }
        return nullptr;
    }
};

int main() {
    List<const char*> list1{ "Hello", "World", "Hey" };
    List<const char*> list2{ "Oops!", "SP" };

    List<int> list3{ 1, 2, 3 };

    list1.Print();

    list1.InsertAfter("World", "Check");

    list1.Print();
}