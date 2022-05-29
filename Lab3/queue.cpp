//ENUNCIADO: Hacer cola con prioridad (16 prioridades)
//PARTICIPANTES: ID NOMBRE APELLIDO
//FECHA:

#include <iostream>
#include <utility>
#include "raylib.h"
#include "raymath.h"
#include "imgui.h"
#include "rlImGui.h"

struct DrawingParams {
    int spacing;
    int verticalSpacing;
    int nodeWidth;
    int nodeHeight;
    Vector2 start;
    Color firstCol;
    Color lastCol;
};

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
        void draw(DrawingParams& params);
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

template<typename T>
void Queue<T>::draw(DrawingParams& params) {
    Node* ptr = first;
    if (first == last){
        int count = 0;
        int xpos = params.start.x + (params.nodeWidth + params.spacing) * count;
        DrawRectangleLines(xpos, params.start.y, params.nodeWidth, params.nodeHeight, params.firstCol);
        DrawLine(xpos + params.nodeWidth / 2, params.start.y, xpos + params.nodeWidth / 2, params.start.y + params.nodeHeight, params.firstCol);
        DrawText(std::to_string(ptr->priority).c_str(), xpos + 10, params.start.y + 10, 25, BLUE);
        DrawText(std::to_string(ptr->value).c_str(), xpos + 10 + params.nodeWidth / 2, params.start.y + 10, 25, params.firstCol);
        ptr = ptr->next;
    } else {
        int count = 0;
        while (ptr->next != nullptr) {
            int xpos = params.start.x + (params.nodeWidth + params.spacing) * count;
            DrawRectangleLines(xpos, params.start.y, params.nodeWidth, params.nodeHeight, WHITE);
            DrawLine(xpos + params.nodeWidth / 2, params.start.y, xpos + params.nodeWidth / 2,
                     params.start.y + params.nodeHeight, WHITE);
            DrawText(std::to_string(ptr->priority).c_str(), xpos + 10, params.start.y + 10, 25, BLUE);
            DrawText(std::to_string(ptr->value).c_str(), xpos + 10 + params.nodeWidth / 2, params.start.y + 10, 25, WHITE);
            ptr = ptr->next;
            count++;
        }
    }
}

int main() {
    InitWindow(800, 600, "Cola con prioridad");
    rlImGuiSetup(true);
    SetTargetFPS(60);
    Camera2D camera;
    camera.target = {0,0};
    camera.zoom = 1;
    camera.offset = {0,0};
    camera.rotation = 0;
    Queue<int> q[100];
    DrawingParams params{};
    params.firstCol = GREEN;
    params.lastCol = RED;
    params.spacing = 50;
    params.verticalSpacing = 20;
    params.nodeHeight = 50;
    params.nodeWidth = 100;
    params.start = {200, 200};
    while (!WindowShouldClose()){
        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)){
            camera.offset = Vector2Add(camera.offset, GetMouseDelta());
        }
        BeginDrawing();
        ClearBackground(BLACK);
        BeginMode2D(camera);
        for (int i = 0; i < 100; ++i) {
            if (!q[i].isEmpty()){
                q[i].draw(params);
                params.start.y += params.nodeHeight + params.verticalSpacing;
            }
        }
        params.start.y = 0;
        EndMode2D();
        rlImGuiBegin();
        if (ImGui::Begin("Control")) {
            static int chosenIndex;
            static int value;
            static int priority;
            ImGui::PushItemWidth(80);
            ImGui::InputInt("Chosen queue", &chosenIndex);
            ImGui::Separator();
            ImGui::InputInt("##", &value); ImGui::SameLine();
            ImGui::SliderInt("Priority", &priority, 0, 15);
            ImGui::PopItemWidth();
            if (ImGui::Button("Enqueue Item"))
                q[chosenIndex].enqueue(value, priority);
            if (ImGui::Button("Break"))
                std::cout << "XD";
            ImGui::End();
        }
        rlImGuiEnd();
        EndDrawing();
    }
}