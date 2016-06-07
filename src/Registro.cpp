#include "Registro.h"
#include <string.h>
#include <iostream>

using namespace std;

Registro::Registro(string codigo, string descripcion) {
	this->codigo = codigo.substr(0, 3);
	this->descripcion = descripcion.substr(0, 1000);
}

void Registro::setId(int unId) {
	this->id = unId;
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
