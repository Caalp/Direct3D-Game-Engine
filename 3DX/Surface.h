#pragma once
#include "Colors.h"
#include <string>


class Surface
{
public:

	Surface(const std::string& filename);
	Surface(int width, int height);
	Surface(const Surface&);
	Surface& operator=(const Surface& rhs);
	~Surface();
	void PutPixel(int x, int y, Color c);
	Color GetPixel(int x, int y) const;
	Color* GetColorPointer();
	int GetWidth() const;
	int GetHeight()const;
public:
	int height;
	int width;
	std::unique_ptr<Color[]> pPixel;
};