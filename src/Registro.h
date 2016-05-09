#ifndef REGISTRO_H_
#define REGISTRO_H_

#include<string>

using namespace std;

struct Registro	{
	int id;
	string codigo;
	string descripcion;

	//pueden agregarse metadatos??
	int tamanio;
};

#endif
