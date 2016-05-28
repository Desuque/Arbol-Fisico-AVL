#include "ArbolAVL.h"
#include "Interfaz.h"
#include <iostream>

using namespace std;

void creg(int id, ArbolAVL* arbol) {
	Registro* unRegistro;

	unRegistro = new Registro();
	unRegistro->id = id;
	arbol->insertar(unRegistro);
}

int main() //int argc, char *argv[] -> como parametro para la interfaz
{
	ArbolAVL* arbol = new ArbolAVL();

	//Interfaz* interfaz = new Interfaz(argc, argv);

	creg(1, arbol);
	creg(2, arbol);
	creg(3, arbol);
	creg(8, arbol);
	creg(9, arbol);
	creg(10, arbol);
	creg(4, arbol);
	creg(5, arbol);
	creg(6, arbol);


	arbol->print();

	return 0;
}

