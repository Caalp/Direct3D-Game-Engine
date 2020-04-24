#pragma once
#include "Drawable.h"

class Sky : public Drawable
{
public:
	Sky(Graphics& gfx, const char* filePath, float skyRadius);
	void Update(float ft) override;
	DirectX::XMMATRIX GetTransformation() const override;
	DirectX::XMMATRIX GetTransformation(Graphics& gfx) const override;

private:
	std::vector<DirectX::XMFLOAT3> vertices;
};