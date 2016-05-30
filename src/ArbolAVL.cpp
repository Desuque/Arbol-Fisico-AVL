//============================================================================
// Name        : ArbolAVL.cpp
// Author      : DDTeam
// Version     :
// Copyright   : FIUBA  2016
//============================================================================

#include "Nodo.h"
#include "ArbolAVL.h"
#include <iostream>
#include <string.h>

using namespace std;

ArbolAVL::ArbolAVL() {
	this->raiz = 0;
}

int altura(Nodo* unNodo) {
	if (unNodo == 0)
		return 0;

	return unNodo->getAltura();
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
				}
			} else {
				if (unRegistro->id > (unNodo->getHijoIzquierdo())->getMayorID()) {
					if (!unNodo->insertar(unRegistro)) {
						unNodo->modificarHijoIzquierdo(insertarEnNodo(unNodo->getHijoIzquierdo(), unRegistro));
					}
				} else {
					unNodo->modificarHijoIzquierdo(insertarEnNodo(unNodo->getHijoIzquierdo(), unRegistro));
				}
			}
		} else {
			if (unRegistro->id > unNodo->getMayorID()) {
				if (unNodo->getHijoDerecho() == 0) {
					if (!unNodo->insertar(unRegistro)) {
						unNodo->modificarHijoDerecho(insertarEnNodo(unNodo->getHijoDerecho(), unRegistro));
					}
				} else {
					if (unRegistro->id < unNodo->getHijoDerecho()->getMenorID()) {
						if (!unNodo->insertar(unRegistro)) {
							unNodo->modificarHijoDerecho(insertarEnNodo(unNodo->getHijoDerecho(), unRegistro));
						}
					} else {
						unNodo->modificarHijoDerecho(insertarEnNodo(unNodo->getHijoDerecho(), unRegistro));
					}
				}
			} else {
				if (!unNodo->insertar(unRegistro)) {
					Registro* tmpRegistro = new Registro();
					Registro* mayorRegistro = unNodo->getRegistroConMayorID();

					tmpRegistro->id = mayorRegistro->id;
					strcpy(tmpRegistro->codigo, mayorRegistro->codigo); 			//tmpRegistro->codigo = mayorRegistro->codigo;
					strcpy(tmpRegistro->descripcion, mayorRegistro->descripcion); 	//tmpRegistro->descripcion = mayorRegistro->descripcion;
					tmpRegistro->tamanio = mayorRegistro->tamanio;

					unNodo->borrarRegistro(tmpRegistro->id);
					unNodo->modificarHijoDerecho(insertarEnNodo(unNodo->getHijoDerecho(), tmpRegistro));
					insertarEnNodo(unNodo, unRegistro); //TODO: Esto seguramente este mal, tendria que asignarle el return a algo
				}
			}
		}
	}

	int altIzq = altura(unNodo->getHijoIzquierdo());
	int altDer = altura(unNodo->getHijoDerecho());

	unNodo->modificarAltura(calcMax(altIzq,altDer) + 1);

	int diferencia = getDiferenciaAlturaHijos(unNodo);

	//TODO: probar a fondo todas las rots. Algunos getHijoIzq a veces devuelven null o 0

	if ((diferencia > 1) && (unRegistro->id < unNodo->getHijoIzquierdo()->getRegistroConMenorID()->id)) {
		return rotacionDerecha(unNodo);
	}

	if ((diferencia < -1) && (unRegistro->id > unNodo->getHijoDerecho()->getRegistroConMayorID()->id)) {
		return rotacionIzquierda(unNodo);
	}

	if ((diferencia > 1) && (unRegistro->id > unNodo->getHijoIzquierdo()->getRegistroConMayorID()->id))
	{
		unNodo->modificarHijoIzquierdo(rotacionIzquierda(unNodo->getHijoIzquierdo()));
		return rotacionIzquierda(unNodo);
	}

	if ((diferencia < -1) && (unRegistro->id < unNodo->getHijoDerecho()->getRegistroConMenorID()->id))
	{
		unNodo->modificarHijoDerecho(rotacionDerecha(unNodo->getHijoDerecho()));
		return rotacionIzquierda(unNodo);
	}

	return unNodo;
}

