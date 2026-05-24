#pragma once
#include <iostream>
#include <fstream>
#include "capas.cpp" 
using namespace std;


struct NodoCapaImagen {
    NodoCapa* capaPuntero; 
    NodoCapaImagen* siguiente;

    NodoCapaImagen(NodoCapa* capaRef){
    capaPuntero = capaRef;
    siguiente = nullptr;
    }
};


struct NodoImagen {
    int idImagen;
    NodoCapaImagen* cabezaCapas; 
    
    NodoImagen* siguiente;
    NodoImagen* anterior;

    NodoImagen(int id){
    idImagen = id;
    cabezaCapas = nullptr;
    siguiente = nullptr;
    anterior = nullptr;
    }
};

class ListaCircularImagenes {
private:
    NodoImagen* cabeza;

public:
    ListaCircularImagenes() {
        cabeza = nullptr;
    }

    void insertarImagen(int id) {
        NodoImagen* nuevo = new NodoImagen(id);

        if (cabeza == nullptr) {
            cabeza = nuevo;
            cabeza->siguiente = cabeza;
            cabeza->anterior = cabeza;
            cout << "Imagen " << id << " insertada como cabeza." << endl;
            return;
        }

        // Buscar si existe para evitar duplicados 
        NodoImagen* aux = cabeza;
        do {
            if (aux->idImagen == id) {
                cout << "Error: La imagen " << id << " ya existe." << endl;
                return;
            }
            aux = aux->siguiente;
        } while (aux != cabeza);

        // Insercion 
        aux = cabeza;
        
        if (id < cabeza->idImagen) {
            NodoImagen* ultimo = cabeza->anterior;
            
            nuevo->siguiente = cabeza;
            nuevo->anterior = ultimo;
            cabeza->anterior = nuevo;
            ultimo->siguiente = nuevo;
            
            cabeza = nuevo; 
        } 
        else {
            while (aux->siguiente != cabeza && aux->siguiente->idImagen < id) {
                aux = aux->siguiente;
            }
            
            nuevo->siguiente = aux->siguiente;
            nuevo->anterior = aux;
            aux->siguiente->anterior = nuevo;
            aux->siguiente = nuevo;
        }
        cout << "Imagen " << id << " insertada en la lista circular." << endl;
    }

    NodoImagen* buscarImagen(int id) {
        if (cabeza == nullptr) return nullptr;

        NodoImagen* aux = cabeza;
        do {
            if (aux->idImagen == id) {
                return aux;
            }
            aux = aux->siguiente;
        } while (aux != cabeza);

        return nullptr;
    }

    void agregarCapaAImagen(int idImagen, NodoCapa* capaRef) {
        if (capaRef == nullptr) {
             cout << "Error: La capa referenciada no existe en el BST." << endl;
             return;
        }

        NodoImagen* img = buscarImagen(idImagen);
        if (img == nullptr) {
            cout << "Error: La imagen " << idImagen << " no existe." << endl;
            return;
        }

        NodoCapaImagen* nuevaCapa = new NodoCapaImagen(capaRef);

        if (img->cabezaCapas == nullptr) {
            img->cabezaCapas = nuevaCapa;
        } else {
            NodoCapaImagen* aux = img->cabezaCapas;
            while (aux->siguiente != nullptr) {
                aux = aux->siguiente;
            }
            aux->siguiente = nuevaCapa;
        }
        cout << "Capa " << capaRef->idCapa << " agregada a la imagen " << idImagen << "." << endl;
    }

