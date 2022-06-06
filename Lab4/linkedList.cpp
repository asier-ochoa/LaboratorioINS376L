//ENUNCIADO: Listas enlazadas con ordenamiento al insertar (se permite el uso de std string)
//PARTICIPANTES: ID NOMBRE APELLIDO
//FECHA:

#include <string>
#include <exception>
#include <sstream>
#include <iostream>
#include "raylib.h"
#include "raymath.h"
#include "imgui.h"
#include "rlImGui.h"

#define FONT_SIZE 30
#define PADDING_HOR 8
#define PADDING_VER 8
#define LINE_THICK 3
#define SPACING 10

#define CENTER Vector2{400, 300}

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

        void Draw();

        //Functions for getting references to the values in the nodes
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
    Node* j = nullptr;
    for (Node* i = first; i != nullptr ; i = i->next) {
        if (value <= i->value) {
            if (i == first){ //In case it's inserted at head
                newN->next = first;
                first = newN;
                return;
            }
            newN->next = i;
            j->next = newN;
            return;
        }
        j = i;
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
    if (IsEmpty())
        throw value_not_found();
    Node* tmp = first->next;
    T ret = first->value;
    if (first == last){
        delete first;
        first = nullptr;
        last = nullptr;
        return ret;
    }
    delete first;
    first = tmp;
    return ret;
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

template<typename T>
void LinkedList<T>::Draw() {
    static std::stringstream buffer;
    int count = 0;
    int centerX;
    for (Node* i = first; i != nullptr; i = i->next) {
        buffer << i->value;
        int textWidth = MeasureText(buffer.str().c_str(), FONT_SIZE);
        centerX = (int)CENTER.x - (textWidth + PADDING_HOR * 2) / 2;
        Color current;
        if (i == first || i == last)
            if (i == first)
                current = GREEN;
            else
                current = RED;
        else
            current = WHITE;
        DrawRectangleLinesEx(Rectangle{(float)centerX, (float)(FONT_SIZE + PADDING_VER * 2 + SPACING) * count, (float)(textWidth + PADDING_HOR * 2), (float)(FONT_SIZE + PADDING_VER * 2)}, LINE_THICK, current);
        DrawText(buffer.str().c_str(), centerX + PADDING_HOR, (FONT_SIZE + PADDING_VER * 2 + SPACING) * count + PADDING_VER, FONT_SIZE, current);
        count++;
        buffer.str("");
    }
}

int main(){
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 600, "Lista Enlazada");
    rlImGuiSetup(true);
    SetTargetFPS(60);

    Camera2D cam;
    cam.target = {0, 0};
    cam.zoom = 1;
    cam.offset = {0, 0};
    cam.rotation = 0;

    LinkedList<int> li;
    LinkedList<std::string> ls;

    while (!WindowShouldClose()){
        static int tab;
        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
            cam.offset = Vector2Add(cam.offset, GetMouseDelta());
        cam.zoom += GetMouseWheelMove() * 0.1;
        BeginDrawing();
        ClearBackground(BLACK);
        BeginMode2D(cam);
        switch (tab) {
            case 0:
                li.Draw();
                break;
            case 1:
                ls.Draw();
                break;
        }
        EndMode2D();
        rlImGuiBegin();
        if (ImGui::Begin("Control")) {
            static int chosenIndex;
            static int value;
            static char buf[256];
            if (ImGui::BeginTabBar("xd")) {
                if (ImGui::BeginTabItem("Int")) {
                    tab = 0;
                    ImGui::PushItemWidth(80);
                    ImGui::InputInt("##", &value); ImGui::SameLine();
                    ImGui::PopItemWidth();
                    if (ImGui::Button("Insert Value"))
                        li.Insert(value);
                    if (ImGui::Button("Remove Value")){
                        try {
                            li.Remove(value);
                        } catch (const value_not_found& e) {}
                    }
                    if (ImGui::Button("Remove Front")){
                        try {
                            li.Dequeue();
                        } catch (const value_not_found& e) {}
                    }
                    ImGui::EndTabItem();
                }
                if (ImGui::BeginTabItem("String")) {
                    tab = 1;
                    ImGui::PushItemWidth(80);
                    ImGui::InputText("##", buf, 256); ImGui::SameLine();
                    ImGui::PopItemWidth();
                    if (ImGui::Button("Insert Value"))
                        ls.Insert(buf);
                    if (ImGui::Button("Remove Value")){
                        try {
                            ls.Remove(buf);
                        } catch (const value_not_found& e) {}
                    }
                    if (ImGui::Button("Remove Front")){
                        try {
                            ls.Dequeue();
                        } catch (const value_not_found& e) {}
                    }
                    ImGui::EndTabItem();
                }
                ImGui::EndTabBar();
            }
            ImGui::End();
        }
        rlImGuiEnd();
        EndDrawing();
    }
    return 0;
}