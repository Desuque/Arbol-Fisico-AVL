#ifndef NODO_H_
#define NODO_H_

#include <list>

#include "Bloque.h"
#include "Registro.h"

using namespace std;

class Bloque;

class Nodo {
private:
	Nodo* izquierdo;
	Nodo* derecho;
	int bytes_libres;
	list<Registro*>* registros;
	int altura;
	int id;
	Bloque* bloque;
	string nombreArchivo;

public:
	Nodo(string nombreArchivo);
	Nodo(string nombreArchivo, int idBloque);

	int maxPorNodo = 3; //TODO: en bytes
	int minPorNodo = 1; //TODO: en bytes

	Bloque* getBloque();
	int getMenorID();
	int getMayorID();
	Nodo* getHijoIzquierdo();
	Nodo* getHijoDerecho();
	Registro* getRegistroConMayorID();
	Registro* getRegistroConMenorID();
	int getAltura();
	int getTamanio();
	list<Registro*>* getRegistros();
	bool estaEnUnderflow();
	bool esHoja();
	int getID();
	bool insertar(Registro* unRegistro);

	void modificarHijoIzquierdo(Nodo* nuevoNodo);
	void modificarHijoDerecho(Nodo* nuevoNodo);
	void modificarAltura(int nuevaAltura);
	bool borrarRegistro(int ID);
	bool existeRegistroConID(int idBuscado);

	virtual ~Nodo();

};

#endif  /* NODO_H */
