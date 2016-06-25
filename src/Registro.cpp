#include "Registro.h"
#include <string.h>
#include <iostream>

using namespace std;

Registro::Registro(string codigo, string descripcion) {
	setCodigo(codigo);
	this->descripcion = descripcion;
}

void Registro::setId(int unId) {
	this->id = unId;
}

void Registro::setCodigo(string nuevoCodigo) {
	/**
	 * Se rellena el espacio restante en caso de que el tamaño del codigo ingresado sea menor al maximo fijado para el TP.
	 */
	if (nuevoCodigo.size() < maxLongCodigo) {
		for (int i= nuevoCodigo.size(); i < maxLongCodigo; i++) {
			nuevoCodigo += " ";
		}
	}
	if (nuevoCodigo.size() > maxLongCodigo) {
		nuevoCodigo.resize(maxLongCodigo);
	}
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

Registro::~Registro() {

}
