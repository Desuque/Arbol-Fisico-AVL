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

class Persistencia {

private:


public:
	void grabar(ArbolAVL* unArbol);
	void cargar();
};

#endif /* NODO_H_ */
