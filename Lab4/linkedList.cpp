//ENUNCIADO: Listas enlazadas con ordenamiento al insertar (se permite el uso de std string)
//PARTICIPANTES: 1101629 Carlos Ismael Garcia
//FECHA:
#include <iostream>
using namespace std;

struct Nodo
{
    int dato;
    Nodo* siguiente;
};

// Prototipos de funciones
void menu();
void InsertarElementos(Nodo*&, int);
int EliminarElementos(Nodo*&, int);
void MostrarElementos(Nodo*);

int main()
{
    
}

void menu()
{
    Nodo* lista = NULL;

};

void InsertarElementos(Nodo*& lista, int n)
{
    Nodo* nuevo_nodo = new Nodo(); //Reserves the space in memory to store the node 
    nuevo_nodo->dato = n;
    Nodo* aux1 = lista;
    Nodo* aux2; // helps order the data 


    /*
  
The loop works with the conditions such that: 1) while the list has not reached its end
    and 2) as long as the new entered data is less than the data that aux1 points to, it orders them in a way
    upward.
    */
    while (aux1 != NULL && aux1->dato < n)
    {
        aux2 = aux1;
        aux1 = aux1->siguiente;
    }

    /*
    
In this conditional we verify if the node that we are going to insert must go to the beginning, in the middle or
     at the end of the list
    */
    if (lista == aux1)
    {
        lista = nuevo_nodo;
    }
    else
    {
        aux2->siguiente = nuevo_nodo;
    }
    nuevo_nodo->siguiente = aux1; // Here it points to NULL, which helps us to reference the last position
};

void MostrarElementos(Nodo* lista)
{
    Nodo* nuevo_nodo = new Nodo();
    nuevo_nodo = lista; //Points to the start of the list to iterate through the elements

    while (nuevo_nodo != NULL)
    {
        cout << nuevo_nodo->dato << " , ";
        nuevo_nodo = nuevo_nodo->siguiente;
    }

};

int EliminarElementos(Nodo*& lista, int n)
{
    //in case its not empty
    if (lista != NULL)
    {
        Nodo* aux_eliminar;//deletes elements
        Nodo* anterior = NULL;

        aux_eliminar = lista;
        /*
        We reference it to the first element of the list, because it will be the pointer that will go through the list
        */


        /*
      In this loop we indicate that until we reach the end of the list, the element
        that we are looking for is not the element that is currently entered. This is to get to the item you want to delete.
        */
        while (aux_eliminar != NULL && aux_eliminar->dato != n)
        {
            anterior = aux_eliminar;
            aux_eliminar = aux_eliminar->siguiente;
        }

        if (aux_eliminar == NULL)
        {
            cout << "El elemento no existe";

        }

        /*
If this condition occurs then it is because the loop was never entered and this
         it is because at the beginning it is initialized as NULL, therefore the element
         to eliminate the is first
        */
        else if (anterior == NULL)
        {
            lista = lista->siguiente;
            delete aux_eliminar;
        }

        /*
This means that the element is in the list, but it will not be the first node to be
        going to delete.
        */
        else
        {
            anterior->siguiente = aux_eliminar->siguiente;
            delete aux_eliminar;
        }

    }return n;
}
    