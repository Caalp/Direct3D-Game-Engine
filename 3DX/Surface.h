#pragma once
#include "Colors.h"
#include <string>
#include "DirectXTex.h"

class Surface
{
public:

	Surface(const std::wstring& filename);
	Surface(int width, int height);
	Surface(const Surface&);
	Surface& operator=(const Surface& rhs);
	~Surface();
	void PutPixel(int x, int y, Color c);
	Color GetPixel(int x, int y) const;
	const Color* GetColorPointer() const;
	int GetWidth() const;
	int GetHeight()const;
public:
	int height;
	int width;
	DXGI_FORMAT format = DXGI_FORMAT_B8G8R8A8_UNORM;
	std::unique_ptr<Color[]> pPixel;
};