#ifndef ARBOLAVL_H_
#define ARBOLAVL_H_
#include "Registro.h"

namespace TPDatos {

	struct Nodo
	{
		int clave;
		Nodo *izquierdo;
		Nodo *derecho;
		int altura;
		Registro *registro;
	};

	class ArbolAVL {

	public:
		ArbolAVL();
		//virtual ~ArbolAVL();

		void insertar(Registro* unRegistro);
		void print();
	private:
		// VARS    --------------------------
		Nodo* raiz;
		// METODOS --------------------------
		Nodo* insertarEnNodo(Nodo* unNodo, Registro* unRegistro);
		Nodo* nuevoNodo(Registro* unRegistro);
		Nodo* rotacionDerecha(Nodo *unNodo);
		Nodo* rotacionIzquierda(Nodo *unNodo);
		int getMax(int x, int y);
		int getAltura(Nodo *unNodo);
		int getDiferenciaAlturaHijos(Nodo *unNodo);
		void preOrder(Nodo* root);
	};

}

#endif
