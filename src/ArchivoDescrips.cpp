
#include <iostream>
#include <stdio.h>
#include <string.h>
#include "ArchivoDescrips.h"


using namespace std;

ArchivoDescrips::ArchivoDescrips(string nombre) {
	this->nombre = nombre + "_descrips.bin";
	//TODO: inicializarArchivo();
}

/** Devuelve el offset en el que esta posicionado el cursor actualmente en el archivo.
 * Se utiliza para obtener la posicion final del cursor luego de escribir una descripcion
 * en un espacio libre. De esta manera se puede actualizar el offset en el archivo de libres.
 */
int ArchivoDescrips::getOffsetLibre() {
	return offsetLibre;
}

bool ArchivoDescrips::existeDescripcion(string descripcion, int offset) {
	string descrip = leerBloque(offset, descripcion.size());

	if (descrip == descripcion) {
		return true;
	}

	return false;
}

void ArchivoDescrips::escribirNull(int offset, int tamanio) {
	char buffer[tamanio];
	std::fill(buffer, buffer + tamanio, '\0');

	fstream archivo;
	archivo.open(nombre.c_str(), ios::in | ios::out | ios::binary );
	archivo.seekp(offset, ios::beg);
	archivo.write(buffer, sizeof(char) * tamanio);
	archivo.close();
}

void ArchivoDescrips::eliminarDescripcion(int offset, int tamanio) {
	escribirNull(offset, tamanio);

	string nombreSinBin = nombre;
	nombreSinBin.resize((nombreSinBin.size())-4);

	archivoLibres = new ArchivoLibres(nombreSinBin);
	archivoLibres->grabarEspacioLibre(offset, tamanio);
	delete archivoLibres;
}

string ArchivoDescrips::leerBloque(int offset, int tamanio_descripcion) {
	char* unBloque = new char[tamanio_descripcion];
	fstream archivo (nombre.c_str() , ios::in | ios::binary);

	archivo.seekg (offset);
	archivo.read (unBloque, tamanio_descripcion);

	string bloque = string(unBloque);
	archivo.close();

	return bloque;
}

int ArchivoDescrips::grabarEnEspacioLibre(string descripcion, int offset_libre) {
	fstream archivo;
	archivo.open(this->nombre.c_str(), ios::in | ios::out | ios::binary );

	//Posicion donde arranca la descripcion
	archivo.seekp (offset_libre, archivo.beg);

	char c_descrip[descripcion.size()];
	strcpy(c_descrip, descripcion.c_str());
	archivo.write(c_descrip, descripcion.size());

	this->offsetLibre = archivo.tellp();
	archivo.close();

	return offset_libre;   //Asi lo guardo en el archivo del arbol

}

int ArchivoDescrips::grabar(string descripcion) {
	fstream archivo;
	archivo.open(this->nombre.c_str(), ios::in | ios::out | ios::binary | ios::app );

	//Posicion donde arranca la descripcion
	archivo.seekg (0, archivo.end);
	int offset = archivo.tellg();

	char c_descrip[descripcion.size()];
	strcpy(c_descrip, descripcion.c_str());
	archivo.write(c_descrip, descripcion.size());

	return offset;   //Asi lo guardo en el archivo del arbol
}

ArchivoDescrips::~ArchivoDescrips() {

}