    void mostrarImagenes() {
        if (cabeza == nullptr) {
            cout << "Lista de imagenes vacia." << endl;
            return;
        }

        NodoImagen* aux = cabeza;
        cout << "\n--- LISTA CIRCULAR DE IMAGENES ---" << endl;
        do {
            cout << "Imagen ID: " << aux->idImagen << " | Capas: ";
            
            NodoCapaImagen* auxCapa = aux->cabezaCapas;
            if (auxCapa == nullptr) {
                cout << "Ninguna";
            }
            while (auxCapa != nullptr) {
                cout << "[" << auxCapa->capaPuntero->idCapa << "] ";
                auxCapa = auxCapa->siguiente;
            }
            cout << endl;

            aux = aux->siguiente;
        } while (aux != cabeza);
        cout << "----------------------------------\n" << endl;
    }
    void graficarListaImagenes() {
        if (cabeza == nullptr) {
            cout << "La lista de imagenes esta vacia." << endl;
            return;
        }

        ofstream archivo("lista_imagenes.dot");
        if (!archivo.is_open()) {
            cout << "Error: No se pudo crear el archivo dot para imagenes." << endl;
            return;
        }

        archivo << "digraph ListaImagenes {\n";
        archivo << "    rankdir=LR;\n"; // Left to Right (De izquierda a derecha)
        archivo << "    node [shape=record, style=filled, fillcolor=lightyellow];\n\n";

        archivo << "    { rank=same;\n";
        NodoImagen* aux = cabeza;
        do {
            archivo << "        \"Img_" << aux->idImagen << "\" [label=\"{ <ant> | Imagen " << aux->idImagen << " | <sig> }\"];\n";
            aux = aux->siguiente;
        } while (aux != cabeza);
        archivo << "    }\n\n";

        aux = cabeza;
        do {
            archivo << "    \"Img_" << aux->idImagen << "\":sig -> \"Img_" << aux->siguiente->idImagen << "\":ant;\n";
            
            archivo << "    \"Img_" << aux->idImagen << "\":ant -> \"Img_" << aux->anterior->idImagen << "\":sig;\n";
            
            aux = aux->siguiente;
        } while (aux != cabeza);

        aux = cabeza;
        do {
            NodoCapaImagen* auxCapa = aux->cabezaCapas;
            if (auxCapa != nullptr) {
                archivo << "    \"CapaImg_" << aux->idImagen << "_" << auxCapa->capaPuntero->idCapa 
                        << "\" [label=\"Capa " << auxCapa->capaPuntero->idCapa << "\", shape=box, fillcolor=lightgrey];\n";
                archivo << "    \"Img_" << aux->idImagen << "\" -> \"CapaImg_" << aux->idImagen << "_" << auxCapa->capaPuntero->idCapa << "\";\n";

                while (auxCapa->siguiente != nullptr) {
                    archivo << "    \"CapaImg_" << aux->idImagen << "_" << auxCapa->siguiente->capaPuntero->idCapa 
                            << "\" [label=\"Capa " << auxCapa->siguiente->capaPuntero->idCapa << "\", shape=box, fillcolor=lightgrey];\n";
                    archivo << "    \"CapaImg_" << aux->idImagen << "_" << auxCapa->capaPuntero->idCapa 
                            << "\" -> \"CapaImg_" << aux->idImagen << "_" << auxCapa->siguiente->capaPuntero->idCapa << "\";\n";
                    
                    auxCapa = auxCapa->siguiente;
                }
            }
            aux = aux->siguiente;
        } while (aux != cabeza);

        archivo << "}\n";
        archivo.close();

        system("dot -Tpng lista_imagenes.dot -o lista_imagenes.png");
        
        cout << "¡Exito! Se genero la imagen lista_imagenes.png en la carpeta del proyecto." << endl;
    }
    void graficarImagenYArbol(int idImagen, BSTCapas& arbolCapas) {
        NodoImagen* img = buscarImagen(idImagen);
        if (img == nullptr) {
            cout << "Error: La imagen " << idImagen << " no existe." << endl;
            return;
        }

        ofstream archivo("imagen_arbol_" + to_string(idImagen) + ".dot");
        if (!archivo.is_open()) {
            cout << "Error al crear el archivo dot." << endl;
            return;
        }

        archivo << "digraph ImagenArbol {\n";
        archivo << "    rankdir=TB;\n";

        archivo << "    \"Imagen_" << img->idImagen << "\" [label=\"Imagen " << img->idImagen << "\", shape=box, color=red, fontcolor=red];\n";

        NodoCapaImagen* aux = img->cabezaCapas;
        if (aux != nullptr) {
            archivo << "    \"Imagen_" << img->idImagen << "\" -> \"CapaList_" << aux->capaPuntero->idCapa << "\" [color=red];\n";
            
            while (aux != nullptr) {
                archivo << "    \"CapaList_" << aux->capaPuntero->idCapa << "\" [label=\"capa_" << aux->capaPuntero->idCapa << "\", shape=box, style=rounded, color=red, fontcolor=red];\n";
                
                if (aux->siguiente != nullptr) {
                    archivo << "    \"CapaList_" << aux->capaPuntero->idCapa << "\" -> \"CapaList_" << aux->siguiente->capaPuntero->idCapa << "\" [color=red];\n";
                }

                archivo << "    \"CapaList_" << aux->capaPuntero->idCapa << "\" -> \"Capa_" << aux->capaPuntero->idCapa << "\" [color=red, constraint=false];\n";
                
                aux = aux->siguiente;
            }
        }

        arbolCapas.escribirDotDelArbol(archivo);

        archivo << "}\n";
        archivo.close();

        string comando = "dot -Tpng imagen_arbol_" + to_string(idImagen) + ".dot -o imagen_arbol_" + to_string(idImagen) + ".png";
        system(comando.c_str());

        cout << "¡Exito! Se genero el grafico combinado para la Imagen " << idImagen << "." << endl;
    }
};