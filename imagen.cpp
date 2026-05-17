#include <iostream>
#include "Capas.cpp" 
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