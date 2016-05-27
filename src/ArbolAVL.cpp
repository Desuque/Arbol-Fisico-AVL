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
	insertarEnNodo(raiz, unRegistro);
}

Nodo* ArbolAVL::crearNodoRaiz(Registro* unRegistro) {
	Nodo* unNodo = new Nodo(this->alturaRaiz);
	unNodo->insertar(unRegistro);

	return unNodo;
}

void ArbolAVL::insertarEnNodo(Nodo* unNodo, Registro* unRegistro) {
	//Si es el la raiz se crea el nodo y entra directo
	if (unNodo == 0) {
		this->raiz = crearNodoRaiz(unRegistro);
	} else {
		if (unRegistro->id < unNodo->getMenorID()) {
			if (unNodo->getHijoIzquierdo() == 0) {
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
				if (unNodo->getHijoDerecho() == 0) {
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
		//No se ejecuta en la primer entrada porque la raiz no hace falta balancearla
		balancear(unNodo);
	}

}

int ArbolAVL::getDiferenciaAlturaHijos(Nodo* unNodo) {
	int alturaIzq;
	int alturaDer;
	Nodo* izq = unNodo->getHijoIzquierdo();
	Nodo* der = unNodo->getHijoDerecho();
	if (izq != 0) {
		alturaIzq = izq->getAltura();
	} else {
		alturaIzq = unNodo->getAltura(); //Me quedo con la altura del padre
	}
	if (der != 0) {
		alturaDer = der->getAltura();
	} else {
		alturaDer = unNodo->getAltura();
	}

	return (alturaIzq-alturaDer);
}

void ArbolAVL::balancear(Nodo* unNodo) {
	int diferencia = getDiferenciaAlturaHijos(unNodo);

	if (diferencia > 1) {
		rotacionDerecha(unNodo);
	}
	if (diferencia < -1) {
		rotacionIzquierda(unNodo);
	}
}

void ArbolAVL::rotacionDerecha(Nodo *unNodo) {
	Nodo* izq = unNodo->getHijoIzquierdo();
	Nodo* der = izq->getHijoDerecho();

	izq->modificarHijoDerecho(unNodo);
	unNodo->modificarHijoIzquierdo(der);

	//Luego de rotar el hijo izquierdo pasa a ser el nodo central
	izq->modificarAltura(unNodo->getAltura());
	unNodo->modificarAltura((unNodo->getAltura())+1);

	//return izq;
}

void ArbolAVL::rotacionIzquierda(Nodo *unNodo) {
	Nodo *der = unNodo->getHijoDerecho();
	Nodo *izq = der->getHijoIzquierdo();

	der->modificarHijoIzquierdo(unNodo);
	unNodo->modificarHijoDerecho(izq);

	der->modificarAltura(unNodo->getAltura());
	unNodo->modificarAltura((unNodo->getAltura())+1);

	//return der;
}

void ArbolAVL::print() {
	preOrder(raiz);
}

void ArbolAVL::preOrder(Nodo* unNodo) {
	Registro* unRegistro;

	if(unNodo != 0) {
		list<Registro*>* registros = unNodo->getRegistros();
		preOrder(unNodo->getHijoIzquierdo());
		preOrder(unNodo->getHijoDerecho());

		cout<<"| ";
		for(list<Registro*>::iterator list_iter = registros->begin(); list_iter != registros->end(); list_iter++) {
			unRegistro = *list_iter;
			if (unNodo->getAltura() == 1) {
				//Como es hoja, podria imprimir todo los datos del reg
				cout<<unRegistro->id<<endl;
			} else {
				cout<<unRegistro->id<<endl;
			}
		}
		cout<<"|";
	}
}

ArbolAVL::~ArbolAVL() {
	// TODO Auto-generated destructor stub
}
