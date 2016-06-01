/*
 * Persistencia.cpp
 *
 */
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include "Persistencia.h"

using namespace std;

struct pNodo {
	int tamano;

	int offsetIzq;
	int offsetDer;
};

void Persistencia::grabar(ArbolAVL* unArbol) {
	  fstream myFile ("myfile.bin", ios::out | ios::binary);
	  myFile.seekp(0);

	  Nodo* unNodo = unArbol->getRaiz();
	  Registro* unRegistro;

		list<Registro*>* registros = unNodo->getRegistros();
		for(list<Registro*>::iterator list_iter = registros->begin(); list_iter != registros->end(); list_iter++) {
			unRegistro = *list_iter;
			myFile.write((char*)unRegistro, sizeof(Registro));
		}

	  myFile.flush();
	  myFile.close();
}

void Persistencia::cargar() {
	  fstream myFile ("myfile.bin", ios::in | ios::binary);
	  Registro* unRegistro;

	  myFile.seekg (ios::beg);

	  myFile.read ((char*)unRegistro, sizeof(Registro));
	  std::cout<<unRegistro->getCodigo()<<endl;
	  myFile.read ((char*)unRegistro, sizeof(Registro));
	  std::cout<<unRegistro->getCodigo()<<endl;
	  myFile.read ((char*)unRegistro, sizeof(Registro));
	  std::cout<<unRegistro->getCodigo()<<endl;
}
