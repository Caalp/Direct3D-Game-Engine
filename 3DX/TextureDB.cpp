#include "TextureDB.h"
#include <memory>
#include <iostream>
#include <cassert>
#include <filesystem>
#include <functional>
#include <fstream>
#include <Windows.h>
#include "Backend.h"


// For now I store texture at the backend and use CreateTexture function to create textures but this will change 
class DDSLoader
{
	enum dwFlags
	{
		DDPF_ALPHAPIXELS = 0x1,
		DDPF_ALPHA = 0x2,
		DDPF_FOURCC = 0x4,
		DDPF_RGB = 0x40,
		DDPF_YUV = 0x200,
		DDPF_LUMINANCE = 0x20000
	};
	enum EdwFourCC
	{
		DXT1 = 0x31545844,
		DXT2 = 0x32545844,
		DXT3 = 0x33545844,
		DXT4 = 0x34545844,
		DXT5 = 0x35545844,
		DX10 = 0x30315844

	};
	typedef struct {
		//DXGI_FORMAT              dxgiFormat;
		//D3D10_RESOURCE_DIMENSION resourceDimension;
		UINT                     miscFlag;
		UINT                     arraySize;
		UINT                     miscFlags2;
	} DDS_HEADER_DXT10;
	struct DDS_PIXELFORMAT {
		DWORD dwSize;
		DWORD dwFlags;
		DWORD dwFourCC;
		DWORD dwRGBBitCount;
		DWORD dwRBitMask;
		DWORD dwGBitMask;
		DWORD dwBBitMask;
		DWORD dwABitMask;
	};

	typedef struct {
		DWORD           dwSize;
		DWORD           dwFlags;
		DWORD           dwHeight;
		DWORD           dwWidth;
		DWORD           dwPitchOrLinearSize;
		DWORD           dwDepth;
		DWORD           dwMipMapCount;
		DWORD           dwReserved1[11];
		DDS_PIXELFORMAT ddspf;
		DWORD           dwCaps;
		DWORD           dwCaps2;
		DWORD           dwCaps3;
		DWORD           dwCaps4;
		DWORD           dwReserved2;
	} DDS_HEADER;
public:
	//Texture(Graphics& gfx, const class Surface& s);

	DDSLoader(const wchar_t* path)
	{

		
		std::ifstream file(path,std::ios_base::binary);
		if (!file.is_open())
		{
			// assert here
		}
		DDS_HEADER header;

		char magic[4];
		file.read(magic, 4);
		// magic value 'DDS '
		if (magic != "DDS ")
		{
			// opps file is not dds
			// halt the operation
		}

		
		file.read((char*)&header.dwSize, 4);
		file.read((char*)&header.dwFlags, 4);
		file.read((char*)&header.dwHeight, 4);
		file.read((char*)&header.dwWidth, 4);
		file.read((char*)&header.dwPitchOrLinearSize, 4);
		file.read((char*)&header.dwDepth, 4);
		file.read((char*)&header.dwMipMapCount, 4);
		file.read((char*)&header.dwReserved1, 4*11);
		file.read((char*)&header.ddspf, sizeof(DDSLoader::DDS_PIXELFORMAT));
		file.read((char*)&header.dwCaps, 4);
		file.read((char*)&header.dwCaps2, 4);
		file.read((char*)&header.dwCaps3, 4);
		file.read((char*)&header.dwCaps4, 4);
		file.read((char*)&header.dwReserved2, 4);

		if (header.ddspf.dwFlags == DDPF_FOURCC && header.ddspf.dwFourCC == EdwFourCC::DX10)
		{
			DDS_HEADER_DXT10 dx10Header;
			// read the header
		}


		


	}
	//Texture(const char* filePath, unsigned int bufferSlot = 0u);
	//Texture(ID3D11ShaderResourceView* paramSrv, unsigned int bufferSlot = 0u);

	~DDSLoader() = default;

private:
	//UINT bufferSlot;
	//ID3D11ShaderResourceView* srv;
};

static std::unique_ptr<TextureDB> s_instance;

void TextureDB::Init()
{
	s_instance.reset(new TextureDB);

	const char* texturePath = "E:\\Users\\calpy\\Source\\Repos\\Compiled\\3DX_Build\\Textures";
	for (const auto& entry : std::filesystem::directory_iterator(texturePath))
	{

		
		std::cout << "path: " << entry.path() << std::endl;
		std::cout << "filename w ext: " << entry.path().filename() << std::endl;
		std::cout << "filename w/o ext: " << entry.path().stem() << std::endl;


		std::wstring st = entry.path().filename().c_str();
		std::size_t hash = std::hash<std::wstring>{}(st);
		std::cout << "hash: " << hash << std::endl;

		TextureInfo info;
		info.m_name = entry.path().filename().c_str();
		info.m_extension = entry.path().extension().c_str();
		info.m_path = entry.path().c_str();

		//DDSLoader texLoader(entry.path().c_str());
		std::string filepath = entry.path().string();
		
		info.m_handle = backend::CreateTexture(filepath.c_str());

		
		s_instance.get()->m_textureStore[hash] = info;
	}

}

void TextureDB::Shutdown()
{
	s_instance.reset(nullptr);
}

TextureDB* TextureDB::GetInstance()
{
	assert(s_instance.get() != nullptr);
	return s_instance.get();
}

TextureHandle TextureDB::GetHandleToTexture(const wchar_t* name)
{
	size_t hash = std::hash<std::wstring>{}(name);
	// assert here texture not found
	assert(m_textureStore.find(hash) != m_textureStore.end());

	return m_textureStore[hash].m_handle;
}

TextureInfo TextureDB::GetTextureInfo(const wchar_t* name) const
{
	size_t hash = std::hash<std::wstring>{}(name);
	//if (m_textureStore.find(hash) == m_textureStore.end())
	//{
	//	// assert here texture not found
	//}
	assert(m_textureStore.find(hash) != m_textureStore.end());
	return m_textureStore.at(hash);
}

TextureDB::~TextureDB()
{
	std::cout << "TextureDB destructor called!" << std::endl;
}


