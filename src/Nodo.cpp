#include "Nodo.h"
#include <iostream>

using namespace std;

// ------------------------------------------------------------------------
// Si es construido solo con el nombre de archivo, inicializa el nodo vacio
Nodo::Nodo(string nombreArchivo) {
	this->izquierdo = -1;
	this->derecho = -1;
	this->registros = new list<Registro*>;
	this->altura = 1;
	this->nombreArchivo = nombreArchivo;
	bloque = 0;
}
// ------------------------------------------------------------------------
// Si es construido con el nombre de archivo y el id de su bloque -> carga el nodo con lo que haya en el disco
Nodo::Nodo(string nombreArchivo, int idBloque) {
	bloque = new Bloque(nombreArchivo, idBloque);
	Nodo* unNodo = bloque->devolverNodo();

	if (unNodo != 0) {
		this->izquierdo = unNodo->getHijoIzquierdo();
		this->derecho = unNodo->getHijoDerecho();
		this->registros = unNodo->getRegistros();
		this->altura = unNodo->getAltura();
	} else {
		this->izquierdo = -1;
		this->derecho = -1;
		this->registros = 0;
		this->altura = 1;
	}

	this->nombreArchivo = nombreArchivo;
}
int Nodo::getMaxIdReg() {
	return bloque->getMaxIdReg();
}
// ------------------------------------------------------------------------
// Devuelve la lista de toodos los registros
list<Registro*>* Nodo::getRegistros() {
	return registros;
}
// ------------------------------------------------------------------------
// Devuelve cuanto ocupan todos los registros dentro del nodo
// TODO: Ver si faltan metadatos, y ver si descr es mayor q 1000 q habria q mandar
int Nodo::getTamanio() {
	Registro* unRegistro;
	int tamanio = 0;

	if (registros != 0) {
		for(list<Registro*>::iterator list_iter = registros->begin(); list_iter != registros->end(); list_iter++) {
			unRegistro = *list_iter;
			tamanio += unRegistro->getTamanio();
		}
	}

	return tamanio;
}
// ------------------------------------------------------------------------
// Devuelve el registro con el id mas pequenio
int Nodo::getMenorID() {
	Registro* regTmp;
	if (!registros->empty()) {
		regTmp = registros->front();
		return regTmp->getId();
	} else {
		return NULL;
	}
}

// ------------------------------------------------------------------------
// Devuelve el registro con el id mas grande
int Nodo::getMayorID() {
	Registro* regTmp;
	if(!registros->empty()) {
		regTmp = registros->back();
		return regTmp->getId();
	} else {
		return NULL;
	}
}

int Nodo::getHijoIzquierdo() {
	return this->izquierdo;
}

int Nodo::getHijoDerecho() {
	return this->derecho;
}

int Nodo::getAltura() {
	return this->altura;
}

void Nodo::setHijoIzquierdo(int nuevoNodo) {
	this->izquierdo = nuevoNodo;
}
void Nodo::setHijoDerecho(int nuevoNodo) {
	this->derecho = nuevoNodo;
}
void Nodo::setAltura(int nuevaAltura) {
	this->altura = nuevaAltura;
}
void Nodo::modificarHijoIzquierdo(int nuevoNodo) {
	this->izquierdo = nuevoNodo;
	bloque->escribirIdIzq(nuevoNodo);
}
void Nodo::modificarHijoDerecho(int nuevoNodo) {
	this->derecho = nuevoNodo;
	bloque->escribirIdDer(nuevoNodo);
}
void Nodo::modificarAltura(int nuevaAltura) {
	this->altura = nuevaAltura;
	bloque->escribirAltura(nuevaAltura);
}

Bloque* Nodo::getBloque() {
	return bloque;
}

bool comparaRegistros(Registro* a, Registro* b) { return a->getId() < b->getId(); }


bool Nodo::insertar(Registro* unRegistro) {
	if (bloque == 0) {
		bloque = new Bloque(nombreArchivo);
	}
	if (bloque->entra(unRegistro)) {

		registros->push_back(unRegistro);
		registros->sort(comparaRegistros);
		bloque->grabar(this);

		return true;
	} else {

		return false;
	}
}

Nodo* Nodo::reescribirEn(int id) {
	bloque = new Bloque(nombreArchivo, id);
	bloque->grabar(this);

	return this;
}

bool Nodo::estaEnUnderflow() {
	if (this->altura > 1) {
		return bloque->estaEnUnderflow(this);
	}

	return false;
}

bool Nodo::esHoja() {

	return this->altura == 1;
}

bool Nodo::modificarRegistro(int ID, string nuevoCodigo, string nuevaDescripcion) {
	bool modificado = false;
	Registro* unRegistro;

	for(list<Registro*>::iterator list_iter = registros->begin(); list_iter != registros->end(); list_iter++) {
		unRegistro = *list_iter;
			if (unRegistro->getId() == ID) {
				if (unRegistro->getDescripcion().size() > 1000) {
					bloque->borrarDescripcionArchivoDescrips(unRegistro->getId());
				}
				unRegistro->setCodigo(nuevoCodigo);
				unRegistro->setDescripcion(nuevaDescripcion);
				bloque->grabar(this);
				modificado = true;
				break;
			}
	}
	return modificado;
}

bool Nodo::borrarRegistro(int ID) {
	bool encontrado = false;
	Registro* unRegistro;
	for(list<Registro*>::iterator list_iter = registros->begin(); list_iter != registros->end(); list_iter++) {
		unRegistro = *list_iter;
		if (unRegistro->getId() == ID) {
			registros->remove(unRegistro);
			bloque->grabar(this);
			encontrado = true;
			break;
		}
	}

	return encontrado;
}

Registro* Nodo::getRegistro(int unID) {
	bool encontrado = false;
	Registro* unRegistro = NULL;

	for(list<Registro*>::iterator list_iter = registros->begin(); list_iter != registros->end(); list_iter++) {
		unRegistro = *list_iter;
		if (unRegistro->getId() == unID) {
			encontrado = true;
			break;
		}
	}
	return unRegistro;
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

Nodo::~Nodo() {
	//TODO Como es una lista de punteros que pidieron memoria, hay que recorrer la lista y borrarlos de a uno
	delete registros;
}

