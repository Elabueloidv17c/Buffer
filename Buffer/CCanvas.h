#pragma once
#include <iostream>

#define SUBDIVISIONS 0.05f;

enum EFormat
{
	UNSET = 0,
	R = 1,
	RG = 2,
	RGB = 3,
	RGBA = 4,
};

enum ESampler
{
	POINT = 1,
	BILINEAR = 2
};

class CCanvas
{
	unsigned char* m_buffer;
	unsigned char* m_endBuffer;

	float* m_fBuffer;
	float* m_fEndBuffer;

	float m_subdivision;
	EFormat m_format;

	unsigned int m_columns;
	unsigned int m_lines;
	unsigned int m_pitch;

public:

	void Initialize(EFormat format, int lines, int columns, unsigned char* value);
	void Initialize(EFormat format, int lines, int columns, float* value);

	void SetValue(float U, float V, unsigned char* pixel, EFormat format);
	void SetValue(float U, float V, float* pixel, EFormat format);

	void* GetValue(float U, float V, EFormat& format);
	
	void PrintArray();
	void Delete();
	//-----------------------------------------------------------------------------------------
	void DrawLine(float U1, float V1, float U2, float V2, unsigned char* pixel, EFormat format);
	void DrawLine(float U1, float V1, float U2, float V2, float* pixel, EFormat format);

	void Copy(CCanvas& original, ESampler filter);

	CCanvas();
	~CCanvas();
};