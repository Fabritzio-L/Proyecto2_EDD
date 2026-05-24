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
    //arbolUsuarios.graficarArbolUsuarios();
   // arbolCapas.graficarArbolCapas();
  //  listaImagenes.graficarListaImagenes();
    
    cout << "\n--- GENERANDO REPORTE DE CAPA (MATRIZ DISPERSA) ---" << endl;
    
    NodoCapa* capaAGraficar = arbolCapas.search(101);
    
    if (capaAGraficar != nullptr) {
        capaAGraficar->pixeles->graficarCapa(101);
    } else {
        cout << "La capa 101 no existe en el sistema." << endl;
    }
    cout << "\n--- GENERANDO REPORTE COMBINADO ---" << endl;
    listaImagenes.graficarImagenYArbol(100, arbolCapas);
    return 0;
}