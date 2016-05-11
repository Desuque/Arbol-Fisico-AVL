#include "ArbolAVL.h"
using namespace TPDatos;

int main()
{
	Registro* unRegistro;
	ArbolAVL* arbol = new ArbolAVL();

	unRegistro = new Registro();
	unRegistro->id = 239;
	arbol->insertar(unRegistro);

	unRegistro = new Registro();
	unRegistro->id = 455;
	arbol->insertar(unRegistro);

	unRegistro = new Registro();
	unRegistro->id = 734;
	arbol->insertar(unRegistro);

	unRegistro = new Registro();
	unRegistro->id = 911;
	arbol->insertar(unRegistro);

	arbol->print();

	return 0;
}
