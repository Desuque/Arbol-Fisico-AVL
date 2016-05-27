#include "ArbolAVL.h"
#include "Interfaz.h"
#include <iostream>

using namespace std;

int main() //int argc, char *argv[] -> como parametro para la interfaz
{
	Registro* unRegistro;
	ArbolAVL* arbol = new ArbolAVL();

	//Interfaz* interfaz = new Interfaz(argc, argv);

	unRegistro = new Registro();
	unRegistro->id = 250;
	arbol->insertar(unRegistro);

	unRegistro = new Registro();
	unRegistro->id = 911;
	arbol->insertar(unRegistro);

	unRegistro = new Registro();
	unRegistro->id = 455;
	arbol->insertar(unRegistro);

	unRegistro = new Registro();
	unRegistro->id = 734;
	arbol->insertar(unRegistro);

	unRegistro = new Registro();
	unRegistro->id = 125;
	arbol->insertar(unRegistro);

	unRegistro = new Registro();
	unRegistro->id = 100;
	arbol->insertar(unRegistro);

	unRegistro = new Registro();
	unRegistro->id = 300;
	arbol->insertar(unRegistro);

	unRegistro = new Registro();
	unRegistro->id = 800;
	arbol->insertar(unRegistro);

	unRegistro = new Registro();
	unRegistro->id = 850;
	arbol->insertar(unRegistro);

	unRegistro = new Registro();
	unRegistro->id = 912;
	arbol->insertar(unRegistro);

	unRegistro = new Registro();
	unRegistro->id = 913;
	arbol->insertar(unRegistro);

	unRegistro = new Registro();
	unRegistro->id = 914;
	arbol->insertar(unRegistro);

	arbol->print();

	return 0;
}
