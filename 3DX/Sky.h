#pragma once
#include "Drawable.h"

class Sky : public Drawable
{
	Sky(Graphics& gfx, const char* filePath, float skyRadius);
	void Update(float ft) override;
	DirectX::XMMATRIX GetTransformation() const override;
};