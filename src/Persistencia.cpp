/*
 * Persistencia.cpp
 *
 */
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "Persistencia.h"
#include "Registro.h"

using namespace std;

Persistencia::Persistencia(string nombreArchivo) {
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

void Persistencia::crearArchivoVacio() {
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

char* Persistencia::leerBloque(int idNodo) {
	char* unBloque = new char[tam_bloque];
	fstream archivo (nombreArchivo.c_str() , ios::in | ios::binary);

	if (archivo) {
		archivo.seekg ((idNodo * tam_bloque) + tam_meta_arbol);
		archivo.read (unBloque, tam_bloque);
		archivo.close();
	} else {
		unBloque[0] = 'E';
	}


	return unBloque;
}


int Persistencia::leerMayorIdNodo() {
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

int Persistencia::leerMayorIdReg() {
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

int Persistencia::getTamanioMetadatos() {
	return tam_meta_arbol;
}

int Persistencia::calcularOffsetRegistro(int idNodo) {
	return (idNodo*tam_bloque) + tam_meta_arbol + tam_meta_nodo;
}

void Persistencia::escribirUnString(string array, int &unaPos) {
	fstream archivo;
	archivo.open(nombreArchivo.c_str(), ios::in | ios::out | ios::binary );
	archivo.seekp(unaPos, ios::beg);
	archivo.write(array.c_str(), array.size());
	archivo.close();

	unaPos += array.size();
}

void Persistencia::escribirUnInt(int unInt, int &unaPos) {
	fstream archivo;
	archivo.open(nombreArchivo.c_str(), ios::in | ios::out | ios::binary );
	archivo.seekp(unaPos, ios::beg);
	archivo.write(reinterpret_cast<const char *>(&unInt), 4);
	archivo.close();

	unaPos += 4;
}

void Persistencia::escribirMaxIDNodo(int maxID) {
	int i = 0;
	escribirUnInt(maxID, i);
}

void Persistencia::escribirMaxIDReg(int maxID) {
	int i = 4;
	escribirUnInt(maxID, i);
}

void Persistencia::grabarRegistroLongFija(Registro* unRegistro, int idNodo, int padding) {
	string flagDeTipo = "F";
	strcpy (buff_flagDeTipo, flagDeTipo.c_str());

	string codigo = unRegistro->getCodigo();
	ostringstream codigo_padding; //Relleno los espacios para mantener el bloque
	codigo_padding<<setfill('0')<<setw(tam_codigo);
	codigo_padding<<codigo;
	codigo = codigo_padding.str();
	strcpy (buff_codigo, (codigo).c_str());

	int tam_descrip = unRegistro->getTamanioDescripcion();
	string s_tam_desc; //Convierto el tamanio de la descripcion a string
	stringstream convert;
	convert << tam_descrip;
	s_tam_desc = convert.str();
	ostringstream tam_descrip_padding; //Relleno los espacios para mantener el bloque
	tam_descrip_padding<<setfill('0')<<setw(tam_descripcion);
	tam_descrip_padding<<s_tam_desc;
	s_tam_desc = tam_descrip_padding.str();
	strcpy(buff_tam_descripcion, (s_tam_desc).c_str());

	//Pido memoria segun la longitud de la descripcion
	buff_descripcion = new char [unRegistro->getTamanioDescripcion()];
	strcpy (buff_descripcion, (unRegistro->getDescripcion()).c_str());

	strcpy (buff_hijoIzquierdo, "V");
	strcpy (buff_hijoDerecho, "V");
	strcpy (buff_flagExisteRegistro, "0");

	//Creo el bloque
	strcat (buff_bloque, buff_flagDeTipo);
	strcat (buff_bloque, buff_codigo);
	strcat (buff_bloque, buff_tam_descripcion);
	strcat (buff_bloque, buff_descripcion);
	strcat (buff_bloque, buff_hijoIzquierdo);
	strcat (buff_bloque, buff_hijoDerecho);
	strcat (buff_bloque, buff_flagExisteRegistro);

	for(int i=0; i<tam_bloque; i++) {
		cout<<buff_bloque[i];
	}
	//escribir(buff_bloque, idNodo, tam_bloque, 4);

}
