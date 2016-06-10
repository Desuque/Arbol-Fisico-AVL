#ifndef BLOQUE_H_
#define BLOQUE_H_

#include "Archivo.h"
#include "Registro.h"
#include "ArchivoDescrips.h"
#include "ArchivoLibres.h"

using namespace std;

class Archivo;

class Bloque {
private:
	static const int tamanio = 4096;
	static const int tamanio_meta = 21;
	static const int tamanio_max_descrinterna = 1000;
	string nombreArchivo;
	int id;
	int bytes_ocupados;
	int cantidad_registros;
	Archivo* archivoArbol;
	ArchivoDescrips* archivoDescripciones;
	ArchivoLibres* archivoLibres;

	struct offsetInicioFinBloque {
	  int off_inicioBloque;
	  int off_finBloque;
	} offsetInicioFin;

	void inicializarBloque();
	int calcularOffsetRegistros();
	int calcularOffsetMetadatos();
	int leerMayorIdBloque();
	int leerMayorIdReg();
	void escribirFlagExistencia();
	void escribirEspacioLibre();
	void escribirAltura(int altura);
	void escribirCantidadRegistros();
	void escribirBloqueVacio();
	void escribirMetaDatos(int idIzq, int idDer, int altura);

public:
	Bloque(string nombreArchivo);
	Bloque(string nombreArchivo, int id);
	bool entra(Registro* &unRegistro);
	void grabar(Nodo* unNodo);
	void escribirIdIzq(int unId);
	void escribirIdDer(int unId);
	int getId();
	int getMaxIdReg();
	Nodo* devolverNodo();
	virtual ~Bloque();
};

#endif   /* BLOQUE_H */
