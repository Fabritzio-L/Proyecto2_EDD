#pragma once
#include <iostream>
#include <string>
#include "usuarios.cpp"
#include "cargas.cpp"

using namespace std;

void menuReportes(BSTCapas& arbolCapas, ListaCircularImagenes& listaImagenes, BSTUsuarios& arbolUsuarios) {
    int opc = 0;
    do {
        cout << "\n--- ESTADO DE LA MEMORIA (REPORTES) ---" << endl;
        cout << "1. Ver lista de imagenes" << endl;
        cout << "2. Ver arbol de capas" << endl;
        cout << "3. Ver capa especifica" << endl;
        cout << "4. Ver imagen y arbol de capas" << endl;
        cout << "5. Ver arbol de usuarios" << endl;
        cout << "6. Regresar al menu principal" << endl;
        cout << "Elige una opcion: ";
        cin >> opc;

        switch(opc) {
            case 1: {
                listaImagenes.graficarListaImagenes();
                break;
            }
            case 2: {
                arbolCapas.graficarArbolCapas();
                break;
            }
            case 3: {
                int idCapa;
                cout << "Ingrese el ID de la capa a graficar: ";
                cin >> idCapa;
                NodoCapa* capa = arbolCapas.search(idCapa);
                if (capa != nullptr) {
                    capa->pixeles->graficarCapa(idCapa);
                } else {
                    cout << "Error: La capa " << idCapa << " no existe en el arbol." << endl;
                }
                break;
            }
            case 4: {
                int idImg;
                cout << "Ingrese el ID de la imagen: ";
                cin >> idImg;
                listaImagenes.graficarImagenYArbol(idImg, arbolCapas);
                break;
            }
            case 5: {                
                arbolUsuarios.graficarArbolUsuarios();
                break;
            }
            case 6: {
                break;
            }
            default:
                cout << "Opcion invalida." << endl;
        }
    } while (opc != 6);
}


void menuCRUD(BSTCapas& arbolCapas, ListaCircularImagenes& listaImagenes, BSTUsuarios& arbolUsuarios) {
    int opc = 0;
    do {
        cout << "\n--- CRUD ---" << endl;
        cout << "   -- GESTION DE USUARIOS --" << endl;
        cout << "1. Agregar nuevo Usuario" << endl;
        cout << "2. Modificar nombre de Usuario" << endl;
        cout << "3. Eliminar Usuario" << endl;
        cout << "4. Asignar imagen a un Usuario" << endl;
        cout << "5. Quitar imagen a un Usuario" << endl;
        cout << "   -- ABC DE IMAGENES GLOBALES --" << endl;
        cout << "6. Agregar nueva Imagen" << endl;
        cout << "7. Eliminar Imagen" << endl;
        cout << "8. Regresar al menu principal" << endl;
        cout << "Elige una opcion: ";
        cin >> opc;

        switch(opc) {
            case 1: {
                string nuevoUsr;
                cout << "Ingrese el nombre del nuevo usuario: ";
                cin >> nuevoUsr;
                if (arbolUsuarios.search(nuevoUsr) == nullptr) {
                    arbolUsuarios.insert(nuevoUsr);
                    cout << "Usuario creado exitosamente." << endl;
                } else {
                    cout << "Error: El usuario ya existe." << endl;
                }
                break;
            }
            case 2: {
                string vNombre, nNombre;
                cout << "Nombre del usuario a modificar: ";
                cin >> vNombre;
                cout << "Ingrese el nuevo nombre: ";
                cin >> nNombre;
                arbolUsuarios.modificarUsuario(vNombre, nNombre);
                break;
            }
            case 3: {
                string usrEliminar;
                cout << "Nombre del usuario a eliminar: ";
                cin >> usrEliminar;
                arbolUsuarios.eliminarUsuario(usrEliminar);
                break;
            }
            case 4: {
                string nombreUsr;
                int idImg;
                cout << "Ingrese el nombre del usuario: ";
                cin >> nombreUsr;
                
                NodoUsuario* user = arbolUsuarios.search(nombreUsr);
                if (user == nullptr) {
                    cout << "Error: El usuario no existe en el sistema." << endl;
                    break;
                }
                
                cout << "Ingrese el ID de la imagen a asignarle: ";
                cin >> idImg;
                
                if (listaImagenes.existeImagen(idImg)) {
                    arbolUsuarios.asociarImagen(nombreUsr, idImg);
                    cout << "Imagen " << idImg << " enlazada correctamente al usuario." << endl;
                } else {
                    cout << "Error: La imagen " << idImg << " no existe en el catalogo global. Primero debe crearla en la Opcion 6." << endl;
                }
                break;
            }
            case 5: {
                string nombreUsr;
                int idImgEliminar;
                cout << "Ingrese el nombre del usuario: ";
                cin >> nombreUsr;
                cout << "Ingrese el ID de la imagen a quitarle: ";
                cin >> idImgEliminar;
                
                arbolUsuarios.eliminarImagenDeUsuario(nombreUsr, idImgEliminar);
                break;
            }
            case 6: { 
                int idNuevaImg;
                cout << "\n--- AGREGAR IMAGEN GLOBAL ---" << endl;
                cout << "Ingrese el ID de la nueva imagen: ";
                cin >> idNuevaImg;
                
                if (listaImagenes.existeImagen(idNuevaImg)) {
                    cout << "Error: El ID de imagen ya existe en el sistema." << endl;
                } else {
                    listaImagenes.insertarImagen(idNuevaImg);
                    cout << "Imagen " << idNuevaImg << " agregada al catalogo global." << endl;
                    
                    char resp;
                    do {
                        cout << " Desea agregarle una capa a esta imagen? (S/N): ";
                        cin >> resp;
                        if (resp == 'S' || resp == 's') {
                            int idCapa;
                            cout << "Ingrese el ID de la capa: ";
                            cin >> idCapa;
                            NodoCapa* cp = arbolCapas.search(idCapa);
                            if (cp != nullptr) {
                                listaImagenes.agregarCapaAImagen(idNuevaImg, cp);
                            } else {
                                cout << "Error: La capa " << idCapa << " no existe en el arbol de capas." << endl;
                            }
                        }
                    } while (resp == 'S' || resp == 's');
                }
                break;
            }
            case 7: { 
                int idImgEliminar;
                cout << "\n--- ELIMINAR IMAGEN GLOBAL ---" << endl;
                cout << "Ingrese el ID de la imagen a eliminar: ";
                cin >> idImgEliminar;
                
                if (listaImagenes.eliminarImagenGlobal(idImgEliminar)) {
                    cout << " Imagen " << idImgEliminar << " eliminada completamente de la memoria global!" << endl;
                } else {
                    cout << "Error: La imagen " << idImgEliminar << " no existe en el catalogo global." << endl;
                }
                break;
            }
            case 8:
                break;
            default:
                cout << "Opcion invalida." << endl;
        }
    } while (opc != 8);
}

