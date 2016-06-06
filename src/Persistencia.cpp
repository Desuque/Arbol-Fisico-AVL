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
		escribirUnInt(0, 0);
		escribirUnInt(0, 4);
	} else {
		archivo.close();
	}
}

int Persistencia::leerMayorIdNodo() {
	int buffer;
	fstream archivo (nombreArchivo.c_str() , ios::in | ios::binary);

	if (archivo) {
		archivo.seekg (0, ios::beg);
		archivo.read ((char*)&buffer, tam_meta_id);
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
		archivo.seekg (tam_meta_id, ios::beg);
		archivo.read ((char*)&buffer, tam_meta_id);
		archivo.close();
	} else {
		buffer = 0;
	}


	return buffer;
}

Nodo* Persistencia::devolverNodo(int idNodo) {
	char* bloque = leerBloque(idNodo);
	Nodo* unNodo = armarNodo(bloque);

	return unNodo;
}

char* Persistencia::leerBloque(int idNodo) {
	char* unBloque = new char[tam_bloque];
	fstream archivo (nombreArchivo.c_str() , ios::in | ios::binary);

	if (archivo) {
		archivo.seekg (idNodo*tam_bloque);
		archivo.read (unBloque, tam_bloque);
		archivo.close();
	} else {
		unBloque[0] = 0;
	}


	return unBloque;
}


Nodo* Persistencia::armarNodo(char* unBloque) {
	int id;
	string codigo;
	string descr;

	if (unBloque[0] == 0) {
		return 0;
	} else {

		//Nodo* unNodo = new Nodo();
		// TODO: armar nodo

		//return unNodo;
	}

}

Nodo* Persistencia::crearNodo(Registro* unRegistro) {
	//TODO: Buscar algun bloque vacio en el mapa de bits o archivo de vacios

	// Creo el nuevo nodo e incremento el IDMAX
	int idNodo = leerMayorIdNodo();
	Nodo* unNodo = new Nodo(idNodo);
	idNodo++;
	escribirMaxIDNodo(idNodo);

	// Escribo en el arch
	escribirNodo(unNodo, unRegistro);

	return unNodo;
}

bool Persistencia::insertar(Nodo* unNodo, Registro* unRegistro) {
	Nodo* nodo = armarNodo(leerBloque(unNodo->getID()));
	int tamanioRealRegistro = unRegistro->getTamanio();

	if (unRegistro->getTamanioDescripcion() > maxCharDescr) {
		// Si long de descr es > que lo aceptado -> solo se grabara el offset del archivo de descrips (de 4bytes)
		tamanioRealRegistro = tamanioRealRegistro - unRegistro->getTamanioDescripcion() + 4;
	}

	if (unNodo->getTamanio() + tamanioRealRegistro > tam_bloque) {
		return false;
	}

	escribirNodo(unNodo, unRegistro);

	return true;
}

void Persistencia::escribirNodo(Nodo* unNodo, Registro* unRegistro) {
	unNodo->insertar(unRegistro);
	escribirMetadatosNodo(unNodo);
	escribirRegistro(unNodo, unRegistro);
}

int Persistencia::calcularOffsetRegistro(int idNodo) {
	return (idNodo*tam_bloque) + tam_meta_arbol + tam_meta_nodo;
}

int Persistencia::calcularOffsetNodo(int idNodo) {
	return (idNodo*tam_bloque) + tam_meta_arbol;
}

void Persistencia::escribirRegistro(Nodo* unNodo, Registro* unRegistro) {
	escribirMaxIDReg(unRegistro->getId());

	int offset = calcularOffsetRegistro(unNodo->getID());
	escribirUnInt(unRegistro->getId(), offset);
	offset += 4;
	escribirUnString(unRegistro->getCodigo(), offset);
	offset += 3; //El codigo es un string de 3 caracteres

	if ((unRegistro->getDescripcion()).size() > maxCharDescr) {
		escribirUnString("O", offset); //O = Offset
		offset += 1;
		//TODO registros long variable
	} else {
		//TODO siempre se mete de un registro, aca hay que ver que tanto hay ocupado del bloque
		//para ver si entra el nuevo registro que se quiere meter. En caso de entrar, se actualiza
		//el flag de proximo registro en el registro ya cargado, y se le pone F en el flag del nuevo
		//registro cargado.
		escribirUnString("F", offset); //F = fijo!
		offset += 1;
		escribirUnString(unRegistro->getDescripcion(), offset);
	}
}

void Persistencia::escribirUnString(string array, int unaPos) {
	fstream archivo;
	archivo.open(nombreArchivo.c_str(), ios::in | ios::out | ios::binary | ios::app );
	archivo.seekp(unaPos, ios::beg);
	archivo.write(array.c_str(), array.size());
	archivo.close();
}

void Persistencia::escribirUnInt(int unInt, int unaPos) {
	fstream archivo;
	archivo.open(nombreArchivo.c_str(), ios::in | ios::out | ios::binary );
	archivo.seekp(unaPos, ios::beg);
	archivo.write(reinterpret_cast<const char *>(&unInt), 4);
	archivo.close();
}

void Persistencia::escribirMaxIDNodo(int maxID) {
	escribirUnInt(maxID, 0);
}

void Persistencia::escribirMaxIDReg(int maxID) {
	escribirUnInt(maxID, tam_meta_id);
}

void Persistencia::inicializarNodo(int idNodo) {
	int offset = calcularOffsetNodo(idNodo);
	string vacio = string(4096, '.');
	fstream archivo;
	archivo.open(nombreArchivo.c_str(), ios::in | ios::out | ios::binary | ios::app );
	archivo.seekp(offset, ios::beg);
	archivo.write(vacio.c_str(), vacio.size());
	archivo.close();
}

void Persistencia::escribirMetadatosNodo(Nodo* unNodo) {
	//inicializarNodo(unNodo->getID());
	int offset = calcularOffsetNodo(unNodo->getID());
	escribirUnInt(unNodo->getID(), offset);
	offset += 4;
	int espacioLibre = tam_bloque - unNodo->getTamanio();
	escribirUnInt(espacioLibre, offset);
	offset += 4;

	if (unNodo->getHijoIzquierdo() != 0) {
		escribirUnInt((unNodo->getHijoIzquierdo())->getID(), offset);
	} else {
		escribirUnInt(0, offset);
	}
	offset += 4;
	if (unNodo->getHijoDerecho() != 0) {
		escribirUnInt((unNodo->getHijoDerecho())->getID(), offset);
	} else {
		escribirUnInt(0, offset);
	}
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
