#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

struct NodoMatriz {
    int fila;
    int columna;
    string color; 
    NodoMatriz* derecha;
    NodoMatriz* izquierda;
    NodoMatriz* abajo;
    NodoMatriz* arriba;

    NodoMatriz(int f, int c, string col) : fila(f), columna(c), color(col), 
        derecha(nullptr), izquierda(nullptr), abajo(nullptr), arriba(nullptr) {}
};

struct Cabecera {
    int indice;
    Cabecera* siguiente;
    NodoMatriz* primerNodo;

    Cabecera(int idx) : indice(idx), siguiente(nullptr), primerNodo(nullptr) {}
};

class MatrizDispersa {
private:
    Cabecera* filaCabeceraRaiz;
    Cabecera* columnaCabeceraRaiz;

    Cabecera* obtenerOCrearCabecera(Cabecera* &raiz, int idx) {
        if (!raiz || idx < raiz->indice) {
            Cabecera* nuevaCabecera = new Cabecera(idx);
            nuevaCabecera->siguiente = raiz;
            raiz = nuevaCabecera;
            return raiz;
        }

        Cabecera* aux = raiz;
        while (aux->siguiente && aux->siguiente->indice <= idx) {
            aux = aux->siguiente;
        }

        if (aux->indice == idx) return aux;

        Cabecera* nuevaCabecera = new Cabecera(idx);
        nuevaCabecera->siguiente = aux->siguiente;
        aux->siguiente = nuevaCabecera;
        return nuevaCabecera;
    }

public:
    MatrizDispersa() : filaCabeceraRaiz(nullptr), columnaCabeceraRaiz(nullptr) {}

    void insertar(int f, int c, string col) {
        Cabecera* cabeceraFila = obtenerOCrearCabecera(filaCabeceraRaiz, f);
        Cabecera* cabeceraColumna = obtenerOCrearCabecera(columnaCabeceraRaiz, c);

        NodoMatriz* existente = buscar(f, c);
        if (existente) {
            existente->color = col; 
            return;
        }

        NodoMatriz* nuevoNodo = new NodoMatriz(f, c, col);

        if (!cabeceraFila->primerNodo || cabeceraFila->primerNodo->columna > c) {
            nuevoNodo->derecha = cabeceraFila->primerNodo;
            if (cabeceraFila->primerNodo) cabeceraFila->primerNodo->izquierda = nuevoNodo;
            cabeceraFila->primerNodo = nuevoNodo;
        } else {
            NodoMatriz* temp = cabeceraFila->primerNodo;
            while (temp->derecha && temp->derecha->columna < c) {
                temp = temp->derecha;
            }
            nuevoNodo->derecha = temp->derecha;
            if (temp->derecha) temp->derecha->izquierda = nuevoNodo;
            nuevoNodo->izquierda = temp;
            temp->derecha = nuevoNodo;
        }

        if (!cabeceraColumna->primerNodo || cabeceraColumna->primerNodo->fila > f) {
            nuevoNodo->abajo = cabeceraColumna->primerNodo;
            if (cabeceraColumna->primerNodo) cabeceraColumna->primerNodo->arriba = nuevoNodo;
            cabeceraColumna->primerNodo = nuevoNodo;
        } else {
            NodoMatriz* temp = cabeceraColumna->primerNodo;
            while (temp->abajo && temp->abajo->fila < f) {
                temp = temp->abajo;
            }
            nuevoNodo->abajo = temp->abajo;
            if (temp->abajo) temp->abajo->arriba = nuevoNodo;
            nuevoNodo->arriba = temp;
            temp->abajo = nuevoNodo;
        }

        cout << "Insertado pixel en [" << nuevoNodo->fila << "][" << nuevoNodo->columna << "] con color " << nuevoNodo->color << endl;
    }

    NodoMatriz* buscar(int f, int c) {
        Cabecera* filaActual = filaCabeceraRaiz;
        while (filaActual && filaActual->indice < f) filaActual = filaActual->siguiente;
        
        if (filaActual && filaActual->indice == f) {
            NodoMatriz* temp = filaActual->primerNodo;
            while (temp && temp->columna < c) temp = temp->derecha;
            if (temp && temp->columna == c) return temp;
        }
        return nullptr;
    }

    void mostrarMatriz(int maxF, int maxC) {
        cout << "\nVisualizacion de Matriz Dispersa de la Capa:\n";
        for (int i = 0; i <= maxF; i++) {
            for (int j = 0; j <= maxC; j++) {
                NodoMatriz* n = buscar(i, j);
                if (n) {
                    cout << setw(8) << n->color << " ";
                } else {
                    cout << setw(8) << "BLANCO" << " ";  
                }
            }
            cout << endl;
        }
    }
};

class NodoCapa {
public:
    int idCapa;
    MatrizDispersa* pixeles; 
    NodoCapa *izq;
    NodoCapa *der;

    NodoCapa(int id) {
        idCapa = id;
        pixeles = new MatrizDispersa();
        izq = der = nullptr;
    }
};

class ABBCapas {
public:
    NodoCapa* raiz;

    ABBCapas() { raiz = nullptr; }

    void insertarCapa(int id) {
    }

    NodoCapa* buscarCapa(int id) {
        return nullptr;
    }
};