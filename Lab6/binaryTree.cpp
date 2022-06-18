//ENUNCIADO: Arbol binario ordenado con borrado e insercion
//PARTICIPANTES: 1101331 Asier Ochoa; Yeuris Terrero | 1099399; Carlos Garcia | 1101629; Miguel Angel | 1100685
//FECHA: 10/06/22

#include "raylib.h" // The data structure has no stdlib dependencies, these are only used for drawing
#include "rlImGui.h"
#include "imgui.h"
#include "raymath.h"
#include <unordered_map>
#include <iostream>
#include <sstream>

#define FONT_SIZE 32
#define PADDING 10
#define LINE_THICK 3
#define SPACING_VER 30
#define SPACING_HOR 15

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
            if (parent != nullptr)
                tmpVal < parent->value ? parent->left = nullptr : parent->right = nullptr;
            else
                root = nullptr;
            return;
        }
        if ((currentRoot->left != nullptr) != (currentRoot->right != nullptr)){ // XOR
            Node* tmp;
            T tmpVal = currentRoot->value;
            currentRoot->left != nullptr ? tmp = currentRoot->left : tmp = currentRoot->right;
            delete currentRoot;
            if (parent != nullptr)
                tmpVal < parent->value ? parent->left = tmp : parent->right = tmp;
            else
                root = tmp;
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

// -------------Rendering stuff below-------------

template <typename T>
class BinaryTreeRenderer {
    private:
        BinarySearchTree<T>& tree;
        std::unordered_map<typename BinarySearchTree<T>::Node*, Vector2> positions;

        int cursorY = 0, orderX = 0, totalWidth = 0;
        std::stringstream buff;
        void RecursiveDraw(typename BinarySearchTree<T>::Node* currentRoot);
        void RecursiveLine(typename BinarySearchTree<T>::Node* currentRoot, typename BinarySearchTree<T>::Node* parent);

    public:
        BinaryTreeRenderer(BinarySearchTree<T>& tree) :tree(tree), buff("") {}
        void Draw();
};

template<typename T>
void BinaryTreeRenderer<T>::RecursiveDraw(typename BinarySearchTree<T>::Node* currentRoot) {
    static int posX;
    static int posY;
    if (currentRoot->left != nullptr){
        cursorY++;
        RecursiveDraw(currentRoot->left);
    }
    if (currentRoot->left == nullptr && currentRoot->right == nullptr){
        buff << currentRoot->value;
        int textWidth = MeasureText(buff.str().c_str(), FONT_SIZE);
        posX = (PADDING * 2 + SPACING_HOR) * orderX + totalWidth;
        posY = (FONT_SIZE + PADDING * 2 + SPACING_VER) * cursorY;
        totalWidth += textWidth;
        positions[currentRoot] = Vector2{(float)posX, (float)posY};
        DrawRectangleLinesEx(Rectangle{(float)posX, (float)posY, (float)textWidth + PADDING * 2, FONT_SIZE + PADDING * 2}, LINE_THICK, WHITE);
        DrawText(buff.str().c_str(), posX + PADDING, posY + PADDING, FONT_SIZE, WHITE);
        buff.str("");
        orderX++;
        cursorY--;
        return;
    }
    if (currentRoot->right != nullptr) {
        buff << currentRoot->value;
        int textWidth = MeasureText(buff.str().c_str(), FONT_SIZE);
        posX = (PADDING * 2 + SPACING_HOR) * orderX + totalWidth;
        posY = (FONT_SIZE + PADDING * 2 + SPACING_VER) * cursorY;
        totalWidth += textWidth;
        positions[currentRoot] = Vector2{(float)posX, (float)posY};
        DrawRectangleLinesEx(Rectangle{(float )posX, (float)posY, (float)textWidth + PADDING * 2, FONT_SIZE + PADDING * 2}, LINE_THICK, WHITE);
        DrawText(buff.str().c_str(), posX + PADDING, posY + PADDING, FONT_SIZE, WHITE);
        buff.str("");
        orderX++;
        cursorY++;
        RecursiveDraw(currentRoot->right);
    }
    if (currentRoot->right == nullptr){
        buff << currentRoot->value;
        int textWidth = MeasureText(buff.str().c_str(), FONT_SIZE);
        posX = (PADDING * 2 + SPACING_HOR) * orderX + totalWidth;
        posY = (FONT_SIZE + PADDING * 2 + SPACING_VER) * cursorY;
        totalWidth += textWidth;
        positions[currentRoot] = Vector2{(float)posX, (float)posY};
        DrawRectangleLinesEx(Rectangle{(float)posX, (float)posY, (float)textWidth + PADDING * 2, FONT_SIZE + PADDING * 2}, LINE_THICK, WHITE);
        DrawText(buff.str().c_str(), posX + PADDING, posY + PADDING, FONT_SIZE, WHITE);
        buff.str("");
        orderX++;
        cursorY--;
        return;
    }
    cursorY--;
}

template<typename T>
void BinaryTreeRenderer<T>::RecursiveLine(typename BinarySearchTree<T>::Node* currentRoot, typename BinarySearchTree<T>::Node* parent) {
    if (currentRoot->left != nullptr){
        Vector2 origin = positions.at(currentRoot);
        Vector2 end = positions.at(currentRoot->left);
        DrawLineEx(origin, end, LINE_THICK, WHITE);
        RecursiveLine(currentRoot->left, currentRoot);
    }
    if (currentRoot->right != nullptr){
        Vector2 origin = positions.at(currentRoot);
        Vector2 end = positions.at(currentRoot->right);
        DrawLineEx(origin, end, LINE_THICK, WHITE);
        RecursiveLine(currentRoot->right, currentRoot);
    }
}

template<typename T>
void BinaryTreeRenderer<T>::Draw() {
    if (!tree.isEmpty()){
        positions.clear();
        RecursiveDraw(tree.root);
        cursorY = 0;
        orderX = 0;
        totalWidth = 0;
        RecursiveLine(tree.root, nullptr);
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
