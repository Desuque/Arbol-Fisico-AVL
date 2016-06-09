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

void ArchivoLibres::actualizarEspacioLibre(int nuevoOffset, int nuevoEspacioLibre) {
	/** Si se encuentra espacio libre quedan actualizadas las variables pos_offset y pos_espacioLibre
	 * las cuales se usan para reescribir y actualizar los datos de offset y espacio libre leidos
	 */
	fstream archivo;
	archivo.open(this->nombre.c_str(), ios::in | ios::out | ios::binary );

	archivo.seekp (pos_offset, archivo.beg);

	if (nuevoEspacioLibre != 0) {
		archivo.write(reinterpret_cast<const char *>(&nuevoOffset), tam_offset);
		archivo.write(reinterpret_cast<const char *>(&nuevoEspacioLibre), tam_offset);
	} else {
		//Si no sobra espacio libre, se guarda 0,0
		int offset_cero = 0;
		archivo.write(reinterpret_cast<const char *>(&offset_cero), tam_offset);
		archivo.write(reinterpret_cast<const char *>(&nuevoEspacioLibre), tam_offset);
	}
	archivo.close();
}

int ArchivoLibres::buscarEspacioLibre(int espacio) {
	bool found = false;

	fstream archivo;
	archivo.open(this->nombre.c_str(), ios::binary | ios::in | ios::out );
	archivo.seekg (ios::beg);

	while (!archivo.eof() && !found) {
		pos_offset = archivo.tellg();
		archivo.read ((char*)&offset, 4);

		pos_espacioLibre = archivo.tellg();
		archivo.read ((char*)&espacioLibre, 4);

		if (espacioLibre >= espacio) {
			found = true;

			cout<<"pos1: "<<pos_offset<<endl;
			cout<<"pos2: "<<pos_espacioLibre<<endl;
			//TODO BORRAR EL ESPACIO ENCONTRADO
			//TODO CREAR UN NUEVO ESPACIO CON EL RESTO EN CASO DE EXISTIR
			//en esta posicion de offset y espacio libre, que las tengo que clcular aca, tengo que
			//cargar el nuevo offset y espacio libre. En cso de no haber espcio libre de sobra,
			//en esta posicion se guarda 0:0
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
