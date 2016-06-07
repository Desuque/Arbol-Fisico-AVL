/*
 * Nodo.h
 *
 *  Created on: 26 de may. de 2016
 *      Author: desuque
 */

#ifndef ARCHIVOLIBRES_H_
#define ARCHIVOLIBRES_H_

#include <fstream>

using namespace std;

class ArchivoLibres {

private:
	string nombre;

public:
	ArchivoLibres(string nombre);
	void grabar(int clave, int espacio);
	int buscarEspacioLibre(int espacio);
	~ArchivoLibres();
};

#endif /* ARCHIVOLIBRES_H */
