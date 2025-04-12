#include <initializer_list>
#include <memory>
#include <iterator>


template <typename T>
class Node {
public:
    T Data;
    Node* prev;
    Node* next;
    Node(const T& data) : Data(data), prev(this), next(this) {}
};


template<typename T>
class MyList
{
public:
    using value_type = T;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using reference = value_type&;
    using const_reference = const value_type&;

    class iterator
    {
    public:

        Node<T>* current;

        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = value_type;
        using difference_type = difference_type;
        using pointer = pointer;
        using reference = reference;

        iterator(Node<T>* node) : current(node) {}

        bool operator==(const iterator& other) const {
            return current == other.current;
        }

        bool operator!=(const iterator& other) const {
            return !(current == other.current);
        }

        pointer operator->() {
            return &current->Data;
        }

        iterator& operator--() {
            if (current) current = current->prev;
            return *this;
        }

        iterator  operator--(int) {
            auto temp = *this;
            --(*this);
            return temp;
        }

        iterator& operator++() {
            current = current->next;
            return *this;
        }

        iterator  operator++(int) {
            auto temp = *this;
            ++(*this);
            return temp;
        }

        reference operator*() {
            return current->Data;
        }
    };

private:
    Node<T>* first;
    Node<T>* last;
    size_type lst_size;

public:
    using reverse_iterator = std::reverse_iterator<iterator>;

    MyList(): lst_size(0) {
        last = static_cast<Node<T>*>(operator new(sizeof(Node<T>)));
        first = last;
        last->next = last;
        last->prev = last;
    }

    MyList(MyList& other) :MyList() {
        for (const auto& item : other)
            push_back(item);
    }

   /* MyList(MyList&& other) noexcept
        : first(other.first), last(other.last), lst_size(other.lst_size) {
        other.first = other.last;
        other.lst_size = 0;
    }*/

    MyList(std::initializer_list<T> init) :MyList() {
        for (const auto& item : init) 
            push_back(item);
    }

    MyList& operator=(MyList& other) {
        if (this != &other) {
            clear();
            for (const auto& item : other)
                push_back(item);
        }
        return *this;
    }

    MyList& operator=(std::initializer_list<T> ilist) {
        if (this != ilist) {
            clear();
            for (const auto& item : ilist)
                push_back(item);
        }
        return *this;
    }

  /*  MyList& operator=(MyList&& other) {
        clear();

        first = other.first;
        last = other.last;
        lst_size = other.lst_size;

        other.first = other.last;
        other.last->prev = other.last;
        other.last->next = other.last;
        other.lst_size = 0; 

        return *this;
    }*/

    reference front() { return first->Data; }
    reference back() { return last->prev->Data; }
    iterator begin() noexcept { return iterator(first); }
    iterator end() noexcept { return iterator(last); }
    reverse_iterator rbegin() noexcept { return reverse_iterator(last); }
    reverse_iterator rend() noexcept { return reverse_iterator(first); }
    bool empty() const noexcept { return lst_size == 0; }
    size_type size() const noexcept { return lst_size; }

    void clear() noexcept {
        while (!empty())
            pop_back();
    }

    iterator insert(iterator pos, const T& value) {
        Node<T>* newNode = new Node(value);
        Node<T>* curr = pos.current;

        newNode->prev = curr->prev;
        newNode->next = curr;
        curr->prev = newNode;
        curr->prev->next = newNode;

        if (curr == first) first = newNode;

        lst_size++;
        return iterator(newNode);
    }

    /*iterator insert(iterator pos, T&& value) {
        Node<T>* newNode = new Node<T>(std::move(value));
        Node<T>* curr = pos;

        newNode->prev = curr->prev;
        newNode->next = curr;
        curr->prev = newNode;
        curr->prev->next = newNode;

        if (curr == first) first = newNode;

        lst_size++;
        return iterator(newNode);
    }*/

    iterator erase(iterator pos) {
        if (pos == end()) return pos;

        Node<T>* curr = pos.current;
        Node<T>* newNode = curr->next;

        if (curr->prev) curr->prev->next = curr->next;
        if (curr->next) curr->next->prev = curr->prev;
        if (curr == first) first = curr->next;
        if (curr == last->prev) last->prev = curr->prev;

        delete curr;
        lst_size--;
        return iterator(newNode);
    }

    iterator erase(iterator first, iterator last) { 
        while (first != last)
            first = erase(first);
        return last;
    }



    void push_back(const T& value) {
        Node<T>* newNode = new Node<T>(value);
        if (empty()) {
            first = newNode;
            first->next = last;
            first->prev = last;
            last->prev = first;
            last->next = first;
        }
        else {
            Node<T>* curr = last->prev;
            last->prev = newNode;
            curr->next = newNode;
            newNode->prev = curr;
            newNode->next = last;
        }
        lst_size++;
    }

