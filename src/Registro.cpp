#include "Registro.h"
#include <string.h>
#include <iostream>

using namespace std;

Registro::Registro(int id, string codigo, string descripcion) {
	this->id = id; //esto se tiene que ir, hay un id por nodo, automatico
	this->codigo = codigo;
	this->descripcion = descripcion;
}

int Registro::getId() {
	return this->id;
}

string Registro::getCodigo() {
	return this->codigo;
}

string Registro::getDescripcion() {
	return this->descripcion;
}

int Registro::getTamanioDescripcion() {
	return (this->descripcion).size();
}

int Registro::getTamanio() {
	int tamanoId = 4;
	int tamanoCodigo = 3;
	int tamanoDescr = string(this->descripcion).size();

	return tamanoId + tamanoCodigo + tamanoDescr;
}
