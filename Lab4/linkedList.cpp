//ENUNCIADO: Listas enlazadas con ordenamiento al insertar (se permite el uso de std string)
//PARTICIPANTES: ID Miguelangel Gonzalez 1100685
//FECHA:


#include <iostream>
using namespace ::std;

struct nodo
{
    int dato;
    nodo *next;
} * primero, *ultimo;

void agregarNodo()
{
    nodo *nuevo = new nodo();
    cout << "Inserte un dato: ";
    cin >> nuevo->dato;
    cout << endl;
    nodo *aux = new nodo();
    nodo *anterior = new nodo();
    aux = primero;
    anterior = NULL;

    if (primero == NULL)
    {
        primero = nuevo;
        primero->next = NULL;
        ultimo = nuevo;
        cout << "Se ha insertado satisfactoriamente el numero " << nuevo->dato << endl;
    }
    else
    {

        if (nuevo->dato < aux->dato)
        {
            primero = nuevo;
            nuevo->next = aux;
        }
        else
        {
            while (aux != NULL && nuevo->dato > aux->dato)
            {
                anterior = aux;
                aux = aux->next;
            }
            if (aux == NULL)
            {
                ultimo->next = nuevo;
                ultimo = nuevo;
                nuevo->next = NULL;
            }
            else
            {
                anterior->next = nuevo;
                nuevo->next = aux;
            }
        }
        cout << "Se ha insertado satisfactoriamente el numero " << nuevo->dato << endl;
    }
}

void eliminarNodo()
{
    nodo *aux = new nodo();
    aux = primero;
    nodo *anterior = new nodo();
    anterior = NULL;
    bool encontrado = false;
    int buscarDato = 0;

    cout << "Ingrese el dato que desea eliminar de la lista: ";
    cin >> buscarDato;
    cout << endl;

    if (primero != NULL)
    {
        while (aux != NULL && encontrado != true)
        {
            if (aux->dato == buscarDato)
            { // indica si se encontro el nodo
                if (aux == primero)
                { // Si se va a borrar el primer elemento
                    primero = primero->next;
                }
                else if (aux == ultimo)
                { // Si se borra el ultimo
                    anterior->next = NULL;
                    ultimo = anterior;
                }
                else
                { // Si se borra numeros entre el primero y el utlimo
                    anterior->next = aux->next;
                }
                cout << "El numero " << buscarDato << " fue eliminado con exito" << endl;
                encontrado = true;
            }

            anterior = aux;
            aux = aux->next;
        }

        if (!encontrado)
        {
            cout << "El numero " << buscarDato << " no es parte de la lista" << endl;
        }
    }
    else
    {
        cout << "No puede eliminar el " << buscarDato << " porque lista esta vacia" << endl;
    }
}

void buscar()
{
    nodo *aux = new nodo();
    aux = primero;
    bool encontrado = false;
    int buscarDato = 0;
    int lugar = 1;
    cout << "Ingrese el dato que desea buscar de la lista: ";
    cin >> buscarDato;
    cout << endl;
    if (primero != NULL)
    {
        while (aux != NULL && encontrado != true)
        {

            if (aux->dato == buscarDato)
            { // indica si se encontro el nodo
                cout << "El dato se ha encontrado en la posicion " << lugar << endl;
                encontrado = true;
            }
            aux = aux->next;
            lugar++;
        }
        if (!encontrado)
        {
            cout << "El elemento no es parte de la lista" << endl;
        }
    }
    else
    {
        cout << "La lista esta vacia" << endl;
    }
}

void show()
{
    nodo *aux3 = new nodo();
    aux3 = primero;
    if (primero == NULL)
    {
        cout << "La Lista se encuentra vacia" << endl;
        cout << "" << endl;
    }
    else
    {
        cout << "" << endl;
        while (aux3 != NULL)
        {
            cout << aux3->dato << endl;
            aux3 = aux3->next;
        }
    }
}

int main(int argc, const char *argv[])
{
    int opcion;

    do
    {
        cout << "Bienvenido a nuestro programam de Lista Enlazada Simple" << endl;
        cout << endl;
        cout << "Que desea hacer? " << endl;
        cout << endl;
        cout << "-------------------------------------" << endl;
        cout << "1.Agregar numero a la lista" << endl;
        cout << "2.Eliminar numero de la lista" << endl;
        cout << "3.Mostrar la lista completa" << endl;
        cout << "4.Revisar si hay un numero en la lista" << endl;
        cout << "5.Salir" << endl;
        cout << "-------------------------------------" << endl;
        cout << endl;

        cout << "Opcion: ";
        cin >> opcion;
        cout << endl;

        switch (opcion)
        {
        case 1:
            agregarNodo();
            cout << endl;
#ifdef WIN32
                system("pause");
#endif
            break;

        case 2:
            eliminarNodo();
            cout << endl;
#ifdef WIN32
                system("pause");
#endif
            break;

        case 3:
            cout << "Lista: " << endl;
            show();
            cout << endl;
#ifdef WIN32
                system("pause");
#endif
            break;

        case 4:
            buscar();
            cout << endl;
#ifdef WIN32
                system("pause");
#endif
            break;
        case 5:
            cout << "Se ha finalizado " << endl;
            cout << endl;
#ifdef WIN32
                system("pause");
#endif
            break;

        default:
            cout << "Opcion no valida, intente nuevamente" << endl;
            cout << endl;
#ifdef WIN32
            system("pause");
#endif
            break;
        }
#ifdef WIN32
        system("cls");
#endif
    } while (opcion != 5);
}