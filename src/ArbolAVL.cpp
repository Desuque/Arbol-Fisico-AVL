//============================================================================
// Name        : ArbolAVL.cpp
// Author      : DDTeam
// Version     :
// Copyright   : FIUBA  2016
//============================================================================

#include "Nodo.h"
#include "ArbolAVL.h"
#include <iostream>
#include <string.h>

using namespace std;

ArbolAVL::ArbolAVL(string nombre) {
	this->nombre = nombre;
	this->raiz = cargarRaiz();
}

Nodo* ArbolAVL::cargarRaiz() {
	Nodo* unNodo = new Nodo(this->nombre, 0);

	maxIdReg = unNodo->getMaxIdReg() + 1;

	if (unNodo->getRegistros() == 0) {
		unNodo = 0;
	}

	return unNodo;
}

Nodo* ArbolAVL::devolverNodo(int unId) {
	if (unId >= 0) {
		Nodo* unNodo = new Nodo(this->nombre, unId);
		if (unNodo->getRegistros() != 0) {
			return unNodo;
		}
	}

	return 0;
}

int altura(Nodo* unNodo) {
	if (unNodo == 0)
		return 0;

	return unNodo->getAltura();
}

void ArbolAVL::insertar(string codigo, string descripcion) {
	Registro* unRegistro;
	unRegistro = new Registro(codigo, descripcion);
	unRegistro->setId(maxIdReg);
	maxIdReg++;

	raiz = insertarEnNodo(raiz, unRegistro);
}

Nodo* ArbolAVL::crearNodo(Registro* unRegistro) {
	Nodo* unNodo = new Nodo(this->nombre);
	unNodo->insertar(unRegistro);

	return unNodo;
}

int calcMax(int x, int y)
{
	return (x > y)? x : y;
}

Nodo* ArbolAVL::insertarEnNodo(Nodo* unNodo, Registro* unRegistro) {

	if (unNodo == 0) {
		return crearNodo(unRegistro);
	} else {
		if (unRegistro->getId() < unNodo->getMenorID()) {
			if (unNodo->getHijoIzquierdo() == 0) {
				if (!unNodo->insertar(unRegistro)) {
					Nodo* nuevoNodo = crearNodo(unRegistro);
					unNodo->modificarHijoIzquierdo(nuevoNodo->getBloque()->getId());
				}
			} else {
				if (unRegistro->getId() > (devolverNodo(unNodo->getHijoIzquierdo()))->getMayorID()) {
					if (!unNodo->insertar(unRegistro)) {
						unNodo->modificarHijoIzquierdo(insertarEnNodo(devolverNodo(unNodo->getHijoIzquierdo()), unRegistro)->getBloque()->getId());
					}
				} else {
					unNodo->modificarHijoIzquierdo(insertarEnNodo(devolverNodo(unNodo->getHijoIzquierdo()), unRegistro)->getBloque()->getId());
				}
			}
		} else {
			if (unRegistro->getId() > unNodo->getMayorID()) {
				if (unNodo->getHijoDerecho() == -1) {
					if (!unNodo->insertar(unRegistro)) {
						Nodo* nuevoNodo = crearNodo(unRegistro);
						unNodo->modificarHijoDerecho(nuevoNodo->getBloque()->getId());
					}
				} else {
					if (unRegistro->getId() < devolverNodo(unNodo->getHijoDerecho())->getMenorID()) {
						if (!unNodo->insertar(unRegistro)) {
							unNodo->modificarHijoDerecho(insertarEnNodo(devolverNodo(unNodo->getHijoDerecho()), unRegistro)->getBloque()->getId());
						}
					} else {
						Nodo* nuevoNodo = insertarEnNodo(devolverNodo(unNodo->getHijoDerecho()), unRegistro);
						unNodo->modificarHijoDerecho(nuevoNodo->getBloque()->getId());
					}
				}
			} else {
				if (!unNodo->insertar(unRegistro)) {
					Registro* mayorRegistro = unNodo->getRegistroConMayorID();
					Registro* tmpRegistro = new Registro(mayorRegistro->getCodigo(), mayorRegistro->getDescripcion());
					tmpRegistro->setId(mayorRegistro->getId());

					unNodo->borrarRegistro(tmpRegistro->getId());
					unNodo->modificarHijoDerecho(insertarEnNodo(devolverNodo(unNodo->getHijoDerecho()), tmpRegistro)->getBloque()->getId());
					insertarEnNodo(unNodo, unRegistro);
				}
			}
		}

	}

	int altIzq = altura(devolverNodo(unNodo->getHijoIzquierdo()));
	int altDer = altura(devolverNodo(unNodo->getHijoDerecho()));

	unNodo->modificarAltura(calcMax(altIzq,altDer) + 1);

	int diferencia = getDiferenciaAlturaHijos(unNodo);

	//TODO: probar a fondo todas las rots. Algunos getHijoIzq a veces devuelven null o 0

	if ((diferencia > 1) && (unRegistro->getId() < devolverNodo(unNodo->getHijoIzquierdo())->getMenorID())) {
		return devolverNodo(rotacionDerecha(unNodo));
	}

	if ((diferencia < -1) && (unRegistro->getId() > devolverNodo(unNodo->getHijoDerecho())->getMayorID())) {
		return devolverNodo(rotacionIzquierda(unNodo));
	}

	if ((diferencia > 1) && (unRegistro->getId() > devolverNodo(unNodo->getHijoIzquierdo())->getMayorID()))
	{
		unNodo->modificarHijoIzquierdo(rotacionIzquierda(devolverNodo(unNodo->getHijoIzquierdo())));
		return devolverNodo(rotacionIzquierda(unNodo));
	}


	if ((diferencia < -1) && (unRegistro->getId() < devolverNodo(unNodo->getHijoDerecho())->getMenorID()))
	{
		unNodo->modificarHijoDerecho(rotacionDerecha(devolverNodo(unNodo->getHijoDerecho())));
		return devolverNodo(rotacionIzquierda(unNodo));
	}

	return unNodo;
}

