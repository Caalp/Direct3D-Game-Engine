#pragma once
#include "Bindable.h"
#include <vector>

	class IndexBuff : public Bindable
	{
		//friend class DrawbleBase;
	public:
		IndexBuff(Graphics& gfx, const std::vector<WORD>& v);
		IndexBuff(Graphics& gfx, const std::vector<UINT>& v,int x);
		void Bind(Graphics& gfx) override;
		UINT GetIndexCount() const;
	private:
		UINT count;
		bool new1 = false;
		Microsoft::WRL::ComPtr<ID3D11Buffer> indexBuffer_;
	};
