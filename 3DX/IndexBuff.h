#pragma once
#include "Bindable.h"
#include <vector>



	class IndexBuff : public Bindable
	{
		//friend class DrawbleBase;
	public:
		IndexBuff() = default;
		void Create(void* data, U32 size, U32 stride)
		{
			D3D11_BUFFER_DESC indexDesc;
			ZeroMemory(&indexDesc, sizeof(indexDesc));
			indexDesc.Usage = D3D11_USAGE_DEFAULT;
			indexDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
			indexDesc.ByteWidth = size;
			indexDesc.StructureByteStride = stride;
			indexDesc.CPUAccessFlags = 0;
			D3D11_SUBRESOURCE_DATA sd = {};
			sd.pSysMem = data;

			GraphicsResources::GetSingleton().pDevice->CreateBuffer(&indexDesc, &sd, &indexBuffer_);
		}
		IndexBuff(Graphics& gfx, const std::vector<WORD>& v);
		IndexBuff(Graphics& gfx, const std::vector<UINT>& v,int x);
		IndexBuff(const std::vector<WORD>& v);
		IndexBuff(const std::vector<UINT>& v, int x);
		void Bind(Graphics& gfx) override;
		void Bind() override;
		UINT GetIndexCount() const;
	private:
		UINT count;
		bool new1 = false;
		Microsoft::WRL::ComPtr<ID3D11Buffer> indexBuffer_;
	};
