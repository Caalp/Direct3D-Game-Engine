#pragma once
#include "Bindables.h"
#include <vector>

	class IndexBuff : public Bindables
	{
		//friend class DrawbleBase;
	public:
		IndexBuff(Graphics& gfx, std::vector<WORD>& v);
		void Bind(Graphics& gfx) override;
		UINT GetIndexCount() const;
	private:
		UINT count;
		Microsoft::WRL::ComPtr<ID3D11Buffer> indexBuffer_;
	};
