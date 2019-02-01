#include "CCanvas.h"

int main()
{
	CCanvas prueba;
	CCanvas copia;

	unsigned char* pixel = new unsigned char(4);

	for (size_t i = 0; i < 4; i++)
	{
		pixel[i] = 'T';
	}

	float* fPixel = new float(4);

	for (size_t i = 0; i < 4; i++)
	{
		fPixel[i] = 0.1f;
	}

	unsigned char defaultvalue = '\0';
	float fDefaultvalue = 0.0f;

	prueba.Initialize(RGB, 8, 8, &defaultvalue);
	copia.Initialize(RGBA, 12, 12, &fDefaultvalue);

	prueba.DrawLine(0.5f, 1.0f, 1.0f, 0.0f, fPixel, RGB);
	prueba.DrawLine(1.0f, 1.0f, 0.0f, 0.0f, pixel, RGB);
	
	copia.Copy(prueba, POINT);

	prueba.PrintArray();
	copia.PrintArray();

	std::cin.get();

	return 0;
}