int ArbolAVL::getDiferenciaAlturaHijos(Nodo* unNodo) {
	if (unNodo == 0)
			return 0;

	Nodo* izq = unNodo->getHijoIzquierdo();
	Nodo* der = unNodo->getHijoDerecho();

	int alturaIzq = altura(izq);
	int alturaDer = altura(der);

	return (alturaIzq-alturaDer);
}

Nodo* ArbolAVL::rotacionDerecha(Nodo *unNodo) {
	Nodo* izq = unNodo->getHijoIzquierdo();
	Nodo* der = izq->getHijoDerecho();

	izq->modificarHijoDerecho(unNodo);
	unNodo->modificarHijoIzquierdo(der);

	unNodo->modificarAltura(calcMax(altura(unNodo->getHijoIzquierdo()), altura(unNodo->getHijoDerecho())) + 1);
	izq->modificarAltura(calcMax(altura(izq->getHijoIzquierdo()), altura(izq->getHijoDerecho())) + 1);

	return izq;
}

Nodo* ArbolAVL::rotacionIzquierda(Nodo *unNodo) {
	Nodo *der = unNodo->getHijoDerecho();
	Nodo *izq = der->getHijoIzquierdo();

	der->modificarHijoIzquierdo(unNodo);
	unNodo->modificarHijoDerecho(izq);

	unNodo->modificarAltura(calcMax(altura(unNodo->getHijoIzquierdo()), altura(unNodo->getHijoDerecho())) + 1);
	der->modificarAltura(calcMax(altura(der->getHijoIzquierdo()), altura(der->getHijoDerecho())) + 1);

	return der;
}

Nodo* ArbolAVL::getRaiz() {
	return raiz;
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

//Se le pasa el nodo padre y el nodo hijo y se actualiza la
//altura y las relaciones entre punteros
void actualizarRelacionPadreHijo(Nodo* nodoPadre, Nodo* nodoHijo, string ) {
	nodoPadre->modificarHijoDerecho()
}

Nodo* ArbolAVL::borrarNodo(Nodo* unNodo, Nodo* nodoVacio) {
	if(unNodo != 0) {
		int menorID = unNodo->getMenorID();
		int mayorID = unNodo->getMayorID();
		if (unNodo->buscarID(idBuscado) == false) {
			if (idBuscado < menorID) {
				return buscarNodoPorID(unNodo->getHijoIzquierdo(), idBuscado);
			}
			if (idBuscado > mayorID) {
				return buscarNodoPorID(unNodo->getHijoDerecho(), idBuscado);
			}
		} else {
			return unNodo;
		}
	}
	return 0;

}

void ArbolAVL::borrarRegistro(int idBuscado) {
	Nodo* unNodo = buscarNodoPorID(raiz, idBuscado);

	if (unNodo != 0) {
		unNodo->borrarRegistro(idBuscado);
		if(unNodo->getCantidadDeRegistros()== 0) {
			raiz = borrarNodo(raiz, unNodo);
		}
	}
}

Nodo* ArbolAVL::buscarNodoPorID(Nodo* unNodo, int idBuscado) {
	if(unNodo != 0) {
		int menorID = unNodo->getMenorID();
		int mayorID = unNodo->getMayorID();
		if (unNodo->buscarID(idBuscado) == false) {
			if (idBuscado < menorID) {
				return buscarNodoPorID(unNodo->getHijoIzquierdo(), idBuscado);
			}
			if (idBuscado > mayorID) {
				return buscarNodoPorID(unNodo->getHijoDerecho(), idBuscado);
			}
		} else {
			return unNodo;
		}
	}
	return 0;
}

ArbolAVL::~ArbolAVL() {
	// TODO Auto-generated destructor stub
}
