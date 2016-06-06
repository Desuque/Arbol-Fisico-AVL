/*
 * Persistencia.cpp
 *
 */
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "Persistencia.h"
#include "Registro.h"

using namespace std;

Persistencia::Persistencia() {
	buff_bloque = new char[tam_bloque];
	buff_flagDeTipo = new char[tam_flagDeTipo];
	buff_codigo = new char[tam_codigo];
	buff_tam_descripcion = new char[tam_descripcion];
	buff_flagExisteRegistro = new char[tam_flagExisteRegistro];
	buff_hijoIzquierdo = new char[tam_hijoIzquierdo];
	buff_hijoDerecho = new char[tam_hijoDerecho];

}

void Persistencia::setNombreArchivo(string nombreArchivo) {
	this->nombreArchivo = nombreArchivo + ".bin";
}

int Persistencia::leerMayorIdNodo() {
	int buffer;
	fstream archivo (nombreArchivo.c_str() , ios::in | ios::binary);

	archivo.seekg (0, ios::beg);
	archivo.read ((char*)&buffer, tam_meta_id);

	return buffer;
}

int Persistencia::leerMayorIdReg() {
	int buffer;
	fstream archivo (nombreArchivo.c_str() , ios::in | ios::binary);

	archivo.seekg (tam_meta_id, ios::beg);
	archivo.read ((char*)&buffer, tam_meta_id);

	return buffer;
}

char* Persistencia::leerBloque(int idNodo) {
	bloque = new char[tam_bloque];
	fstream archivo (nombreArchivo.c_str() , ios::in | ios::binary);

	archivo.seekg (idNodo*tam_bloque);
	archivo.read (bloque, tam_bloque);

	return bloque;
}

void Persistencia::grabar(Nodo* unNodo, Registro* unRegistro) {
	escribirMetadatosNodo(unNodo);
	escribirRegistro(unNodo, unRegistro);
}

void Persistencia::escribirRegistro(Nodo* unNodo, Registro* unRegistro) {
	int offset = (unNodo->getID())*tam_bloque+tam_meta_arbol+tam_meta_nodo;
	escribirUnInt(unRegistro->getId(), offset);
	offset += 4;
	escribirUnString(unRegistro->getCodigo(), offset); //El codigo es un string de 3 caracteres
	offset += 3;
	//TODO registros long variable
	//TODO siempre se mete de un registro, aca hay que ver que tanto hay ocupado del bloque
	//para ver si entra el nuevo registro que se quiere meter. En caso de entrar, se actualiza
	//el flag de proximo registro en el registro ya cargado, y se le pone F en el flag del nuevo
	//registro cargado.
	escribirUnString("F", offset);
	offset += 1;
	escribirUnString(unRegistro->getDescripcion(), offset);


}

void Persistencia::escribirUnString(string array, int unaPos) {
	fstream archivo;
	archivo.open(nombreArchivo.c_str(), ios::out | ios::binary | ios::app );
	archivo.seekp(unaPos, ios::beg);
	archivo.write(array.c_str(), array.size());
	archivo.close();
}

void Persistencia::escribirUnInt(int unInt, int unaPos) {
	fstream archivo;
	archivo.open(nombreArchivo.c_str(), ios::out | ios::binary | ios::app );
	archivo.seekp(unaPos, ios::beg);
	archivo.write(reinterpret_cast<const char *>(&unInt), 4);
	archivo.close();
}

void Persistencia::escribirMaxIDNodo(int maxID) {
	escribirUnInt(maxID, 0);
}

void Persistencia::escribirMaxIDReg(int maxID) {
	escribirUnInt(maxID, tam_meta_id);
}

void Persistencia::escribirMetadatosNodo(Nodo* unNodo) {
	int offset = ((unNodo->getID())*tam_bloque)+tam_meta_arbol;
	escribirUnInt(unNodo->getID(), offset);
	offset += 4;
	escribirUnInt(unNodo->getEspacioLibre(), offset);
	offset += 4;
	escribirUnInt((unNodo->getHijoIzquierdo())->getID(), offset);
	offset += 4;
	escribirUnInt((unNodo->getHijoDerecho())->getID(), offset);
}

void Persistencia::grabarRegistroLongFija(Registro* unRegistro, int idNodo, int padding) {
	string flagDeTipo = "F";
	strcpy (buff_flagDeTipo, flagDeTipo.c_str());

	string codigo = unRegistro->getCodigo();
	ostringstream codigo_padding; //Relleno los espacios para mantener el bloque
	codigo_padding<<setfill('0')<<setw(tam_codigo);
	codigo_padding<<codigo;
	codigo = codigo_padding.str();
	strcpy (buff_codigo, (codigo).c_str());

	int tam_descrip = unRegistro->getTamanioDescripcion();
	string s_tam_desc; //Convierto el tamanio de la descripcion a string
	stringstream convert;
	convert << tam_descrip;
	s_tam_desc = convert.str();
	ostringstream tam_descrip_padding; //Relleno los espacios para mantener el bloque
	tam_descrip_padding<<setfill('0')<<setw(tam_descripcion);
	tam_descrip_padding<<s_tam_desc;
	s_tam_desc = tam_descrip_padding.str();
	strcpy(buff_tam_descripcion, (s_tam_desc).c_str());

	//Pido memoria segun la longitud de la descripcion
	buff_descripcion = new char [unRegistro->getTamanioDescripcion()];
	strcpy (buff_descripcion, (unRegistro->getDescripcion()).c_str());

	strcpy (buff_hijoIzquierdo, "V");
	strcpy (buff_hijoDerecho, "V");
	strcpy (buff_flagExisteRegistro, "0");

	//Creo el bloque
	strcat (buff_bloque, buff_flagDeTipo);
	strcat (buff_bloque, buff_codigo);
	strcat (buff_bloque, buff_tam_descripcion);
	strcat (buff_bloque, buff_descripcion);
	strcat (buff_bloque, buff_hijoIzquierdo);
	strcat (buff_bloque, buff_hijoDerecho);
	strcat (buff_bloque, buff_flagExisteRegistro);

	for(int i=0; i<tam_bloque; i++) {
		cout<<buff_bloque[i];
	}
	//escribir(buff_bloque, idNodo, tam_bloque, 4);

}

void Persistencia::escribirBloqueAlFinal(char* buffer, int idNodo) {
	fstream archivo;
	archivo.open(nombreArchivo.c_str(), ios::in | ios::out | ios::binary | ios::app);
	archivo.seekp(0, ios::end);
	archivo.write(buffer, tam_bloque);
	archivo.close();

	delete (buffer);
}

void Persistencia::escribirBloque(char* buffer, int idNodo, int posicion) { //posicion tiene que venir con +4 de metadatos
	fstream archivo;
	archivo.open(nombreArchivo.c_str(), ios::out | ios::in | ios::binary);
	archivo.seekp(posicion, ios::beg);
	archivo.write(buffer, tam_bloque);
	archivo.close();
	delete buffer;
}
