#include "Water.h"
#include "TextureLoader.h"
#include "Texture.h"
Water::Water(): numCols(0), numRows(0), vertexCount(0), triangleCount(0),
x(0), y(0), z(0)
{
}

Water::Water(Graphics & gfx): numCols(0), numRows(0), vertexCount(0), triangleCount(0),
x(0),y(0),z(0)
{

}

void Water::Init(Graphics & gfx, UINT numRow, UINT numCol, float dx)
{
	if (!isStaticallyBinded())
	{
		
		numRows = numRow;
		numCols = numCol;

		vertexCount = numRows * numCols;
		triangleCount = (numRows - 1)*(numCols - 1) * 2;

		currSolution.resize(vertexCount);

		float halfWidth = 0.5f *dx*(numCols - 1);
		float halfHeight = 0.5f *dx*(numRows - 1);

		//Generate grid vertices
		for (UINT i = 0; i < numRows; i++)
		{
			float z = halfHeight - i * dx;
			for (UINT j = 0; j < numCols; j++)
			{
				float x = -halfWidth + j * dx;
				currSolution[i*numCols + j].pos = DirectX::XMFLOAT3(x, 0.0f, z);
				currSolution[i*numCols + j].normal = DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f);
				currSolution[i*numCols + j].texCoord = DirectX::XMFLOAT2(0.05f*i*dx,0.05f*j*dx);
			}
		}

		
		//reserve space for indices
		waterIndices.resize(3 * triangleCount);
		//Create indices
		int k = 0;
		for (UINT i = 0; i < numRows - 1; i++)
		{
			for (UINT j = 0; j < numCols - 1; j++)
			{
				waterIndices[k] = i * numCols + j;
				waterIndices[k+1] = i * numCols + j+1;
				waterIndices[k+2] = (i+1) * numCols + j;

				waterIndices[k+3] = (i+1) * numCols + j;
				waterIndices[k+4] = i * numCols + j+1;
				waterIndices[k+5] = (i+1) * numCols + j+1;

				k += 6;
			}
		}



		AddStaticBind(std::make_unique<VertexBuffer>(gfx, currSolution));
		AddStaticBind(std::make_unique<PixelShader>(gfx, L"PhongLightingPS.cso"));
		auto vs = std::make_unique<VertexShader>(gfx, L"TexPhongVS.cso");
		auto vsBlob = vs->GetVBlob();
		AddStaticBind(std::move(vs));
		AddStaticBind(std::make_unique<IndexBuff>(gfx, waterIndices));
		TextureLoader texLoader("water2.dds");
		struct MaterialConstantPS
		{

			DirectX::XMFLOAT4 amb;
			DirectX::XMFLOAT4 diff;
			DirectX::XMFLOAT4 spec;

		}matConst;

		matConst.amb = DirectX::XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
		matConst.diff = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		matConst.spec = DirectX::XMFLOAT4(0.8f, 0.8f, 0.8f, 32.0f);

		AddStaticBind(std::make_unique<PSConstBuff<MaterialConstantPS>>(gfx, matConst, 1u));

		AddStaticBind(std::make_unique<Texture>(gfx, texLoader));

		AddStaticBind(std::make_unique<SamplerState>(gfx));

		const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
		{
			{ "Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
			{"Normal",0,DXGI_FORMAT_R32G32B32_FLOAT,0,12u,D3D11_INPUT_PER_VERTEX_DATA,0},
			{"TexCoord",0,DXGI_FORMAT_R32G32_FLOAT,0,24u,D3D11_INPUT_PER_VERTEX_DATA,0},

		};


		AddStaticBind(std::make_unique<InputLayout>(gfx, ied, vsBlob));
		AddStaticBind(std::make_unique<PrimitiveTopology>(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
	}
	else
	{
		SetIndexBufferFromStatic();
	}
	
	AddBind(std::make_unique<TransformationBuffer>(gfx, *this));
}

void Water::Update(float ft)
{
	
}

void Water::updatePosX(float x)
{
	this->x += x;
}

void Water::updatePosY(float y)
{
	this->y += y;
}

void Water::updatePosZ(float z)
{
	this->z += z;
}

DirectX::XMMATRIX Water::GetTransformation() const
{
	return DirectX::XMMatrixIdentity() * DirectX::XMMatrixTranslation(x, y, z);
}

