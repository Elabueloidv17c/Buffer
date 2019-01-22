#include "CCanvas.h"

int main()
{
	CCanvas prueba;
	prueba.Initialize(R8G8B8A8, 5, 5, '\0');

	prueba.DrawLine(0.5f, 0.5f, '@');
	prueba.DrawColumn(0.5f, 0.5f, '@');

	prueba.SetValue(0.5f, 0.1f, 'd');
	
	CCanvas copia;
	copia.Initialize(R8G8B8A8, 10, 10, '\0');
	copia.Copy(prueba, BILINEAR);

	std::cout << prueba.GetValue(0.5f, 0.1f) << std::endl << std::endl;
	
	prueba.PrintArray();
	copia.PrintArray();

	std::cin.get();

	return 0;
}