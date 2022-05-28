//ENUNCIADO: Hacer programa que use stacks
//PARTICIPANTES: 1101331 Asier Ochoa, 1099399 Yeuris Terrero, 1101629 Carlos Garcia, 1100685 Miguel Angel
//FECHA: 27/5/22

#include <iostream>

struct Node
{
    int data;
    Node *next;
};

void pushNode(Node *&stack, int num)
{
    Node *new_Node = new Node;
    new_Node -> data = num;
    new_Node -> next = stack;
    stack = new_Node;
}

void popNode(Node *&stack, int num)
{
    Node *temp = stack;
    num = temp -> data;
}

int main()
{
    Node* stack = nullptr;
    pushNode(stack, 1);
}
