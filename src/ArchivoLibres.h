#ifndef ARCHIVOLIBRES_H_
#define ARCHIVOLIBRES_H_

#include <fstream>

using namespace std;

class ArchivoLibres {

private:
	string nombre;
	static const int tam_offset = 4;
	static const int tam_espacioLibre = 4;
	int offset;
	int espacioLibre;

public:
	ArchivoLibres(string nombre);
	bool hayEspacio(int espacio);
	void grabarEspacioLibre(int offset, int espacioLibre);
	int getOffset();
	int getEspacioLibre();
	~ArchivoLibres();

private:
	int buscarEspacioLibre(int espacio);

};

#endif /* ARCHIVOLIBRES_H */
