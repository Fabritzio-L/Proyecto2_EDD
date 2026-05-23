#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "capas.cpp" 

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
            try {
                idCapaActual = stoi(linea);
                arbolCapas.insert(idCapaActual);
            } catch (...) {
                cout << "Linea ignorada (No es ID valido): " << linea << endl;
            }
        }
    }

    archivo.close(); 
    cout << "--- CARGA DE CAPAS FINALIZADA EXITOSAMENTE ---" << endl;
}

