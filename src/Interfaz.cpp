/*
 * Interfaz.cpp
 *
 *  Created on: 20 de may. de 2016
 *      Author: desuque
 */

#include "Interfaz.h"
#include "ArbolAVL.h"
#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

Interfaz::Interfaz(int argc, char *argv[]) {
	validarParametros(argc, argv);
}

void Interfaz::msgError() {
	cout<<"Por favor, verifique los parametros ingresados."<<endl;
	cout<<"En caso de necesitar ayuda, ingrese --help"<<endl;
}

void Interfaz::msgHelp() {
	cout<<"Ayuda sobre la interfaz de usuario:"<<endl;
	cout<<"==================================="<<endl;
	cout<<endl;
	cout<<"Modo de empleo: arbolesFisicos [-argumento] [ID/Codigo/Descripcion] [path al archivo]."<<endl;
	cout<<"En el caso de usar el argumento -q el modo de empleo sera: arbolFisico [nombre grupo] -q [codigo de consulta] [-f path al archivo]."<<endl;
	cout<<endl;
	cout<<"Argumentos:"<<endl;
	cout<<"-a, da en alta en [archivo]. Ej: -a Codigo 'Descripcion' productos.bin."<<endl;
	cout<<"-b, da de baja en [archivo]. Ej: -b 'ID' 'productos.bin'"<<endl;
	cout<<"-m, modifica el [archivo]. Ej: -m 'ID' 'Nuevo Codigo' 'Nueva Descripcion' productos.bin"<<endl;
	cout<<"-q, realiza una consulta segun el codigo ingresado."<<endl;
	cout<<endl;
	cout<<"Codigos de consulta:"<<endl;
	cout<<"A Búsqueda de Vendedor por Identificador."<<endl;
	cout<<"B Búsqueda de Vendedor por Nombre."<<endl;
	cout<<"C Búsqueda de Venta por Código de Vendedor."<<endl;
	cout<<"D Búsqueda de Venta por Código de Producto."<<endl;
	cout<<"E Búsqueda de Producto por Identificador."<<endl;
	cout<<"F Búsqueda de Producto por Nombre."<<endl;
	cout<<"G Búsqueda de Grupo por Identificador."<<endl;
	cout<<"H Búsqueda de Vendedor por Identificador, con el índice."<<endl;
	cout<<"I Búsqueda de Vendedor por Nombre, con el índice."<<endl;
	cout<<"J Búsqueda de Venta por Código de Vendedor, con el índice."<<endl;
	cout<<"K Búsqueda de Venta por Código de Producto, con el índice."<<endl;
	cout<<"L Búsqueda de Producto por Identificador, con el índice."<<endl;
	cout<<"M Búsqueda de Producto por Nombre, con el índice."<<endl;
	cout<<"N Búsqueda de Grupo por Identificador, con el índice."<<endl;
	cout<<"O Informe: Listado de ventas por Vendedor."<<endl;
	cout<<"P Informe: Ahorro de espacio por compresión."<<endl;
	cout<<endl;
	cout<<"-f, (Solo con argumento -q) indica que se guardará el resultado en un archivo, de no utlizarse, se mostrará por pantalla."<<endl;
}

void Interfaz::validarParametros(int argc, char *argv[]) {
	if ( argc > this->maxParametros ) {
		msgError();
	}
	if ( string(argv[1]) == "--help" ) {
		msgHelp();
	}
	if ( string(argv[1]) == "-a" ) {
		/**
		 * Ej de uso: -a "ABC" "Descripcion" "productos.bin"
		 */
		crearInstancia(argv);
	}
	if ( string(argv[1]) == "-b" ) {
		/**
		* Ej de uso: -b "ID" "productos.bin"
		*/
		eliminarInstancia(argv);
	}
	if ( string(argv[1]) == "-m" ) {
		/**
		* Ej de uso: -m "ID" "Nuevo Codigo" "Nueva Descripcion" productos.bin
		*/
		modificarInstancia(argv);
	}
	if ( string(argv[1]) == "-q" ) {
		listarInstancias(argv);
	}
}

string Interfaz::renombrarArchivo(string nombreConBin) {
	string str = nombreConBin;
	str.resize((nombreConBin.size())-4);
	return str;
}

void Interfaz::mostrarInsertar(string codigo, ArbolAVL* unArbol) {
	cout << "El registro con Codigo: '"<< codigo << "' ha sido insertado con el ID: " << unArbol->getMaxRegistroID() << endl;
}

void Interfaz::crearInstancia(char *argv[]) {
	string nombre = renombrarArchivo(string(argv[4]));

	ArbolAVL* arbol = new ArbolAVL(nombre);

	arbol->insertar(argv[2], argv[3]);
	mostrarInsertar(argv[2], arbol);

	arbol->print(); //TODO: Dejar solo para pruebas

	delete arbol;
}
/*
void Interfaz::listarRegistros(string nombre) {
	ArbolAVL* arbol = new ArbolAVL(nombre);

	arbol->print(); //TODO: Solo para pruebas

	delete arbol;
}
*/
void Interfaz::eliminarInstancia(char *argv[]) {
	string nombre = renombrarArchivo(string(argv[3]));

	ArbolAVL* arbol = new ArbolAVL(nombre);
	arbol->borrarRegistro(atoi(argv[2]));
	arbol->print();

	delete arbol;
}

void Interfaz::modificarInstancia(char *argv[]) {
	string nombre = renombrarArchivo(string(argv[5]));
	ArbolAVL* arbol = new ArbolAVL(nombre);
	arbol->modificarRegistro(atoi(argv[2]), string(argv[3]), string(argv[4]));
	arbol->print();

	delete arbol;
}

void Interfaz::listarInstancias(char *argv[]) {
	//TODO
}

Interfaz::~Interfaz() {
	// TODO Auto-generated destructor stub
}

