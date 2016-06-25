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

	//Guardan la posicion en el archivo de libres en el que se leyeron el offset y el espacio libre correspondientemente
	int pos_offset;
	int pos_espacioLibre;

public:
	ArchivoLibres(string nombre);
	bool hayEspacio(int espacio);
	void grabarEspacioLibre(int offset, int espacioLibre);
	int getOffset();
	int getEspacioEnOffset(int unOffset);
	int getEspacioLibre();
	void actualizarEspacioLibre(int nuevoOffset, int nuevoEspacioLibre);
	~ArchivoLibres();

private:
	int buscarEspacioLibre(int espacio);

};

#endif /* ARCHIVOLIBRES_H */
