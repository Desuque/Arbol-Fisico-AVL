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
#include <sstream>
#include <stdlib.h>
#include <stdlib.h>

using namespace std;

// ---------------    Bloque    -------------------------------
//     [1b]         [4b]      [4b]      [4b]       [4b]    [4b]      =  17b de tamanio_meta
// Flag Existe - Esp Libre - Altura - Cant Regs - Id Izq - Id Der - Registros
// ---------------    Registro    -------------------------------
//     [4b]     [4b]     [3b]       [1b]          [xb]
// Tam Descr - Id Reg - Codigo - Flag Descr - Descripcion (u offset)

// ------------------------------------------------------------------------
// Si es construido solo con el nombre de archivo -> ya escribe el bloque en el archivo
Bloque::Bloque(string nombreArchivo) {
	this->nombreArchivo = nombreArchivo;
	this->archivoArbol = new Archivo(nombreArchivo);
	this->tamanio = setearTamanioBloque();
	inicializarBloque();
}
// ------------------------------------------------------------------------
// Si es construido solo con el nombre de archivo y id -> asume que ya tiene el bloque escrito en disco
Bloque::Bloque(string nombreArchivo, int id) {
	this->nombreArchivo = nombreArchivo;
	this->archivoArbol = new Archivo(nombreArchivo);
	this->tamanio = setearTamanioBloque();
	this->id = id;
}

int Bloque::setearTamanioBloque() {
	return archivoArbol->leerTamanioBloque();
}

int Bloque::getId() {
	return this->id;
}

// ------------------------------------------------------------------------
// Parsea todo el bloque y devuelve el nodo correspondiente
Nodo* Bloque::devolverNodo() {
	char* charBloq = archivoArbol->leerBloque(id, tamanio);

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
		int altura = *(reinterpret_cast<int *>(charBloq + offset));
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
		}

		unNodo->setHijoIzquierdo(idIzq);
		unNodo->setHijoDerecho(idDer);
		unNodo->setAltura(altura);

		return unNodo;
	}
}
// ------------------------------------------------------------------------
// Escribe el bloque entero en el archivo (con sus metadatos correspondientes)
void Bloque::inicializarBloque() {
	archivoLibres = new ArchivoLibres(nombreArchivo);

	if (archivoLibres->hayEspacio(tamanio)) {
		int idBloqueLibre = ((archivoLibres->getOffset()) / (tamanio + archivoArbol->getTamanioMetadatos()));
		this->id = idBloqueLibre;
		archivoLibres->actualizarEspacioLibre(0,0);
	} else {
		this->id = archivoArbol->leerMayorIdNodo();
		archivoArbol->escribirMaxIDNodo(id + 1);
	}

	escribirBloqueVacio();
	bytes_ocupados = tamanio_meta;
	cantidad_registros = 0;
	escribirMetaDatos(-1, -1, -1);

	delete archivoLibres;
}

void Bloque::escribirBloqueVacio() {
	int offset = calcularOffsetMetadatos();
	archivoArbol->escribirNull(offset, tamanio);
}

