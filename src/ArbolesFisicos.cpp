#include "ArbolAVL.h"
#include "Interfaz.h"
#include "Persistencia.h"
#include <string.h>
#include <iostream>

using namespace std;

void creg(int id, char codigo [3], char descr [1000], ArbolAVL* arbol) {
	Registro* unRegistro;

	unRegistro = new Registro();
	unRegistro->id = id;
	strcpy(unRegistro->codigo, codigo);
	strcpy(unRegistro->descripcion, descr);
	arbol->insertar(unRegistro);
}

int main() //int argc, char *argv[] -> como parametro para la interfaz
{
	ArbolAVL* arbol = new ArbolAVL();

	//Interfaz* interfaz = new Interfaz(argc, argv);

	creg(1, "AAA", "Descripcion larga 1", arbol);
	creg(2, "APL", "Descripcion larga 2", arbol);
	creg(3, "ZUC", "Descripcion larga 3", arbol);
	creg(4, "AAA", "Descripcion larga 1", arbol);
	creg(5, "AAA", "Descripcion larga 1", arbol);
	creg(6, "ZUC", "Descripcion larga 3", arbol);
	creg(7, "AAA", "Descripcion larga 1", arbol);
	//creg(8, "AAA", "Descripcion larga 1", arbol);
	//creg(9, "AAA", "Descripcion larga 1", arbol);

	arbol->print();
	arbol->borrarRegistro(3);
	arbol->borrarRegistro(4);
	arbol->borrarRegistro(5);
	arbol->borrarRegistro(6);
	//arbol->borrarRegistro(6);
	arbol->print();

	//Persistencia pers;
	//pers.grabar(arbol);


	//pers.cargar();
	return 0;
}

