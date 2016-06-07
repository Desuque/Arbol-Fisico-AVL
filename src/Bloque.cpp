/*
 * Nodo.cpp
 *
 *  Created on: 26 de may. de 2016
 *      Author: desuque
 */

#include "Bloque.h"

using namespace std;

Bloque::Bloque(string nombreArchivo) {
	this->nombreArchivo = nombreArchivo;
	this->archivoArbol = new Persistencia(nombreArchivo);
	this->id = archivoArbol->leerMayorIdNodo();

	inicializarBloque();
}

Bloque::Bloque(string nombreArchivo, int id) {
	this->nombreArchivo = nombreArchivo;
	this->archivoArbol = new Persistencia(nombreArchivo);
	this->id = id;
}

Nodo* Bloque::devolverNodo() {
	char* charBloq = archivoArbol->leerBloque(id);

	if (charBloq[0] != 'E') {
		return 0;
	} else {
		Nodo* unNodo = new Nodo(nombreArchivo);

		int offset = 0;
		offset += 4;
		int espLibre = *(reinterpret_cast<int *>(charBloq + offset));
		offset += 4;
		int idIzq = *(reinterpret_cast<int *>(charBloq + offset));
		offset += 4;
		int idDer = *(reinterpret_cast<int *>(charBloq + offset));

		return unNodo;
	}
}

void Bloque::inicializarBloque() {
	// TODO: Escribir los 4kb vacios
	archivoArbol->escribirMaxIDNodo(id + 1);
	escribirFlagExistencia();
	bytes_ocupados = tamanio_meta;
	escribirEspacioLibre();
}

int Bloque::calcularOffsetMetadatos() {
	return (id * tamanio) + archivoArbol->getTamanioMetadatos();
}

int Bloque::calcularOffsetRegistros() {
	return (id * tamanio) + archivoArbol->getTamanioMetadatos() + tamanio_meta;
}

void Bloque::escribirFlagExistencia() {
	int offset = calcularOffsetMetadatos();
	archivoArbol->escribirUnString("E", offset);
}

void Bloque::escribirEspacioLibre() {
	int offset = calcularOffsetMetadatos() + 1;
	int espacioLibre = tamanio - bytes_ocupados;
	archivoArbol->escribirUnInt(espacioLibre, offset);
}

void Bloque::escribirIdIzq(int unId) {
	int offset = calcularOffsetMetadatos() + 8;
	archivoArbol->escribirUnInt(unId, offset);
}

void Bloque::escribirIdDer(int unId) {
	int offset = calcularOffsetMetadatos() + 12;
	archivoArbol->escribirUnInt(unId, offset);
}

bool Bloque::entra(Registro* &unRegistro) {
	Nodo* unNodo = new Nodo(nombreArchivo, id);
	int tamanioRealRegistro = unRegistro->getTamanio();

	if (unRegistro->getTamanioDescripcion() > tamanio_max_descrinterna) {
		// Si long de descr es > que lo aceptado -> solo se grabara el offset del archivo de descrips (de 4bytes)
		tamanioRealRegistro = tamanioRealRegistro - unRegistro->getTamanioDescripcion() + 4;
	}

	if (unNodo->getTamanio() + tamanioRealRegistro > tamanio) {
		return false;
	}

	// Como entra, ya le asigno su ID
	int maxIdReg = archivoArbol->leerMayorIdReg();
	unRegistro->setId(maxIdReg);
	maxIdReg++;
	archivoArbol->escribirMaxIDReg(maxIdReg);

	return true;
}

void Bloque::grabar(Nodo* unNodo) {
	bytes_ocupados = tamanio_meta;
	int offset = calcularOffsetRegistros();
	list<Registro*>* registros = unNodo->getRegistros();
	Registro* unRegistro;

	for(list<Registro*>::iterator list_iter = registros->begin(); list_iter != registros->end(); list_iter++) {
		unRegistro = *list_iter;

		archivoArbol->escribirUnInt(unRegistro->getDescripcion().size(), offset);
		archivoArbol->escribirUnInt(unRegistro->getId(), offset);
		archivoArbol->escribirUnString(unRegistro->getCodigo(), offset);

		if ((unRegistro->getDescripcion()).size() > tamanio_max_descrinterna) {
			archivoArbol->escribirUnString("N", offset); //N = No contiene el dato
			bytes_ocupados += 4; // 4 = tam offset
			//TODO registros long variable
		} else {
			archivoArbol->escribirUnString("S", offset); //S = Si contiene el dato
			archivoArbol->escribirUnString(unRegistro->getDescripcion(), offset);
			bytes_ocupados += unRegistro->getDescripcion().size();
		}

		bytes_ocupados += 4; // Tam descr
		bytes_ocupados += 4; // ID
		bytes_ocupados += 3; // Codigo
		bytes_ocupados += 1; // Flag descr
	}

	escribirEspacioLibre();
}

Bloque::~Bloque() {

}

