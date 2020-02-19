#pragma once
#include "Drawable.h"

namespace dx = DirectX;
class Water: public Drawable
{
public:
	Water();
	Water(Graphics& gfx);
	void Init(Graphics& gfx, UINT numRow, UINT numCol, float dx, float dt, float speed, float damping);
	void Update(float dt) override {};
	void Update(Graphics& gfx, float ft);
	void Disturb(UINT i, UINT j, float magnitude);
	void UpdateVBuff(Graphics& gfx);

	const dx::XMFLOAT3& operator[](int i)const { return currSolution[i]; }

	const dx::XMFLOAT3& Normal(int i) const { return Normals[i]; }

	//const dx::XMFLOAT3& TangentX(int i) const { return this->TangentX[i]; }
	
	dx::XMMATRIX GetTexTransformXM() const;

	void Bind(Graphics& gfx);
	UINT GetRowCount() const;
	UINT GetColumnCount() const;
	void updatePosX(float x);
	void updatePosY(float y);
	void updatePosZ(float z);
	DirectX::XMMATRIX GetTransformation() const override;

	struct Vertex
	{
		DirectX::XMFLOAT3 Pos;
		DirectX::XMFLOAT3 Normal;
		DirectX::XMFLOAT2 Tex;
	};

private:
	//std::unique_ptr<VertexBuffer> vbf;
	float x, y, z;
	UINT numCols;
	UINT numRows;
	UINT vertexCount;
	UINT triangleCount;
	float timeStep;
	float spatialStep;
	float dt;
	
	

	float width;
	float depth;

	float mK1;
	float mK2;
	float mK3;
	dx::XMFLOAT3* prevSolution;
	dx::XMFLOAT3* currSolution;
	dx::XMFLOAT3* Normals;
	dx::XMFLOAT3* TangentX;

	std::vector<Vertex> vertexData;
	//std::vector<Vertex> prevSolution;
	std::vector<WORD> waterIndices;

};