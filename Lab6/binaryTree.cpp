//ENUNCIADO: Arbol binario ordenado con borrado, insercion y busqueda
//PARTICIPANTES: 1101331 Asier Ochoa; Yeuris Terrero | 1099399; Carlos Garcia | 1101629; Miguel Angel | 1100685
//FECHA: 10/06/22

#include "raylib.h"
#include "rlImGui.h"
#include "imgui.h"
#include "raymath.h"
#include <iostream>
#include <sstream>

#define FONT_SIZE 25
#define PADDING 8
#define LINE_THICK 3
#define SPACING_VER 10
#define SPACING_HOR 20

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

        template <typename U>
        friend class BinaryTreeRenderer; // Allows for rendering to be completely decoupled
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

template <typename T>
class BinaryTreeRenderer {
    private:
        BinarySearchTree<T>& tree;

        int cursorY, orderX;
        void RecursiveDraw(typename BinarySearchTree<T>::Node* currentRoot, typename BinarySearchTree<T>::Node* parent);

    public:
        BinaryTreeRenderer(BinarySearchTree<T>& tree) :tree(tree), cursorY(0), orderX(0) {}
        void Draw();
};

template<typename T>
void BinaryTreeRenderer<T>::RecursiveDraw(typename BinarySearchTree<T>::Node* currentRoot, typename BinarySearchTree<T>::Node* parent) {
    if (currentRoot->left != nullptr){
        cursorY++;
        RecursiveDraw(currentRoot->left, currentRoot);
    }
    if (currentRoot->left == nullptr && currentRoot->right == nullptr){
        DrawRectangleLinesEx(Rectangle{(FONT_SIZE + PADDING * 2 + SPACING_HOR) * orderX, (FONT_SIZE + PADDING * 2 + SPACING_VER) * cursorY, FONT_SIZE + PADDING * 2, FONT_SIZE + PADDING * 2}, LINE_THICK, WHITE);
        //std::cout << "Drawn: " << currentRoot->value << " | O: " << orderX << " | C: " << cursorY << '\n';
        orderX++;
        cursorY--;
        return;
    }
    if (currentRoot->right != nullptr) {
        DrawRectangleLinesEx(Rectangle{(FONT_SIZE + PADDING * 2 + SPACING_HOR) * orderX, (FONT_SIZE + PADDING * 2 + SPACING_VER) * cursorY, FONT_SIZE + PADDING * 2, FONT_SIZE + PADDING * 2}, LINE_THICK, WHITE);
        //std::cout << "Drawn: " << currentRoot->value << " | O: " << orderX << " | C: " << cursorY << '\n';
        orderX++;
        cursorY++;
        RecursiveDraw(currentRoot->right, currentRoot);
    } else {
        DrawRectangleLinesEx(Rectangle{(FONT_SIZE + PADDING * 2 + SPACING_HOR) * orderX, (FONT_SIZE + PADDING * 2 + SPACING_VER) * cursorY, FONT_SIZE + PADDING * 2, FONT_SIZE + PADDING * 2}, LINE_THICK, WHITE);
        //std::cout << "Drawn: " << currentRoot->value << " | O: " << orderX << " | C: " << cursorY << '\n';
        orderX++;
        cursorY--;
        return;
    }
}

template<typename T>
void BinaryTreeRenderer<T>::Draw() {
    if (!tree.isEmpty()){
        RecursiveDraw(tree.root, nullptr);
        cursorY = 0;
        orderX = 0;
    }
}

int main() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1280, 720, "Binary Search Tree");
    rlImGuiSetup(true);
    SetTargetFPS(60);

    Camera2D cam;
    cam.target = {0, 0};
    cam.zoom = 1;
    cam.offset = {0, 0};
    cam.rotation = 0;
    BinarySearchTree<int> t;
    BinaryTreeRenderer<int> renderer(t);

    while (!WindowShouldClose()){
        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
            cam.offset = Vector2Add(cam.offset, GetMouseDelta());
        cam.zoom += GetMouseWheelMove() * 0.1;
        BeginDrawing();
        ClearBackground(BLACK);
        BeginMode2D(cam);
        renderer.Draw();
        EndMode2D();
        rlImGuiBegin();
        if (ImGui::Begin("Control")) {
            static int value;

            ImGui::PushTextWrapPos(ImGui::GetWindowWidth());
            ImGui::Text("LOLXD", nullptr);
            ImGui::PopTextWrapPos();
            ImGui::Separator();
            ImGui::PushItemWidth(80);
            ImGui::InputInt("##", &value); ImGui::SameLine();
            ImGui::PopItemWidth();
            if (ImGui::Button("Insert Value"))
                t.Insert(value);
            if (ImGui::Button("Remove Value")){
                t.Remove(value);
            }
        }
        ImGui::End();
        rlImGuiEnd();
        EndDrawing();
    }
    return 0;
}
