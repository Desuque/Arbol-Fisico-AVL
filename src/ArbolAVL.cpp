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
	int height;
};

int height(nodo *N)
{
	if (N == NULL)
		return 0;

	return N->height;
}

int max(int a, int b)
{
	return (a > b)? a : b;
}

nodo* nuevoNodo(int clave)
{

	nodo* unNodo = new nodo();

	unNodo->clave = clave;
	unNodo->izquierdo = NULL;
	unNodo->derecho = NULL;
	unNodo->height = 1;

	return(unNodo);
}

nodo *rotacionDerecha(nodo *y)
{
	nodo* x = y->izquierdo;
	nodo* T2 = x->derecho;

	x->derecho = y;
	y->izquierdo = T2;

	y->height = max(height(y->izquierdo), height(y->derecho))+1;
	x->height = max(height(x->izquierdo), height(x->derecho))+1;

	return x;
}

nodo *rotacionIzquierda(nodo *x)
{
	nodo *y = x->derecho;
	nodo *T2 = y->izquierdo;

	y->izquierdo = x;
	x->derecho = T2;

	x->height = max(height(x->izquierdo), height(x->derecho))+1;
	y->height = max(height(y->izquierdo), height(y->derecho))+1;

	return y;
}

int getBalance(nodo *N)
{
	if (N == NULL)
		return 0;
	return height(N->izquierdo) - height(N->derecho);
}

nodo* insert(nodo* nodo, int clave)
{
	if (nodo == NULL)
		return(nuevoNodo(clave));

	if (clave < nodo->clave)
		nodo->izquierdo = insert(nodo->izquierdo, clave);
	else
		nodo->derecho = insert(nodo->derecho, clave);

	nodo->height = max(height(nodo->izquierdo), height(nodo->derecho)) + 1;

	int balance = getBalance(nodo);

	// If this nodo becomes unbalanced, then there are 4 cases

	if (balance > 1 && clave < nodo->izquierdo->clave)
		return rotacionDerecha(nodo);

	if (balance < -1 && clave > nodo->derecho->clave)
		return rotacionIzquierda(nodo);

	if (balance > 1 && clave > nodo->izquierdo->clave)
	{
		nodo->izquierdo = rotacionIzquierda(nodo->izquierdo);
		return rotacionDerecha(nodo);
	}

	if (balance < -1 && clave < nodo->derecho->clave)
	{
		nodo->derecho = rotacionDerecha(nodo->derecho);
		return rotacionIzquierda(nodo);
	}

	return nodo;
}

// A utility function to print preorder traversal of the tree.
// The function also prints height of every nodo
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