int ArbolAVL::getDiferenciaAlturaHijos(Nodo* unNodo) {
	if (unNodo == 0)
			return 0;

	Nodo* izq = devolverNodo(unNodo->getHijoIzquierdo());
	Nodo* der = devolverNodo(unNodo->getHijoDerecho());

	int alturaIzq = altura(izq);
	int alturaDer = altura(der);

	return (alturaIzq-alturaDer);
}

int ArbolAVL::obtenerId(Nodo* unNodo) {
	if (unNodo != 0) {
		if (unNodo->getBloque() != 0) {
			return unNodo->getBloque()->getId();
		}
	}

	return -1;
}

int ArbolAVL::rotacionDerecha(Nodo *unNodo) {
	Nodo* izq = devolverNodo(unNodo->getHijoIzquierdo());
	Nodo* der = devolverNodo(izq->getHijoDerecho());

	// Si es la raiz tengo que reescribirla (si no, con cambiar los ids a los que referencian alcanza)
	if (unNodo->getBloque()->getId() == 0) {

		int idNodo = unNodo->getBloque()->getId();
		int idIzq = izq->getBloque()->getId();

		izq = izq->reescribirEn(idNodo);
		unNodo = unNodo->reescribirEn(idIzq);
	}

	izq->modificarHijoDerecho(unNodo->getBloque()->getId());
	unNodo->modificarHijoIzquierdo(der->getBloque()->getId());

	unNodo->modificarAltura(calcMax(altura(devolverNodo(unNodo->getHijoIzquierdo())), altura(devolverNodo(unNodo->getHijoDerecho()))) + 1);
	izq->modificarAltura(calcMax(altura(devolverNodo(izq->getHijoIzquierdo())), altura(devolverNodo(izq->getHijoDerecho()))) + 1);

	return izq->getBloque()->getId();
}

int ArbolAVL::rotacionIzquierda(Nodo *unNodo) {
	Nodo *der = devolverNodo(unNodo->getHijoDerecho());
	Nodo *izq = devolverNodo(der->getHijoIzquierdo());

	// Si es la raiz tengo que reescribirla (si no, con cambiar los ids a los que referencian alcanza)
	if (unNodo->getBloque()->getId() == 0) {

		int idNodo = unNodo->getBloque()->getId();
		int idDer = der->getBloque()->getId();

		der = der->reescribirEn(idNodo);
		unNodo = unNodo->reescribirEn(idDer);
	}

	der->modificarHijoIzquierdo(obtenerId(unNodo));
	unNodo->modificarHijoDerecho(obtenerId(izq));

	unNodo->modificarAltura(calcMax(altura(devolverNodo(unNodo->getHijoIzquierdo())), altura(devolverNodo(unNodo->getHijoDerecho()))) + 1);
	der->modificarAltura(calcMax(altura(devolverNodo(der->getHijoIzquierdo())), altura(devolverNodo(der->getHijoDerecho()))) + 1);

	return der->getBloque()->getId();
}

