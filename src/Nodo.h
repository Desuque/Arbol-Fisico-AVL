/*
 * Nodo.h
 *
 *  Created on: 26 de may. de 2016
 *      Author: desuque
 */

#ifndef NODO_H_
#define NODO_H_
#include <list>

using namespace std;

class Nodo {
private:
	Nodo* izquierdo;
	Nodo* derecho;
	int cantidadDeElementos;
	int bytes_libres;
	list<Registro*> registros;
	int maxElementos = 3;

public:
	Nodo();

	int getMenorID();
	int getMayorID();
	Nodo* getHijoIzquierdo();
	Nodo* getHijoDerecho();
	Registro* getRegistroConMayorID();
	int insertar(Registro* unRegistro);

	void crearHijoIzquierdo(Registro* unRegistro);
	void crearHijoDerecho(Registro* unRegistro);

	void borrarRegistro(int ID);

	virtual ~Nodo();
};

#endif /* NODO_H_ */
