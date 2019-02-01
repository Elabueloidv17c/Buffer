#include "CCanvas.h"

CCanvas::CCanvas()
{
	m_buffer = nullptr;
	m_fBuffer = nullptr;
}

CCanvas::~CCanvas()
{
	if (m_buffer != nullptr)
	{
		delete[] m_buffer;
		m_buffer = nullptr;
	}

	if (m_fBuffer != nullptr)
	{
		delete[] m_fBuffer;
		m_fBuffer = nullptr;
	}
}

void CCanvas::Initialize(EFormat format, int lines, int columns, unsigned char* value)
{
	if (m_fBuffer != nullptr)
	{
		std::cout << "The buffer was already created with channels of 4 bytes" << std::endl;
		return;
	}

	if (m_buffer != nullptr)
	{
		std::cout << "The buffer already exist" << std::endl;
		return;
	}

	if (lines <= 0 || columns <= 0)
	{
		std::cout << "The size input is invalid, the buffer will be created with '1 X 1' size" << std::endl;
		lines = 1;
		columns = 1;
	}

	switch (format)
	{
	case(R):

		std::cout << "Format: R_8" << std::endl;
		break;

	case(RG):

		std::cout << "Format: RG_8" << std::endl;
		break;

	case(RGB):

		std::cout << "Format: RGB_8" << std::endl;
		break;

	case(RGBA):
		std::cout << "Format: RGBA_8" << std::endl;
		break;
	}

	m_format = format;
	m_lines = lines;
	m_columns = columns;
	m_subdivision = SUBDIVISIONS;

	m_pitch = lines * format;
	m_buffer = (unsigned char*) malloc (lines * columns * format);
	m_endBuffer = m_buffer + (lines * columns * format) - 1;

	for (size_t i = 0; i < m_columns; i++)
	{
		for (size_t j = 0; j < m_lines; j++)
		{
			for (size_t k = 0; k < m_format; k++)
			{
				m_buffer[(i * m_pitch) + (j * m_format) + k] = *value;
			}
		}
	}
}

void CCanvas::Initialize(EFormat format, int lines, int columns, float* value)
{
	if (m_fBuffer != nullptr)
	{
		std::cout << "The buffer already exist" << std::endl;
		return;
	}

	if (m_buffer != nullptr)
	{
		std::cout << "The buffer was already created with channels of 4 bytes" << std::endl;
		return;
	}

	if (lines <= 0 || columns <= 0)
	{
		std::cout << "The size input is invalid, the buffer will be created with '1 X 1' size" << std::endl;
		lines = 1;
		columns = 1;
	}

	switch (format)
	{
	case(R):

		std::cout << "Format: R_F32" << std::endl;
		break;

	case(RG):

		std::cout << "Format: RG_F32" << std::endl;
		break;

	case(RGB):

		std::cout << "Format: RGB_F32" << std::endl;
		break;

	case(RGBA):
		std::cout << "Format: RGBA_F32" << std::endl;
		break;
	}

	m_format = format;
	m_lines = lines;
	m_columns = columns;
	m_subdivision = SUBDIVISIONS;

	m_pitch = lines * m_format;
	m_fBuffer = (float*)malloc(lines * columns * m_format);
	m_fEndBuffer = m_fBuffer + (lines * columns * m_format) - 1;

	for (size_t i = 0; i < m_columns; i++)
	{
		for (size_t j = 0; j < m_lines; j++)
		{
			for (size_t k = 0; k < m_format; k++)
			{
				m_fBuffer[(i * m_pitch) + (j * m_format) + k] = *value;
			}
		}
	}
}

void CCanvas::PrintArray()
{
	if (m_buffer != nullptr)
	{
		for (size_t i = 0; i < m_columns; i++)
		{
			for (size_t j = 0; j < m_lines; j++)
			{
				std::cout << "|'";

				for (size_t k = 0; k < m_format; k++)
				{
					std::cout << m_buffer[(i * m_pitch) + (j * m_format) + k] << " ";
				}

				std::cout << "'|	";
			}

			std::cout << std::endl << std::endl;
		}

		std::cout << std::endl << std::endl;
	}

	if (m_fBuffer != nullptr)
	{
		for (size_t i = 0; i < m_columns; i++)
		{
			for (size_t j = 0; j < m_lines; j++)
			{
				std::cout << "|'";

				for (size_t k = 0; k < m_format; k++)
				{
					unsigned char toPrint = (unsigned char)(m_fBuffer[(i * m_pitch) + (j * m_format) + k] * 255);

					std::cout << toPrint << " ";
				}

				std::cout << "'|	";
			}

			std::cout << std::endl << std::endl;
		}

		std::cout << std::endl << std::endl;

	}
}

