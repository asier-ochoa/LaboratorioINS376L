//ENUNCIADO: Hacer cola con prioridad (16 prioridades)
//PARTICIPANTES: ID NOMBRE APELLIDO
//FECHA:

#include <iostream>
#include <utility>

template<typename T>
//REMEMBER!!! first-> node-> last-> NULL
class Queue {
    private:
        struct Node {
            Node(T val, unsigned char priority=0): value(std::move(val)), next(nullptr), priority(priority){}
            T value;
            Node* next;
            unsigned char priority;
        };
        Node* first;
        Node* last;

    public:
        Queue();
        void enqueue(const T& val);
        void enqueue(const T& val, unsigned char priority);
        T dequeue();
        T& peek();
        bool isEmpty();
        size_t count();
};

template<typename T>
Queue<T>::Queue()
    :first(nullptr), last(nullptr){}

template<typename T>
void Queue<T>::enqueue(const T& val) {
    if (isEmpty()) {
        first = new Node(val);
        last = first;
        return;
    }
    last->next = new Node(val);
    last = last->next;
}

template<typename T>
void Queue<T>::enqueue(const T &val, const unsigned char priority) {
    if (isEmpty()) {
        first = new Node(val, priority);
        last = first;
        return;
    }
    Node* ptr = first;
    if (ptr->priority < priority){
        first = new Node(val, priority);
        first->next = ptr;
        return;
    }
    while (ptr->next != nullptr){
        if (ptr->next->priority < priority)
            break;
        ptr = ptr->next;
    }
    if (ptr->next == nullptr)
        ptr->next = new Node(val, priority);
    else {
        Node* tmp = ptr->next;
        ptr->next = new Node(val, priority);
        ptr->next->next = tmp;
    }
}

template<typename T>
T Queue<T>::dequeue() {
    if (!isEmpty()){
        T ret = first->value;
        if (first == last){
            delete first;
            first = nullptr;
            last = nullptr;
            return ret;
        } else {
            Node* tmp = first->next;
            delete first;
            first = tmp;
            return ret;
        }
    }
    return T();
}

template<typename T>
T& Queue<T>::peek() {
    return first->value;
}

template<typename T>
bool Queue<T>::isEmpty() {
    return first == nullptr;
}

template<typename T>
size_t Queue<T>::count() {
    if (!isEmpty()) {
        Node* iter = first;
        size_t count = 1;
        while (iter->next != nullptr) {
            iter = iter->next;
            count++;
        }
        return count;
    }
    return 0;
}

int main() {
    Queue<int> q;
    q.enqueue(3,9);
    q.enqueue(62);
    q.enqueue(903);
    q.enqueue(2);
    q.enqueue(12345, 10);
    q.enqueue(54321, 10);
    std::cout << "peek: " << q.peek() << "\n";
    std::cout << "count: " << q.count() << "\n";
    std::cout << q.dequeue() << "\n";
    std::cout << q.dequeue() << "\n";
    std::cout << "count: " << q.count() << "\n";
    std::cout << q.dequeue() << "\n";
    std::cout << q.dequeue() << "\n";
    std::cout << q.dequeue() << "\n";
    q.enqueue(333, 2);
    std::cout << q.dequeue() << "\n";
    Queue<std::string> q2;
    q2.enqueue("XDD");
    q2.enqueue("LMAOO");
    std::cout << "------str-------\n";
    std::cout << q2.dequeue() << "\n";
    std::cout << q2.dequeue() << "\n";
    std::cout << "might segfault\n";
    std::cout << q2.dequeue() << "\n";
    q2.enqueue("IT WORKED");
    std::cout << q2.dequeue() << "\n";
    return 0;
}