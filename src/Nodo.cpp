/*
 * Nodo.cpp
 *
 *  Created on: 26 de may. de 2016
 *      Author: desuque
 */

#include "Nodo.h"

using namespace std;

Nodo::Nodo(int alturaPadre) {
	//NULL no es estandar papa, 0 es null.
	this->izquierdo = 0;
	this->derecho = 0;
	this->cantidadDeElementos = 0;
	this->registros = new list<Registro*>;
	this->altura = 0;
	this->altura = altura + alturaPadre;

	//Esto es para la persistencia, 8===3
	this->bytes_libres = 3000;
}

list<Registro*>* Nodo::getRegistros() {
	return registros;
}

int Nodo::getMenorID() {
	//Por la documentacion de list, ordena por defecto en forma ascendente
	//Asi que el primer elemento de la lista es el registro que necesito

	Registro* regTmp = registros->front();
	return regTmp->id;
}

int Nodo::getMayorID() {
	Registro* regTmp = registros->back();
	return regTmp->id;
}

Nodo* Nodo::getHijoIzquierdo() {
	return this->izquierdo;
}

Nodo* Nodo::getHijoDerecho() {
	return this->derecho;
}

int Nodo::getAltura() {
	return this->altura;
}

void Nodo::modificarHijoIzquierdo(Nodo* nuevoNodo) {
	this->izquierdo = nuevoNodo;
}

void Nodo::modificarHijoDerecho(Nodo* nuevoNodo) {
	this->derecho = nuevoNodo;
}

void Nodo::modificarAltura(int nuevaAltura) {
	this->altura = nuevaAltura;
}

int Nodo::insertar(Registro* unRegistro) {
	//TODO probablemente no sea con el tamaño de la lista, sino
	//con la cantidad de bytes_libres

	//TODO el sort ordena por lo que se le canta la chota
	//porque como sabe que yo quiero por ID?
	//Ya fue loco, me voy a la mierda (despues lo miro)

	registros->push_front(unRegistro);

/**
	if (cantidadDeElementos < this->maxElementos) {
		registros->push_front(unRegistro);
		//registros->sort(); //Siempre dejo la lista ordenada
		return 0;
	}
	return 1;
	**/
	return 0;
}

void Nodo::crearHijoIzquierdo(Registro* unRegistro) {
	izquierdo = new Nodo(this->altura);
	izquierdo->insertar(unRegistro);
}

void Nodo::crearHijoDerecho(Registro* unRegistro) {
	derecho = new Nodo(this->altura);
	derecho->insertar(unRegistro);
}

void Nodo::borrarRegistro(int ID) {
	bool encontrado = false;
	list<Registro*>::iterator it=registros->begin();
/** ERROR PAPAAAA
	while((!encontrado) && (it != registros->end())) {
		list<Registro*>::iterator regIt;
		regIt  = it;
		if (regIt->id == ID) {
			registros->remove(regIt);
			encontrado = true;
		}
		it++;
	}
	**/
}

Registro* Nodo::getRegistroConMayorID() {
	return registros->back();
}


Nodo::~Nodo() {
	//TODO Como es una lista de punteros que pidieron memoria, hay que recorrer la lista y borrarlos de a uno
	delete registros;
}

