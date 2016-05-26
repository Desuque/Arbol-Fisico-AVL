#ifndef ARBOLAVL_H_
#define ARBOLAVL_H_
#include "Registro.h"
#include "Nodo.h"
#include <list>

using namespace std;

class ArbolAVL {
private:
	int maxInternos = 3; //TODO: en bytes
	int maxHoja = 3;	 //TODO: en bytes
	Nodo* raiz;
public:
	ArbolAVL();

	void insertar(Registro* unRegistro);
	void print();

	virtual ~ArbolAVL();

private:
	Nodo* insertarEnNodo(Nodo* unNodo, Registro* unRegistro);
	Nodo* crearNuevoNodo(Registro* unRegistro, int alturaPadre);
	Nodo* rotacionDerecha(Nodo *unNodo);
	Nodo* rotacionIzquierda(Nodo *unNodo);
	int getDiferenciaAlturaHijos(Nodo* unNodo);
	void preOrder(Nodo* root);
	Nodo* balancear(Nodo* unNodo);
};

#endif
