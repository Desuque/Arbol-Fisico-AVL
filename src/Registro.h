#ifndef REGISTRO_H_
#define REGISTRO_H_

#include<string>

using namespace std;

class Registro {

	private:
		int id;
		string codigo;
		string descripcion;
		static const int maxLongCodigo = 3;

	public:
		Registro(string codigo, string descripcion);
		void setId(int unId);
		void setCodigo(string nuevoCodigo);
		void setDescripcion(string nuevaDescripcion);
		int getId();
		string getCodigo();
		string getDescripcion();
		int getTamanio();
		int getTamanioDescripcion();
		~Registro();
};

#endif /* REGISTRO_H */
