#pragma once

#include "FreeImage.h"
#include <memory>
class TextureLoader
{
public:
	TextureLoader() = default;
	TextureLoader(const char* filePath);
	~TextureLoader();
	unsigned int GetWidth() const;
	unsigned int GetHeight() const;
	FIBITMAP* GetImage() const;
	const BYTE* GetImageData() const;
	
private:

	bool LoadTexture(const char* filePath);

private:
	unsigned int width, height;
	FREE_IMAGE_FORMAT imgFormat;
	FIBITMAP* pImage;
	BYTE* bits;
};