int main() {
    BSTCapas arbolCapas; 
    ListaCircularImagenes listaImagenes;
    BSTUsuarios arbolUsuarios; 

    int opcion = 0;
    do {
        cout << "\n SISTEMA GENERADOR DE IMAGENES " << endl;
        cout << "1. Carga Masiva de Archivos" << endl;
        cout << "2. Generacion de Imagenes" << endl;
        cout << "3. Reportes (Estado de la Memoria)" << endl;
        cout << "4. CRUD " << endl;
        cout << "5. Salir" << endl;
        cout << "Elige una opcion: ";
        cin >> opcion;

        switch(opcion) {
            case 1: {
                cout << "\n--- INICIANDO CARGA MASIVA AUTOMATICA ---" << endl;
                
                cargarArchivoCapas("../capas.cap", arbolCapas);
                cargarArchivoImagenes("../imagenes.im", listaImagenes, arbolCapas);
                cargarArchivoUsuarios("../prueba.usr", arbolUsuarios);
                
                cout << "--- CARGA AUTOMATICA COMPLETADA ---" << endl;
                break;
            }
            case 2: {
                cout << "\n--- GENERACION DE IMAGENES ---" << endl;
                cout << "1. Por recorrido limitado" << endl;
                cout << "2. Por lista de imagenes" << endl;
                cout << "Seleccione: ";
                int opcGen;
                cin >> opcGen;
                
                if (opcGen == 1) {
                    int tipoRecorrido, limite;
                    cout << "\n--- POR RECORRIDO LIMITADO ---" << endl;
                    cout << "Tipo (1. Preorden, 2. Inorden, 3. Postorden): ";
                    cin >> tipoRecorrido;
                    cout << "Cantidad de capas a procesar: ";
                    cin >> limite;
                    arbolCapas.generarPorRecorrido(tipoRecorrido, limite);
                } 
                else if (opcGen == 2) {
                    cout << "\n--- POR LISTA DE IMAGENES ---" << endl;
                    cout << "1. Buscar por ID de imagen general" << endl;
                    cout << "2. Buscar por Usuario" << endl;
                    cout << "Seleccione: ";
                    int opcLista;
                    cin >> opcLista;

                    if (opcLista == 1) {
                        int idImg;
                        cout << "Ingrese el ID de la imagen a generar: ";
                        cin >> idImg;
                        listaImagenes.generarImagenFinal(idImg);
                    }
                    else if (opcLista == 2) {
                        string nombreBuscar;
                        cout << "Ingrese el nombre de usuario: ";
                        cin >> nombreBuscar;

                        NodoUsuario* usuarioNodo = arbolUsuarios.search(nombreBuscar);

                        if (usuarioNodo == nullptr) {
                            cout << "Error: El usuario \"" << nombreBuscar << "\" no existe en el sistema." << endl;
                        } 
                        else {
                            cout << "\nImagenes asignadas a " << nombreBuscar << ":" << endl;
                            NodoImagenUsuario* auxImg = usuarioNodo->cabezaImagenes;
                            
                            if (auxImg == nullptr) {
                                cout << "Este usuario no tiene ninguna imagen asociada." << endl;
                            } 
                            else {
                                while (auxImg != nullptr) {
                                    cout << "- Imagen ID: " << auxImg->idImagen << endl;
                                    auxImg = auxImg->siguiente;
                                }

                                int idElegido;
                                cout << "Ingrese el ID de la imagen que desea generar: ";
                                cin >> idElegido;

                                bool tienePermiso = false;
                                auxImg = usuarioNodo->cabezaImagenes;
                                while (auxImg != nullptr) {
                                    if (auxImg->idImagen == idElegido) {
                                        tienePermiso = true;
                                        break;
                                    }
                                    auxImg = auxImg->siguiente;
                                }

                                if (tienePermiso) {
                                    listaImagenes.generarImagenFinal(idElegido);
                                } else {
                                    cout << "Error: La imagen " << idElegido << " no pertenece a este usuario." << endl;
                                }
                            }
                        }
                    } else {
                        cout << "Opcion invalida." << endl;
                    }
                }
                break;
            }
            case 3:
                menuReportes(arbolCapas, listaImagenes, arbolUsuarios);
                break;
            case 4:
                menuCRUD(arbolCapas, listaImagenes, arbolUsuarios);
                break;
            case 5:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opcion invalida." << endl;
        }
    } while (opcion != 5);

    return 0;
}