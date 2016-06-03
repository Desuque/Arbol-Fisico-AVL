#ifndef REGISTRO_H_
#define REGISTRO_H_

#include<string>

using namespace std;

class Registro {

	private:
		int id;
		string codigo;
		string descripcion;

	public:
		Registro(int id, string codigo, string descripcion);
		int getId();
		string getCodigo();
		string getDescripcion();
		int getTamanio();
		int getTamanioDescripcion();
};

#endif
