#include "TextureLoader.h"
#include <assert.h>

TextureLoader::TextureLoader(const char* filePath) 
	: index(0u)
	, width(0)
	, height(0)
	, imgFormat(FIF_UNKNOWN)
	, pImage(nullptr)
{
	if (std::filesystem::is_directory(filePath))
	{
		for (const auto& elem : std::filesystem::directory_iterator(filePath))
		{
			sfilePath.push_back(elem.path().generic_string());
			assert(LoadTexture(elem.path().generic_string().c_str()) == true);
		}
	}
	else
	{
		sfilePath.push_back(filePath);
		assert(LoadTexture(filePath) == true);
	}
}

TextureLoader::TextureLoader(std::vector<const char*> filePaths) 
	: index(0u)
	, width(0)
	, height(0)
	, imgFormat(FIF_UNKNOWN)
	, pImage(nullptr)
{
	for (size_t i = 0; i < filePaths.size(); i++)
	{
		if (std::filesystem::is_directory(filePaths[i]))
		{
			for (const auto& elem : std::filesystem::directory_iterator(filePaths[i]))
			{
				sfilePath.push_back(elem.path().generic_string());
				assert(LoadTexture(elem.path().generic_string().c_str()) == true);
			}
		}
		else
		{
			sfilePath.push_back(filePaths[i]);
			assert(LoadTexture(filePaths[i]) == true);
		}
	}
}

TextureLoader::TextureLoader(const TextureLoader& rhs)
{
	*this = rhs;
}

TextureLoader& TextureLoader::operator=(const TextureLoader& rhs)
{
	index = rhs.index;
	width = rhs.width;
	height = rhs.height;
	imgFormat = rhs.imgFormat;
	pImage = rhs.pImage;
	bits.clear();
	for (const auto& elem : rhs.bits)
	{
		bits.push_back(elem);
	}
	return *this;
}

TextureLoader::TextureLoader(const TextureLoader&& rhs)
{
	*this = std::move(rhs);
}

TextureLoader::~TextureLoader()
{
	// Free the image data
	if (pImage)
	{
		FreeImage_Unload(pImage);
	}
}

unsigned int TextureLoader::GetWidth() const
{
	return width;
}

uint32_t TextureLoader::GetMemoryPitch() const
{
	return memPitch;
}

unsigned int TextureLoader::GetHeight() const
{
	return height;
}

unsigned int TextureLoader::GetImageCount() const
{
	return bits.size();
}

FIBITMAP* TextureLoader::GetImage() const
{
	return pImage;
}
void TextureLoader::GetImageByIndex(unsigned int i)
{
	index = i;
}
const BYTE* TextureLoader::GetImageData(unsigned int index) const
{
	return bits[index];
}

std::vector<std::string> TextureLoader::filePath() const
{
	return this->sfilePath;
}

bool TextureLoader::LoadTexture(const char* filePath)
{
	auto a = sizeof(FIBITMAP);
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
	FIBITMAP* temp = FreeImage_ConvertTo32Bits(pImage);
	bits.emplace_back(FreeImage_GetBits(temp));
	memPitch = FreeImage_GetPitch(pImage);
	//width and height of image
	width = FreeImage_GetWidth(pImage);
	height = FreeImage_GetHeight(pImage);
	//If one of them is zero something is wrong return false
	// add checking for bits too
	if ((width == 0 || height == 0))
		return false;
	// else true successfully loaded
	return true;
}