void Bloque::escribirMetaDatos(int idIzq, int idDer, int altura) {
	escribirFlagExistencia();
	escribirEspacioLibre();
	escribirAltura(altura);
	escribirCantidadRegistros();
	escribirIdIzq(idIzq);
	escribirIdDer(idDer);
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
// Escribe el metadato altura en su lugar correspondiente
void Bloque::escribirAltura(int altura) {
	int offset = calcularOffsetMetadatos() + 5;
	archivoArbol->escribirUnInt(altura, offset);
}
// ------------------------------------------------------------------------
// Escribe el metadato de cuantos registros tiene el nodo en el bloque
void Bloque::escribirCantidadRegistros() {
	int offset = calcularOffsetMetadatos() + 9;
	archivoArbol->escribirUnInt(cantidad_registros, offset);
}
// ------------------------------------------------------------------------
// Escribe el id del bloque izq
void Bloque::escribirIdIzq(int unId) {
	int offset = calcularOffsetMetadatos() + 13;
	archivoArbol->escribirUnInt(unId, offset);
}
// ------------------------------------------------------------------------
// Escribe el id del bloque der
void Bloque::escribirIdDer(int unId) {
	int offset = calcularOffsetMetadatos() + 17;
	archivoArbol->escribirUnInt(unId, offset);
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
// Calcula si entra el nuevo registro en cuestion el el bloque
bool Bloque::entra(Registro* &unRegistro) {
	Nodo* unNodo = new Nodo(nombreArchivo, id);
	int tamanioRealRegistro = unRegistro->getTamanio();

	if (unRegistro->getTamanioDescripcion() > tamanio_max_descrinterna) {
		// Si long de descr es > que lo aceptado -> solo se grabara el offset del archivo de descrips (de 4bytes)
		tamanioRealRegistro = tamanioRealRegistro - unRegistro->getTamanioDescripcion() + 4;
	}

	//cout<<unNodo->getTamanio()+ tamanioRealRegistro + tamanio_meta<<endl;
	//cout<<tamanioRealRegistro<<endl;

	if (unNodo->getTamanio() + tamanioRealRegistro + tamanio_meta > tamanio) {
		return false;
	}

	return true;
}

void Bloque::borrarDescripcionArchivoDescrips(int idRegistro) {
	char* charBloq = archivoArbol->leerBloque(id, tamanio);

	int tamDescr;
	int offsetDescr;
	int idReg;
	char codReg [4];
	char* descrReg;
	char flagDescr [1];

	// ---------------    Bloque    -------------------------------
	//     [1b]         [4b]      [4b]      [4b]       [4b]    [4b]      =  17b de tamanio_meta
	// Flag Existe - Esp Libre - Altura - Cant Regs - Id Izq - Id Der - Registros
	// ---------------    Registro    -------------------------------
	//     [4b]     [4b]     [3b]       [1b]          [xb]
	// Tam Descr - Id Reg - Codigo - Flag Descr - Descripcion (u offset)


	int offset = 0;
	offset += 1; //Flag existe
	int espLibre = *(reinterpret_cast<int *>(charBloq + offset));
	offset += 4; //Esp libre
	int altura = *(reinterpret_cast<int *>(charBloq + offset));
	offset += 4; //Altura
	int cantRegs = *(reinterpret_cast<int *>(charBloq + offset));
	offset += 4; //Cant Regs
	int idIzq = *(reinterpret_cast<int *>(charBloq + offset));
	offset += 4; //Id Izq
	int idDer = *(reinterpret_cast<int *>(charBloq + offset));
	offset += 4; //Id Der
	// Registros
	for (int i = 0; i < cantRegs; i++) {
		tamDescr = *(reinterpret_cast<int *>(charBloq + offset));
		offset += 4; //Tam descrip
		idReg = *(reinterpret_cast<int *>(charBloq + offset));
		offset += 4; //Id Reg
		copy(charBloq + offset, charBloq + offset + 3, codReg);
		codReg[3] = '\0';
		offset += 3; //Codigo
		copy(charBloq + offset, charBloq + offset + 1, flagDescr);
		offset += 1; //Flag Descr

		descrReg = new char [tamDescr+1]; //Descripcion
		offsetDescr = *(reinterpret_cast<int *>(charBloq + offset));

		if (idReg == idRegistro) {
			archivoDescripciones = new ArchivoDescrips(nombreArchivo);
			archivoDescripciones->eliminarDescripcion(offsetDescr, tamDescr);
			break;
		}
		if (flagDescr[0] == 'S') {
			offset += tamDescr;
		} else {
			offset += 4;
		}
	}
}

void Bloque::persistirRegistros(Nodo* unNodo, int &maxIdReg) {
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

			archivoLibres = new ArchivoLibres(nombreArchivo+"_descrips");
			archivoDescripciones = new ArchivoDescrips(nombreArchivo);
			cout<<"entre";
			//int offsetSinAvanzar = offset;
			//Obtengo el offset de la descripcion larga
			int offsetArchivoDescrips = atoi(archivoArbol->leerPorcionBloque(id, offset+1, 4, tamanio));
			//offset = offsetSinAvanzar;

			if (archivoDescripciones->existeDescripcion(unRegistro->getDescripcion(), offsetArchivoDescrips)) {
				archivoArbol->escribirUnString("N", offset); //N = No contiene el dato
				//Escribo la posicion del archivoDescrips en el archivoArbol
				archivoArbol->escribirUnInt(offsetArchivoDescrips, offset);
			} else {
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

					//Actualizo el offset y el espacioLibre en el archivo de libres
					int nuevoEspacioLibre = archivoLibres->getEspacioLibre() - unRegistro->getDescripcion().size();
					//archivoLibres->actualizarEspacioLibre(archivoDescripciones->getOffsetLibre(), nuevoEspacioLibre);
					archivoLibres->grabarEspacioLibre(archivoLibres->getOffset(), nuevoEspacioLibre);
				}
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
}


// ------------------------------------------------------------------------
// Ya sabiendo que entra, reescribe toodo el nodo. Haciendo update de los metadatos necesarios
void Bloque::grabar(Nodo* unNodo) {
	int maxIdReg = archivoArbol->leerMayorIdReg();
	escribirBloqueVacio();

	if (unNodo->getCantidadDeRegistros() != 0) {
		persistirRegistros(unNodo, maxIdReg);
		archivoArbol->escribirMaxIDReg(maxIdReg);
		escribirMetaDatos(unNodo->getHijoIzquierdo(), unNodo->getHijoDerecho(), unNodo->getAltura());
	} else {
		/**
		 * Escribo espacio libre de bloque
		 */
		archivoLibres = new ArchivoLibres(nombreArchivo);
		int offset = calcularOffsetMetadatos();
		int espacioLibre = tamanio;
		//Grabo archivo de libres
		archivoLibres->grabarEspacioLibre(offset, espacioLibre);
		//Libero espacio en el archivo de bloques
		archivoArbol->escribirNull(offset, espacioLibre);

		delete archivoLibres;
	}
}

int Bloque::getMaxIdReg() {
	return archivoArbol->leerMayorIdReg();
}

bool Bloque::estaEnUnderflow(Nodo* unNodo) {
	bytes_ocupados = tamanio_meta;
	list<Registro*>* registros = unNodo->getRegistros();
	Registro* unRegistro;

	for(list<Registro*>::iterator list_iter = registros->begin(); list_iter != registros->end(); list_iter++) {
		unRegistro = *list_iter;
		if ((unRegistro->getDescripcion()).size() > tamanio_max_descrinterna) {
			bytes_ocupados += 4; // 4 = tam offset
		} else {
			bytes_ocupados += unRegistro->getDescripcion().size();
		}
		bytes_ocupados += 4; // Tam descr
		bytes_ocupados += 4; // ID
		bytes_ocupados += 3; // Codigo
		bytes_ocupados += 1; // Flag descr
	}

	if (bytes_ocupados < (tamanio / 2)) {
		return true;
	} else {
		return false;
	}

}

Bloque::~Bloque() {

}
