#include "ArbolAVL.h"
#include "Interfaz.h"
#include "Persistencia.h"
#include <string.h>
#include <iostream>

using namespace std;

void creg(int id, char codigo [3], ArbolAVL* arbol) {
	Registro* unRegistro;

	unRegistro = new Registro();
	unRegistro->id = id;
	strcpy(unRegistro->codigo, codigo);
	arbol->insertar(unRegistro);
}

int main() //int argc, char *argv[] -> como parametro para la interfaz
{
	ArbolAVL* arbol = new ArbolAVL();

	//Interfaz* interfaz = new Interfaz(argc, argv);

	creg(1, "asd", arbol);
	creg(2, "zzz", arbol);
	creg(3, "xxx", arbol);

	Persistencia pers;
	//pers.grabar(arbol);

	arbol->print();

	//pers.cargar();
	return 0;
}

