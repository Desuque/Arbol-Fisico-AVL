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

void ArbolAVL::insertar(Registro* unRegistro){
	raiz = insertarEnNodo(raiz, unRegistro);
}

Nodo* ArbolAVL::crearNodo(Registro* unRegistro) {
	Nodo* unNodo = new Nodo();
	unNodo->insertar(unRegistro);

	return unNodo;
}

int calcMax(int x, int y)
{
	return (x > y)? x : y;
}
Nodo* ArbolAVL::insertarEnNodo(Nodo* unNodo, Registro* unRegistro) {

	if (unNodo == 0) {
		return crearNodo(unRegistro);
	} else {
		if (unRegistro->id < unNodo->getMenorID()) {
			if (unNodo->getHijoIzquierdo() == 0) {
				if (!unNodo->insertar(unRegistro)) {
					unNodo->modificarHijoIzquierdo(insertarEnNodo(unNodo->getHijoIzquierdo(), unRegistro));
					//unNodo->crearHijoIzquierdo(unRegistro);
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
				if (unNodo->getHijoDerecho() == 0) {
					if (!unNodo->insertar(unRegistro)) {
						unNodo->modificarHijoDerecho(insertarEnNodo(unNodo->getHijoDerecho(), unRegistro));
						//unNodo->crearHijoDerecho(unRegistro);
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

					tmpRegistro->codigo = mayorRegistro->codigo;
					tmpRegistro->id = mayorRegistro->id;
					tmpRegistro->descripcion = mayorRegistro->descripcion;
					tmpRegistro->tamanio = mayorRegistro->tamanio;

					unNodo->borrarRegistro(tmpRegistro->id);
					/*
					if (unNodo->getHijoDerecho() == 0) {
						unNodo->crearHijoDerecho(tmpRegistro);
					} else {
						insertarEnNodo(unNodo->getHijoDerecho(), tmpRegistro);
					}
					*/
					unNodo->modificarHijoDerecho(insertarEnNodo(unNodo->getHijoDerecho(), tmpRegistro));
					insertarEnNodo(unNodo, unRegistro);
				}
			}
		}
	}

	int altIzq;
	int altDer;

	if (unNodo->getHijoIzquierdo() != 0) {
		altIzq = unNodo->getHijoIzquierdo()->getAltura();
	} else {
		altIzq = 0;
	}

	if (unNodo->getHijoDerecho() != 0) {
		altDer = unNodo->getHijoDerecho()->getAltura();
	} else {
		altDer = 0;
	}

	unNodo->modificarAltura(calcMax(altIzq,altDer) + 1);

	int diferencia = getDiferenciaAlturaHijos(unNodo);

	if (diferencia > 1) {
		return rotacionDerecha(unNodo);
	}
	if (diferencia < -1) {
		return rotacionIzquierda(unNodo);
	}

	return unNodo;
}

int ArbolAVL::getDiferenciaAlturaHijos(Nodo* unNodo) {
	if (unNodo == NULL)
			return 0;

	int alturaIzq;
	int alturaDer;

	Nodo* izq = unNodo->getHijoIzquierdo();
	Nodo* der = unNodo->getHijoDerecho();

	if (izq != 0) {
		alturaIzq = izq->getAltura();
	} else {
		alturaIzq = 0;
	}

	if (der != 0) {
		alturaDer = der->getAltura();
	} else {
		alturaDer = 0;
	}

	return (alturaIzq-alturaDer);
}

Nodo* ArbolAVL::rotacionDerecha(Nodo *unNodo) {
	Nodo* izq = unNodo->getHijoIzquierdo();
	Nodo* der = izq->getHijoDerecho();

	izq->modificarHijoDerecho(unNodo);
	unNodo->modificarHijoIzquierdo(der);

	unNodo->modificarAltura(calcMax(altIzq, altDer)+ 1);
	izq->modificarAltura(unNodo->getAltura());

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
	Registro* unRegistro;

	if(unNodo != 0) {
		cout<<"| ";
		list<Registro*>* registros = unNodo->getRegistros();
		for(list<Registro*>::iterator list_iter = registros->begin(); list_iter != registros->end(); list_iter++) {
			unRegistro = *list_iter;
			if (unNodo->getAltura() == 1) {
				//Como es hoja, podria imprimir todo los datos del reg
				cout<<unRegistro->id<<" ";
			} else {
				cout<<unRegistro->id<<" ";
			}
		}
		cout<<"|"<<endl;
		preOrder(unNodo->getHijoIzquierdo());
		preOrder(unNodo->getHijoDerecho());
	}
}

ArbolAVL::~ArbolAVL() {
	// TODO Auto-generated destructor stub
}
