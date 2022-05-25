//ENUNCIADO: Hacer cola con prioridad (16 prioridades)
//PARTICIPANTES: ID NOMBRE APELLIDO
//FECHA:

#include <iostream>

template<typename T>
class Queue {
    private:
        struct Node {
            Node(T val): value(val), next(nullptr){}
            T value;
            Node* next;
        };
        Node* first;
        Node* last;

    public:
        Queue();
        void enqueue(const T& val);
        T dequeue();
        T peek();
        bool isEmpty();
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
    Node* tmp = last;
    last = new Node(val);
    tmp->next = last;
}

template<typename T>
T Queue<T>::dequeue() {
    if (!isEmpty()){
        Node* tmp = first->next;
        T ret = first->value;
        delete first;
        first = tmp;
        return ret;
    }
    return T();
}

template<typename T>
T Queue<T>::peek() {
    return first->value;
}

template<typename T>
bool Queue<T>::isEmpty() {
    return first == nullptr;
}

int main() {
    Queue<int> q;
    q.enqueue(3);
    q.enqueue(62);
    q.enqueue(903);
    q.enqueue(2);
    std::cout << q.peek() << "\n";
    std::cout << q.dequeue() << "\n";
    std::cout << q.dequeue() << "\n";
    std::cout << q.dequeue() << "\n";
    std::cout << q.dequeue() << "\n";
    std::cout << "might segfault\n";
    std::cout << q.dequeue() << "\n";
    Queue<std::string> q2;
    q2.enqueue("XDD");
    q2.enqueue("LMAOO");
    std::cout << "------str-------\n";
    std::cout << q2.dequeue() << "\n";
    std::cout << q2.dequeue() << "\n";
    std::cout << "might segfault\n";
    std::cout << q2.dequeue() << "\n";
    return 0;
}