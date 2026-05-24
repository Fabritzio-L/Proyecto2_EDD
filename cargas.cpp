#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "usuarios.cpp" 

using namespace std;

void cargarArchivoCapas(string ruta, BSTCapas& arbolCapas) {
    ifstream archivo(ruta);
    if (!archivo.is_open()) {
        cout << "Error: No se pudo abrir el archivo " << ruta << endl;
        return;
    }

    string linea;
    int idCapaActual = -1; 

    cout << "--- INICIANDO CARGA MASIVA DE CAPAS ---" << endl;

    while (getline(archivo, linea)) {
        if (linea.empty()) continue;

        if (linea.find(',') != string::npos) {
            
            stringstream ss(linea);
            string token;
            
            int fila, columna;
            string color;

            try {
                getline(ss, token, ',');
                fila = stoi(token);

                getline(ss, token, ',');
                columna = stoi(token);

                getline(ss, token, ';');
                color = token;

                if (!color.empty() && color[0] == ' ') {
                    color.erase(0, 1);
                }

                if (idCapaActual != -1) {
                    NodoCapa* capaDestino = arbolCapas.search(idCapaActual);
                    if (capaDestino != nullptr) {
                        capaDestino->pixeles->insertar(fila, columna, color);
                    }
                }
            } catch (...) {
                cout << "Error de formato al leer el pixel: " << linea << endl;
            }

        } 
        else {
            string posibleID = "";
            
            for (char c : linea) {
                if (isdigit(c)) {
                    posibleID += c;
                }
            }
            
            if (!posibleID.empty()) {
                idCapaActual = stoi(posibleID);
                arbolCapas.insert(idCapaActual);
            }
        }
    }

    archivo.close();
    cout << "--- CARGA DE CAPAS FINALIZADA EXITOSAMENTE ---" << endl;
}


void cargarArchivoImagenes(string ruta, ListaCircularImagenes& listaImg, BSTCapas& arbolCapas) {
    ifstream archivo(ruta);
    if (!archivo.is_open()) {
        cout << "Error: No se pudo abrir el archivo de imagenes: " << ruta << endl;
        return;
    }

    string linea;
    cout << "\n--- INICIANDO CARGA MASIVA DE IMAGENES ---" << endl;

    while (getline(archivo, linea)) {
        if (linea.empty()) continue;

        size_t posLlaveAbre = linea.find('{');
        size_t posLlaveCierra = linea.find('}');

        if (posLlaveAbre != string::npos && posLlaveCierra != string::npos) {
            try {
                string strId = linea.substr(0, posLlaveAbre);
                int idImagen = stoi(strId);

                listaImg.insertarImagen(idImagen);

                string strCapas = linea.substr(posLlaveAbre + 1, posLlaveCierra - posLlaveAbre - 1);
                
                if (!strCapas.empty()) {
                    stringstream ss(strCapas);
                    string tokenCapa;
                    
                    while (getline(ss, tokenCapa, ',')) {
                        int idCapa = stoi(tokenCapa);
                        
                        NodoCapa* capaRef = arbolCapas.search(idCapa);
                        if (capaRef != nullptr) {
                            listaImg.agregarCapaAImagen(idImagen, capaRef);
                        } else {
                            cout << "Advertencia: Capa " << idCapa << " no encontrada en el BST." << endl;
                        }
                    }
                } else {
                     cout << "Nota: La imagen " << idImagen << " no tiene capas asociadas." << endl;
                }
            } catch (...) {
                cout << "Error al procesar el formato de la linea: " << linea << endl;
            }
        }
    }
    
    archivo.close();
    cout << "--- CARGA DE IMAGENES FINALIZADA EXITOSAMENTE ---\n" << endl;
}
void cargarArchivoUsuarios(string ruta, BSTUsuarios& arbolUsuarios) {
    ifstream archivo(ruta);
    if (!archivo.is_open()) {
        cout << "Error: No se pudo abrir el archivo de usuarios: " << ruta << endl;
        return;
    }

    string linea;
    cout << "\n--- INICIANDO CARGA MASIVA DE USUARIOS ---" << endl;

    while (getline(archivo, linea)) {
        if (linea.empty()) continue;

        size_t posDosPuntos = linea.find(':');
        size_t posPuntoComa = linea.find(';');

        if (posDosPuntos != string::npos && posPuntoComa != string::npos) {
            try {
                string nombre = linea.substr(0, posDosPuntos);
                
                arbolUsuarios.insert(nombre);

                string strImagenes = linea.substr(posDosPuntos + 1, posPuntoComa - posDosPuntos - 1);
                
                if (!strImagenes.empty()) {
                    stringstream ss(strImagenes);
                    string tokenImg;
                    
                    while (getline(ss, tokenImg, ',')) {
                        int idImagen = stoi(tokenImg);
                        arbolUsuarios.asociarImagen(nombre, idImagen);
                    }
                } else {
                     cout << "Nota: El usuario \"" << nombre << "\" no tiene imagenes asociadas." << endl;
                }
            } catch (...) {
                cout << "Error al procesar el formato de la linea: " << linea << endl;
            }
        }
    }
    
    archivo.close();
    cout << "--- CARGA DE USUARIOS FINALIZADA EXITOSAMENTE ---\n" << endl;
}
