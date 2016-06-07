/*
 * Nodo.cpp
 *
 *  Created on: 26 de may. de 2016
 *      Author: desuque
 */

#include "Bloque.h"

using namespace std;

// ------------------------------------------------------------------------
// Si es construido solo con el nombre de archivo -> ya escribe el bloque en el archivo
Bloque::Bloque(string nombreArchivo) {
	this->nombreArchivo = nombreArchivo;
	this->archivoArbol = new Persistencia(nombreArchivo);
	this->id = archivoArbol->leerMayorIdNodo();

	inicializarBloque();
}
// ------------------------------------------------------------------------
// Si es construido solo con el nombre de archivo y id -> asume que ya tiene el bloque escrito en disco
Bloque::Bloque(string nombreArchivo, int id) {
	this->nombreArchivo = nombreArchivo;
	this->archivoArbol = new Persistencia(nombreArchivo);
	this->id = id;
}
// ------------------------------------------------------------------------
// Parsea todo el bloque y devuelve el nodo correspondiente
Nodo* Bloque::devolverNodo() {
	char* charBloq = archivoArbol->leerBloque(id);

	if (charBloq[0] != 'E') {
		return 0;
	} else {
		int tamDescr;
		int idReg;
		char codReg [4];
		char* descrReg;
		char flagDescr [1];
		Registro* unRegistro;
		Nodo* unNodo = new Nodo(nombreArchivo);

		int offset = 0;
		offset += 1;
		int espLibre = *(reinterpret_cast<int *>(charBloq + offset));
		offset += 4;
		int cantRegs = *(reinterpret_cast<int *>(charBloq + offset));
		offset += 4;
		int idIzq = *(reinterpret_cast<int *>(charBloq + offset));
		offset += 4;
		int idDer = *(reinterpret_cast<int *>(charBloq + offset));
		offset += 4;
		// Registros
		for (int i = 0; i < cantRegs; i++) {
			tamDescr = *(reinterpret_cast<int *>(charBloq + offset));
			offset += 4;
			idReg = *(reinterpret_cast<int *>(charBloq + offset));
			offset += 4;
			copy(charBloq + offset, charBloq + offset + 3, codReg);
			codReg[4] = '\0';
			offset += 3;
			copy(charBloq + offset, charBloq + offset + 1, flagDescr);
			offset += 1;
			if (flagDescr[0] = 'S') {
				descrReg = new char [tamDescr+1];
				copy(charBloq + offset, charBloq + offset + tamDescr, descrReg);
				descrReg[tamDescr] = '\0';
				offset += tamDescr;
			} else {
				// TODO: Leer del arch de libres
				offset += 4;
			}
			unRegistro = new Registro(string(codReg), string(descrReg));
			unRegistro->setId(idReg);
			unNodo->getRegistros()->push_back(unRegistro);
			delete descrReg;
		}

		return unNodo;
	}
}
// ------------------------------------------------------------------------
// Escribe el bloque entero en el archivo (con sus metadatos correspondientes)
void Bloque::inicializarBloque() {
	// TODO: Escribir los 4kb vacios
	archivoArbol->escribirMaxIDNodo(id + 1);
	escribirFlagExistencia();
	bytes_ocupados = tamanio_meta;
	escribirEspacioLibre();
	cantidad_registros = 0;
	escribirCantidadRegistros();
}
// ------------------------------------------------------------------------
// Escribe la "E" de que el bloque existe
void Bloque::escribirFlagExistencia() {
	int offset = calcularOffsetMetadatos();
	archivoArbol->escribirUnString("E", offset);
}
// ------------------------------------------------------------------------
// Escribe el metadato de espaciolibre en su lugar correspondiente
void Bloque::escribirEspacioLibre() {
	int offset = calcularOffsetMetadatos() + 1;
	int espacioLibre = tamanio - bytes_ocupados;
	archivoArbol->escribirUnInt(espacioLibre, offset);
}
// ------------------------------------------------------------------------
// Escribe el metadato de cuantos registros tiene el nodo en el bloque
void Bloque::escribirCantidadRegistros() {
	int offset = calcularOffsetMetadatos() + 5;
	archivoArbol->escribirUnInt(cantidad_registros, offset);
}
// ------------------------------------------------------------------------
// Determina a partir de que offset se empiezan a escribir los metadatos del bloque
int Bloque::calcularOffsetMetadatos() {
	return (id * tamanio) + archivoArbol->getTamanioMetadatos();
}
// ------------------------------------------------------------------------
// Determina a partir de que offset se empiezan a escribir los registros del bloque
int Bloque::calcularOffsetRegistros() {
	return (id * tamanio) + archivoArbol->getTamanioMetadatos() + tamanio_meta;
}
// ------------------------------------------------------------------------
// Escribe el id del bloque izq
void Bloque::escribirIdIzq(int unId) {
	int offset = calcularOffsetMetadatos() + 8;
	archivoArbol->escribirUnInt(unId, offset);
}
// ------------------------------------------------------------------------
// Escribe el id del bloque der
void Bloque::escribirIdDer(int unId) {
	int offset = calcularOffsetMetadatos() + 12;
	archivoArbol->escribirUnInt(unId, offset);
}
// ------------------------------------------------------------------------
// Calcula si entra el nuevo registro en cuestion el el bloque
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
// ------------------------------------------------------------------------
// Ya sabiendo que entra, reescribe toodo el nodo. Haciendo update de los metadatos necesarios
void Bloque::grabar(Nodo* unNodo) {
	bytes_ocupados = tamanio_meta;
	cantidad_registros = 0;
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
		cantidad_registros++;
	}

	escribirEspacioLibre();
	escribirCantidadRegistros();
}

Bloque::~Bloque() {

}
