#include <iostream>
#include "usuarios.cpp"
#include "cargas.cpp"

int main() {
    BSTCapas arbolCapas; 
    ListaCircularImagenes listaImagenes;

    cargarArchivoCapas("C:\\Users\\fabri\\Desktop\\Proyecto2_EDD\\prueba.cap", arbolCapas);
    
    cargarArchivoImagenes("C:\\Users\\fabri\\Desktop\\Proyecto2_EDD\\prueba.im", listaImagenes, arbolCapas);

    BSTUsuarios arbolUsuarios;
    cargarArchivoUsuarios("C:\\Users\\fabri\\Desktop\\Proyecto2_EDD\\prueba.usr", arbolUsuarios);

    listaImagenes.mostrarImagenes();

    cout << "\n--- GENERANDO REPORTES VISUALES ---" << endl;
    arbolUsuarios.graficarArbolUsuarios();
    arbolCapas.graficarArbolCapas();
    listaImagenes.graficarListaImagenes();

    
    return 0;
}