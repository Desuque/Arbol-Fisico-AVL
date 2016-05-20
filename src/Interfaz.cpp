/*
 * Interfaz.cpp
 *
 *  Created on: 20 de may. de 2016
 *      Author: desuque
 */

#include "Interfaz.h"
#include <iostream>
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
	cout<<"Modo de empleo: arbolFisico [nombre grupo] [-argumento] [categoria] [path al archivo]."<<endl;
	cout<<"En el caso de usar el argumento -q el modo de empleo sera: arbolFisico [nombre grupo] -q [codigo de consulta] [-f path al archivo]."<<endl;
	cout<<endl;
	cout<<"Argumentos:"<<endl;
	cout<<"-a, da en alta en [categoria]. Ej: -a vendedores [path al archivo]."<<endl;
	cout<<"-b, da de baja en [categoria]."<<endl;
	cout<<"-m, modifica la [categoria]."<<endl;
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
}

Interfaz::~Interfaz() {
	// TODO Auto-generated destructor stub
}

