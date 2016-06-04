#include "ArchivoLibres.h"

using namespace std;

struct ClaveValor {
	int clave;
	int valor;
};

ArchivoLibres::ArchivoLibres(string nombre) {
	nombre = nombre + ".bin";
	archivo.open(nombre.c_str(), ios::binary | ios::in | ios::out);
}

void ArchivoLibres::grabar(int clave, int valor) {
	archivo.seekp( ios::end );

	ClaveValor reg;
	reg.clave = clave;
	reg.valor = valor;

	archivo.write((char*) &reg, sizeof(ClaveValor));
}

int ArchivoLibres::buscar(int clave) {
	archivo.seekg( ios::beg );

	bool found = false;
	ClaveValor reg;

	while (!archivo.eof() && !found) {
		archivo.read (reinterpret_cast<char *>(&reg), sizeof(ClaveValor));
		if (reg.clave == clave) {
			found = true;
		}
	}

	if (found) {
		//TODO: si encuentra.. borrar siempre?
		return reg.valor;
	} else {
		return 0;
	}
}

ArchivoLibres::~ArchivoLibres() {
	archivo.close();
}
