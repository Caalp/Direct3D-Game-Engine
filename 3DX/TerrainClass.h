#pragma once
#include "additional_headers.h"
class TerrainClass : public DrawableSource<TerrainClass>
{
public:
	TerrainClass(Graphics& gfx,Camera& cam,int tW,int tH);
	//int GetIndexCount();
	void Update(float dt) { return; };
	DirectX::XMMATRIX GetViewXM() const override;
	DirectX::XMMATRIX GetWorldXM() const override;
	DirectX::XMMATRIX GetProjXM() const override;
private:
	Camera& cam;
	int terrainWidth, terrainHeight;
};