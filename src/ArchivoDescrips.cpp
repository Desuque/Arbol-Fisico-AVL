
#include <iostream>
#include <stdio.h>
#include <string.h>
#include "ArchivoDescrips.h"


using namespace std;

ArchivoDescrips::ArchivoDescrips(string nombre) {
	this->nombre = nombre + "_descrips.bin";
	//TODO: inicializarArchivo();
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
	archivo.close();
	cout<<"c_desc"<<c_descrip<<endl;

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
