#pragma once
#include <iostream>
#include <string>
#include <fstream>
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
private:
    void generarDotUsuarios(NodoUsuario* node, ofstream& archivo) {
        if (node == nullptr) return;

        archivo << "    \"" << node->nombreUsuario << "\" [label=\"" << node->nombreUsuario << "\", shape=box, style=filled, fillcolor=lightblue];\n";

        if (node->left != nullptr) {
            archivo << "    \"" << node->nombreUsuario << "\" -> \"" << node->left->nombreUsuario << "\";\n";
            generarDotUsuarios(node->left, archivo);
        }
        
        if (node->right != nullptr) {
            archivo << "    \"" << node->nombreUsuario << "\" -> \"" << node->right->nombreUsuario << "\";\n";
            generarDotUsuarios(node->right, archivo);
        }
    }

public:
    void graficarArbolUsuarios() {
        if (root == nullptr) {
            cout << "El arbol de usuarios esta vacio." << endl;
            return;
        }

        ofstream archivo("arbol_usuarios.dot");
        if (!archivo.is_open()) {
            cout << "Error: No se pudo crear el archivo dot." << endl;
            return;
        }

        archivo << "digraph ArbolUsuarios {\n";
        archivo << "    rankdir=TB;\n"; 

        generarDotUsuarios(root, archivo);

        archivo << "}\n";
        archivo.close();

        system("dot -Tpng arbol_usuarios.dot -o arbol_usuarios.png");
        
        cout << "¡Exito! Se genero la imagen arbol_usuarios.png en la carpeta del proyecto." << endl;
        
        // system("arbol_usuarios.png"); 
    }
private:
    // Función auxiliar recursiva para encontrar el nodo menor (sucesor en inorden)
    NodoUsuario* encontrarMinimo(NodoUsuario* nodo) {
        while (nodo->left != nullptr) nodo = nodo->left;
        return nodo;
    }

    // Función auxiliar recursiva para eliminar un nodo del BST
    NodoUsuario* eliminarNodoUsuario(NodoUsuario* raiz, string nombre, bool& eliminado) {
        if (raiz == nullptr) return raiz;

        if (nombre < raiz->nombreUsuario) {
            raiz->left = eliminarNodoUsuario(raiz->left, nombre, eliminado);
        } else if (nombre > raiz->nombreUsuario) {
            raiz->right = eliminarNodoUsuario(raiz->right, nombre, eliminado);
        } else {
            eliminado = true;
            // Caso 1 y 2: Un hijo o ninguno
            if (raiz->left == nullptr) {
                NodoUsuario* temp = raiz->right;
                delete raiz;
                return temp;
            } else if (raiz->right == nullptr) {
                NodoUsuario* temp = raiz->left;
                delete raiz;
                return temp;
            }
            // Caso 3: Dos hijos, se obtiene el sucesor en inorden
            NodoUsuario* temp = encontrarMinimo(raiz->right);
            raiz->nombreUsuario = temp->nombreUsuario;
            raiz->cabezaImagenes = temp->cabezaImagenes; // Conserva sus imágenes
            raiz->right = eliminarNodoUsuario(raiz->right, temp->nombreUsuario, eliminado);
        }
        return raiz;
    }

public:
    // E-liminar Usuario del BST
    void eliminarUsuario(string nombre) {
        bool eliminado = false;
        root = eliminarNodoUsuario(root, nombre, eliminado);
        if (eliminado) {
            cout << "Usuario \"" << nombre << "\" eliminado exitosamente del sistema." << endl;
        } else {
            cout << "Error: El usuario \"" << nombre << "\" no fue encontrado." << endl;
        }
    }

    // M-odificar Nombre de Usuario
    void modificarUsuario(string nombreViejo, string nombreNuevo) {
        NodoUsuario* user = search(nombreViejo);
        if (user == nullptr) {
            cout << "Error: El usuario \"" << nombreViejo << "\" no existe." << endl;
            return;
        }
        if (search(nombreNuevo) != nullptr) {
            cout << "Error: El nombre \"" << nombreNuevo << "\" ya esta en uso." << endl;
            return;
        }

        // Resguardamos su lista de imágenes asociadas
        NodoImagenUsuario* listaImgsGuardada = user->cabezaImagenes;

        // Lo eliminamos y lo reinstanciamos para que mantenga el orden alfabético correcto del BST
        bool de = false;
        root = eliminarNodoUsuario(root, nombreViejo, de);
        
        insert(nombreNuevo);
        NodoUsuario* nuevoNodo = search(nombreNuevo);
        nuevoNodo->cabezaImagenes = listaImgsGuardada;

        cout << "Usuario actualizado correctamente de \"" << nombreViejo << "\" a \"" << nombreNuevo << "\"." << endl;
    }

    // Eliminar una imagen de la lista enlazada simple de un usuario específico
    void eliminarImagenDeUsuario(string nombreUsuario, int idImagen) {
        NodoUsuario* user = search(nombreUsuario);
        if (user == nullptr) return;

        NodoImagenUsuario* actual = user->cabezaImagenes;
        NodoImagenUsuario* anterior = nullptr;

        while (actual != nullptr) {
            if (actual->idImagen == idImagen) {
                if (anterior == nullptr) {
                    user->cabezaImagenes = actual->siguiente;
                } else {
                    anterior->siguiente = actual->siguiente;
                }
                delete actual;
                cout << "Imagen " << idImagen << " removida de la lista del usuario." << endl;
                return;
            }
            anterior = actual;
            actual = actual->siguiente;
        }
    }
};
