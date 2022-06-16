//ENUNCIADO: Arbol binario ordenado con borrado, insercion y busqueda
//PARTICIPANTES: 1101331 Asier Ochoa ; Yeuris Terrero | 1099399 ; Carlos Garcia | 1101629 ; Miguel Angel | 1100685
//FECHA: 10/06/22

template <typename T>
class BinaryTree {
    private:
        struct Node{
            Node(T value): value(value), left(nullptr), right(nullptr) {}
            T value;
            Node* left;
            Node* right;
        };
        Node* root;
        Node* traverse(Node* currentRoot, T &value) {
            if (currentRoot->left != nullptr && currentRoot->right != nullptr) {
                currentRoot->left > currentRoot->right ? traverse(currentRoot->left, value) : traverse(currentRoot->right, value);
            }
        }
        bool isEmpty();

    public:
        BinaryTree() :root(nullptr) {}
        void Insert(T value);
        void Remove(T& value);
};

template<typename T>
bool BinaryTree<T>::isEmpty() {
    return root == nullptr;
}

template<typename T>
void BinaryTree<T>::Insert(T value) {
    if (isEmpty()) {
        root = new Node(value);
        return;
    }

}
