/*
 * Nodo.h
 *
 *  Created on: 26 de may. de 2016
 *      Author: desuque
 */

#ifndef PERSISTENCIA_H_
#define PERSISTENCIA_H_
#include "ArbolAVL.h"
#include "Nodo.h"
#include "Registro.h"
#include <fstream>


class Persistencia {

	/**
	 * Estructura del bloque fijo
	 *
	 * | flag tipo de bloque - codigo - tamaño descrip - descrip - flag existe registro - id hijo I - id hijo D |
	 *
	 */

private:
	static const int maxCaracteresRegistroFijo = 1000;

	int tam_bloque = 4096;
	int tam_espacioLibre = 4;
	int tam_flagDeTipo = 1; // 1 o 0 segun bloque de long fija (1) o bloque de long variable (0)
	int tam_codigo = 8; // Tamaño del codigo
	int tam_descripcion = 4; // En un registro de long fija, como maximo son 1000 caracteres
	int tam_flagExisteRegistro = 1; // 1 o 0 segun exista otro registro (1) o no (0)
	int tam_hijoIzquierdo = 4; // Tamaño del ID del hijo izquierdo
	int tam_hijoDerecho = 4;
	int tam_meta_id = 4; //Tamaño metadato mayor id registro, mayor id nodo
	int tam_meta_arbol = tam_meta_id*2; //Tamaño de todos los metadatos del arbol
	int tam_meta_nodo = 16;

	char* buff_espacioLibre;
	char* buff_bloque;
	char* buff_flagDeTipo;
	char* buff_codigo;
	char* buff_tam_descripcion;
	char* buff_descripcion;
	char* buff_flagExisteRegistro;
	char* buff_hijoIzquierdo;
	char* buff_hijoDerecho;

	char* bloque;

	string nombreArchivo;

public:
	Persistencia(string nombreArchivo);
	char* leerBloque(int id);
	void grabar(Nodo* unNodo, Registro* unRegistro);
	int leerMayorIdNodo();
	int leerMayorIdReg();

	bool esRegistroFijo(Registro* unRegistro);
	void escribirUnInt(int unInt, int unaPos);
	void escribirUnString(string array, int unaPos);
	void escribirMaxIDNodo(int maxID);
	void escribirMaxIDReg(int maxID);
	void escribirRegistro(Nodo* unNodo, Registro* unRegistro);


	//El padding sirve para grabar mas de un registro sabiendo hasta donde esta cargado
	void grabarRegistroLongFija(Registro* unRegistro, int idNodo, int padding);
	int calcularEspacioLibre(int padding, int tamanioDescripcion);
	void escribirMetadatosNodo(Nodo* unNodo);
	char* calcularEspacioLibreBloque(Registro* unRegistro);
	~Persistencia();
};

#endif /* NODO_H_ */
