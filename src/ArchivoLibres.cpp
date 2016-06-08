#include "ArchivoLibres.h"

using namespace std;

struct ClaveValor {
	int clave;
	int espacio;
};

ArchivoLibres::ArchivoLibres(string nombre) {
	this->nombre = nombre + "_libres.bin";
}

void ArchivoLibres::grabar(int clave, int espacio) {
	ClaveValor reg;
	reg.clave = clave;
	reg.espacio = espacio;

	fstream archivo;
	archivo.open(this->nombre.c_str(), ios::binary | ios::out | ios::app);
	archivo.seekp( 0,  ios::end );
	archivo.write((char*) &reg, sizeof(ClaveValor));
	archivo.close();
}

int ArchivoLibres::buscarEspacioLibre(int espacio) {
	fstream archivo;
	archivo.open(this->nombre.c_str(), ios::binary | ios::in);
	archivo.seekg( ios::beg );

	bool found = false;
	ClaveValor reg;

	while (!archivo.eof() && !found) {
		archivo.read (reinterpret_cast<char *>(&reg), sizeof(ClaveValor));
		if (reg.espacio >= espacio) {
			found = true;
		}
	}

	if (found) {
		//TODO: si encuentra.. borrar siempre?
		return reg.clave;
	} else {
		return -1;
	}
}

ArchivoLibres::~ArchivoLibres() {

}
