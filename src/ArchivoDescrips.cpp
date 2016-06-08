
#include <iostream>
#include <stdio.h>
#include <string.h>
#include "ArchivoDescrips.h"


using namespace std;

ArchivoDescrips::ArchivoDescrips(string nombre) {
	this->nombre = nombre + "_descrips.bin";
	//TODO: inicializarArchivo();
}

char* ArchivoDescrips::leerBloque(int offset, int tamanio_descripcion) {
	char* unBloque = new char[tamanio_descripcion];
	fstream archivo (nombre.c_str() , ios::in | ios::binary);

	archivo.seekg (offset);
	archivo.read (unBloque, tamanio_descripcion);
	archivo.close();

	return unBloque;
}

int ArchivoDescrips::grabar(string descripcion) {
	fstream archivo;
	archivo.open(this->nombre.c_str(), ios::in | ios::out | ios::binary | ios::app );

	  /** TODO hacer archivo de libres
	  ArchivoLibres* archivoLibres = new ArchivoLibres("descripciones");
	  int offset = archivoLibres.buscarEspacioLibre(descripcion.size());

	  if (offset >= 0) {
	 		archivo.seekp(offsetLibre, ios::beg);
	  } else {
	  		archivo.seekp( 0,  ios::end );
	  		offset = ver como obtener el offset;
	  }
	**/

	//Posicion donde arranca la descripcion
	archivo.seekg (0, archivo.end);
	int offset = archivo.tellg();
	cout<<"lengtg:"<<offset<<endl;

	char c_descrip[descripcion.size()];
	strcpy(c_descrip, descripcion.c_str());
	archivo.write(c_descrip, descripcion.size());

	cout<<"beta"<<endl;
	char* unBloque = leerBloque(offset, descripcion.size());
	for(int i=0; i<descripcion.size(); i++) {
		cout<<unBloque[i];
	}

	return offset;   //Asi lo guardo en el archivo del arbol
}

string ArchivoDescrips::leer(int offset, int tamanio) {
	/*
	string unaDescr;
	fstream archivo;
	archivo.open(this->nombre.c_str(), ios::binary | ios::in);
	archivo.seekg( offset,  ios::beg );

	archivo.read (unaDescr, tamanio);

	return unaDescr;
	*/
}

ArchivoDescrips::~ArchivoDescrips() {

}
