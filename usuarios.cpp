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

