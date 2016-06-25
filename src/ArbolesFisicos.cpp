#include "Interfaz.h"
#include <string.h>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
	Interfaz* interfaz = new Interfaz(argc, argv);
	delete interfaz;

	return 0;
}

