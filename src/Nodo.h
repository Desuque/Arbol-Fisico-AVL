#ifndef NODO_H_
#define NODO_H_

#include <list>

#include "Bloque.h"
#include "Registro.h"

using namespace std;

class Bloque;

class Nodo {
private:
	int izquierdo;
	int derecho;
	list<Registro*>* registros;
	int altura;
	//int id;
	Bloque* bloque;
	string nombreArchivo;

public:
	Nodo(string nombreArchivo);
	Nodo(string nombreArchivo, int idBloque);

	Bloque* getBloque();
	int getMenorID();
	int getMayorID();
	int getMaxIdReg();
	int getHijoIzquierdo();
	int getHijoDerecho();
	Registro* getRegistroConMayorID();
	Registro* getRegistroConMenorID();
	int getAltura();
	int getTamanio();
	list<Registro*>* getRegistros();
	int getCantidadDeRegistros();
	bool estaEnUnderflow();
	bool esHoja();
	//int getID();
	bool insertar(Registro* unRegistro);
	Registro* getRegistro(int unID);
	Nodo* reescribirEn(int id);
	// Set = Solo realiza los cambios en memoria
	void setHijoIzquierdo(int idIzq);
	void setHijoDerecho(int idDer);
	void setAltura(int altura);
	// Modificar = Escribe los cambios en disco
	void modificarHijoIzquierdo(int nuevoNodo);
	void modificarHijoDerecho(int nuevoNodo);
	void modificarAltura(int nuevaAltura);
	bool borrarRegistro(int ID);
	bool existeRegistroConID(int idBuscado);
	bool modificarRegistro(int ID, string nuevoCodigo, string nuevaDescripcion);
	virtual ~Nodo();

};

#endif  /* NODO_H */
