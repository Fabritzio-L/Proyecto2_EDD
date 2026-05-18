#include <iostream>
#include <string>
#include "imagen.cpp" 

using namespace std;

struct NodoImagenUsuario {
    int idImagen;
    NodoImagenUsuario* siguiente;

    NodoImagenUsuario(int id) {
        idImagen = id;
        siguiente = nullptr;
    }
};


class NodoUsuario {
public:
    string nombreUsuario;
    NodoImagenUsuario* cabezaImagenes; 
    
    NodoUsuario* left;
    NodoUsuario* right;

    NodoUsuario(string nombre) {
        nombreUsuario = nombre;
        cabezaImagenes = nullptr;
        left = right = nullptr;
    }
};

class BSTUsuarios {
private:
    NodoUsuario* root;

    NodoUsuario* insert(NodoUsuario* node, string nombre) {
        if (node == nullptr) {
            return new NodoUsuario(nombre);
        }

        if (nombre < node->nombreUsuario) {
            node->left = insert(node->left, nombre);
        }
        else if (nombre > node->nombreUsuario) {
            node->right = insert(node->right, nombre);
        }
        return node;
    }

    NodoUsuario* search(NodoUsuario* node, string nombre) {
        if (node == nullptr || node->nombreUsuario == nombre) {
            return node;
        }

        if (nombre < node->nombreUsuario) {
            return search(node->left, nombre);
        }
        return search(node->right, nombre);
    }

    // Raiz, izquierda, derecha
    void preorden(NodoUsuario* node) {
        if (node == nullptr) 
            return; 

        cout << "Nombre de usuario: " << node->nombreUsuario << endl;

        preorden(node->left);
        preorden(node->right);
    }

    // Izquierda, raiz, derecha
    void inorden(NodoUsuario* node) {
        if (node == nullptr) return;

        inorden(node->left);

        cout << "Nombre de usuario: " << node->nombreUsuario << endl;

        inorden(node->right);
    }

    // Izquierda, derecha, raiz
    void postorden(NodoUsuario* node) {
        if (node == nullptr) return;

        postorden(node->left);  
        postorden(node->right); 

        cout << "Nombre de usuario: " << node->nombreUsuario << endl;
    }

public:
    BSTUsuarios() {
        root = nullptr;
    }

    void insert(string nombre) {
        root = insert(root, nombre);
    }

    NodoUsuario* search(string nombre) {
        return search(root, nombre);
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

    void asociarImagen(string nombre, int idImagen) {
        NodoUsuario* user = search(nombre);
        if (user == nullptr) {
            cout << "Error: El usuario no existe." << endl;
            return;
        }

        NodoImagenUsuario* nuevoNodo = new NodoImagenUsuario(idImagen);

        if (user->cabezaImagenes == nullptr) {
            user->cabezaImagenes = nuevoNodo;
        } else {
            NodoImagenUsuario* aux = user->cabezaImagenes;
            while (aux->siguiente != nullptr) {
                aux = aux->siguiente;
            }
            aux->siguiente = nuevoNodo;
        }
    }
};