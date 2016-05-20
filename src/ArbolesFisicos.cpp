#include "ArbolAVL.h"
#include "Interfaz.h"
#include <iostream>
using namespace TPDatos;

int main(int argc, char *argv[])
{
	Registro* unRegistro;
	ArbolAVL* arbol = new ArbolAVL();

	Interfaz* interfaz = new Interfaz(argc, argv);

	unRegistro = new Registro();
	unRegistro->id = 239;
	arbol->insertar(unRegistro);

	unRegistro = new Registro();
	unRegistro->id = 455;
	arbol->insertar(unRegistro);

	unRegistro = new Registro();
	unRegistro->id = 734;
	arbol->insertar(unRegistro);

/**
	unRegistro = new Registro();
	unRegistro->id = 911;
	arbol->insertar(unRegistro);
**/
	arbol->print();

	return 0;
}
