//ENUNCIADO: Listas enlazadas con ordenamiento al insertar (se permite el uso de std string)
//PARTICIPANTES: ID NOMBRE APELLIDO
//FECHA: 5/6/2020

#include <iostream>

struct Node
{
    int data;
    Node *next;
};

void pushList(Node *&list, int num)
{
    Node *new_node = new Node; //creates new node
    new_node->data = num; //adds data to node

    Node *temp1 = list;
    Node *temp2 = new Node;

    while ((temp1 != NULL) && (temp1->data < num)) //orders the list
    {
        temp2 = temp1;
        temp1 = temp1->next;
    }

    if (list == temp1)
    {
        list = new_node;
    }
    else
    {
        temp2->next = new_node;
    }

    new_node -> next = temp1;
    
}

void showList(Node *list)
{
    Node *temp = new Node;
    temp = list;

    while (temp != NULL)
    {
        std::cout<<temp->data<<" -> ";
        temp = temp->next;
    }
    
    std::cout<<"NULL\n";
}

void searchList(Node *list, int num)
{
    Node *temp = new Node;
    bool result = false;
    temp = list;

    while ((temp != NULL) && (temp->data <= num))
    {
        if (temp->data == num)
        {
            result = true;
        }
        temp = temp->next;
    }

    if (result == true)
    {
        std::cout<<num<<" found in the list\n";
    }
    else
    {
        std::cout<<num<<" not found in the list\n";
    }
    
    
}

void popList()
{

}

void popAllList()
{

}

int main()
{
    Node* list = nullptr;

    pushList(list, 10);
    pushList(list, 5);
    pushList(list, 50);
    showList(list);

    int num = 10;
    searchList(list, 10);

    return 0;
}
