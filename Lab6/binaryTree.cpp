//ENUNCIADO: Arbol binario ordenado con borrado, insercion y busqueda
//PARTICIPANTES: 1101331 Asier Ochoa ; Yeuris Terrero | 1099399 ; Carlos Garcia | 1101629 ; Miguel Angel | 1100685
//FECHA: 10/06/22

template <typename T>
class BinarySearchTree {
    private:
        struct Node{
            Node(T value): value(value), left(nullptr), right(nullptr) {}
            T value;
            Node* left;
            Node* right;
        };
        Node* root;
        void recursiveInsert(Node* currentRoot, T &value);
        bool isEmpty();

    public:
        BinarySearchTree() : root(nullptr) {}
        void Insert(T value);
        void Remove(T& value);
};

template<typename T>
bool BinarySearchTree<T>::isEmpty() {
    return root == nullptr;
}

template<typename T>
void BinarySearchTree<T>::Insert(T value) {
    if (isEmpty()) {
        root = new Node(value);
        return;
    }
    recursiveInsert(root, value);
}

template<typename T>
void BinarySearchTree<T>::recursiveInsert(BinarySearchTree::Node* currentRoot, T &value) {
    if (value < currentRoot->value){
        if (currentRoot->left == nullptr) {
            currentRoot->left = new Node(value);
            return;
        }
        recursiveInsert(currentRoot->left, value);
    } else {
        if (currentRoot->right == nullptr) {
            currentRoot->right = new Node(value);
            return;
        }
        recursiveInsert(currentRoot->right, value);
    }
}

int main() {
    BinarySearchTree<int> t;
    t.Insert(43);
    t.Insert(21);
    t.Insert(42);
    t.Insert(56);
    t.Insert(45);
    return 0;
}
