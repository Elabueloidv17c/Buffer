#include "CCanvas.h"

CCanvas::CCanvas()
{
	m_buffer = nullptr;
}

CCanvas::~CCanvas()
{
	if (m_buffer != nullptr)
	{
		delete[] m_buffer;
		m_buffer = nullptr;
	}
}

void CCanvas::Delete()
{
	m_buffer = nullptr;

	m_format = UNSET;
	m_columns = 0;
	m_lines = 0;
	m_pitch = 0;
}

void CCanvas::Initialize(Format format, int lines, int columns, unsigned char value)
{
	if (lines <= 0 || columns <= 0)
	{
		std::cout << "The size input is invalid, the buffer will be created with '1 X 1' size" << std::endl;
		lines = 1;
		columns = 1;
	}

	if (m_buffer != nullptr)
	{
		std::cout << "The buffer already exist" << std::endl;
		return;
	}

	switch (format)
	{
	case(R8):

		std::cout << "Format: R8" << std::endl;
		break;

	case(R8G8):

		std::cout << "Format: R8G8" << std::endl;
		break;

	case(R8G8B8):

		std::cout << "Format: R8G8B8" << std::endl;
		break;

	case(R8G8B8A8):
		std::cout << "Format: R8G8B8A8" << std::endl;
		break;
	}

	m_format = format;
	m_lines = lines;
	m_columns = columns;

	m_pitch = lines * format;
	m_buffer = (unsigned char*) malloc (lines * columns * format);

	for (size_t i = 0; i < m_columns; i++)
	{
		for (size_t j = 0; j < m_lines; j++)
		{
			for (size_t k = 0; k < m_format; k++)
			{
				m_buffer[(i * m_pitch) + (j * m_format) + k] = value;
			}
		}
	}
}

void CCanvas::SetValue(float U, float V, unsigned char value)
{
	if (U >= 0 && U <= 1 && V >= 0 && V <= 1)
	{

		unsigned int position = (((int)(U * (m_lines - 1) * m_format) + (((int)(V * (m_columns - 1))) * m_pitch)));

		for (size_t i = 0; i < m_format; i++)
		{
			m_buffer[position + i] = value;
		}
	}

	else
	{
		std::cout << "Positions out of range" << std::endl;
	}
}

unsigned char* CCanvas::GetValue(float U, float V)
{
	if (U >= 0 && U <= 1 && V >= 0 && V <= 1)
	{
		return m_buffer + (((int) (U * (m_lines - 1) * m_format) + (((int) (V * (m_columns - 1))) * m_pitch)));
	}

	else
	{
		std::cout << "Positions out of range" << std::endl;
		return m_buffer;
	}
}

void CCanvas::PrintArray()
{
	for (size_t i = 0; i < m_columns; i++)
	{
		for (size_t j = 0; j < m_lines; j++)
		{
			std::cout << "|'";

			if (m_format > 1)
			{
				for (size_t k = 0; k < m_format; k++)
				{
					std::cout << m_buffer[(i * m_pitch) + (j * m_format) + k];
				}

				std::cout << "'|	";
			}

			else
			{
				std::cout << m_buffer[(i * m_columns) + j] << "'|	";
			}
		}

		std::cout << std::endl << std::endl;
	}

	std::cout << std::endl << std::endl;
}

void CCanvas::DrawLine(float U, float V, unsigned char value)
{
	if (U >= 0 && U <= 1 && V >= 0 && V <= 1)
	{
		unsigned int position = (((int)(U * (m_lines - 1) * m_format) + (((int)(V * (m_columns - 1))) * m_pitch)));
		unsigned int start = (int) (U * (m_lines - 1) * m_format);
		long index = 0;

		while (start < m_pitch)
		{
			m_buffer[position + (index++)] = value;
			start++;
		}
	}

	else
	{
		std::cout << "Positions out of range" << std::endl;
	}
}

void CCanvas::DrawColumn(float U, float V, unsigned char value)
{
	if (U < m_columns && V < m_lines)
	{
		unsigned int position = (((int)(U * (m_lines - 1) * m_format) + (((int)(V * (m_columns - 1))) * m_pitch)));
		size_t arraySize = m_pitch * m_lines;

		while (position < arraySize)
		{
			for (size_t i = 0; i < m_format; i++)
			{
				m_buffer[position + i] = value;
			}

			position += m_pitch;
		}
	}

	else
	{
		std::cout << "Positions out of range" << std::endl;
	}
}

void CCanvas::Copy(const CCanvas& original, Sampler filter)
{
	unsigned int format = m_format;

	if (original.m_format < m_format)
	{
		format = original.m_format;
	}

	if (filter == POINT)
	{
		std::cout << "Filter: Point" << std::endl;

		for (float i = 0.0f; i <= 1.01f;)
		{
			for (float j = 0.0f; j <= 1.01f;)
			{
				for (size_t k = 0; k < format; k++)
				{
					m_buffer[((int)(i * (m_lines - 1)) * m_pitch) + ((int)(j * (m_columns - 1)) * m_format) + k] = original.m_buffer
					[((int)(i * (original.m_lines - 1)) * original.m_pitch) + ((int)(j * (original.m_columns - 1)) * original.m_format) + k];
				}

				j += SUBDIVISIONS;
			}

			i += SUBDIVISIONS;
		}
	}

	else if (filter == BILINEAR)
	{
		std::cout << "Filter: Bilinear" << std::endl;

		int X = 0;
		int Y = 0;
		int position = 0;
		
		int originalX = 0;
		int originalY = 0;
		int originalPosition = 0;

		int currentValue = 0;
		int numValues = 1;

		for (float i = 0.0f; i <= 1.01f;)
		{
			for (float j = 0.0f; j <= 1.01f;)
			{
				for (size_t k = 0; k < format; k++)
				{
					X = ((int)(j * (m_columns - 1)) * m_format);
					Y = ((int)(i * (m_lines - 1)) * m_pitch);
					originalX = ((int)(j * (original.m_columns - 1)) * original.m_format);
					originalY = ((int)(i * (original.m_lines - 1)) * original.m_pitch);

					position = Y + X + k;
					originalPosition = originalY + originalX + k;

					numValues = 1;
					currentValue = (int) original.m_buffer[originalPosition];
					
					for (size_t z = 1; z <= BILINEAR; z++)
					{
						if (originalX + (z * original.m_format) < original.m_pitch)
						{
							currentValue += (int)original.m_buffer[originalPosition + (z * original.m_format)];
							numValues++;
						}
						
						if (originalX >= (z * original.m_format))
						{
							currentValue += (int)original.m_buffer[originalPosition - (z * original.m_format)];
							numValues++;
						}
						
						if ((originalPosition + (original.m_pitch * z)) < (original.m_lines * original.m_columns * original.m_format))
						{
							currentValue += (int)original.m_buffer[originalPosition + (z * original.m_pitch)];
							numValues++;
						}
						
						if (originalPosition >= (original.m_pitch * z))
						{
							currentValue += (int)original.m_buffer[originalPosition - (z * original.m_pitch)];
							numValues++;
						}
					}

					for (size_t z = 0; z < format; z++)
					{
						m_buffer[position + z] = currentValue / numValues;
					}

				}

				j += SUBDIVISIONS;
			}

			i += SUBDIVISIONS;
		}
	}
}