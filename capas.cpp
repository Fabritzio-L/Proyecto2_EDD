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
    void graficarCapa(int idCapa) {
        ofstream archivo("capa_" + to_string(idCapa) + ".dot");
        if (!archivo.is_open()) {
            cout << "Error: No se pudo crear el archivo dot de la capa." << endl;
            return;
        }

        archivo << "digraph MatrizCapa_" << idCapa << " {\n";
        archivo << "    node [shape=box, style=filled, fillcolor=white];\n";

        archivo << "  splines=ortho;" << endl; 

        archivo << "  nodesep=0.5;" << endl;
        archivo << "    rankdir=TB;\n"; 

        archivo << "    Raiz [label=\"Matriz\", fillcolor=darkgray];\n";

        Cabecera* auxCol = columnaCabeceraRaiz;
        if (auxCol != nullptr) {
            archivo << "    Raiz -> Col_" << auxCol->indice << ";\n";
            while (auxCol != nullptr) {
                archivo << "    Col_" << auxCol->indice << " [label=\"" << auxCol->indice 
                        << "\", fillcolor=lightgray, group=\"" << auxCol->indice << "\"];\n";
                if (auxCol->siguiente != nullptr) {
                    archivo << "    Col_" << auxCol->indice << " -> Col_" << auxCol->siguiente->indice << ";\n";
                }
                auxCol = auxCol->siguiente;
            }
            archivo << "    { rank=same; Raiz; ";
            auxCol = columnaCabeceraRaiz;
            while (auxCol != nullptr) {
                archivo << "Col_" << auxCol->indice << "; ";
                auxCol = auxCol->siguiente;
            }
            archivo << "}\n";
        }

        Cabecera* auxFila = filaCabeceraRaiz;
        if (auxFila != nullptr) {
            archivo << "    Raiz -> Fila_" << auxFila->indice << ";\n";
        }
        
        while (auxFila != nullptr) {
            archivo << "    Fila_" << auxFila->indice << " [label=\"" << auxFila->indice << "\", fillcolor=lightgray];\n";
            if (auxFila->siguiente != nullptr) {
                archivo << "    Fila_" << auxFila->indice << " -> Fila_" << auxFila->siguiente->indice << ";\n";
            }

            NodoMatriz* auxNodo = auxFila->primerNodo;
            if (auxNodo != nullptr) {
                archivo << "    Fila_" << auxFila->indice << " -> Nodo_" << auxNodo->fila << "_" << auxNodo->columna << ";\n";
            }

            while (auxNodo != nullptr) {
                archivo << "    Nodo_" << auxNodo->fila << "_" << auxNodo->columna 
                        << " [label=\"" << auxNodo->color << "\", fillcolor=\"" << auxNodo->color 
                        << "\", group=\"" << auxNodo->columna << "\"];\n";
                
                if (auxNodo->derecha != nullptr) {
                    archivo << "    Nodo_" << auxNodo->fila << "_" << auxNodo->columna << " -> Nodo_" << auxNodo->derecha->fila << "_" << auxNodo->derecha->columna << ";\n";
                }
                auxNodo = auxNodo->derecha;
            }

            archivo << "    { rank=same; Fila_" << auxFila->indice << "; ";
            auxNodo = auxFila->primerNodo;
            while (auxNodo != nullptr) {
                archivo << "Nodo_" << auxNodo->fila << "_" << auxNodo->columna << "; ";
                auxNodo = auxNodo->derecha;
            }
            archivo << "}\n";

            auxFila = auxFila->siguiente;
        }

        auxCol = columnaCabeceraRaiz;
        while (auxCol != nullptr) {
            NodoMatriz* auxNodo = auxCol->primerNodo;
            if (auxNodo != nullptr) {
                archivo << "    Col_" << auxCol->indice << " -> Nodo_" << auxNodo->fila << "_" << auxNodo->columna << ";\n";
                while (auxNodo->abajo != nullptr) {
                    archivo << "    Nodo_" << auxNodo->fila << "_" << auxNodo->columna << " -> Nodo_" << auxNodo->abajo->fila << "_" << auxNodo->abajo->columna << ";\n";
                    auxNodo = auxNodo->abajo;
                }
            }
            auxCol = auxCol->siguiente;
        }

        archivo << "}\n";
        archivo.close();

        string comando = "dot -Tpng capa_" + to_string(idCapa) + ".dot -o capa_" + to_string(idCapa) + ".png";
        system(comando.c_str());

        cout << "¡Exito! Se genero el grafico de la matriz para la Capa " << idCapa << " en la carpeta." << endl;
    }
    void superponer(MatrizDispersa* capaSuperior) {
        if (capaSuperior == nullptr) return;

        Cabecera* auxFila = capaSuperior->filaCabeceraRaiz;
        while (auxFila != nullptr) {
            NodoMatriz* auxNodo = auxFila->primerNodo;
            while (auxNodo != nullptr) {
                insertar(auxNodo->fila, auxNodo->columna, auxNodo->color);
                auxNodo = auxNodo->derecha;
            }
            auxFila = auxFila->siguiente;
        }
    }

    void exportarImagenHTML(string nombreArchivo) {
        int maxFila = 0, maxCol = 0;
        
        Cabecera* auxF = filaCabeceraRaiz;
        while (auxF != nullptr) {
            if (auxF->indice > maxFila) maxFila = auxF->indice;
            auxF = auxF->siguiente;
        }
        
        Cabecera* auxC = columnaCabeceraRaiz;
        while (auxC != nullptr) {
            if (auxC->indice > maxCol) maxCol = auxC->indice;
            auxC = auxC->siguiente;
        }

        ofstream archivo(nombreArchivo + ".dot");
        if (!archivo.is_open()) return;

        archivo << "digraph G {\n";
        archivo << "    node [shape=plaintext];\n";
        archivo << "    matriz [label=<\n";
        archivo << "        <TABLE BORDER=\"0\" CELLBORDER=\"0\" CELLSPACING=\"0\">\n";

        Cabecera* fActual = filaCabeceraRaiz;

        for (int i = 1; i <= maxFila; i++) {
            archivo << "            <TR>\n";
            NodoMatriz* nodoActual = nullptr;
            
            if (fActual != nullptr && fActual->indice == i) {
                nodoActual = fActual->primerNodo;
                fActual = fActual->siguiente;
            }

            for (int j = 1; j <= maxCol; j++) {
                if (nodoActual != nullptr && nodoActual->columna == j) {
                    archivo << "                <TD BGCOLOR=\"" << nodoActual->color << "\" WIDTH=\"20\" HEIGHT=\"20\"></TD>\n";
                    nodoActual = nodoActual->derecha;
                } else {
                    archivo << "                <TD BGCOLOR=\"#000000\" WIDTH=\"20\" HEIGHT=\"20\"></TD>\n"; 
                }
            }
            archivo << "            </TR>\n";
        }

        archivo << "        </TABLE>\n";
        archivo << "    >];\n";
        archivo << "}\n";
        archivo.close();

        string comando = "dot -Tpng " + nombreArchivo + ".dot -o " + nombreArchivo + ".png";
        system(comando.c_str());
        cout << "Imagen generada: " << nombreArchivo << ".png" << endl;
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
    void escribirDotDelArbol(ofstream& archivo) {
        if (root != nullptr) {
            generarDotCapas(root, archivo);
        }
    }
private:
    void preordenLimitado(NodoCapa* nodo, int& contador, int limite, MatrizDispersa* lienzo) {
        if (nodo == nullptr || contador >= limite) return;
        lienzo->superponer(nodo->pixeles);
        contador++;
        preordenLimitado(nodo->left, contador, limite, lienzo);
        preordenLimitado(nodo->right, contador, limite, lienzo);
    }

    void inordenLimitado(NodoCapa* nodo, int& contador, int limite, MatrizDispersa* lienzo) {
        if (nodo == nullptr || contador >= limite) return;
        inordenLimitado(nodo->left, contador, limite, lienzo);
        if (contador < limite) {
            lienzo->superponer(nodo->pixeles);
            contador++;
        }
        inordenLimitado(nodo->right, contador, limite, lienzo);
    }

    void postordenLimitado(NodoCapa* nodo, int& contador, int limite, MatrizDispersa* lienzo) {
        if (nodo == nullptr || contador >= limite) return;
        postordenLimitado(nodo->left, contador, limite, lienzo);
        postordenLimitado(nodo->right, contador, limite, lienzo);
        if (contador < limite) {
            lienzo->superponer(nodo->pixeles);
            contador++;
        }
    }

public:
    void generarPorRecorrido(int tipo, int limite) {
        MatrizDispersa lienzo; 
        int contador = 0;
        string nombre_salida = "recorrido_"; 
        
        if (tipo == 1) {
            preordenLimitado(root, contador, limite, &lienzo);
            nombre_salida += "preorden_" + to_string(limite);
        }
        else if (tipo == 2) {
            inordenLimitado(root, contador, limite, &lienzo);
            nombre_salida += "inorden_" + to_string(limite);
        }
        else if (tipo == 3) {
            postordenLimitado(root, contador, limite, &lienzo);
            nombre_salida += "postorden_" + to_string(limite);
        }
        else {
            cout << "Tipo de recorrido invalido." << endl;
            return;
        }
        
        lienzo.exportarImagenHTML(nombre_salida);
    }
}; 