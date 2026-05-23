#include <iostream>
#include "usuarios.cpp"
#include "cargas.cpp"

int main() {
    BSTCapas arbolCapas; 
    ListaCircularImagenes listaImagenes;

    cargarArchivoCapas("C:\\Users\\fabri\\Desktop\\Proyecto2_EDD\\prueba.cap", arbolCapas);
    
    
    listaImagenes.mostrarImagenes();

    
    return 0;
}