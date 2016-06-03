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
	int tam_bloque = 4096;
	int tam_espacioLibre = 4;
	int tam_flagDeTipo = 1; // 1 o 0 segun bloque de long fija (1) o bloque de long variable (0)
	int tam_codigo = 8; // Tamaño del codigo
	int tam_descripcion = 4; // En un registro de long fija, como maximo son 1000 caracteres
	int tam_flagExisteRegistro = 1; // 1 o 0 segun exista otro registro (1) o no (0)
	int tam_hijoIzquierdo = 4; // Tamaño del ID del hijo izquierdo
	int tam_hijoDerecho = 4;

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

public:
	Persistencia();
	void leerBloque(int id);
	void grabar(Registro* unRegistro, int idNodo);

	//El padding sirve para grabar mas de un registro sabiendo hasta donde esta cargado
	void grabarRegistroLongFija(Registro* unRegistro, int idNodo, int padding);
	int calcularEspacioLibre(int padding, int tamanioDescripcion);
	void escribir(char* bloque, int idNodo, int padding);
	~Persistencia();
};

#endif /* NODO_H_ */
