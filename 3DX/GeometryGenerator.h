#pragma once
#include "Drawable.h"
#include "TextureLoader.h"


class GeometryGenerator : public Drawable
{
	struct Vertex
	{
		DirectX::XMFLOAT3 Pos;
		DirectX::XMFLOAT3 Normal;
		DirectX::XMFLOAT3 texCoord;

	};
	std::vector<Vertex> vertexData;
	std::vector<WORD> indices;
public:
	GeometryGenerator();
	void GenerateGrid(Graphics& gfx, const char* filePath, UINT numRow, UINT numCol, float dx, float dt, float damping, float texScale=1.0f );
	void Update(float ft) override;
	DirectX::XMMATRIX GetTransformation() const override;
	void RotateGeometry(float pitch, float yaw, float roll);
	void TranslateGeometry(float x, float y, float z);
	void Bind(Graphics& gfx);
private:
	std::string filePath;
	float pitch;
	float yaw;
	float roll;
	float x, y, z;
};