//============================================================================
// Name        : ArbolAVL.cpp
// Author      : DDTeam
// Version     :
// Copyright   : FIUBA  2016
//============================================================================

#include "Nodo.h"
#include "ArbolAVL.h"
#include <iostream>

using namespace std;

ArbolAVL::ArbolAVL() {
	this->raiz = 0;
}

void ArbolAVL::insertar(Registro* unRegistro) {
	raiz = insertarEnNodo(raiz, unRegistro);
}

Nodo* ArbolAVL::crearNuevoNodo(Registro* unRegistro, int alturaPadre) {
	Nodo* unNodo = new Nodo(alturaPadre);
	unNodo->insertar(unRegistro);

	return unNodo;
}

Nodo* ArbolAVL::insertarEnNodo(Nodo* unNodo, Registro* unRegistro)
{

	if (unNodo == 0)
		return(crearNuevoNodo(unRegistro, 0));

	if (unRegistro->id < unNodo->getMenorID()) {
		if (unNodo->getHijoIzquierdo() == NULL) {
			if (!unNodo->insertar(unRegistro)) {
				unNodo->crearHijoIzquierdo(unRegistro);
			}
		} else {
			if (unRegistro->id > (unNodo->getHijoIzquierdo())->getMayorID()) {
				if (!unNodo->insertar(unRegistro)) {
					insertarEnNodo(unNodo->getHijoIzquierdo(), unRegistro);
				}
			} else {
				insertarEnNodo(unNodo->getHijoIzquierdo(), unRegistro);
			}
		}
	} else {
		if (unRegistro->id > unNodo->getMayorID()) {
			if (unNodo->getHijoDerecho() == NULL) {
				if (!unNodo->insertar(unRegistro)) {
					unNodo->crearHijoDerecho(unRegistro);
				}
			} else {
				if (unRegistro->id < unNodo->getHijoDerecho()->getMenorID()) {
					if (!unNodo->insertar(unRegistro)) {
						insertarEnNodo(unNodo->getHijoDerecho(), unRegistro);
					}
				} else {
					insertarEnNodo(unNodo->getHijoDerecho(), unRegistro);
				}
			}
		} else {
			if (!unNodo->insertar(unRegistro)) {
				Registro* tmpRegistro = new Registro();
				Registro* mayorRegistro = unNodo->getRegistroConMayorID();
				//TODO: hacer fn copiarRegistro()
				tmpRegistro->codigo = mayorRegistro->codigo;
				tmpRegistro->id = mayorRegistro->id;
				tmpRegistro->descripcion = mayorRegistro->descripcion;
				tmpRegistro->tamanio = mayorRegistro->tamanio;

				unNodo->borrarRegistro(tmpRegistro->id);
				insertarEnNodo(unNodo->getHijoDerecho(), tmpRegistro);
				insertarEnNodo(unNodo, unRegistro);
			}
		}
	}

	return balancear(unNodo);
}

int ArbolAVL::getDiferenciaAlturaHijos(Nodo* unNodo) {
	Nodo* izq = unNodo->getHijoIzquierdo();
	Nodo* der = unNodo->getHijoDerecho();
	return (izq->getAltura()-der->getAltura());
}

Nodo* ArbolAVL::balancear(Nodo* unNodo) {
	int diferencia = getDiferenciaAlturaHijos(unNodo);

	if (diferencia > 1) {
		return rotacionDerecha(unNodo);
	}
	if (diferencia < -1) {
		return rotacionIzquierda(unNodo);
	}
}

Nodo* ArbolAVL::rotacionDerecha(Nodo *unNodo) {
	Nodo* izq = unNodo->getHijoIzquierdo();
	Nodo* der = izq->getHijoDerecho();

	izq->modificarHijoDerecho(unNodo);
	unNodo->modificarHijoIzquierdo(der);

	//Luego de rotar el hijo izquierdo pasa a ser el nodo central
	izq->modificarAltura(unNodo->getAltura());
	unNodo->modificarAltura((unNodo->getAltura())+1);

	return izq;
}

Nodo* ArbolAVL::rotacionIzquierda(Nodo *unNodo) {
	Nodo *der = unNodo->getHijoDerecho();
	Nodo *izq = der->getHijoIzquierdo();

	der->modificarHijoIzquierdo(unNodo);
	unNodo->modificarHijoDerecho(izq);

	der->modificarAltura(unNodo->getAltura());
	unNodo->modificarAltura((unNodo->getAltura())+1);

	return der;
}

void ArbolAVL::print() {
	preOrder(raiz);
}

void ArbolAVL::preOrder(Nodo* unNodo) {
	Registro unRegistro;

	list<Registro*>* registros = unNodo->getRegistros();
	if(unNodo != 0) {
		preOrder(unNodo->getHijoIzquierdo());
		preOrder(unNodo->getHijoDerecho());

		cout<<"| ";
/* No se que problema me tira el iterador
		for(iterator list_iter = registros->begin(); list_iter != registros->end(); list_iter++) {
			unRegistro = list_iter;

			if (unNodo->getAltura() == 1) {
				//Como es hoja, podria imprimir todo los datos del reg
				cout<<unRegistro.id<<endl;
			} else {
				cout<<unRegistro.id<<endl;
			}
		}
		cout<<"|";
*/	}
}

ArbolAVL::~ArbolAVL() {
	// TODO Auto-generated destructor stub
}
