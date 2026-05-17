#include <iostream>
#include <string>

using namespace std;

class NodoMatriz {
public:
    int fila, columna;
    string color; 
    NodoMatriz *arriba, *abajo, *izquierda, *derecha;

    NodoMatriz(int f, int c, string col) {
        fila = f; 
        columna = c; 
        color = col;
        arriba = abajo = izquierda = derecha = nullptr;
    }
};

class MatrizDispersa {
public:
    NodoMatriz* raiz;
    
    MatrizDispersa() {
        raiz = new NodoMatriz(-1, -1, "RAIZ"); 
    }

    void insertar(int fila, int columna, string color) {
    }
};

class NodoCapa {
public:
    int idCapa;
    MatrizDispersa* pixeles; 
    NodoCapa *izq, *der;

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