//ENUNCIADO: Listas enlazadas con ordenamiento al insertar (se permite el uso de std string)
//PARTICIPANTES: ID NOMBRE APELLIDO
//FECHA:

template <typename T>
class LinkedList {
    private:
        struct Node{
            Node();
            T value;
            Node* next;
        };
        Node* first;
        Node* last;
        bool IsEmpty(){return first == nullptr || last == nullptr;}

    public:
        LinkedList();
        void Push(T& value);
        T Pop();

        void Enqueue(T& value);
        T Dequeue();

        //Functions for getting references to the values in the nodes
        T& End();
        T& operator[](T& value); //Use this to access an element instead of peek
};

template<typename T>
LinkedList<T>::LinkedList()
    :first(nullptr), last(nullptr){}

template<typename T>
T &LinkedList<T>::operator[](T &value) {
    if (IsEmpty()) //safety check
        return nullptr;
    Node* ptr = first;
    while(ptr != nullptr) {
        if (ptr->value == value){
            return value;
        }
    }
    return nullptr;
}

int main(){
    int a;
    return 0;
}