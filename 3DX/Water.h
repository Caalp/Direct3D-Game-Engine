#pragma once
#include "Drawable.h"

class Water: public Drawable
{
public:
	Water();
	Water(Graphics& gfx);
	void Init(Graphics& gfx, UINT numRow, UINT numCol, float dx);
	void Update(float ft) override;
	void updatePosX(float x);
	void updatePosY(float y);
	void updatePosZ(float z);
	DirectX::XMMATRIX GetTransformation() const override;

	struct Vertex
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT3 normal;
		DirectX::XMFLOAT2 texCoord;
	};

private:
	float x, y, z;
	UINT numCols;
	UINT numRows;
	UINT vertexCount;
	UINT triangleCount;
	std::vector<Vertex> currSolution;
	std::vector<WORD> waterIndices;

};