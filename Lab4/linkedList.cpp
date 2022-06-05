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
        T Remove(T value); //Remove from arbitrary place
        T Dequeue(); //Remove from front

        //Functions for getting references to the values in the nodes
        const T& End();
        const T& operator[](T value); //Use this to access an element instead of peek
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
T LinkedList<T>::Remove(T value) {
    if (IsEmpty())
        throw value_not_found();
    Node* j = nullptr;
    for (Node* i = first; i != nullptr; i = i->next) {
        if (i->value == value){
            Node* tmp = i->next;
            T ret = i->value;
            if (i == first){
                first = tmp;
                if (i == last)
                    last = tmp;
                delete i;
                return ret;
            }
            if (i == last){
                delete i;
                j->next = nullptr;
                last = j;
                return ret;
            }
            delete i;
            j->next = tmp;
            return ret;
        }
        j = i;
    }
    throw value_not_found();
}

template<typename T>
T LinkedList<T>::Dequeue() {
    return nullptr;
}

template<typename T>
const T &LinkedList<T>::operator[](T value) {
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
    std::cout << l[3] << '\n';
    l.Remove(3);
    l.Insert(4);
    l.Insert(4);
    l.Insert(2);
    return 0;
}