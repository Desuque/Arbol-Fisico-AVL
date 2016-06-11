#ifndef ARCHIVO_H_
#define ARCHIVO_H_
#include "ArbolAVL.h"
#include "Nodo.h"
#include "Registro.h"
#include <fstream>

class Archivo {


	// ---------------    Arbol    -------------------------------
	//     [4b]         [4b]   =  8b de tam_meta_arbol
	// Max ID Nodo - Max ID Reg

private:
	static const int tam_meta_arbol = 8;

	string nombreArchivo;
	int offsetInicioBloque;

	int calcularOffsetNodo(int idNodo); //TODO: Implementar en esta clase
	void verificarArchivo();
	void inicializarNodo(int idNodo);

public:
	Archivo(string nombreArchivo);

	char* leerBloque(int id, int tamBloque);
	int leerMayorIdNodo();
	int leerMayorIdReg();

	void escribirUnInt(int unInt, int &unaPos);
	void escribirUnString(string array, int &unaPos);
	void escribirNull(int offset, int tamanio);
	void escribirMaxIDNodo(int maxID);
	void escribirMaxIDReg(int maxID);

	int getTamanioMetadatos();
	~Archivo();
};

#endif /* PERSISTENCIA_H */
