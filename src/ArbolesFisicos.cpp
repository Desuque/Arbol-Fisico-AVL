#include "ArbolAVL.h"
#include "Interfaz.h"
#include "Persistencia.h"
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

	//Test persistencia

	Nodo* miNodo = new Nodo();
	Registro* miRegistro = new Registro("123","hola");
	//Registro* otroRegistro = new Registro("23","hola, soy un test muy eficiente");
	//Registro* ultimoReg = new Registro("1", "Este es el ultimo registro que cargo papa");
	miNodo->insertar(miRegistro);

	Persistencia* persistir = new Persistencia();
	persistir->setNombreArchivo("arbol.bin");
	cout<<"Arranca a leer el archivo:"<<endl;

	persistir->escribirMaxIDNodo(50000);
	persistir->escribirMaxIDReg(128);

	cout<<persistir->leerMayorIdReg()<<endl;
	cout<<persistir->leerMayorIdNodo()<<endl;


	cout<<"Bloque"<<persistir->leerBloque(0)<<endl;
	//persistir->grabar(miRegistro, 0);
	//persistir->grabar(otroRegistro, 0);
	//persistir->grabar(ultimoReg, 0);

	//Fin test persistencia


	ArbolAVL* arbol = new ArbolAVL();

	//Interfaz* interfaz = new Interfaz(argc, argv);

	creg("AAA", "Descripcion larga 1", arbol);
	creg("AAB", "Descripcion larga 2", arbol);
	creg("AAC", "Descripcion larga 3", arbol);

	arbol->print();

	return 0;
}

