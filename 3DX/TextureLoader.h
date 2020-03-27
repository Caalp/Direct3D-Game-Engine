#pragma once

#include "FreeImage.h"
#include <memory>
#include <filesystem>
class TextureLoader
{
public:
	TextureLoader() = default;
	TextureLoader(const char* filePath);
	TextureLoader(const TextureLoader& rhs);
	TextureLoader& operator=(const TextureLoader& rhs);
	TextureLoader(const TextureLoader&& rhs);
	~TextureLoader();
	unsigned int GetWidth() const;
	unsigned int GetHeight() const;
	FIBITMAP* GetImage() const;
	void GetImageByIndex(unsigned int i);
	const BYTE* GetImageData(unsigned int index = 0) const;
	
	
private:

	bool LoadTexture(const char* filePath);
	
private:
	unsigned int index;
	unsigned int width, height;
	FREE_IMAGE_FORMAT imgFormat;
	FIBITMAP* pImage;
	std::vector<BYTE*> bits;
};