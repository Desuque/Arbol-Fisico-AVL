#include "Registro.h"
#include <string.h>
#include <iostream>

using namespace std;

Registro::Registro(int id, string codigo, string descripcion) {
	this->id = id;
	strcpy(this->codigo, codigo.c_str());
	strcpy(this->descripcion, descripcion.c_str());
}

int Registro::getId() {
	return this->id;
}

string Registro::getCodigo() {
	return string(this->codigo);
}

string Registro::getDescripcion() {
	return string(this->descripcion);
}

int Registro::getTamanio() {
	int tamanoId = 4;
	int tamanoCodigo = 3;
	int tamanoDescr = string(this->codigo).size();

	return tamanoId + tamanoCodigo + tamanoDescr;
}
