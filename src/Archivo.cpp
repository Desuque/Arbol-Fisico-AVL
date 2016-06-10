/*
 * Archivo.cpp
 *
 */
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

#include "Archivo.h"
#include "Registro.h"

using namespace std;

Archivo::Archivo(string nombreArchivo) {
	buff_bloque = new char[tam_bloque];
	buff_flagDeTipo = new char[tam_flagDeTipo];
	buff_codigo = new char[tam_codigo];
	buff_tam_descripcion = new char[tam_descripcion];
	buff_flagExisteRegistro = new char[tam_flagExisteRegistro];
	buff_hijoIzquierdo = new char[tam_hijoIzquierdo];
	buff_hijoDerecho = new char[tam_hijoDerecho];

	this->nombreArchivo = nombreArchivo + ".bin";
	crearArchivoVacio();
}

void Archivo::crearArchivoVacio() {
	fstream archivo (nombreArchivo.c_str() , ios::in | ios::binary);
	if (!archivo) {
		archivo.open(nombreArchivo.c_str() , ios::out | ios::binary);
		// FIX: Escribo los metadatos iniciales en 0
		int i = 0;
		escribirUnInt(0, i);
		escribirUnInt(0, i);
	} else {
		archivo.close();
	}
}

int Archivo::getOffsetInicioBloque() {
	return offsetInicioBloque;
}

char* Archivo::leerBloque(int idNodo) {
	char* unBloque = new char[tam_bloque];
	fstream archivo (nombreArchivo.c_str() , ios::in | ios::binary);

	if (archivo) {
		archivo.seekg ((idNodo * tam_bloque) + tam_meta_arbol);
		this->offsetInicioBloque = archivo.tellp();
		archivo.read (unBloque, tam_bloque);
		archivo.close();
	} else {
		unBloque[0] = 'E';
	}


	return unBloque;
}


int Archivo::leerMayorIdNodo() {
	int buffer;
	fstream archivo (nombreArchivo.c_str() , ios::in | ios::binary);

	if (archivo) {
		archivo.seekg (0, ios::beg);
		archivo.read ((char*)&buffer, 4);
		archivo.close();
	} else {
		buffer = 0;
	}


	return buffer;
}

int Archivo::leerMayorIdReg() {
	int buffer;
	fstream archivo (nombreArchivo.c_str() , ios::in | ios::binary);

	if (archivo) {
		archivo.seekg (4, ios::beg);
		archivo.read ((char*)&buffer, 4);
		archivo.close();
	} else {
		buffer = 0;
	}


	return buffer;
}

int Archivo::getTamanioMetadatos() {
	return tam_meta_arbol;
}

int Archivo::calcularOffsetRegistro(int idNodo) {
	return (idNodo*tam_bloque) + tam_meta_arbol + tam_meta_nodo;
}

void Archivo::escribirUnString(string array, int &unaPos) {
	fstream archivo;
	archivo.open(nombreArchivo.c_str(), ios::in | ios::out | ios::binary );
	archivo.seekp(unaPos, ios::beg);
	archivo.write(array.c_str(), array.size());
	archivo.close();

	unaPos += array.size();
}

void Archivo::escribirUnInt(int unInt, int &unaPos) {
	fstream archivo;
	archivo.open(nombreArchivo.c_str(), ios::in | ios::out | ios::binary );
	archivo.seekp(unaPos, ios::beg);
	archivo.write(reinterpret_cast<const char *>(&unInt), 4);
	archivo.close();

	unaPos += 4;
}

void Archivo::escribirNull(int offset, int tamanio) {
	char buffer[tamanio];
	std::fill(buffer, buffer + tamanio, '\0');

	fstream archivo;
	archivo.open(nombreArchivo.c_str(), ios::in | ios::out | ios::binary );
	archivo.seekp(offset, ios::beg);
	archivo.write(buffer, sizeof(char) * tamanio);
	archivo.close();
}

void Archivo::escribirMaxIDNodo(int maxID) {
	int i = 0;
	escribirUnInt(maxID, i);
}

void Archivo::escribirMaxIDReg(int maxID) {
	int i = 4;
	escribirUnInt(maxID, i);
}
