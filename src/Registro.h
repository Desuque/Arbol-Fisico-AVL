#ifndef REGISTRO_H_
#define REGISTRO_H_

#include<string>

using namespace std;

struct Registro	{
	int id;
	//TODO: ok 1+ para el 0 terminator?
	char codigo [4];
	char descripcion [1001];

	//pueden agregarse metadatos??
	int tamanio;
};

#endif
