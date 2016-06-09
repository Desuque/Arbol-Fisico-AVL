#ifndef ARCHIVODESCRIPS_H_
#define ARCHIVODESCRIPS_H_

#include <fstream>

using namespace std;

class ArchivoDescrips {

private:
	string nombre;

public:
	ArchivoDescrips(string nombre);
	int grabar(string descripcion);


	string leerBloque(int offset, int tamanio_descripcion);
	~ArchivoDescrips();
};

#endif /* ARCHIVODESCRIPS_H */
