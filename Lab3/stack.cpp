//ENUNCIADO: Hacer programa que use stacks
//PARTICIPANTES: 1101331 Asier Ochoa, 1099399 Yeuris Terrero, 1101629 Carlos Garcia, 1100685 Miguel Angel
//FECHA: 27/5/22

#include <iostream>

struct Node //creates a node struct
{
    int data;
    Node *next;
};

void pushNode(Node *&stack, int num) //pushes a node to the pile
{
    Node *new_Node = new Node; //creates space in the memory for a new node
    new_Node -> data = num; //moves data and pointer to the new node
    new_Node -> next = stack;
    stack = new_Node;// makes the stack point to the new node
}

void popNode(Node *&stack, int &num) //pops top node
{
    Node *temp = stack; //creates a temporay node that points where the stack is pointing
    num = temp -> data; //moves data to temporary node
    stack = temp -> next; //makes the stack point to the next node
    delete temp; //deletes the data of the previous node
}

int main()
{
    Node* stack = nullptr; //creates the stack, wich is a code that points to null

    int num = 0, choice;

    //menu for interactive stack
    MENU:std::cout<<"What would you like to do?\n";
    std::cout<<"1. Push the list\n";
    std::cout<<"2. Pop the list\n";
    std::cout<<"3. Exit\n";
    std::cin>>choice;

    switch (choice)
    {
    case 1: //pushes input number to the stack
        std::cout<<"Number to push: \n";
        std::cin>>num;
        pushNode(stack, num);
        std::cout<< num << " added to the pile\n";
        goto MENU; //repeats the program for another input, unsafe but works xd
        break;
    case 2: //pops the list
        popNode(stack, num);
        std::cout<< num << " removed from the pile\n";
        if (stack == nullptr)
        {
            std::cout<<"stack is empty\n";
        }
        goto MENU;
        break;
    case 3: //ends program
        return 0;
        break;
    default: //type check
        std::cout<<"Wrong choice\n";
        goto MENU;
        break;
    }

    /*for (size_t i = 0; i < 5; i++) //adds numbers to the pile to show it works
    {
        num = i;
        pushNode(stack, num);
        std::cout<< i << " added to the pile\n";
    }

    std::cout<< "\nFirst in Last out:\n" << "\n";

    while (stack != nullptr) //removes elements from the pile FILO
    {
        popNode(stack, num);
        std::cout<< num << " removed from the pile\n";
    }*/
    
}
