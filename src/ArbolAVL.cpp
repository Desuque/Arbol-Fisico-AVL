//============================================================================
// Name        : ArbolAVL.cpp
// Author      : DDTeam
// Version     :
// Copyright   : FIUBA 2016
//============================================================================

#include "ArbolAVL.h"
#include <stdio.h>
#include <stdlib.h>

using namespace TPDatos;

ArbolAVL::ArbolAVL() {
	raiz = NULL;
}

void ArbolAVL::insertar(Registro* unRegistro) {
	raiz = insertarEnNodo(raiz, unRegistro);
}

int getMenorClave(Nodo* unNodo) {
	// TODO: recorrer todos los reg del nodo
	return unNodo->registro->id;
}

Nodo* ArbolAVL::insertarEnNodo(Nodo* unNodo, Registro* unRegistro)
{
	//TODO: por ahora cap max = 1 reg
	bool entra = false;

	if (unNodo == NULL)
		return(nuevoNodo(unRegistro));

	if (unNodo->altura == 1) {
		if (!entra) {
			if (unRegistro->id < getMenorClave(unNodo)) {
				unNodo->izquierdo = insertarEnNodo(unNodo->izquierdo, unRegistro);
				unNodo->derecho = insertarEnNodo(unNodo->derecho, unNodo->registro);
			} else {
				unNodo->derecho = insertarEnNodo(unNodo->derecho, unRegistro);
				unNodo->izquierdo = insertarEnNodo(unNodo->izquierdo, unNodo->registro);
			}

			unNodo->registro = NULL;
			unNodo->clave = getMenorClave(unNodo->derecho);
		} else {
			//TODO: cuando implemente lista de regs entonces agregar a la lista
		}
	} else {
		if (unRegistro->id < unNodo->clave) {
			unNodo->izquierdo = insertarEnNodo(unNodo->izquierdo, unRegistro);
		} else {
			unNodo->derecho = insertarEnNodo(unNodo->derecho, unRegistro);
		}
	}


	unNodo->altura = getMax(getAltura(unNodo->izquierdo), getAltura(unNodo->derecho)) + 1;

	//TODO: metodo balancear??
	int diferencia = getDiferenciaAlturaHijos(unNodo);

	if (diferencia > 1 && unRegistro->id < unNodo->izquierdo->clave)
		return rotacionDerecha(unNodo);

	if (diferencia < -1 && unRegistro->id > unNodo->derecho->clave)
		return rotacionIzquierda(unNodo);

	if (diferencia > 1 && unRegistro->id > unNodo->izquierdo->clave)
	{
		unNodo->izquierdo = rotacionIzquierda(unNodo->izquierdo);
		return rotacionDerecha(unNodo);
	}

	if (diferencia < -1 && unRegistro->id < unNodo->derecho->clave)
	{
		unNodo->derecho = rotacionDerecha(unNodo->derecho);
		return rotacionIzquierda(unNodo);
	}

	return unNodo;
}

Nodo* ArbolAVL::nuevoNodo(Registro* unRegistro)
{

	Nodo* unNodo = new Nodo();

	unNodo->clave = NULL;
	unNodo->izquierdo = NULL;
	unNodo->derecho = NULL;
	unNodo->registro = unRegistro;
	unNodo->altura = 1;

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

void ArbolAVL::preOrder(Nodo* root) {
	if(root != NULL)
	{
		preOrder(root->izquierdo);
		preOrder(root->derecho);
		if (root->altura == 1) {
			printf("%d ", root->registro->id);
		} else {
			printf("%d ", root->clave);
		}
	}
}
