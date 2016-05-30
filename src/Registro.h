#ifndef REGISTRO_H_
#define REGISTRO_H_

#include<string>

using namespace std;

struct Registro	{
	int id;
	char codigo [3];
	char descripcion [1000];

	//pueden agregarse metadatos??
	int tamanio;
};

#endif
