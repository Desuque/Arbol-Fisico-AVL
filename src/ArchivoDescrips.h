#ifndef ARCHIVODESCRIPS_H_
#define ARCHIVODESCRIPS_H_

#include <fstream>
#include "ArchivoLibres.h"

using namespace std;

class ArchivoDescrips {

private:
	string nombre;
	int offsetLibre;
	ArchivoLibres* archivoLibres;

public:
	ArchivoDescrips(string nombre);
	int grabar(string descripcion);
	int grabarEnEspacioLibre(string descripcion, int offset_libre);
	int getOffsetLibre();
	string leerBloque(int offset, int tamanio_descripcion);
	void eliminarDescripcion(int offset, int tamanio);
	~ArchivoDescrips();

private:
	void escribirNull(int offset, int tamanio);
};

#endif /* ARCHIVODESCRIPS_H */
