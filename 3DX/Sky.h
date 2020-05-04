#pragma once
#include "Drawable.h"
#include "Camera.h"

class Sky : public Drawable
{
public:
	Sky(Graphics& gfx, const char* filePath, float skyRadius);
	void Update(float ft) override;
	DirectX::XMMATRIX GetTransformation() const override;
	DirectX::XMMATRIX GetTransformation(Graphics& gfx) const override;
	void CreateDynamicCubeMapCamera(float x, float y, float z);

private:
	Camera dynamicCubeMapCamera[6];
	std::vector<DirectX::XMFLOAT3> vertices;
};