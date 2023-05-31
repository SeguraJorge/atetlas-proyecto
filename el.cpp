#include <iostream>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

using namespace std;

struct atleta {
    char nombre[30];
    int documento;
    float tiempo;
    int promedio;
    int total;
    int vuelta;
    atleta* der;
    atleta* izq;
};

atleta* Raiz = NULL;
atleta* aux = NULL;
atleta* aux3 = NULL;

//jhon neiver valencia grueso
//juan camilo angulo naboyan
//jorge enrique segura rodriguez

int preorden(atleta* aux2) {
         cout<<"ATLETAS REGISTRADOS"<<endl;
     cout<<"--------------------------"<<endl;
    cout << "Numero de documento: " << aux2->documento<<endl;
    cout << "Nombre del Atleta: " << aux2->nombre<<endl;
    cout << "Ultima vuelta " << aux2->tiempo<< endl;
    cout<<"--------------------------"<<endl;
    if (aux2->izq != NULL) {
        preorden(aux2->izq);
    }
    if (aux2->der != NULL) {
        preorden(aux2->der);
    }
    return 0;
}

int promedio_orden(atleta* aux2) {
             cout<<"PROMEDIOS"<<endl;
     cout<<"--------------------------"<<endl;
    if (aux2 != NULL) {
        promedio_orden(aux2->izq);
        cout << " --  Numero de documento: " << aux2->documento << " "
             << "  Nombre del Atleta:  " << aux2->nombre << " "
             << "  Promedio:  " << aux2->promedio << endl;
        promedio_orden(aux2->der);
    }
}

atleta* buscarCorredor(atleta* nodo, int documento) {
    if (nodo == NULL || nodo->documento == documento) {
        return nodo;
    }
    if (documento < nodo->documento) {
        return buscarCorredor(nodo->izq, documento);
    } else {
        return buscarCorredor(nodo->der, documento);
    }
}

void RegistrarVuelta() {
        cout<<"REGISTRO DE VUELTAS"<<endl;
     cout<<"--------------------------"<<endl;
     cout<<endl;
    int documento;
    cout << "Registrar el número del documento del corredor: ";
    cin >> documento;
    cout <<endl;
    atleta* corredorvisto = buscarCorredor(Raiz, documento);

    if (corredorvisto != NULL) {
        corredorvisto->vuelta++;
        cout << "Nombre del atleta: " << corredorvisto->nombre << " "
             << "Ultima vuelta " << corredorvisto->tiempo << " "
             << "vuelta: " << corredorvisto->vuelta << endl;
        cout << "\n";
        cout << "Registre el tiempo de la última vuelta:" << endl;
        cin >> corredorvisto->tiempo;
        corredorvisto->total += corredorvisto->tiempo;
        corredorvisto->promedio = corredorvisto->total / corredorvisto->vuelta;
    } else {
        cout << "No se encuentra el atleta" << endl;
    }
}


int Posicionar() {
    if (aux->documento < aux3->documento) {
        if (aux3->izq != NULL) {
            aux3 = aux3->izq;
            Posicionar();
        } else {
            aux3->izq = aux;
        }
    } else if (aux->documento > aux3->documento) {
        if (aux3->der != NULL) {
            aux3 = aux3->der;
            Posicionar();
        } else {
            aux3->der = aux;
        }
    }
    return 0;
}

atleta* rotacionSimpleIzquierda(atleta* nodo) {
    atleta* aux = nodo->izq;
    nodo->izq = aux->der;
    aux->der = nodo;
    return aux;
}

atleta* rotacionSimpleDerecha(atleta* nodo) {
    atleta* aux = nodo->der;
    nodo->der = aux->izq;
    aux->izq = nodo;
    return aux;
}

atleta* rotacionDobleIzquierda(atleta* nodo) {
    nodo->izq = rotacionSimpleDerecha(nodo->izq);
    return rotacionSimpleIzquierda(nodo);
}

atleta* rotacionDobleDerecha(atleta* nodo) {
    nodo->der = rotacionSimpleIzquierda(nodo->der);
    return rotacionSimpleDerecha(nodo);
}

int altura(atleta* nodo) {
    if (nodo == NULL) {
        return 0;
    }
    int alturaIzquierda = altura(nodo->izq);
    int alturaDerecha = altura(nodo->der);
    return (alturaIzquierda > alturaDerecha) ? alturaIzquierda + 1 : alturaDerecha + 1;
}

int factorEquilibrio(atleta* nodo) {
    if (nodo == NULL) {
        return 0;
    }
    return altura(nodo->izq) - altura(nodo->der);
}

atleta* balancearArbol(atleta* nodo) {
    int factor = factorEquilibrio(nodo);
    if (factor > 1) {
        if (factorEquilibrio(nodo->izq) > 0) {
            nodo = rotacionSimpleIzquierda(nodo);
        } else {
            nodo = rotacionDobleIzquierda(nodo);
        }
    } else if (factor < -1) {
        if (factorEquilibrio(nodo->der) < 0) {
            nodo = rotacionSimpleDerecha(nodo);
        } else {
            nodo = rotacionDobleDerecha(nodo);
        }
    }
    return nodo;
}

atleta* insertarNodo(atleta* nodo, atleta* nuevoNodo) {
    if (nodo == NULL) {
        return nuevoNodo;
    }
    if (nuevoNodo->documento < nodo->documento) {
        nodo->izq = insertarNodo(nodo->izq, nuevoNodo);
    } else if (nuevoNodo->documento > nodo->documento) {
        nodo->der = insertarNodo(nodo->der, nuevoNodo);
    }
    return balancearArbol(nodo);
}

int Registro() {
         cout<<"REGISTRO DE ATLETAS"<<endl;
     cout<<"--------------------------"<<endl;
     cout<<endl;
    aux = (struct atleta*)malloc(sizeof(struct atleta));
    cout << "Ingrese el nombre del atleta: " << endl;
    cout<<"--> ";
    cin >> aux->nombre;
    cout << "Ingresar el número de documento del atleta: " << endl;
    cout<<"--> ";
    cin >> aux->documento;
    aux->der = NULL;
    aux->tiempo = 0;
    aux->vuelta = 0;
    aux->izq = NULL;

    if (Raiz == NULL) {
        Raiz = aux;
    } else {
        Raiz = insertarNodo(Raiz, aux);
    }

    return 0;
}

int main() {
    int op = 0;
    do {
          cout<<" BIENVENIDO AL MENU "<<endl;
        cout<<"----------------------"<<endl;
        cout << "(1). Registrar atleta" << endl;
        cout << "(2). Mostrar atletas" << endl;
        cout << "(3). Registrar tiempo" << endl;
        cout << "(4). Promedio de los  atletas" << endl;
        cout << "(5). Salir" << endl;
        cout<<"--> ";
        cin >>op;

        switch (op) {
            case 1:
                
                Registro();
                break;
            case 2:
                 preorden(Raiz);
                break;
            case 3:
                RegistrarVuelta();
                break;
            case 4:
                
                promedio_orden(Raiz);
                break;
            default:
                cout << "Opción no válida" << endl;
                break;
        }
    } while (op != 5);

    return 0;
}