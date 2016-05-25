#ifndef ARBOLAVL_H_
#define ARBOLAVL_H_
#include <list>
#include "Registro.h"

namespace TPDatos {

	struct Nodo
	{
		Nodo *izquierdo;
		Nodo *derecho;
		int altura;
		std::list <Registro> registros;
	};

	class ArbolAVL {

	public:
		ArbolAVL();
		//virtual ~ArbolAVL();

		void insertar(Registro* unRegistro);
		void print();
	private:
		// VARS    --------------------------
		int maxInternos = 3; //TODO: en bytes
		int maxHoja = 3;	 //TODO: en bytes
		Nodo* raiz;
		// METODOS --------------------------
		Nodo* insertarEnNodo(Nodo* unNodo, Registro* unRegistro);
		Nodo* nuevoNodoHoja(Registro* unRegistro);
		Nodo* nuevoNodoInterno(int alturaVieja);
		Nodo* rotacionDerecha(Nodo *unNodo);
		Nodo* rotacionIzquierda(Nodo *unNodo);
		int getMax(int x, int y);
		int getAltura(Nodo *unNodo);
		int getDiferenciaAlturaHijos(Nodo *unNodo);
		void preOrder(Nodo* root);
		bool entraUnRegistroMas(Nodo* unNodo);
	};

}

#endif
