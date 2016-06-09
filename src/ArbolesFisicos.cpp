#include "ArbolAVL.h"
#include "Interfaz.h"
#include "ArchivoLibres.h"
#include <string.h>
#include <iostream>

#include "Registro.h"

using namespace std;

/**
void creg(string codigo, string descr , ArbolAVL* arbol) {
	Registro* unRegistro;

	unRegistro = new Registro(codigo, descr);
	arbol->insertar(unRegistro);
}
**/

int main(int argc, char *argv[])
{
	Interfaz* interfaz = new Interfaz(argc, argv);
	delete interfaz;


	/**
	ArbolAVL* arbol = new ArbolAVL("DNIs");

	creg("LGD", "Leandro Gonzalo Devesa", arbol);
	creg("LHD", "Leandro Huemul Desuque", arbol);
	creg("ABC", "Contador de palabras y contador de caracteres es una herramienta que te permite contar la cantidad de palabras o de caracteres que posee un texto. Simplemente, debes posicionar el cursor dentro de la ventana y comenzar a escribir con el teclado. El sistema contará automáticamente la cantidad de palabras y caracteres que has ingresado. También es posible copiar y pegar un texto que hayas escrito fuera del sistema; automáticamente mostrará el recuento de palabras y caracteres del texto copiado. Además, Contador de palabras y contador de caracteres posee dos botones sobre la derecha de la pantalla, los cuales te permiten borrar y contar, respectivamente. Verás que uno de ellos posee un icono de una papelera con el que podrás borrar todo el contenido de la ventana. El otro, que posee el icono de una flecha, te permite contar palabras y caracteres de lo que hayas escrito. Saber el número de palabras o caracteres de un documento puede ser muy útil. Como ejemplo, si se le pide a un autor un mínimo o un máximo de palabras permitidas para escribir, el contador de palabras lo ayudará a saber si su artículo cumple con los requisitos.", arbol);
	//creg("ZZZ", "1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890", arbol);

	arbol->print();
	**/
	return 0;
}

