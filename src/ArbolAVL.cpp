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
	//TODO: Abrir el archivo
	this->mayorIdReg = 0; //TODO: Lo lee del archivo (Metadato de la raiz)
}

int altura(Nodo* unNodo) {
	if (unNodo == 0)
		return 0;

	return unNodo->getAltura();
}

void ArbolAVL::insertar(Registro* unRegistro){
	unRegistro->setId(mayorIdReg);
	mayorIdReg++;
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
		if (unRegistro->getId() < unNodo->getMenorID()) {
			if (unNodo->getHijoIzquierdo() == 0) {
				if (!unNodo->insertar(unRegistro)) {
					unNodo->modificarHijoIzquierdo(insertarEnNodo(unNodo->getHijoIzquierdo(), unRegistro));
				}
			} else {
				if (unRegistro->getId() > (unNodo->getHijoIzquierdo())->getMayorID()) {
					if (!unNodo->insertar(unRegistro)) {
						unNodo->modificarHijoIzquierdo(insertarEnNodo(unNodo->getHijoIzquierdo(), unRegistro));
					}
				} else {
					unNodo->modificarHijoIzquierdo(insertarEnNodo(unNodo->getHijoIzquierdo(), unRegistro));
				}
			}
		} else {
			if (unRegistro->getId() > unNodo->getMayorID()) {
				if (unNodo->getHijoDerecho() == 0) {
					if (!unNodo->insertar(unRegistro)) {
						unNodo->modificarHijoDerecho(insertarEnNodo(unNodo->getHijoDerecho(), unRegistro));
					}
				} else {
					if (unRegistro->getId() < unNodo->getHijoDerecho()->getMenorID()) {
						if (!unNodo->insertar(unRegistro)) {
							unNodo->modificarHijoDerecho(insertarEnNodo(unNodo->getHijoDerecho(), unRegistro));
						}
					} else {
						unNodo->modificarHijoDerecho(insertarEnNodo(unNodo->getHijoDerecho(), unRegistro));
					}
				}
			} else {
				if (!unNodo->insertar(unRegistro)) {
					Registro* mayorRegistro = unNodo->getRegistroConMayorID();
					Registro* tmpRegistro = new Registro(mayorRegistro->getCodigo(), mayorRegistro->getDescripcion());
					tmpRegistro->setId(mayorRegistro->getId());

					unNodo->borrarRegistro(tmpRegistro->getId());
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

	if ((diferencia > 1) && (unRegistro->getId() < unNodo->getHijoIzquierdo()->getMenorID())) {
		return rotacionDerecha(unNodo);
	}

	if ((diferencia < -1) && (unRegistro->getId() > unNodo->getHijoDerecho()->getMayorID())) {
		return rotacionIzquierda(unNodo);
	}

	if ((diferencia > 1) && (unRegistro->getId() > unNodo->getHijoIzquierdo()->getMayorID()))
	{
		unNodo->modificarHijoIzquierdo(rotacionIzquierda(unNodo->getHijoIzquierdo()));
		return rotacionIzquierda(unNodo);
	}

	if ((diferencia < -1) && (unRegistro->getId() < unNodo->getHijoDerecho()->getMenorID()))
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
				cout<<unRegistro->getId()<<" ";
			} else {
				cout<<unRegistro->getId()<<" ";
			}
		}
		cout<<"|"<<endl;
		preOrder(unNodo->getHijoIzquierdo());
		preOrder(unNodo->getHijoDerecho());
	}
}

void ArbolAVL::borrarRegistro(int unID) {
	raiz = borrarRegistroPorID(raiz, unID);
}

Nodo* ArbolAVL::borrarRegistroPorID(Nodo* unNodo, int idBuscado) {
	if(unNodo != 0) {
		int menorID = unNodo->getMenorID();
		int mayorID = unNodo->getMayorID();
		if (!unNodo->existeRegistroConID(idBuscado)) {
			if (idBuscado < menorID) {
				unNodo->modificarHijoIzquierdo(borrarRegistroPorID(unNodo->getHijoIzquierdo(), idBuscado));

				//TODO: idem derecho pero con izquierdo
			}
			if (idBuscado > mayorID) {
				unNodo->modificarHijoDerecho(borrarRegistroPorID(unNodo->getHijoDerecho(), idBuscado));

				if (unNodo->getHijoDerecho() != 0) {
					if (unNodo->getHijoDerecho()->estaEnUnderflow()) {
						Registro* tmpReg;

						//TODO: if (unNodo->getTamanio() - unNodo->getRegistroConMayorID()->getTamanio() >= (unNodo->bytesLibres / 2)) {
						if (unNodo->getTamanio() - 1 >= unNodo->minPorNodo) {
							// Si al ancestro le sobra un registro entonces bajo uno
							unNodo->modificarHijoDerecho(insertarEnNodo(unNodo->getHijoDerecho(), unNodo->getRegistroConMayorID()));
							unNodo->borrarRegistro(unNodo->getMayorID());
						} else {
							// Si al ancestro no le sobra uno, me fijo si le puedo pedir al hijo izq
							bool suboYBorroNodo = false;
							if (unNodo->getHijoIzquierdo() != 0) {
								//TODO: if (unNodo->getHijoIzquierdo->getTamanio() - unNodo->getHijoIzquierdo->getRegistroConMayorID()->getTamanio() >= (unNodo->getHijoIzquierdo()->bytesLibres / 2)) {
								if (unNodo->getHijoIzquierdo()->getRegistros()->size() - 1 >= unNodo->minPorNodo) {
									// El mayor del ancestro se lo paso al hijo derecho
									tmpReg = unNodo->getRegistroConMayorID();
									unNodo = borrarRegistroPorID(unNodo, unNodo->getMayorID());
									unNodo->modificarHijoDerecho(insertarEnNodo(unNodo->getHijoDerecho(), tmpReg));
									// El mayor del hijo izq se lo paso al ancestro para que no quede en UF
									tmpReg = unNodo->getHijoIzquierdo()->getRegistroConMayorID();
									unNodo->modificarHijoIzquierdo(borrarRegistroPorID(unNodo->getHijoIzquierdo(), unNodo->getHijoIzquierdo()->getMayorID()));
									unNodo = insertarEnNodo(unNodo, tmpReg);
								} else {
									suboYBorroNodo = true;
								}
							} else {
								suboYBorroNodo = true;
							}
							if (suboYBorroNodo) {
								list<Registro*>* registros = unNodo->getHijoDerecho()->getRegistros();
								Registro* unRegistro;
								unNodo->modificarHijoDerecho(0); //TODO: hay q hacer delete p liberar mem?? -> ojo pq puedo perder la list de registros
								for(list<Registro*>::iterator list_iter = registros->begin(); list_iter != registros->end(); list_iter++) {
									unRegistro = *list_iter;
									unNodo = insertarEnNodo(unNodo, unRegistro);
								}
							}
						}

					}
				}
			}
		} else {
			unNodo->borrarRegistro(idBuscado);
		}
	}

	return unNodo;
}

Nodo* ArbolAVL::buscarNodoPorID(Nodo* unNodo, int idBuscado) {
	if(unNodo != 0) {
		int menorID = unNodo->getMenorID();
		int mayorID = unNodo->getMayorID();
		if (!unNodo->existeRegistroConID(idBuscado)) {
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
