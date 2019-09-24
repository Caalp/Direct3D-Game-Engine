#pragma once
#include "Bindables.h"
#include <vector>
class IndexBuff : public Bindables
{
public:
	IndexBuff(Graphics& gfx, std::vector<WORD>& v);
	void Bind(Graphics& gfx) override;
private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> indexBuffer_;
};