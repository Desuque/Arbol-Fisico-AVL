#include "ArbolAVL.h"
using namespace TPDatos;

int main()
{
	Registro* unRegistro;
	ArbolAVL* arbol = new ArbolAVL();

	unRegistro = new Registro();
	unRegistro->id = 10;

	arbol->insertar(unRegistro);

	unRegistro = new Registro();
	unRegistro->id = 8;

	arbol->insertar(unRegistro);

	arbol->print();

	return 0;
}
