#include <iostream>
#include <stdexcept>

template<typename T>
class LList {
private:
    struct Node {
        T data;
        Node* next;
        explicit Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* head; // Дополнительный служебный узел

public:
    // Конструктор
    LList() : head(new Node(T())) {
        head->next = head; // Указываем на самого себя
    }

    // Деструктор
    ~LList() {
        clear();
        delete head;
    }

    // Конструктор копирования
    LList(const LList& other) : head(new Node(T())) {
        head->next = head; // Указываем на самого себя
        Node* temp = other.head->next;
        while (temp != other.head) {
            push_back(temp->data);
            temp = temp->next;
        }
    }

    // Оператор присваивания
    LList& operator=(const LList& other) {
        if (this != &other) {
            clear();
            Node* temp = other.head->next;
            while (temp != other.head) {
                push_back(temp->data);
                temp = temp->next;
            }
        }
        return *this;
    }

    // Метод добавления элемента в конец списка
    void push_back(const T& value) {
        insert(size(), value);
    }

    // Метод добавления элемента в начало списка
    void push_front(const T& value) {
        insert(0, value);
    }

    // Метод добавления элемента по индексу
    void insert(size_t idx, const T& value) {
        if (idx > size()) {
            throw std::out_of_range("Index out of range");
        }
        Node* newNode = new Node(value);
        Node* temp = head;
        for (size_t i = 0; i < idx; ++i) {
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
    }

    // Метод удаления последнего элемента
    void pop_back() {
        remove_at(size() - 1);
    }

    // Метод удаления первого элемента
    void pop_front() {
        remove_at(0);
    }

    // Метод удаления элемента по индексу
    void remove_at(size_t index) {
        if (index >= size()) {
            throw std::out_of_range("Index out of range");
        }
        Node* temp = head;
        for (size_t i = 0; i < index; ++i) {
            temp = temp->next;
        }
        Node* toDelete = temp->next;
        temp->next = toDelete->next;
        delete toDelete;
    }

    // Оператор доступа к элементу по индексу для записи
    T& operator[](size_t index) {
        if (index >= size()) {
            throw std::out_of_range("Index out of range");
        }
        Node* temp = head->next;
        for (size_t i = 0; i < index; ++i) {
            temp = temp->next;
        }
        return temp->data;
    }

    // Оператор доступа к элементу по индексу для чтения
    const T& operator[](size_t index) const {
        if (index >= size()) {
            throw std::out_of_range("Index out of range");
        }
        Node* temp = head->next;
        for (size_t i = 0; i < index; ++i) {
            temp = temp->next;
        }
        return temp->data;
    }

    // Метод получения размера списка
    size_t size() const {
        size_t count = 0;
        Node* temp = head->next;
        while (temp != head) {
            ++count;
            temp = temp->next;
        }
        return count;
    }

    // Метод проверки на пустоту
    bool empty() const {
        return head->next == head;
    }

    // Метод очистки списка
    void clear() {
        while (!empty()) {
            pop_front();
        }
    }

    // Метод получения первого элемента
    T front() const {
        if (empty()) {
            throw std::out_of_range("List is empty");
        }
        return head->next->data;
    }

    // Метод получения последнего элемента
    T back() const {
        if (empty()) {
            throw std::out_of_range("List is empty");
        }
        Node* temp = head->next;
        while (temp->next != head) {
            temp = temp->next;
        }
        return temp->data;
    }

    // Класс итератора
    class Iterator {
    private:
        Node* current;

    public:
        explicit Iterator(Node* node) : current(node) {}

        T& operator*() const {
            return current->data;
        }

        Iterator& operator++() {
            current = current->next;
            return *this;
        }

        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }
    };

    // Метод получения итератора на начало списка
    Iterator begin() const {
        return Iterator(head->next);
    }

    // Метод получения итератора на конец списка
    Iterator end() const {
        return Iterator(head);
    }
};

// Функция для печати списка
template<typename T>
void print_lst(const LList<T>& l) {
    typename LList<T>::Iterator it = l.begin();
    while (it != l.end()) {
        std::cout << *it << " -> ";
        ++it;
    }
    std::cout << std::endl;
}

int main() {
    LList<char> lst;
    std::cout << std::boolalpha << lst.empty() << std::endl;

    for (int i = 0; i < 5; ++i)
        lst.push_back('a' + i);

    print_lst(lst);

    for (int i = 0; i < 5; ++i)
        lst.insert(0, 'z' - i);

    print_lst(lst);

    for (size_t i = 0; i != lst.size(); ++i)
        lst[i] = 'a' + i;

    print_lst(lst);

    lst.pop_back();
    lst.pop_front();

    print_lst(lst);

    lst.remove_at(5);
    lst.insert(3, 'o');

    print_lst(lst);

    lst.clear();

    lst.push_back('q');
    lst.push_back('w');

    std::cout << lst.size() << ' ' << std::boolalpha << lst.empty() << std::endl;

    return 0;
}