Nodo* ArbolAVL::getRaiz() {
	return raiz;
}

void ArbolAVL::print() {
	preOrder(raiz);
}

int ArbolAVL::getMaxRegistroID() {
	return this->raiz->getMaxIdReg();
}

void ArbolAVL::preOrder(Nodo* unNodo) {
	Registro* unRegistro;

	if(unNodo != 0) {
		cout<<"| ";
		list<Registro*>* registros = unNodo->getRegistros();
		for(list<Registro*>::iterator list_iter = registros->begin(); list_iter != registros->end(); list_iter++) {
			unRegistro = *list_iter;
			if (unNodo->getAltura() == 1) {
				cout<<unRegistro->getId()<<" ";
			} else {
				cout<<unRegistro->getId()<<" ";
			}
		}
		cout<<"|"<<endl;
		preOrder(devolverNodo(unNodo->getHijoIzquierdo()));
		preOrder(devolverNodo(unNodo->getHijoDerecho()));
	}
}

Registro* ArbolAVL::getRegistro(int unId) {
	Registro* registro;
	buscarRegistro(unId, registro);
	return registro;
}

void ArbolAVL::buscarRegistro(int unID, Registro* &registro) {
	raiz = buscarRegistroPorID(raiz, unID, registro);
}

Nodo* ArbolAVL::buscarRegistroPorID(Nodo* unNodo, int idBuscado, Registro* &unRegistro) {
	if(unNodo != 0) {
		int menorID = unNodo->getMenorID();
		int mayorID = unNodo->getMayorID();
		if (idBuscado < menorID) {
			buscarRegistroPorID(devolverNodo(unNodo->getHijoIzquierdo()), idBuscado, unRegistro);
		} else {
			if (idBuscado > mayorID) {
				buscarRegistroPorID(devolverNodo(unNodo->getHijoDerecho()), idBuscado, unRegistro);
			} else {
				if (unNodo->existeRegistroConID(idBuscado)) {
					unRegistro = unNodo->getRegistro(idBuscado);
				} else {
					unRegistro = NULL; // En interfaz pregunta si es NULL
				}
			}
		}
	} else {
		unRegistro = NULL; // En interfaz pregunta si es NULL
	}
	return unNodo;
}

void ArbolAVL::modificarRegistro(int unID, string nuevoCodigo, string nuevaDescripcion) {
	bool existiaRegistro = false;
	raiz = modificarRegistroPorID(raiz, unID, nuevoCodigo, nuevaDescripcion, existiaRegistro);

	if (existiaRegistro) {
		cout<<"El registro con ID: "<<unID<<" fue modificado con exito."<<endl;
	} else {
		cout<<"El registro con ID: "<<unID<<" no existe, no es posible modificarlo."<<endl;
	}
}

Nodo* ArbolAVL::modificarRegistroPorID(Nodo* unNodo, int idBuscado, string nuevoCodigo, string nuevaDescripcion, bool &existiaRegistro) {
	if(unNodo != 0) {
		int menorID = unNodo->getMenorID();
		int mayorID = unNodo->getMayorID();
		if (idBuscado < menorID) {
			modificarRegistroPorID(devolverNodo(unNodo->getHijoIzquierdo()), idBuscado, nuevoCodigo, nuevaDescripcion, existiaRegistro);
		} else {
			if (idBuscado > mayorID) {
				modificarRegistroPorID(devolverNodo(unNodo->getHijoDerecho()), idBuscado, nuevoCodigo, nuevaDescripcion, existiaRegistro);
			} else {
				if (unNodo->existeRegistroConID(idBuscado)) {
					if (unNodo->modificarRegistro(idBuscado, nuevoCodigo, nuevaDescripcion)) {
						existiaRegistro = true;
					}
				}
			}
		}
	}
	return unNodo;
}

void ArbolAVL::borrarRegistro(int unID) {
	bool existiaRegistro = false;
	raiz = borrarRegistroPorID(raiz, unID, existiaRegistro);

	if (existiaRegistro) {
		cout<<"El registro con ID: "<<unID<<" fue eliminado con exito."<<endl;
	} else {
		cout<<"El registro con ID: "<<unID<<" no existe."<<endl;
	}
}

