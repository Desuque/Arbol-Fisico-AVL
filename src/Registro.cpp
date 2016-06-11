#include "Registro.h"
#include <string.h>
#include <iostream>

using namespace std;

Registro::Registro(string codigo, string descripcion) {
	this->codigo = codigo;
	this->descripcion = descripcion;
}

void Registro::setId(int unId) {
	this->id = unId;
}

void Registro::setCodigo(string nuevoCodigo) {
	this->codigo = nuevoCodigo;
}

void Registro::setDescripcion(string nuevaDescripcion) {
	this->descripcion = nuevaDescripcion;
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
	int tamanoTamDescr = 4;
	int tamanoId = 4;
	int tamanoCodigo = 3;
	int tamanoFlagDescr = 1;
	int tamanoDescr = string(this->descripcion).size();

	if (tamanoDescr > 1000) {  //TODO: sacar el hardcodeo
		tamanoDescr = 4;
	}

	return tamanoTamDescr + tamanoId + tamanoCodigo + tamanoFlagDescr + tamanoDescr;
}
