#ifndef BLOQUE_H_
#define BLOQUE_H_

#include "Registro.h"
#include "Persistencia.h"

using namespace std;

class Persistencia;

class Bloque {
private:
	static const int tamanio = 4096;
	static const int tamanio_meta = 17;
	static const int tamanio_max_descrinterna = 1000;
	string nombreArchivo;
	int id;
	int bytes_ocupados;
	int cantidad_registros;
	Persistencia* archivoArbol;

	void inicializarBloque();
	int calcularOffsetRegistros();
	int calcularOffsetMetadatos();
	int leerMayorIdBloque();
	int leerMayorIdReg();
	void escribirFlagExistencia();
	void escribirEspacioLibre();
	void escribirCantidadRegistros();
public:
	Bloque(string nombreArchivo);
	Bloque(string nombreArchivo, int id);
	bool entra(Registro* &unRegistro);
	void grabar(Nodo* unNodo);
	void escribirIdIzq(int unId);
	void escribirIdDer(int unId);
	Nodo* devolverNodo();
	virtual ~Bloque();
};

#endif   /* BLOQUE_H */
