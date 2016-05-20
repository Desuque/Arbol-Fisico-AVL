/*
 * Interfaz.h
 *
 *  Created on: 20 de may. de 2016
 *      Author: desuque
 */

#ifndef SRC_INTERFAZ_H_
#define SRC_INTERFAZ_H_

class Interfaz {
private:
	int maxParametros = 4;


public:
	Interfaz(int argc, char *argv[]);
	virtual ~Interfaz();

private:
	void msgError();
	void msgHelp();
	void validarParametros(int argc, char *argv[]);
	void crearInstancia();
	void modificarInstancia();
	void eliminarInstancia();
	void listarInstancias();
};

#endif /* SRC_INTERFAZ_H_ */
