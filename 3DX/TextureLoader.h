#pragma once

#include "FreeImage/FreeImage.h"
#include <memory>
#include <filesystem>

#pragma comment(lib,"FreeImage/x86/FreeImage.lib")

class TextureLoader
{
public:
	TextureLoader() = default;
	TextureLoader(const char* filePath);
	TextureLoader(std::vector<const char*>filePaths);
	TextureLoader(const TextureLoader& rhs);
	TextureLoader& operator=(const TextureLoader& rhs);
	TextureLoader(const TextureLoader&& rhs);
	~TextureLoader();
	unsigned int GetWidth() const;
	uint32_t GetMemoryPitch() const;
	unsigned int GetHeight() const;
	unsigned int GetImageCount() const;
	FIBITMAP* GetImage() const;
	void GetImageByIndex(unsigned int i);
	const BYTE* GetImageData(unsigned int index = 0) const;
	std::vector<std::string> filePath() const;
private:
	bool LoadTexture(const char* filePath);
private:
	std::vector<std::string> sfilePath;
	unsigned int index;
	uint32_t memPitch;
	unsigned int width, height;
	FREE_IMAGE_FORMAT imgFormat;
	FIBITMAP* pImage = nullptr;
	std::vector<BYTE*> bits;
};