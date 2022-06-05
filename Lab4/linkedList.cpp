//ENUNCIADO: Listas enlazadas con ordenamiento al insertar (se permite el uso de std string)
//PARTICIPANTES: ID NOMBRE APELLIDO
//FECHA:

#include <string>
#include <iostream>
#include <exception>

class value_not_found : public std::exception{};

template <typename T>
class LinkedList {
    private:
        struct Node{
            explicit Node(T& val): value(val), next(nullptr){}
            T value;
            Node* next;
        };
        Node* first;
        Node* last;
        bool IsEmpty(){return first == nullptr || last == nullptr;}

    public:
        LinkedList();
        void Insert(T value);
        T Remove();

        //Functions for getting references to the values in the nodes
        T& End();
        T& operator[](T value); //Use this to access an element instead of peek
};

template<typename T>
LinkedList<T>::LinkedList()
    :first(nullptr), last(nullptr){}

template<typename T>
void LinkedList<T>::Insert(T value) {
    if (IsEmpty()) { //If is empty, set both to the same node
        first = new Node(value);
        last = first;
        return;
    }
    Node* newN = new Node(value);
    for (Node* i = first; i != nullptr ; i = i->next) {
        if (value <= i->value) {
            if (i == first){ //In case it's inserted at head
                newN->next = first;
                first = newN;
                return;
            }
            if (i == last){
                last->next = newN;
                last = newN;
                return;
            }
            newN->next = i->next->next;
            i->next = newN;
            return;
        }
    }
    last->next = newN;
    last = newN;
}

template<typename T>
T &LinkedList<T>::operator[](T value) {
    if (IsEmpty()) //safety check
        throw value_not_found();
    for (Node* i = first; i != nullptr; i = i->next)
        if (i->value == value)
            return i->value;
    throw value_not_found();
}

int main(){
    LinkedList<int> l;
    l.Insert(3);
    l.Insert(4);
    l.Insert(4);
    l.Insert(2);
    std::cout << l[3] << '\n';
    return 0;
}