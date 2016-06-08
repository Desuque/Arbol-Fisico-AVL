#include "ArchivoDescrips.h"

using namespace std;

ArchivoDescrips::ArchivoDescrips(string nombre) {
	this->nombre = nombre + "_descrips.bin";
	//TODO: inicializarArchivo();
}

int ArchivoDescrips::grabar(string descripcion) {
	/* TODO:
	 *
	  fstream archivo;
	  archivo.open(this->nombre.c_str(), ios::in | ios::out | ios::binary );

	  ArchivoLibres* archivoLibres = new ArchivoLibres("descripciones");
	  int offset = archivoLibres.buscarEspacioLibre(descripcion.size());

	  if (offset >= 0) {
	 		archivo.seekp(offsetLibre, ios::beg);
	  } else {
	  		archivo.seekp( 0,  ios::end );
	  		offset = ver como obtener el offset;
	  }

	 	archivo.write((char*) &descripcion, descripcion.size());
	 	archivo.close();

	 	return offset;   //Asi lo guardo en el archivo del arbol
	 */
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
