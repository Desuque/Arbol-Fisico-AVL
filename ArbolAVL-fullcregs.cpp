//============================================================================
// Name        : ArbolAVL.cpp
// Author      : DDTeam
// Version     :
// Copyright   : FIUBA 2016
//============================================================================

#include<stdio.h>
#include<stdlib.h>
#include<string>

using std::string;

struct Registro
{
	int id;
	string codigo;
	string descripcion;
	//pueden agregarse metadatos??
	int tamanio;
};

struct Nodo
{
	int clave;
	Nodo *izquierdo;
	Nodo *derecho;
	int altura;
	Registro *registro;
};

int getAltura(Nodo *unNodo)
{
	if (unNodo == NULL)
		return 0;

	return unNodo->altura;
}

int getMax(int x, int y)
{
	return (x > y)? x : y;
}

Nodo* nuevoNodo(int clave)
{

	Nodo* unNodo = new Nodo();

	unNodo->clave = clave;
	unNodo->izquierdo = NULL;
	unNodo->derecho = NULL;
	unNodo->altura = 1;

	return(unNodo);
}

Nodo *rotacionDerecha(Nodo *unNodo)
{
	Nodo* izq = unNodo->izquierdo;
	Nodo* der = izq->derecho;

	izq->derecho = unNodo;
	unNodo->izquierdo = der;

	unNodo->altura = getMax(getAltura(unNodo->izquierdo), getAltura(unNodo->derecho))+1;
	izq->altura = getMax(getAltura(izq->izquierdo), getAltura(izq->derecho))+1;

	return izq;
}

Nodo *rotacionIzquierda(Nodo *unNodo)
{
	Nodo *der = unNodo->derecho;
	Nodo *izq = der->izquierdo;

	der->izquierdo = unNodo;
	unNodo->derecho = izq;

	unNodo->altura = getMax(getAltura(unNodo->izquierdo), getAltura(unNodo->derecho))+1;
	der->altura = getMax(getAltura(der->izquierdo), getAltura(der->derecho))+1;

	return der;
}

int getDiferenciaAlturaHijos(Nodo *unNodo)
{
	if (unNodo == NULL)
		return 0;
	return getAltura(unNodo->izquierdo) - getAltura(unNodo->derecho);
}

Nodo* nuevoNodoHoja(Registro* unRegistro)
{

	Nodo* unNodo = new Nodo();

	unNodo->clave = NULL;
	unNodo->izquierdo = NULL;
	unNodo->derecho = NULL;
	unNodo->registro = unRegistro;
	unNodo->altura = 1;

	return(unNodo);
}

Nodo* insertar(Nodo* unNodo, Registro* unRegistro)
{
	//TODO: por ahora cap max = 1 reg
	bool entra = false;

	if (unNodo == NULL)
		return(nuevoNodoHoja(unRegistro));

	if (!entra) {

		unNodo->clave = unNodo->registro->id;
		unNodo->derecho = insertar(unNodo->derecho, unNodo->registro);

		unNodo->registro = NULL;

		if (unRegistro->id < unNodo->clave)
			unNodo->izquierdo = insertar(unNodo->izquierdo, unRegistro);
		else
			unNodo->derecho = insertar(unNodo->derecho, unRegistro);

	}
	unNodo->altura = getMax(getAltura(unNodo->izquierdo), getAltura(unNodo->derecho)) + 1;

	int diferencia = getDiferenciaAlturaHijos(unNodo);

	if (diferencia > 1 && unRegistro->id < unNodo->izquierdo->clave)
		return rotacionDerecha(unNodo);

	if (diferencia < -1 && unRegistro->id > unNodo->derecho->clave)
		return rotacionIzquierda(unNodo);

	if (diferencia > 1 && unRegistro->id > unNodo->izquierdo->clave)
	{
		unNodo->izquierdo = rotacionIzquierda(unNodo->izquierdo);
		return rotacionDerecha(unNodo);
	}

	if (diferencia < -1 && unRegistro->id < unNodo->derecho->clave)
	{
		unNodo->derecho = rotacionDerecha(unNodo->derecho);
		return rotacionIzquierda(unNodo);
	}

	return unNodo;
}

void preOrder(Nodo *root)
{
	if(root != NULL)
	{
		if (root->altura == 1) {
			printf("%d ", root->registro->id);
		} else {
			printf("%d ", root->clave);
		}
		preOrder(root->izquierdo);
		preOrder(root->derecho);
	}
}

int main()
{

//TODO: definir un nuevoArbol que devuelva el null
Nodo* arbol = NULL;

Registro* unRegistro = new Registro();

unRegistro->id = 10;
unRegistro->codigo = "pen";
unRegistro->descripcion = "pen de 4gb";


arbol = insertar(arbol, unRegistro);

unRegistro = new Registro();

unRegistro->id = 8;
unRegistro->codigo = "pen";
unRegistro->descripcion = "pen de 4gb";

arbol = insertar(arbol, unRegistro);


printf("Pre order traversal of the constructed AVL tree is \n");
preOrder(arbol);

return 0;
}
