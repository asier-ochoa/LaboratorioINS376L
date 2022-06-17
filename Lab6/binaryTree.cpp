//ENUNCIADO: Arbol binario ordenado con borrado, insercion y busqueda
//PARTICIPANTES: 1101331 Asier Ochoa; Yeuris Terrero | 1099399; Carlos Garcia | 1101629; Miguel Angel | 1100685
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
        void recursiveInsert(Node* currentRoot, T& value);
        void recursiveRemove(Node* currentRoot, Node* parent, T& value);
        T findSuccesor(Node* currentRoot, Node* parent, T& value); // Succesor's value gets returned as copy and is deleted
        bool isEmpty();

    public:
        BinarySearchTree() : root(nullptr) {}
        void Insert(T value);
        void Remove(T value);
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

template<typename T>
void BinarySearchTree<T>::Remove(T value) {
    if (isEmpty())
        return;
    recursiveRemove(root, nullptr, value);
}

template<typename T>
void BinarySearchTree<T>::recursiveRemove(BinarySearchTree::Node* currentRoot, BinarySearchTree::Node* parent, T &value) {
    if (currentRoot->value == value){ // Everything to the left is guaranteed to be smaller and everything to the right is guarantied to be larger than the parent!!!
        if (currentRoot->left == nullptr && currentRoot->right == nullptr){ // Case if leaf
            T tmpVal = currentRoot->value;
            delete currentRoot;
            tmpVal < parent->value ? parent->left = nullptr : parent->right = nullptr;
            return;
        }
        if ((currentRoot->left != nullptr) != (currentRoot->right != nullptr)){ // XOR
            Node* tmp;
            T tmpVal = currentRoot->value;
            currentRoot->left != nullptr ? tmp = currentRoot->left : tmp = currentRoot->right;
            delete currentRoot;
            tmpVal < parent->value ? parent->left = tmp : parent->right = tmp;
            return;
        }
        currentRoot->value = findSuccesor(currentRoot->right, currentRoot, value);
        return;
    }
    if (value < currentRoot->value){ // Recursive search
        if (currentRoot->left != nullptr)
            recursiveRemove(currentRoot->left, currentRoot, value);
    } else {
        if (currentRoot->right != nullptr)
            recursiveRemove(currentRoot->right, currentRoot, value);
    }
}

template<typename T>
T BinarySearchTree<T>::findSuccesor(BinarySearchTree::Node* currentRoot, BinarySearchTree::Node* parent, T &value) {
    if (currentRoot->left != nullptr) {
        return findSuccesor(currentRoot->left, currentRoot, value);
    }
    T ret = currentRoot->value;
    recursiveRemove(currentRoot, parent, currentRoot->value);
    return ret;
}

int main() {
    BinarySearchTree<int> t;
    t.Insert(43);
    t.Insert(21);
    t.Insert(42);
    t.Insert(56);
    t.Insert(45);
    t.Insert(18);
    t.Insert(15);
    t.Insert(14);
    t.Remove(21);
    return 0;
}
