#include "ArchivoLibres.h"
#include <iostream>
#include <sstream>
#include <stdlib.h>

using namespace std;

/** El archivo de libres guarda el offset de espacio libre en el archivo de Bloques y en el archivo de Descripciones.
 * Ademas, guarda la cantidad de espacio libre. Devuelve, en caso de encontrar espacio, ambos parametros.
 *
 * Estructura del archivo: offset [4bytes], espacioLibre [4bytes] ... [], [] ...
 *
 */

ArchivoLibres::ArchivoLibres(string nombre) {
	this->nombre = nombre + "_libres.bin";
	this->offset = 0;
	this->espacioLibre = 0;
}

int ArchivoLibres::getOffset() {
	return this->offset;
}

int ArchivoLibres::getEspacioLibre() {
	return this->espacioLibre;
}

void ArchivoLibres::grabarEspacioLibre(int offset, int espacioLibre) {
	fstream archivo;
	archivo.open(nombre.c_str(), ios::in | ios::out | ios::binary | ios::app );
	archivo.write(reinterpret_cast<const char *>(&offset), tam_offset);
	archivo.write(reinterpret_cast<const char *>(&espacioLibre), tam_espacioLibre);
	archivo.close();
}

bool ArchivoLibres::hayEspacio(int espacio) {
	fstream archivo (nombre.c_str() , ios::in | ios::binary);

	if (!archivo) {
		return false;
	} else {
		if (buscarEspacioLibre(espacio) == 0) {
			return true;
		}
	}
	return false;
}

int ArchivoLibres::buscarEspacioLibre(int espacio) {
	bool found = false;

	fstream archivo;
	archivo.open(this->nombre.c_str(), ios::binary | ios::in | ios::out );
	archivo.seekg( ios::beg );
	archivo.seekg (ios::beg);

	while (!archivo.eof() && !found) {
		archivo.read ((char*)&offset, 4);
		archivo.read ((char*)&espacioLibre, 4);

		if (espacioLibre >= espacio) {
			found = true;

			//TODO BORRAR EL ESPACIO ENCONTRADO
			//TODO CREAR UN NUEVO ESPACIO CON EL RESTO EN CASO DE EXISTIR

		}
	}
	archivo.close();

	if (found) {
		/** Si encuentra espacio, las variables offset y espacioLibre
		 * ya se encuentran cargadas para poder ser leidas por el bloque.
		 */
		return 0;
	} else {
		return -1;
	}
}

ArchivoLibres::~ArchivoLibres() {

}
