#ifndef ARBOLAVL_H_
#define ARBOLAVL_H_
#include "Registro.h"
#include <list>

using namespace std;

class Nodo;

#include "Nodo.h"
class ArbolAVL {
private:
	static const int idRaiz = 0;
	Nodo* raiz;
	string nombre;
	int maxIdReg;

public:
	ArbolAVL(string nombre);

	void insertar(string codigo, string descripcion);
	void borrarRegistro(int unID);
	void print();
	Nodo* getRaiz();
	Nodo* buscarNodoPorID(Nodo* unNodo, int idBuscado);
	Nodo* borrarRegistroPorID(Nodo* unNodo, int idBuscado, bool &existiaRegistro);
	int getMaxRegistroID();
	void modificarRegistro(int unID, string nuevoCodigo, string nuevaDescripcion);
	Registro* getRegistro(int unId);
	void buscarRegistro(int unID, Registro* &registro);
	virtual ~ArbolAVL();

private:
	Nodo* insertarEnNodo(Nodo* unNodo, Registro* unRegistro);
	Nodo* crearNodo(Registro* unRegistro);
	int rotacionDerecha(Nodo *unNodo);
	int rotacionIzquierda(Nodo *unNodo);
	int getDiferenciaAlturaHijos(Nodo* unNodo);
	int obtenerId(Nodo* unNodo);
	void preOrder(Nodo* root);
	void balancear(Nodo* unNodo);
	Nodo* solucionarUnderflow(Nodo* unNodo);
	Nodo* cargarRaiz();
	Nodo* devolverNodo(int unId);
	Nodo* modificarRegistroPorID(Nodo* unNodo, int idBuscado, string nuevoCodigo, string nuevaDescripcion);
	Nodo* buscarRegistroPorID(Nodo* unNodo, int idBuscado, Registro* &unRegistro);

};

#endif /* ARBOLAVL_H */
