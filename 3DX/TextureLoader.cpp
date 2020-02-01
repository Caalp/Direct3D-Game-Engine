#include "TextureLoader.h"
#include <assert.h>

TextureLoader::TextureLoader(const char * filePath):
	width(0),height(0),
	imgFormat(FIF_UNKNOWN),
	pImage(nullptr),
	bits(nullptr)
{
	assert(LoadTexture(filePath) == true,"Image Loading in FreeImage is Failed");
}

TextureLoader::~TextureLoader()
{
	// Free the image data
	FreeImage_Unload(pImage);
}

unsigned int TextureLoader::GetWidth() const
{
	return width;
}

unsigned int TextureLoader::GetHeight() const
{
	return height;
}

FIBITMAP* TextureLoader::GetImage() const
{
	return pImage;
}

BYTE* TextureLoader::GetImageData() const
{
	return bits;
}

bool TextureLoader::LoadTexture(const char * filePath)
{
	
	
	//Image format.
	imgFormat = FreeImage_GetFileType(filePath, 0);

	//If format is still unknown get it from filename
	if (imgFormat == FIF_UNKNOWN)
		imgFormat = FreeImage_GetFIFFromFilename(filePath);
	//If still unknown return false
	if (imgFormat == FIF_UNKNOWN)
		return false;
	//Check if it can read and load the file
	if (FreeImage_FIFSupportsReading(imgFormat))
		pImage = FreeImage_Load(imgFormat, filePath);
	//If can't read return false
	if (!pImage)
		return false;
	//Get the image data
	bits = FreeImage_GetBits(pImage);
	//width and height of image
	width = FreeImage_GetWidth(pImage);
	height = FreeImage_GetHeight(pImage);
	//If one of them is zero something is wrong return false
	if ((bits == 0 || width == 0 || height == 0))
		return false;
	// else true successfully loaded
	return true;
}
