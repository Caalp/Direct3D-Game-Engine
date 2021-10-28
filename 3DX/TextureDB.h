#pragma once
#include <unordered_map>
#include "defines.h"

enum class TextureType
{
	Diffuse = 0u,
	Specular,
	Normal,
	TextureArray,
	Count

};
struct TextureInfo
{
	const wchar_t* m_path;
	const wchar_t* m_name;
	const wchar_t* m_extension;
	uint32_t width, height;
	TextureType m_type;
	TextureHandle m_handle;

};

class TextureDB
{

public:
	static void Init();
	static void Shutdown();
	static TextureDB* GetInstance();

	TextureHandle GetHandleToTexture(const wchar_t* name);
	TextureInfo GetTextureInfo(const wchar_t* name) const;


	bool Load(const char* path, TextureType type);
	~TextureDB();
private:
	std::unordered_map<size_t, TextureInfo> m_textureStore;
};


