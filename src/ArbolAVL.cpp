//============================================================================
// Name        : ArbolAVL.cpp
// Author      : DDTeam
// Version     :
// Copyright   : FIUBA  2016
//============================================================================

#include "ArbolAVL.h"
#include <stdio.h>
#include <stdlib.h>

using namespace TPDatos;

ArbolAVL::ArbolAVL() {
	raiz = NULL;
}

void ArbolAVL::insertar(Registro* unRegistro) {
	raiz = insertarEnNodo(raiz, unRegistro, false);
}

int getMenorClave(Nodo* unNodo) {
	list<Registro>::iterator list_iter = unNodo->registros.begin();
	Registro unRegistro = *list_iter;

	return unRegistro.id;
}

bool ArbolAVL::entraUnRegistroMas(Nodo* unNodo) {
	if (unNodo->altura == 1) {
		if (unNodo->registros.size() == maxHoja) {
			return false;
		}
	} else {
		if (unNodo->registros.size() == maxInternos) {
			return false;
		}
	}
	return true;
}

Nodo* ArbolAVL::insertarEnNodo(Nodo* unNodo, Registro* unRegistro, bool agregaNuevoNodo)
{

	if (unNodo == NULL)
		return(nuevoNodoHoja(unRegistro));

	if (unRegistro->id < unNodo->getRegistroMasChico()->id) {
		if (unNodo->getHijoIzquierdo() == NULL) {
			if (!unNodo->insertar(unRegistro)) {
				unNodo->crearHijoIzquierdo(unRegistro);
			}
		} else {
			if (unRegistro->id > unNodo->getIzquierdo()->getMayor()) {
				if (!unNodo->insertar(unRegistro)) {
					insertarEnNodo(unNodo->getIzquierdo(), unRegistro);
				}
			} else {
				insertarEnNodo(unNodo->getIzquierdo(), unRegistro);
			}
		}
	}


	unNodo->altura = getMax(getAltura(unNodo->izquierdo), getAltura(unNodo->derecho)) + 1;

	//TODO: metodo balancear??
	int diferencia = getDiferenciaAlturaHijos(unNodo);

	if (diferencia > 1 && unRegistro->id < getMenorClave(unNodo->izquierdo))
		return rotacionDerecha(unNodo);

	if (diferencia < -1 && unRegistro->id > getMenorClave(unNodo->derecho))
		return rotacionIzquierda(unNodo);

	if (diferencia > 1 && unRegistro->id > getMenorClave(unNodo->izquierdo))
	{
		unNodo->izquierdo = rotacionIzquierda(unNodo->izquierdo);
		return rotacionDerecha(unNodo);
	}

	if (diferencia < -1 && unRegistro->id < getMenorClave(unNodo->derecho))
	{
		unNodo->derecho = rotacionDerecha(unNodo->derecho);
		return rotacionIzquierda(unNodo);
	}

	return unNodo;
}

Nodo* ArbolAVL::nuevoNodoInterno(int alturaVieja)
{

	Nodo* unNodo = new Nodo();

	unNodo->izquierdo = NULL;
	unNodo->derecho = NULL;
	unNodo->altura = alturaVieja + 1;

	return unNodo;
}

Nodo* ArbolAVL::nuevoNodoHoja(Registro* unRegistro)
{

	Nodo* unNodo = new Nodo();

	unNodo->izquierdo = NULL;
	unNodo->derecho = NULL;
	unNodo->altura = 1;

	unNodo->registros.push_back(*unRegistro);

	return unNodo;
}

Nodo* ArbolAVL::rotacionDerecha(Nodo *unNodo)
{
	Nodo* izq = unNodo->izquierdo;
	Nodo* der = izq->derecho;

	izq->derecho = unNodo;
	unNodo->izquierdo = der;

	unNodo->altura = getMax(getAltura(unNodo->izquierdo), getAltura(unNodo->derecho))+1;
	izq->altura = getMax(getAltura(izq->izquierdo), getAltura(izq->derecho))+1;

	return izq;
}

Nodo* ArbolAVL::rotacionIzquierda(Nodo *unNodo)
{
	Nodo *der = unNodo->derecho;
	Nodo *izq = der->izquierdo;

	der->izquierdo = unNodo;
	unNodo->derecho = izq;

	unNodo->altura = getMax(getAltura(unNodo->izquierdo), getAltura(unNodo->derecho))+1;
	der->altura = getMax(getAltura(der->izquierdo), getAltura(der->derecho))+1;

	return der;
}

int ArbolAVL::getAltura(Nodo *unNodo)
{
	if (unNodo == NULL)
		return 0;

	return unNodo->altura;
}

int ArbolAVL::getMax(int x, int y)
{
	return (x > y)? x : y;
}

int ArbolAVL::getDiferenciaAlturaHijos(Nodo *unNodo)
{
	if (unNodo == NULL)
		return 0;
	return getAltura(unNodo->izquierdo) - getAltura(unNodo->derecho);
}

void ArbolAVL::print()
{
	preOrder(raiz);
}

void ArbolAVL::preOrder(Nodo* unNodo) {
	Registro unRegistro;

	if(unNodo != NULL)
	{
		preOrder(unNodo->izquierdo);
		preOrder(unNodo->derecho);

		printf("| ");
		for(list<Registro>::iterator list_iter = unNodo->registros.begin();
				list_iter != unNodo->registros.end();
				list_iter++)
		{
			unRegistro = *list_iter;

			if (unNodo->altura == 1) {
				//Como es hoja, podria imprimir todo los datos del reg
				printf("%d ", unRegistro.id);
			} else {
				printf("%d ", unRegistro.id);
			}
		}
		printf("|");
	}
}
