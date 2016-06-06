#include "ArbolAVL.h"
#include "Interfaz.h"
#include "ArchivoLibres.h"
#include <string.h>
#include <iostream>

using namespace std;

void creg(string codigo, string descr , ArbolAVL* arbol) {
	Registro* unRegistro;

	unRegistro = new Registro(codigo, descr);
	arbol->insertar(unRegistro);
}

int main() //int argc, char *argv[] -> como parametro para la interfaz
{
	ArbolAVL* arbol = new ArbolAVL("DNIs");

	creg("LGD", "Leandro Gonzalo Devesa", arbol);
	creg("LHD", "Leandro Huemul Desuque", arbol);
	//creg("ZZZ", "Z Z Z", arbol);

	arbol->print();

	return 0;
}

