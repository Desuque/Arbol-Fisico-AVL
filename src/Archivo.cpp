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
	this->nombreArchivo = nombreArchivo + ".bin";
	verificarArchivo();
}

void Archivo::verificarArchivo() {
	fstream archivo (nombreArchivo.c_str() , ios::in | ios::binary);
	if (!archivo) {
		archivo.open(nombreArchivo.c_str() , ios::out | ios::binary);
		escribirNull(0, tam_meta_arbol);
		escribirMaxIDReg(-1);
		pedirTamanioBloque();
		archivo.close();
	} else {
		archivo.close();
	}
}

void Archivo::pedirTamanioBloque() {
	string input = "";
	int myNumber = 0;
	int offset = 8;

	while (true) {
	  cout << "Por favor ingrese el tamanio del bloque: ";
	  cout << "En bytes (Min: 8. Max: 2.147.483.647)";
	  getline(cin, input);

	  stringstream myStream(input);
	  if (myStream >> myNumber) {
		  if ((myNumber >= 8) && (myNumber <= 2147483647)) {
			  escribirUnInt(myNumber, offset);
			  break;
		  }
	  }
	  cout << "Numero invalido, por favor vuelva a intentar" << endl;
	}

}

char* Archivo::leerBloque(int idNodo, int tamBloque) {
	char* unBloque = new char[tamBloque];
	fstream archivo (nombreArchivo.c_str() , ios::in | ios::binary);

	if (archivo) {
		archivo.seekg ((idNodo * tamBloque) + tam_meta_arbol);
		this->offsetInicioBloque = archivo.tellp();
		archivo.read (unBloque, tamBloque);
		archivo.close();
	} else {
		unBloque[0] = 'E';
	}


	return unBloque;
}

char* Archivo::leerPorcionBloque(int idNodo, int offset, int tamanio, int tamBloque) {
	cout<<"entre";
	char* porcionBloque = new char[tamanio];
	fstream archivo (nombreArchivo.c_str() , ios::in | ios::binary);

	archivo.seekg ((idNodo * tamBloque) + tam_meta_arbol + offset);
	archivo.read (porcionBloque, tamanio);
	archivo.close();

	return porcionBloque;
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

int Archivo::leerTamanioBloque() {
	int buffer;
	fstream archivo (nombreArchivo.c_str() , ios::in | ios::binary);

	if (archivo) {
		archivo.seekg (8, ios::beg);
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

Archivo::~Archivo() {
	// TODO Auto-generated destructor stub
}