    //void push_back(T&& value) {
    //    Node<T>* newNode = new Node<T>(std::move(value));
    //    if (lst_size == 0) {
    //        first = newNode;
    //        first->next = last;
    //        first->prev = last;
    //        last->prev = first;
    //        last->next = first;
    //    }
    //    else {
    //        Node<T>* curr = last->prev;
    //        last->prev = newNode;
    //        curr->next = newNode;
    //        newNode->prev = curr;
    //        newNode->next = last;
    //    }
    //    lst_size++;
    //}

    //void push_front(T&& value) {
    //    Node<T>* newNode = new Node<T>(std::move(value));
    //    if (lst_size == 0) {
    //        first = newNode;
    //        first->next = last;
    //        first->prev = last;
    //        last->prev = first;
    //        last->next = first;
    //    }
    //    else {
    //        newNode->next = first;
    //        newNode->prev = last;
    //        first->prev = newNode;
    //        last->next = newNode;
    //        first = newNode;
    //    }
    //    lst_size++;
    //}

    void push_front(T && value) {
        Node<T>* newNode = new Node<T>(value);
        if (lst_size == 0) {
            first = newNode;
            first->next = last;
            first->prev = last;
            last->prev = first;
            last->next = first;
        }
        else {
            newNode->next = first;
            newNode->prev = last;
            first->prev = newNode;
            last->next = newNode;
            first = newNode;
        }
        lst_size++;
    }

    void pop_back() {
        if (empty()) return;

        if (lst_size == 1) {
            delete first;
            first = nullptr;
            last->prev = last;
            last->next = last;
        }
        else {
            Node<T>* curr = last->prev;
            Node<T>* newNode = curr->prev;
            newNode->next = last;
            last->prev = newNode;
            delete curr;
        }
        lst_size--;
    }


    void pop_front() {
        if (empty()) return;

        if (lst_size == 1) {
            delete first;
            first = nullptr;
            last->prev = last;
            last->next = last;
        }
        else {
            Node<T>* newNode = first->next;
            newNode->prev = last;
            last->next = newNode;
            delete first;
            first = newNode;
        }
        lst_size--;
    }

    void reverse() noexcept {
        if (empty()) return;

        Node<T>* curr = first;
        Node<T>* tmp;
        while (curr != last) {
            tmp = curr->prev;
            curr->prev = curr->next;
            curr->next = tmp;
            curr = tmp;
        }
        tmp = first;
        first = last->prev;
        last->prev = tmp;
    }

    int countOfEvenElem() {
        int count = 0;

        for (auto it = begin(); it != end(); ++it)
            if (*it % 2 == 0)
                count++;

        return count;
    }

    std::pair<T, int> findMaxElemAndCountItEntry() {
        int count = 0;
        T max = T();
        for (auto it = begin(); it != end(); ++it){
            if (*it > max) {
                max = *it;
                count = 1;
            }
            else if (*it == max) count++;
        }
        return std::make_pair(max, count);
    }

    void add_to_list(Node<T>* node) {
        if (empty()) {
            first = node;
            last->prev = node;
            last->next = first;
            node->next = last;
            node->prev = last;
        }
        else {
            Node<T>* prev = last->prev;
            prev->next = node;
            node->prev = prev;
            node->next = last;
            last->prev = node;
        }
        lst_size++;
    }

    std::pair<MyList<T>, MyList<T>> splitList() {
        MyList<T> neg;
        MyList<T> pos;

        for(Node<T>* curr = first; curr != last;) {
            Node<T>* next = curr->next;

            if (curr->prev) curr->prev->next = curr->next;
            if (curr->next) curr->next->prev = curr->prev;

            curr->next = nullptr;
            curr->prev = nullptr;

            if (curr->Data < 0) neg.add_to_list(curr);
            else pos.add_to_list(curr);
            curr = next;
        }

        first = last;
        last->prev = last;
        last->next = last;
        lst_size = 0;

        return std::make_pair(neg, pos);
    }

    void reverse_custom()
    {
        for (auto curr = first; curr != last;)
        {
            auto tmp = curr->prev;
            curr->prev = curr->next;
            curr->next = tmp;
            curr = curr->prev;
        }
        std::swap(first,last->prev);
        std::swap(last->prev, last->next);
    }


    ~MyList() { 
        clear();
        operator delete(last,sizeof(Node<T>));
    }

    // ____________________________ БОНУСНОЕ ЗАДАНИЕ ____________________________
    //     Для бонусного задания необходимо реализовать конструкторы, работающие с move семантикой
    // MyList(MyList&& other) noexcept;
    // MyList& operator=(MyList&& other) noexcept;

    //     И методы добавления элементов

    // iterator insert(iterator pos, T&& value);
    // void push_back(T&& value);
    // void push_front(T&& value);

    //     ИЛИ использовать универсальную ссылку и std::forward вместо обычных методов (https://en.cppreference.com/w/cpp/utility/forward)
    //     Подробное введение в rvalue-ссылки (https://habr.com/ru/articles/322132/)

    // template<typename U>
    // iterator insert(iterator pos, U&& value);
    // template<typename U>
    // void push_back(U&& value);
    // template<typename U>
    // void push_front(U&& value);
};