Nodo* ArbolAVL::borrarRegistroPorID(Nodo* unNodo, int idBuscado, bool &existiaRegistro) {
	if(unNodo != 0) {
		int menorID = unNodo->getMenorID();
		int mayorID = unNodo->getMayorID();
		if ((idBuscado < menorID) && (menorID != NULL)) {
			borrarRegistroPorID(devolverNodo(unNodo->getHijoIzquierdo()), idBuscado, existiaRegistro);

			//Quito la referencia al hijo
			Nodo* hijoIzq = devolverNodo(unNodo->getHijoIzquierdo());
			if (hijoIzq == 0) {
				unNodo->modificarHijoIzquierdo(-1);
			}
		} else {
			if ((idBuscado > mayorID) && (mayorID != NULL)) {
				borrarRegistroPorID(devolverNodo(unNodo->getHijoDerecho()), idBuscado, existiaRegistro);

				//Quito la referencia al hijo
				Nodo* hijoDer = devolverNodo(unNodo->getHijoDerecho());
				if (hijoDer == 0 ) {
					unNodo->modificarHijoDerecho(-1);
				}

			} else {
				existiaRegistro = unNodo->borrarRegistro(idBuscado);
				if (existiaRegistro) {
					if (unNodo->estaEnUnderflow()) {
						unNodo = solucionarUnderflow(unNodo);
					}
				}
			}
		}
	}

	return unNodo;
}

Nodo* ArbolAVL::solucionarUnderflow(Nodo* unNodo) {
	// Si esta en underflow -> tiene al menos 1 hijo izq y/o 1 hijo der
	Nodo* nodoHijo;
	Registro* unRegistro;

	// Si tiene hijo der, me traigo los registros necesarios de ahi
	if (unNodo->getHijoDerecho() != -1) {
		nodoHijo = devolverNodo(unNodo->getHijoDerecho());

		while ((unNodo->estaEnUnderflow()) && (nodoHijo != 0)) {

			unRegistro = nodoHijo->getRegistroConMenorID();

			/**
			 * Se desactiva la salida estandar para poder solucionar el underflow
			 * sin mostrar que un registro se ha borrado (en realidad se mueve).
			 * De esta forma el underflow se hace transparente al usuario.
			 */
			streambuf* orig_buf = cout.rdbuf();
			cout.rdbuf(0);

			//Se borra el registro a mover sin mostrar el mensaje de "Registro borrado con exito"
			borrarRegistro(unRegistro->getId()); // Si por sacar del hijo, este queda en UF -> pasara por esta rutina automaticamente

			/**
			 * Reactivo la salida estandar luego de solucionado el underflow
			 */
			cout.rdbuf(orig_buf);

			unNodo->insertar(unRegistro);
			nodoHijo = devolverNodo(unNodo->getHijoDerecho());
		}
	}
	// Si no tenia hijo der o no alcanzo con los registros del der, pruebo con los reg del izq
	if (unNodo->estaEnUnderflow()) {
		if (unNodo->getHijoIzquierdo() != -1) {
			nodoHijo = devolverNodo(unNodo->getHijoIzquierdo());

			while ((unNodo->estaEnUnderflow()) && (nodoHijo != 0)) {

				unRegistro = nodoHijo->getRegistroConMayorID();
				borrarRegistro(unRegistro->getId()); // Si por sacar del hijo, este queda en UF -> pasara por esta rutina automaticamente
				unNodo->insertar(unRegistro);

				nodoHijo = devolverNodo(unNodo->getHijoIzquierdo());
			}
		}
	}

	return unNodo;
}

Nodo* ArbolAVL::buscarNodoPorID(Nodo* unNodo, int idBuscado) {
	if(unNodo != 0) {
		int menorID = unNodo->getMenorID();
		int mayorID = unNodo->getMayorID();
		if (!unNodo->existeRegistroConID(idBuscado)) {
			if (idBuscado < menorID) {
				return buscarNodoPorID(devolverNodo(unNodo->getHijoIzquierdo()), idBuscado);
			}
			if (idBuscado > mayorID) {
				return buscarNodoPorID(devolverNodo(unNodo->getHijoDerecho()), idBuscado);
			}
		} else {
			return unNodo;
		}
	}
	return 0;
}

ArbolAVL::~ArbolAVL() {
	// TODO Auto-generated destructor stub
}
