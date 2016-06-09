/*
 * Interfaz.h
 *
 *  Created on: 20 de may. de 2016
 *      Author: desuque
 */

#ifndef SRC_INTERFAZ_H_
#define SRC_INTERFAZ_H_

#include <iostream>
#include <string.h>
#include "ArbolAVL.h"

using namespace std;

class Interfaz {
private:
	int maxParametros = 6;
public:
	Interfaz(int argc, char *argv[]);
	virtual ~Interfaz();

private:
	void msgError();
	void msgHelp();
	void validarParametros(int argc, char *argv[]);
	void crearInstancia(char *argv[]);
	void modificarInstancia(char *argv[]);
	void eliminarInstancia(char *argv[]);
	void listarInstancias(char *argv[]);
	string renombrarArchivo(string nombreConBin);
};

#endif /* SRC_INTERFAZ_H_ */
