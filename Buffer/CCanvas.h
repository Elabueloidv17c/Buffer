#pragma once
#include <iostream>

#define SUBDIVISIONS 0.1f;

enum Format
{
	UNSET = 0,
	R8 = 1,
	R8G8 = 2,
	R8G8B8 = 3,
	R8G8B8A8 = 4
};

enum Sampler
{
	POINT = 1,
	BILINEAR = 2
};

class CCanvas
{
	unsigned char* m_buffer;

	Format m_format;
	unsigned int m_columns;
	unsigned int m_lines;
	unsigned int m_pitch;

public:
	void Initialize(Format format, int lines, int columns, unsigned char value);
	void Delete();
	
	void SetValue(float U, float V, unsigned char value);
	unsigned char* GetValue(float U, float V);
	
	void DrawColumn(float U, float V, unsigned char value);
	void DrawLine(float U, float V, unsigned char value);
	
	void Copy(const CCanvas& original, Sampler filter);

	void PrintArray();

	CCanvas();
	~CCanvas();
};