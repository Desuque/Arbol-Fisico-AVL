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

char* Persistencia::calcularEspacioLibreBloque(Registro* unRegistro) {
	buff_espacioLibre = new char[tam_espacioLibre];

	//Calculo el espacio libre luego de insertar el registro
	int resto = tam_espacioLibre + tam_flagDeTipo + tam_codigo + tam_descripcion + unRegistro->getTamanioDescripcion() + tam_flagExisteRegistro + tam_hijoIzquierdo + tam_hijoDerecho;
	int espacioLibre =  tam_bloque - resto;

	string s_espacioLibre; //Convierto el tamanio de espacio libre a string
	stringstream convertir;
	convertir << espacioLibre;
	s_espacioLibre = convertir.str();

	ostringstream espacioLibre_padding; //Relleno los espacios para mantener el bloque
	espacioLibre_padding<<setfill('0')<<setw(tam_espacioLibre);
	espacioLibre_padding<<s_espacioLibre;
	s_espacioLibre = espacioLibre_padding.str();
	strcpy(buff_espacioLibre, (s_espacioLibre).c_str());

	return buff_espacioLibre;
}

void Persistencia::grabar(Registro* unRegistro, int idNodo) {
	//Grabo el espacio libre
	escribirMetadatosNodo(calcularEspacioLibreBloque(unRegistro), 2); //offset= 2


	cout<<"sale"<<endl;
	/**
	leerBloque(idNodo); //Queda el bloque a leer cargado en la variable bloque

	//TODO falta calcular que el registro a ingresar tiene mas de 1000 caracteres, aca supongo que es fijo siempre

	int cargaDeBloque = strlen(bloque);

	if (cargaDeBloque == 0) { //Quiere decir que el bloque esta vacio, habria que ver con lo del espacio libre como hacemos
		grabarRegistroLongFija(unRegistro, idNodo, tam_espacioLibre);
	} else { //Supongo que ya hay un registro cargado
		grabarRegistroLongFija(unRegistro, idNodo, cargaDeBloque);
	}**/
	//grabarRegistroLongFija(unRegistro, idNodo, 0);
}

void Persistencia::escribirUnInt(int unInt, int unaPos) {
	fstream archivo;
	archivo.open(nombreArchivo.c_str(), ios::out | ios::binary | ios::app );
	archivo.seekp(0, ios::beg);
	archivo.write(reinterpret_cast<const char *>(&unInt), 4);
	archivo.close();
}

void Persistencia::escribirMaxIDNodo(int maxID) {
	escribirUnInt(maxID, 0);
}

void Persistencia::escribirMaxIDReg(int maxID) {
	escribirUnInt(maxID, tam_meta_id);
}

void Persistencia::escribirMetadatosNodo(char* buffer, int posicion) {
	fstream archivo;
	archivo.open(nombreArchivo.c_str(), ios::out | ios::binary );
	archivo.seekp(posicion);
	string str(buffer);
	archivo.write(buffer, str.size());
	archivo.close();
	delete buffer;
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
