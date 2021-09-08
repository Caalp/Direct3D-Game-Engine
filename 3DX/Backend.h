#pragma once
#include "config.h"
#include "IRenderer.h"


DEFINE_HANDLER(VertexBufferHandle)
DEFINE_HANDLER(IndexBufferHandle)
DEFINE_HANDLER(VertexLayoutHandle)
DEFINE_HANDLER(ConstantBufferHandle)
DEFINE_HANDLER(ShaderHandle) 




namespace backend
{
	enum ShaderType : U8
	{
		PS = 0u,
		VS = 1u,
		CS = 2u,
		HS = 3u,
	};

	template<ShaderType> struct ShaderDesc {};
	template<> struct ShaderDesc<VS>
	{
		std::string shaderName;
		Microsoft::WRL::ComPtr<ID3D11VertexShader> shader;
		void Create(ID3DBlob* blob)
		{
			GraphicsResources::GetSingleton().pDevice->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &shader);
		}
		void Bind()
		{
			GraphicsResources::GetSingleton().pImmediateContext->VSSetShader(shader.Get(), nullptr, 0u);
		}
	};
	template<> struct ShaderDesc<PS>
	{
		std::string shaderName;
		Microsoft::WRL::ComPtr<ID3D11PixelShader> shader;
		void Create(ID3DBlob* blob)
		{
			GraphicsResources::GetSingleton().pDevice->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &shader);
		}
		void Bind()
		{
			GraphicsResources::GetSingleton().pImmediateContext->PSSetShader(shader.Get(), nullptr, 0u);
		}
	};
	template<ShaderType type>
	class Shader
	{
	public:
		Microsoft::WRL::ComPtr<ID3DBlob> GetBlob()
		{
			return m_blob;
		}
		void Create(std::string filename)
		{
			m_shader.shaderName = filename;
			// read shader to blob
			std::string fullPath = SHADER_DIRECTORY + m_shader.shaderName;
			D3DReadFileToBlob(std::wstring(fullPath.begin(), fullPath.end()).c_str(), &m_blob);
			m_shader.Create(m_blob.Get());
		}
		std::string GetType() const
		{
			switch (type)
			{
			case backend::PS:
				return "PS";
				break;
			case backend::VS:
				return "VS";
				break;
			case backend::CS:
				return "CS";
				break;
			case backend::HS:
				return "HS";
				break;
			default:
				break;
			}
		}
		U8 GetTypeId() const
		{
			return (U8)type;
		}
		void Bind()
		{
			m_shader.Bind();
		}
	private:
		ShaderDesc<type> m_shader;
		Microsoft::WRL::ComPtr<ID3DBlob> m_blob;
	};


	// static idx until alloc op
	static uint16_t vbh_idx = 0;
	static uint16_t ibh_idx = 0;
	static uint16_t vsh_idx = 0;
	static uint16_t psh_idx = 0;
	static uint16_t sh_idx = 0;

	//DEFINE_HANDLER(VertexBufferHandler)
	constexpr uint8_t k_sortKeyFullscreenLayerNumBits = 2u;
	constexpr uint8_t k_sortKeyFullscreenLayerBitShift = 64u - k_sortKeyFullscreenLayerNumBits;
	constexpr uint64_t k_sortKeyFullscreenMask = uint64_t(3u) << k_sortKeyFullscreenLayerBitShift;
	//constexpr uint8_t k_sortKeyFullscreenLayerWindowed = 1 << k_sortKeyFullscreenLayerBitShift;
	//constexpr uint8_t k_sortKeyFullscreenLayerFu = 1 << k_sortKeyFullscreenLayerBitShift;

	constexpr uint8_t k_sortKeyViewportNumBits = 3u;
	constexpr uint8_t k_sortKeyViewportBitShift = k_sortKeyFullscreenLayerBitShift - k_sortKeyViewportNumBits;
	constexpr uint64_t k_sortKeyViewportMask = uint64_t(7u) << k_sortKeyViewportBitShift;

	constexpr uint8_t k_sortKeyViewportLayerNumBits = 3u;
	constexpr uint8_t k_sortKeyViewportLayerBitShift = k_sortKeyViewportBitShift - k_sortKeyViewportLayerNumBits;
	constexpr uint64_t k_sortKeyViewportLayerMask = uint64_t(7u) << k_sortKeyViewportLayerBitShift;

	constexpr uint8_t k_sortKeyTranslucencyNumBits = 2u;
	constexpr uint8_t k_sortKeyTranslucencyBitShift = k_sortKeyViewportLayerBitShift - k_sortKeyTranslucencyNumBits;
	constexpr uint64_t k_sortKeyTranslucencyMask = uint64_t(3u) << k_sortKeyTranslucencyBitShift;

	constexpr uint8_t k_sortKeyCmdNumBits = 1u;
	constexpr uint8_t k_sortKeyCmdBitShift = k_sortKeyTranslucencyBitShift - k_sortKeyCmdNumBits;
	constexpr uint64_t k_sortKeyCmdMask = uint64_t(1u) << k_sortKeyCmdBitShift;

	constexpr uint8_t k_sortKeyDepthNumBits = 24u;
	constexpr uint8_t k_sortKeyDepthBitShift = k_sortKeyCmdBitShift - k_sortKeyDepthNumBits;
	constexpr uint64_t k_sortKeyDepthMask = uint64_t(0xfffff) << k_sortKeyDepthBitShift;

	constexpr uint8_t k_sortKeyMaterialNumBits = 29u;
	constexpr uint8_t k_sortKeyMaterialBitShift = k_sortKeyDepthBitShift - k_sortKeyMaterialNumBits;
	constexpr uint64_t k_sortKeyMaterialMask = uint64_t(0x1fffffff) << k_sortKeyMaterialBitShift;





	IRenderer* m_renderer;
	VertexBufferHandle m_vbh[TORC_MAX_VERTEX_BUFFER_COUNT];
	IndexBufferHandle m_ibh[TORC_MAX_INDEX_BUFFER_COUNT];
	ShaderHandle m_sh[10];




	struct SortKey
	{
		uint64_t m_sortKey;



	};

	VertexBufferHandle CreateVertexBuffer(void* data, U32 size, U32 stride)
	{
		VertexBufferHandle vbh;
		vbh.idx = vbh_idx;
		m_vbh[vbh_idx] = vbh;
		vbh_idx++;

		// call to the backend
		m_renderer->CreateVertexBuffer(vbh,data,size,stride);

		return vbh;
	}

	IndexBufferHandle CreateIndexBuffer(void* data, U32 size, U32 stride)
	{
		IndexBufferHandle ibh;
		ibh.idx = ibh_idx;
		m_ibh[ibh.idx] = ibh;
		ibh_idx++;
		// call to the backend
		m_renderer->CreateIndexBuffer(ibh,data,size,stride);

		return ibh;
	}

	ShaderHandle CreateShader(std::string _name,ShaderType type)
	{
		ShaderHandle sh;
		sh.idx = sh_idx;
		m_sh[sh.idx] = sh;
		sh_idx++;
		
		m_renderer->CreateShader(sh,_name,type);
		return sh;
	}

	void Init(IRenderer* renderer)
	{
		if (renderer)
			m_renderer = renderer;
	}



};