void CCanvas::Delete()
{
	m_buffer = nullptr;
	m_fBuffer = nullptr;

	m_endBuffer = nullptr;
	m_fEndBuffer = nullptr;

	m_subdivision = 0.0f;
	m_format = UNSET;

	m_columns = 0;
	m_lines = 0;
	m_pitch = 0;
}

void CCanvas::SetValue(float U, float V, unsigned char* pixel, EFormat format)
{
	if (U > 1.0f) { U = 1.0f; }
	if (U < 0.0f) { U = 0.0f; }
	if (V > 1.0f) { V = 1.0f; }
	if (V < 0.0f) { V = 0.0f; }

	if (format > m_format)
	{
		format = m_format;
	}

	unsigned int position = (((int)(U * (m_lines - 1)) * m_format) + (((int)(V * (m_columns - 1))) * m_pitch));
	unsigned int index = 0;

	if (m_buffer != nullptr)
	{
		while (index < format)
		{
			m_buffer[position + index] = pixel[index];
			index++;
		}

		while (index < m_format)
		{
			m_buffer[position + index++] = (unsigned char)0;
		}
	}

	if (m_fBuffer != nullptr)
	{
		while (index < format)
		{
			m_fBuffer[position + index] = (float) (pixel[index] / 255.0f);
			index++;
		}

		while (index < m_format)
		{
			m_fBuffer[position + index++] = 0.0f;
		}
	}
}

void CCanvas::SetValue(float U, float V, float* pixel, EFormat format)
{
	if (U > 1.0f) { U = 1.0f; }
	if (U < 0.0f) { U = 0.0f; }
	if (V > 1.0f) { V = 1.0f; }
	if (V < 0.0f) { V = 0.0f; }

	if (*pixel > 1.0f) { *pixel = 1.0f; }
	if (*pixel < 0.0f) { *pixel = 0.0f; }

	if (format > m_format)
	{
		format = m_format;
	}

	unsigned int position = (((int)(U * (m_lines - 1)) * m_format) + (((int)(V * (m_columns - 1))) * m_pitch));
	unsigned int index = 0;

	if (m_buffer != nullptr)
	{
		while (index < format)
		{
			m_buffer[position + index] = (unsigned char) (pixel[index] * 255);
			index++;
		}

		while (index < m_format)
		{
			m_buffer[position + index++] = (unsigned char)0;
		}
	}

	if (m_fBuffer != nullptr)
	{
		while (index < format)
		{
			m_fBuffer[position + index] = pixel[index];
			index++;
		}

		while (index < m_format)
		{
			m_fBuffer[position + index++] = 0.0f;
		}
	}
}

void CCanvas::DrawLine(float U1, float V1, float U2, float V2, unsigned char* pixel, EFormat format)
{
	//Ensuring valid indices
	if (U1 > 1.0f) { U1 = 1.0f; }
	if (U1 < 0.0f) { U1 = 0.0f; }
	if (V1 > 1.0f) { V1 = 1.0f; }
	if (V1 < 0.0f) { V1 = 0.0f; }

	if (U2 > 1.0f) { U2 = 1.0f; }
	if (U2 < 0.0f) { U2 = 0.0f; }
	if (V2 > 1.0f) { V2 = 1.0f; }
	if (V2 < 0.0f) { V2 = 0.0f; }

	//Setting values in the right order (if the first point is to the right)
	if (U1 > U2)
	{
		float tempU = U1;
		float tempV = V1;

		U1 = U2;
		V1 = V2;

		U2 = tempU;
		V2 = tempV;
	}

	//Creating the variables to calculate the inclination of the line 
	float m = m_subdivision * ((V2 - V1)/(U2 - U1));
	float index = 0;


	//Setting the information in the pixels
	for (float i = U1; i < U2 + m_subdivision;)
	{
		SetValue(i, V1 + (m * index), pixel, format);

		index += 1.0f;
		i += m_subdivision;
	}
}

void CCanvas::DrawLine(float U1, float V1, float U2, float V2, float* pixel, EFormat format)
{
	//Ensuring valid indices
	if (*pixel > 1.0f) { *pixel = 1.0f; }
	if (*pixel < 0.0f) { *pixel = 0.0f; }

	if (U1 > 1.0f) { U1 = 1.0f; }
	if (U1 < 0.0f) { U1 = 0.0f; }
	if (V1 > 1.0f) { V1 = 1.0f; }
	if (V1 < 0.0f) { V1 = 0.0f; }

	if (U2 > 1.0f) { U2 = 1.0f; }
	if (U2 < 0.0f) { U2 = 0.0f; }
	if (V2 > 1.0f) { V2 = 1.0f; }
	if (V2 < 0.0f) { V2 = 0.0f; }

	if (*pixel > 1.0f) { *pixel = 1.0f; }
	if (*pixel < 0.0f) { *pixel = 0.0f; }

	//Setting values in the right order (if the first point is to the right)
	if (U1 > U2)
	{
		float tempU = U1;
		float tempV = V1;

		U1 = U2;
		V1 = V2;

		U2 = tempU;
		V2 = tempV;
	}

	//Creating the variables to calculate the inclination of the line 
	float m = m_subdivision * ((V2 - V1) / (U2 - U1));
	float index = 0;

	//Setting the information in the pixels
	for (float i = U1; i < U2 + m_subdivision;)
	{
		SetValue(i, V1 + (m * index), pixel, format);

		index += 1.0f;
		i += m_subdivision;
	}
}

