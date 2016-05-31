#ifndef ARBOLAVL_H_
#define ARBOLAVL_H_
#include "Registro.h"
#include "Nodo.h"
#include <list>

using namespace std;

class ArbolAVL {
private:
	Nodo* raiz;
	int alturaRaiz = 0; //declarar como constante
public:
	ArbolAVL();

	void insertar(Registro* unRegistro);
	void borrarRegistro(int unID);
	void print();
	Nodo* getRaiz();
	Nodo* buscarNodoPorID(Nodo* unNodo, int idBuscado);
	Nodo* borrarRegistroPorID(Nodo* unNodo, int idBuscado);
	virtual ~ArbolAVL();

private:
	Nodo* insertarEnNodo(Nodo* unNodo, Registro* unRegistro);
	Nodo* crearNodo(Registro* unRegistro);
	Nodo* rotacionDerecha(Nodo *unNodo);
	Nodo* rotacionIzquierda(Nodo *unNodo);
	int getDiferenciaAlturaHijos(Nodo* unNodo);
	void preOrder(Nodo* root);
	void balancear(Nodo* unNodo);

};

#endif
