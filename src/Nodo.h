/*
 * Nodo.h
 *
 *  Created on: 26 de may. de 2016
 *      Author: desuque
 */

#ifndef NODO_H_
#define NODO_H_
#include <list>
#include "Registro.h"

using namespace std;

class Nodo {
private:
	Nodo* izquierdo;
	Nodo* derecho;
	int cantidadDeElementos;
	int bytes_libres;
	list<Registro*>* registros;
	int altura;

public:
	Nodo();

	int maxPorNodo = 3; //TODO: en bytes
	int minPorNodo = 2; //TODO: en bytes

	int getMenorID();
	int getMayorID();
	Nodo* getHijoIzquierdo();
	Nodo* getHijoDerecho();
	Registro* getRegistroConMayorID();
	Registro* getRegistroConMenorID();
	int getAltura();
	list<Registro*>* getRegistros();
	bool estaEnUnderflow();

	bool insertar(Registro* unRegistro);

	void modificarHijoIzquierdo(Nodo* nuevoNodo);
	void modificarHijoDerecho(Nodo* nuevoNodo);
	void modificarAltura(int nuevaAltura);
	bool borrarRegistro(int ID);
	bool existeRegistroConID(int idBuscado);
	int getCantidadDeRegistros();

	virtual ~Nodo();

};

#endif /* NODO_H_ */