void* CCanvas::GetValue(float U, float V, EFormat& format)
{
	if (U > 1.0f) { U = 1.0f; }
	if (U < 0.0f) { U = 0.0f; }
	if (V > 1.0f) { V = 1.0f; }
	if (V < 0.0f) { V = 0.0f; }

	format = m_format;

	if (m_buffer != nullptr)
	{
		return m_buffer + (((int)(U * (m_lines - 1)) * m_format) + (((int)(V * (m_columns - 1))) * m_pitch));
	}

	if (m_fBuffer != nullptr)
	{
		return m_fBuffer + (((int)(U * (m_lines - 1)) * m_format) + (((int)(V * (m_columns - 1))) * m_pitch));
	}
}

//-----------------------------------------------------------------------------------------
void CCanvas::Copy(CCanvas& original, ESampler filter)
{
	EFormat currentFormat;

	if (filter == POINT)
	{
		std::cout << "Filter: Point" << std::endl;

		for (float i = 0.0f; i < 1.0f + m_subdivision;)
		{
			for (float j = 0.0f; j < 1.0f + m_subdivision;)
			{
				if (original.m_buffer != nullptr)
				{
					unsigned char* currentPixel = (unsigned char*) original.GetValue(j, i, currentFormat);

					if (m_buffer != nullptr)
					{
						SetValue(j, i, currentPixel, currentFormat);
					}

					if (m_fBuffer != nullptr)
					{
						float* floatPixel = new float[currentFormat];

						for (int k = 0; k < currentFormat; k++)
						{
							floatPixel[k] = (currentPixel[k] / 255.0f);
						}

						SetValue(j, i, currentPixel, currentFormat);

						delete[] floatPixel;
					}
				}

				if (original.m_fBuffer != nullptr)
				{
					float* currentPixel = (float*) original.GetValue(j, i, currentFormat);
					SetValue(j, i, currentPixel, currentFormat);
				}

				j += m_subdivision;
			}

			i += m_subdivision;
		}
	}

	else if (filter == BILINEAR)
	{
		std::cout << "Filter: Bilinear" << std::endl;

		for (float i = 0.0f; i < 1.0f + m_subdivision;)
		{
			for (float j = 0.0f; j < 1.0f + m_subdivision;)
			{
				unsigned short divisor = 1;
				unsigned char* currentPixel = (unsigned char*)original.GetValue(j, i, currentFormat);

				//Creating a copy of the current pixel and assigning the values from the original to it
				unsigned short*	pixelCopy = new unsigned short[currentFormat];

				for (int k = 0; k < currentFormat; k++)
				{
					pixelCopy[k] = (unsigned int) currentPixel[k];
				}

				//Adding the values of the adjacent pixels
				for (int k = 1; k <= BILINEAR; k++)
				{
					//Left pixel
					if (currentPixel - (currentFormat * k) >= original.m_buffer)
					{
						for (int l = 0; l < currentFormat; l++)
						{
							pixelCopy[l] += (unsigned int) *(currentPixel - currentFormat + l);
						}

						divisor++;
					}

					//Right pixel
					if ((currentPixel - original.m_buffer) * currentFormat + (currentFormat * k) < original.m_pitch)
					{
						for (int l = 0; l < currentFormat; l++)
						{
							pixelCopy[l] += (unsigned int) * (currentPixel + currentFormat + l);
						}

						divisor++;
					}

					//Pixel above
					if ((currentPixel - original.m_pitch * k) >= original.m_buffer)
					{
						for (int l = 0; l < currentFormat; l++)
						{
							pixelCopy[l] += (unsigned int) * (currentPixel - original.m_pitch + l);
						}

						divisor++;
					}

					//Pixel below
					if ((currentPixel + original.m_pitch * k) <= original.m_endBuffer)
					{
						for (int l = 0; l < currentFormat; l++)
						{
							pixelCopy[l] += (unsigned int) * (currentPixel + original.m_pitch + l);
						}

						divisor++;
					}
				}

				//Calculating the final value of the pixel by averaging
				unsigned char* newPixel = new unsigned char[currentFormat];

				for (int k = 0; k < currentFormat; k++)
				{
					newPixel[k] = pixelCopy[k] / divisor;
				}

				SetValue(j, i, newPixel, currentFormat);

				delete[] newPixel;
				delete[] pixelCopy;

				divisor = 1;
				j += m_subdivision;
			}

			i += m_subdivision;
		}
	}
}