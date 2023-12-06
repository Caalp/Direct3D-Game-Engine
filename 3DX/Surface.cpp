#include "Surface.h"
#include <fstream>
#include <assert.h>
#include <windows.h>


Surface::Surface(const std::string& filename)
{
	std::ifstream file(filename, std::ios_base::binary);
	assert(file);
	BITMAPFILEHEADER bmpfile;
	file.read(reinterpret_cast<char*>(&bmpfile),sizeof(bmpfile));

	BITMAPINFOHEADER bmpinfo;
	file.read(reinterpret_cast<char*>(&bmpinfo), sizeof(bmpinfo));
	width = bmpinfo.biWidth;
	
	assert(bmpinfo.biBitCount == 24 || bmpinfo.biBitCount == 32);
	assert(bmpinfo.biCompression == BI_RGB);
	bool bi32 = bmpinfo.biBitCount == 32;
	//const int size = bmpinfo.biSize;
	
	const int padding = (4 - (width * 3) % 4) % 4;
	file.seekg(bmpfile.bfOffBits);
	int pstart;
	int pend;
	int dy;

	if (bmpinfo.biHeight < 0)
	{
		height = -bmpinfo.biHeight;
		pstart = 0;
		pend = height;
		dy = 1;
	}
	else
	{
		height = bmpinfo.biHeight;
		pstart = height - 1;
		pend = -1;
		dy = -1;
	}
	
	pPixel = std::make_unique<Color[]> (height*width);
	
	for (int y = pstart; y != pend; y += dy)
	{
		for (int x = 0; x < width; x++)
		{
			PutPixel(x, y, Color(file.get(), file.get(), file.get()));
			
		}
		if (!bi32)
		{
			file.seekg(padding, std::ios_base::cur);
		}
		else if (bi32)
		{
			file.seekg(0, std::ios_base::cur);
		}
	}

}

Surface::Surface(int width, int height):
	width(width),
	height(height),
	pPixel(new Color[width*height])
{
}

Surface::Surface(const Surface& rhs):
	Surface(rhs.width,rhs.height)
{

	const int nPixel = width * height;
	for (int i = 0; i < nPixel; i++)
	{
		pPixel[i] = rhs.pPixel[i];
	}
}

Surface& Surface::operator=(const Surface& rhs)
{
	
	width = rhs.width;
	height = rhs.height;

	
	pPixel.reset(nullptr);
	const int nPixel = width * height;
	pPixel = std::make_unique<Color[]>(width*height);
	for (int i = 0; i < nPixel; i++)
	{
		pPixel[i] = rhs.pPixel[i];
	}
	
	
	return *this;
}

Surface::~Surface()
{
	pPixel.release();
}

void Surface::PutPixel(int x, int y, Color c)
{
	pPixel[y*width + x] = c;
}

Color Surface::GetPixel(int x, int y)const
{
	return pPixel[y*width+x];
}

const Color* Surface::GetColorPointer() const 
{
	return pPixel.get();
}



int Surface::GetWidth() const 
{
	return width;
}

int Surface::GetHeight() const
{
	return height;
}
