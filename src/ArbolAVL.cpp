//============================================================================
// Name        : ArbolAVL.cpp
// Author      : DDTeam
// Version     :
// Copyright   : FIUBA 2016
//============================================================================

#include<stdio.h>
#include<stdlib.h>

struct nodo
{
	int clave;
	nodo *izquierdo;
	nodo *derecho;
	int altura;
};

int getAltura(nodo *unNodo)
{
	if (unNodo == NULL)
		return 0;

	return unNodo->altura;
}

int getMax(int x, int y)
{
	return (x > y)? x : y;
}

nodo* nuevoNodo(int clave)
{

	nodo* unNodo = new nodo();

	unNodo->clave = clave;
	unNodo->izquierdo = NULL;
	unNodo->derecho = NULL;
	unNodo->altura = 1;

	return(unNodo);
}

nodo *rotacionDerecha(nodo *unNodo)
{
	nodo* izq = unNodo->izquierdo;
	nodo* der = izq->derecho;

	izq->derecho = unNodo;
	unNodo->izquierdo = der;

	unNodo->altura = getMax(getAltura(unNodo->izquierdo), getAltura(unNodo->derecho))+1;
	izq->altura = getMax(getAltura(izq->izquierdo), getAltura(izq->derecho))+1;

	return izq;
}

nodo *rotacionIzquierda(nodo *unNodo)
{
	nodo *der = unNodo->derecho;
	nodo *izq = der->izquierdo;

	der->izquierdo = unNodo;
	unNodo->derecho = izq;

	unNodo->altura = getMax(getAltura(unNodo->izquierdo), getAltura(unNodo->derecho))+1;
	der->altura = getMax(getAltura(der->izquierdo), getAltura(der->derecho))+1;

	return der;
}

int getDiferenciaAlturaHijos(nodo *unNodo)
{
	if (unNodo == NULL)
		return 0;
	return getAltura(unNodo->izquierdo) - getAltura(unNodo->derecho);
}

nodo* insert(nodo* nodo, int clave)
{
	if (nodo == NULL)
		return(nuevoNodo(clave));

	if (clave < nodo->clave)
		nodo->izquierdo = insert(nodo->izquierdo, clave);
	else
		nodo->derecho = insert(nodo->derecho, clave);

	nodo->altura = getMax(getAltura(nodo->izquierdo), getAltura(nodo->derecho)) + 1;

	int diferencia = getDiferenciaAlturaHijos(nodo);

	if (diferencia > 1 && clave < nodo->izquierdo->clave)
		return rotacionDerecha(nodo);

	if (diferencia < -1 && clave > nodo->derecho->clave)
		return rotacionIzquierda(nodo);

	if (diferencia > 1 && clave > nodo->izquierdo->clave)
	{
		nodo->izquierdo = rotacionIzquierda(nodo->izquierdo);
		return rotacionDerecha(nodo);
	}

	if (diferencia < -1 && clave < nodo->derecho->clave)
	{
		nodo->derecho = rotacionDerecha(nodo->derecho);
		return rotacionIzquierda(nodo);
	}

	return nodo;
}

void preOrder(nodo *root)
{
	if(root != NULL)
	{
		printf("%d ", root->clave);
		preOrder(root->izquierdo);
		preOrder(root->derecho);
	}
}

int main()
{
nodo *root = NULL;

root = insert(root, 10);
root = insert(root, 20);
root = insert(root, 30);
root = insert(root, 40);
root = insert(root, 50);
root = insert(root, 25);

/* The constructed AVL Tree would be
			30
		/ \
		20 40
		/ \	 \
	10 25 50
*/

printf("Pre order traversal of the constructed AVL tree is \n");
preOrder(root);

return 0;
}
