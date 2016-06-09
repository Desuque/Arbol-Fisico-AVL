/*
 * Nodo.cpp
 *
 *  Created on: 26 de may. de 2016
 *      Author: desuque
 */

#include "Bloque.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
#include<sstream>

using namespace std;

// ---------------    Bloque    -------------------------------
//     [1b]         [4b]      [4b]     [4b]
// Flag Existe - Esp Libre - Id Izq - Id Der - Registros
// ---------------    Registro    -------------------------------
//     [4b]     [4b]     [3b]       [1b]          [xb]
// Tam Descr - Id Reg - Codigo - Flag Descr - Descripcion (u offset)




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
int Bloque::getId() {
	return this->id;
}
// ------------------------------------------------------------------------
// Parsea todo el bloque y devuelve el nodo correspondiente
Nodo* Bloque::devolverNodo() {
	char* charBloq = archivoArbol->leerBloque(id);

	if (charBloq[0] != 'E') {
		return 0;
	} else {
		int tamDescr;
		int offsetDescr;
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
			codReg[3] = '\0';
			offset += 3;
			copy(charBloq + offset, charBloq + offset + 1, flagDescr);
			offset += 1;
			if (flagDescr[0] == 'S') {
				descrReg = new char [tamDescr+1];
				copy(charBloq + offset, charBloq + offset + tamDescr, descrReg);
				descrReg[tamDescr] = '\0';
				offset += tamDescr;
			} else if (flagDescr[0] == 'N') {
				descrReg = new char [tamDescr+1];
				offsetDescr = *(reinterpret_cast<int *>(charBloq + offset));
				archivoDescripciones = new ArchivoDescrips(nombreArchivo);
				string desc = archivoDescripciones->leerBloque(offsetDescr, tamDescr);
				strcpy(descrReg, desc.c_str());
				descrReg[tamDescr] = '\0';
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

	return true;
}
// ------------------------------------------------------------------------
// Ya sabiendo que entra, reescribe toodo el nodo. Haciendo update de los metadatos necesarios
void Bloque::grabar(Nodo* unNodo) {
	bytes_ocupados = tamanio_meta;
	cantidad_registros = 0;
	int maxIdReg = archivoArbol->leerMayorIdReg();
	int offset = calcularOffsetRegistros();
	list<Registro*>* registros = unNodo->getRegistros();
	Registro* unRegistro;

	for(list<Registro*>::iterator list_iter = registros->begin(); list_iter != registros->end(); list_iter++) {
		unRegistro = *list_iter;

		archivoArbol->escribirUnInt(unRegistro->getDescripcion().size(), offset);
		archivoArbol->escribirUnInt(unRegistro->getId(), offset);
		archivoArbol->escribirUnString(unRegistro->getCodigo(), offset);

		if ((unRegistro->getDescripcion()).size() > tamanio_max_descrinterna) {
			archivoLibres = new ArchivoLibres(nombreArchivo+"_descrips");
			archivoDescripciones = new ArchivoDescrips(nombreArchivo);

			// BETA
			/** CREO ESPACIO LIBRE PARA TESTEAR
			* NADA, ESO.
			* TOMATELA'TE DIJE
			*/

			/**ACLARACION: Es necesario que realmente haya espacio libre y no que el archivo se va a crear gracias a esta accion
			 * si esa zona del archivo no esta definida esto no va a grabar nada, porque no inventa espacio, ocupa el espacio
			 * no ocupado. Si se testea, previamente tiene que existir el archivo de descripciones, y el espacio realmente debe estar
			 * vacio (o escrito, en su defecto, ya que es una prueba) para que funcione.
			 */
			archivoLibres->grabarEspacioLibre(3500,2000);
			// BETA
			/** CREO ESPACIO LIBRE PARA TESTEAR
			* NADA, ESO.
			* TOMATELA'TE DIJE
			*/

			//Si el archivo de libres no tiene espacio o no existe, grabo la descripcion al final del archivo de descripciones
			if (!archivoLibres->hayEspacio((unRegistro->getDescripcion()).size())) {
				int offsetArchivoDescrips = archivoDescripciones->grabar(unRegistro->getDescripcion());
				archivoArbol->escribirUnString("N", offset); //N = No contiene el dato
				//Escribo la posicion del archivoDescrips en el archivoArbol
				archivoArbol->escribirUnInt(offsetArchivoDescrips, offset);

			//Si el archivo de libres encuentra espacio libre en el archivo de descripciones, utilizo ese espacio para almacenar la descripcion
			} else {
				int offsetArchivoDescrips = archivoDescripciones->grabarEnEspacioLibre(unRegistro->getDescripcion(), archivoLibres->getOffset());
				archivoArbol->escribirUnString("N", offset); //N = No contiene el dato
				//Escribo la posicion del archivoDescrips en el archivoArbol
				archivoArbol->escribirUnInt(offsetArchivoDescrips, offset);

			}
			bytes_ocupados += 4; // 4 = tam offset
			delete archivoLibres;
			delete archivoDescripciones;

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

		if (unRegistro->getId() > maxIdReg) {
			maxIdReg = unRegistro->getId();
		}
	}

	archivoArbol->escribirMaxIDReg(maxIdReg);
	escribirIdIzq(unNodo->getHijoIzquierdo());
	escribirIdDer(unNodo->getHijoDerecho());
	escribirEspacioLibre();
	escribirCantidadRegistros();
}

int Bloque::getMaxIdReg() {
	return archivoArbol->leerMayorIdReg();
}

Bloque::~Bloque() {

}
