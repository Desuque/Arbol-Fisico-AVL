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

	creg(9, "AAX", "Descripcion larga 1", arbol);
	creg(10, "APL", "Descripcion larga 2", arbol);
	creg(11, "ZUC", "Descripcion larga 3", arbol);

	//beta borrar registro
	arbol->print();
	arbol->borrarRegistro(1);

	Persistencia pers;
	pers.grabar(arbol);

	arbol->print();

	pers.cargar();
	return 0;
}

