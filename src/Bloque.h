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
	string archivoConfigTamBloque = "tamBloque.conf";
	int tamanio;
	static const int tamanio_meta = 21;
	static const int tamanio_max_descrinterna = 1000;
	string nombreArchivo;
	int id;
	int bytes_ocupados;
	int cantidad_registros;
	Archivo* archivoArbol;
	ArchivoDescrips* archivoDescripciones;
	ArchivoLibres* archivoLibres;

public:
	Bloque(string nombreArchivo);
	Bloque(string nombreArchivo, int id);
	bool entra(Registro* &unRegistro);
	void grabar(Nodo* unNodo);
	void escribirIdIzq(int unId);
	void escribirIdDer(int unId);
	void escribirAltura(int altura);
	bool estaEnUnderflow(Nodo* unNodo);
	int getId();
	int getMaxIdReg();
	Nodo* devolverNodo();
	void borrarDescripcionArchivoDescrips(int idRegistro);
	virtual ~Bloque();

private:
	void inicializarBloque();
	int calcularOffsetRegistros();
	int calcularOffsetMetadatos();  //TODO: Deberia esta en Archivo.h y ser calcularOffsetBloque(bloque, tamanio)
	int leerMayorIdBloque();
	int leerMayorIdReg();
	void escribirFlagExistencia();
	void escribirEspacioLibre();
	void escribirCantidadRegistros();
	void escribirBloqueVacio();
	void escribirMetaDatos(int idIzq, int idDer, int altura);
	int setearTamanioBloque();
	void persistirRegistros(Nodo* unNodo, int maxIdReg);
};

#endif   /* BLOQUE_H */
