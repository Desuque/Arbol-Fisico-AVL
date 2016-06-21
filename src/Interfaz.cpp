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
	cout<<"En el caso de usar el argumento -q el modo de empleo sera: arbolFisico -q [codigo de consulta] [-f path al archivo]."<<endl;
	cout<<endl;
	cout<<"Argumentos:"<<endl;
	cout<<"-conf, guarda el tamaño del bloque en un archivo de configuracion. Ej: -conf 4096 (Valor en bytes)."<<endl;
	cout<<endl;
	cout<<"-a, da en alta en [archivo]. Ej: -a Codigo 'Descripcion' productos.bin."<<endl;
	cout<<"-b, da de baja en [archivo]. Ej: -b 'ID' 'productos.bin'"<<endl;
	cout<<"-m, modifica el [archivo]. Ej: -m 'ID' 'Nuevo Codigo' 'Nueva Descripcion' productos.bin"<<endl;
	cout<<"-q, realiza una consulta segun el codigo ingresado. Ej: -q 'Codigo' 'ID' [-f] productos.bin"<<endl;
	cout<<"[-f], opcional"<<endl;
	cout<<endl;
	cout<<"Codigos de consulta:"<<endl;
	/**
	 * Solo un unico codigo de consulta por ID, ya que las que se publicaron no corresponden con este trabajo
	 * Devuelve el codigo y la descripcion
	 */
	cout<<"A Búsqueda por Identificador."<<endl;
	cout<<endl;
	cout<<"-f, (Solo con argumento -q) indica que se guardará el resultado en un archivo, de no utlizarse, se mostrará por pantalla."<<endl;
}

void Interfaz::validarParametros(int argc, char *argv[]) {
	if (argc > this->maxParametros) {
		msgError();
	}
	if ((string(argv[1]) == "-a") && (existeArchivoDeConfiguracion())) {
		/**
		* Ej de uso: -a "ABC" "Descripcion" productos.bin
		*/
		crearInstancia(argv);
	}
	if ((string(argv[1]) == "-b") && (existeArchivoDeConfiguracion())) {
		/**
		* Ej de uso: -b "ID" productos.bin
		*/
		eliminarInstancia(argv);
	}
	if ((string(argv[1]) == "-m") && (existeArchivoDeConfiguracion())) {
		/**
		* Ej de uso: -m "ID" "Nuevo Codigo" "Nueva Descripcion" productos.bin
		*/
		modificarInstancia(argv);
	}
	if ((string(argv[1]) == "-q") && (existeArchivoDeConfiguracion())) {
		/**
		* Ej de uso: -q 'A' 'ID' [-f] productos.bin
		*/
		listarInstancias(argv);
	}

	if ( string(argv[1]) == "-conf" ) {
		/**
		 * Setea el tamaño del bloque en bytes
		 * Ej de uso: -conf 4096
		 */
		setearTamanioBloque(argv);
	}

	if ( string(argv[1]) == "--help" ) {
		msgHelp();
	}
}

bool Interfaz::existeArchivoDeConfiguracion() {
	fstream archivo (archivoConfigTamBloque.c_str() , ios::in | ios::binary);
	if (archivo) {
		return true;
	} else {
		cout<<"No se encontro el archivo de configuracion, por lo tanto no es posible setear el tamaño del bloque."<<endl;
		cout<<"Es necesario que el archivo de configuracion exista antes de realizar cualquier accion sobre el arbol."<<endl;
	}
	return false;
}

void Interfaz::setearTamanioBloque(char *argv[]) {
	ofstream fs(archivoConfigTamBloque.c_str());
	fs << argv[2];
	fs.close();

	cout<<"Se ha seteado el tamaño del bloque en " << argv[2] << " bytes." <<endl;
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

	//arbol->print(); //TODO: Dejar solo para pruebas

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
	//arbol->print();

	delete arbol;
}

void Interfaz::modificarInstancia(char *argv[]) {
	string nombre = renombrarArchivo(string(argv[5]));
	ArbolAVL* arbol = new ArbolAVL(nombre);
	arbol->modificarRegistro(atoi(argv[2]), string(argv[3]), string(argv[4]));
	//arbol->print();

	delete arbol;
}

bool Interfaz::registroExiste(Registro* unRegistro, int ID) {
	bool existe = false;
	if (unRegistro == NULL) {
		cout<<"El registro con ID: "<<ID<<" no existe. No es posible listarlo."<<endl;
	} else {
		existe = true;
	}
	return existe;
}

void Interfaz::listarInstancias(char *argv[]) {
	Registro* unRegistro;
	if (string(argv[2]) == "A") { //No hay otro argumento que A, pero lo agrego por si esto cambia
		if (string(argv[4]) != "-f") {
			string nombre = renombrarArchivo(string(argv[4]));
			ArbolAVL* arbol = new ArbolAVL(nombre);
			unRegistro = arbol->getRegistro(atoi(argv[3]));
			if (registroExiste(unRegistro, atoi(argv[3]))) {
				cout<<"Codigo: "<<unRegistro->getCodigo()<<endl;
				cout<<"Descripcion: "<<unRegistro->getDescripcion()<<endl;
			}
			delete arbol;
		} else {
			string nombre = renombrarArchivo(string(argv[5]));
			ArbolAVL* arbol = new ArbolAVL(nombre);
			unRegistro = arbol->getRegistro(atoi(argv[3]));
			if (registroExiste(unRegistro, atoi(argv[3]))) {
				crearArchivoSalida(unRegistro);
			}
			delete arbol;
		}
	}
}

void Interfaz::crearArchivoSalida(Registro* unRegistro) {
	fstream fs("Salida.txt", ios::app);
	fs << "Codigo: " << unRegistro->getCodigo() << " , Descripcion: " << unRegistro->getDescripcion();
	fs.close();
}

Interfaz::~Interfaz() {
	// TODO Auto-generated destructor stub
}

