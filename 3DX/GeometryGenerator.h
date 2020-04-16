#pragma once
#include "Drawable.h"
#include "TextureLoader.h"
#include "MatHelper.h"

constexpr float PI = 3.14159265359f;

class GeometryGenerator : public Drawable
{
	
	struct Vertex
	{
		DirectX::XMFLOAT3 Pos;
		DirectX::XMFLOAT3 Normal;
		DirectX::XMFLOAT2 texCoord;

	};
	struct Vertex2
	{
		DirectX::XMFLOAT3 Pos;
		//DirectX::XMFLOAT3 Normal;
		//DirectX::XMFLOAT2 texCoord;

	};
	std::vector<Vertex> vertexData;
	std::vector<Vertex> vertexData2;
	std::vector<WORD> indices;
public:
	GeometryGenerator();
	void GenerateGrid(Graphics& gfx, const char* filePath, UINT numRow, UINT numCol, float dx, float dt, float damping, float texScale=1.0f );
	void GenerateCylinder(Graphics& gfx, const char* filePath, float bottomRadius,float topRadius,float height, UINT sliceCount, UINT stackCount, float texScale = 1.0f);
	void GenerateIcosahedron(Graphics& gfx, const char* filePath);
	void Update(float ft) override;
	DirectX::XMMATRIX GetTransformation() const override;
	DirectX::XMMATRIX GetTexTransformXM() const override;
	void RotateGeometry(float pitch, float yaw, float roll);
	void TranslateGeometry(float x, float y, float z);
	void Bind(Graphics& gfx);
	void ReflactionOn(bool reflactionStatus);
	void UpdateTex(float dt);
private:
	
	//TextureLoader tx;
	unsigned int index = 0;
	std::string filePath;
	float pitch;
	float yaw;
	float roll;
	float x, y, z;
	bool isReflaction = false;
	bool isTexUsed = false;
};