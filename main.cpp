#include <iostream>
#include "usuarios.cpp"
#include "cargas.cpp"

int main() {
    BSTCapas arbolCapas; 
    ListaCircularImagenes listaImagenes;

    cargarArchivoCapas("C:\\Users\\fabri\\Desktop\\Proyecto2_EDD\\prueba.cap", arbolCapas);
    
    cargarArchivoImagenes("C:\\Users\\fabri\\Desktop\\Proyecto2_EDD\\prueba.im", listaImagenes, arbolCapas);

    
    listaImagenes.mostrarImagenes();

    
    return 0;
}