#pragma once
#include <iostream>
#include <fstream> 
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
    NodoCapa *left;
    NodoCapa *right;

    NodoCapa(int id) {
        idCapa = id;
        pixeles = new MatrizDispersa();
        left = right = nullptr;
    }
};

class BSTCapas {
private:
    NodoCapa* root;

    NodoCapa* insert(NodoCapa* node, int id) {
        if (node == nullptr) {
            cout << "Capa " << id << " agregada al BST." << endl;
            return new NodoCapa(id);
        }

        if (id < node->idCapa) {
            node->left = insert(node->left, id);
        }
        else if (id > node->idCapa) {
            node->right = insert(node->right, id);
        }
        else {
            cout << "Atencion: La capa con id " << id << " ya existe." << endl;
        }
        return node;
    }

    NodoCapa* search(NodoCapa* node, int id) {
        if (node == nullptr || node->idCapa == id) {
            return node;
        }

        if (id < node->idCapa) {
            return search(node->left, id);
        }
        return search(node->right, id);
    }

    // Raiz, izquierda, cerecha
    void preorden(NodoCapa* node) {
        if (node == nullptr) 
            return; 

        cout << "Capa ID: " << node->idCapa << endl;

        preorden(node->left);
        preorden(node->right);
    }

    // Izquierda, raiz, derecha
    void inorden(NodoCapa* node) {
        if (node == nullptr) return;

        inorden(node->left);

        cout << "Capa ID: " << node->idCapa << endl;

        inorden(node->right);
    }

    // Izquierda, derecha, raiz
    void postorden(NodoCapa* node) {
        if (node == nullptr) return;

        postorden(node->left);  
        postorden(node->right); 

        cout << "Capa ID: " << node->idCapa << endl;
    }

public:
    BSTCapas() {
        root = nullptr;
    }

    void insert(int id) {
        root = insert(root, id);
    }

    NodoCapa* search(int id) {
        return search(root, id);
    }

    void preorden() {
        preorden(root);
        cout << endl;
    }

    void inorden() {
        inorden(root);
        cout << endl;
    }

    void postorden() {
        postorden(root);
        cout << endl;
    }

private:

    void generarDotCapas(NodoCapa* node, ofstream& archivo) {
        if (node == nullptr) return;

        archivo << "    \"Capa_" << node->idCapa << "\" [label=\"Capa " << node->idCapa << "\", shape=box, style=filled, fillcolor=lightgreen];\n";

        if (node->left != nullptr) {
            archivo << "    \"Capa_" << node->idCapa << "\" -> \"Capa_" << node->left->idCapa << "\";\n";
            generarDotCapas(node->left, archivo);
        }
        
        if (node->right != nullptr) {
            archivo << "    \"Capa_" << node->idCapa << "\" -> \"Capa_" << node->right->idCapa << "\";\n";
            generarDotCapas(node->right, archivo);
        }
    }

public:
    void graficarArbolCapas() {
        if (root == nullptr) {
            cout << "El arbol de capas esta vacio." << endl;
            return;
        }

        ofstream archivo("arbol_capas.dot");
        if (!archivo.is_open()) {
            cout << "Error: No se pudo crear el archivo dot para capas." << endl;
            return;
        }

        archivo << "digraph ArbolCapas {\n";
        archivo << "    rankdir=TB;\n"; 

        generarDotCapas(root, archivo);

        archivo << "}\n";
        archivo.close();

        system("dot -Tpng arbol_capas.dot -o arbol_capas.png");
        
        cout << "¡Exito! Se genero la imagen arbol_capas.png en la carpeta del proyecto." << endl;
    }
}; 