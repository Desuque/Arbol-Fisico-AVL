/*
 * Nodo.cpp
 *
 *  Created on: 26 de may. de 2016
 *      Author: desuque
 */

#include "Nodo.h"

using namespace std;

Nodo::Nodo() {
	this->izquierdo = 0;
	this->derecho = 0;
	this->cantidadDeElementos = 0;
	this->registros = new list<Registro*>;
	this->altura = 1;

	this->bytes_libres = 3024; // 1008 cada registro. Admite hasta 3 reg llenos
}

list<Registro*>* Nodo::getRegistros() {
	return registros;
}

int Nodo::getTamanio() {
	Registro* unRegistro;
	int tamanio = 0;

	for(list<Registro*>::iterator list_iter = registros->begin(); list_iter != registros->end(); list_iter++) {
		unRegistro = *list_iter;
		//TODO:
		//tamanio += unRegistro->getTamanio();
		tamanio += 1;
	}

	return tamanio;
}

int Nodo::getMenorID() {
	Registro* regTmp = registros->front();
	return regTmp->getId();
}

int Nodo::getMayorID() {
	Registro* regTmp = registros->back();
	return regTmp->getId();
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

bool comparaRegistros(Registro* a, Registro* b) { return a->getId() < b->getId(); }


bool Nodo::insertar(Registro* unRegistro) {
	//TODO:
	// if (unRegistro->getTamanio() <= this->bytesLibres) {
	//		registros->push_front(unRegistro);
	//		cantidadDeElementos++;
	//		registros->sort(comparaRegistros);
	//      this->bytesLibres -= unRegistro->getTamanio();
	//		return true;
	// }

	if (cantidadDeElementos < this->maxPorNodo) {
		registros->push_front(unRegistro);
		cantidadDeElementos++;
		registros->sort(comparaRegistros);

		return true;
	}
	return false;
}

bool Nodo::estaEnUnderflow() {

	//TODO:
	//if (getTamanio() < (bytesLibres / 2))
	if (cantidadDeElementos < this->minPorNodo) {
		return true;
	}

	return false;
}

bool Nodo::borrarRegistro(int ID) {
	bool encontrado = false;
	Registro* unRegistro;

	for(list<Registro*>::iterator list_iter = registros->begin(); list_iter != registros->end(); list_iter++) {
		unRegistro = *list_iter;
		if (unRegistro->getId() == ID) {
			registros->remove(unRegistro);
			encontrado = true;
			cantidadDeElementos--;
			break;
		}
	}

	return encontrado;
}

bool Nodo::existeRegistroConID(int idBuscado) {
	bool encontrado = false;
	Registro* unRegistro;

	for(list<Registro*>::iterator list_iter = registros->begin(); list_iter != registros->end(); list_iter++) {
		unRegistro = *list_iter;
		if (unRegistro->getId() == idBuscado) {
			encontrado = true;
			break;
		}
	}
	return encontrado;
}

Registro* Nodo::getRegistroConMayorID() {
	return registros->back();
}

Registro* Nodo::getRegistroConMenorID() {
	return registros->front();
}

int Nodo::getCantidadDeRegistros() {
	return cantidadDeElementos;
}

Nodo::~Nodo() {
	//TODO Como es una lista de punteros que pidieron memoria, hay que recorrer la lista y borrarlos de a uno
	delete registros;
}

