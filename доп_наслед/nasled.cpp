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

// Интерфейсы IDeque и IStack
template <typename T>
struct IDeque {
    virtual void push_front(const T& data) = 0;
    virtual void push_back(const T& data) = 0;
    virtual void pop_front() = 0;
    virtual void pop_back() = 0;
    virtual T front() const = 0;
    virtual T back() const = 0;
    virtual size_t size() const = 0;
    virtual bool empty() const = 0;
    virtual ~IDeque() {}
};

// Класс Deque, реализующий интерфейс IDeque
template <typename T>
class Deque : public IDeque<T>, public LList<T> {
public:
    Deque() : LList<T>() {}
    void push_front(const T& data) override {
        LList<T>::push_front(data);
    }
    void push_back(const T& data) override {
        LList<T>::push_back(data);
    }
    void pop_front() override {
        LList<T>::pop_front();
    }
    void pop_back() override {
        LList<T>::pop_back();
    }
    T front() const override {
        return LList<T>::front();
    }
    T back() const override {
        return LList<T>::back();
    }
    size_t size() const override {
        return LList<T>::size();
    }
    bool empty() const override {
        return LList<T>::empty();
    }
};

// Тестирование Deque
int main() {
    Deque<int> dq;

    // Добавление элементов в начало и конец дека
    dq.push_front(1);
    dq.push_back(2);
    dq.push_front(0);
    dq.push_back(3);

    // Вывод первого и последнего элементов дека
    std::cout << "First element: " << dq.front() << std::endl;
    std::cout << "Last element: " << dq.back() << std::endl;

    // Удаление элементов из начала и конца дека
    dq.pop_front();
    dq.pop_back();

    // Вывод размера дека после удаления элементов
    std::cout << "Size after pop: " << dq.size() << std::endl;

    return 0;
}
