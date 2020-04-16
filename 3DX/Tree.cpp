#include "Tree.h"

Tree::Tree(Graphics & gfx, std::vector<const char*> filePath)
{
	if (!isStaticallyBinded())
	{
		Vertex v;
		v.Pos = { -14.0f,14.004f,4.45f };
		v.Size = { 24.0f,24.0f };
		vertexData.push_back(v);
		v.Pos = { 0.0f,1.004f,14.45f };
		v.Size = { 24.0f,24.0f };
		vertexData.push_back(v);
		v.Pos = { -20.0f,1.004f,10.45f };
		v.Size = { 24.0f,24.0f };
		vertexData.push_back(v);
		v.Pos = { -14.0f,1.004f,14.45f };
		v.Size = { 24.0f,24.0f };
		vertexData.push_back(v);
		v.Pos = { -10.0f,1.004f,24.45f };
		v.Size = { 24.0f,24.0f };
		vertexData.push_back(v);
		AddBind(std::make_unique<VertexBuffer>(gfx, vertexData));
		AddStaticBind(std::make_unique<PixelShader>(gfx, L"PS_BillBoarding.cso"));
		AddStaticBind(std::make_unique<GeometryShader>(gfx, L"GS_BillBoarding.cso"));
		auto vs = std::make_unique<VertexShader>(gfx, L"VS_BillBoarding.cso");
		auto vsBlob = vs->GetVBlob();
		AddStaticBind(std::move(vs));
		


		struct MaterialConstantPS
		{

			DirectX::XMFLOAT4 amb;
			DirectX::XMFLOAT4 diff;
			DirectX::XMFLOAT4 spec;

		}matConst;

		matConst.amb = DirectX::XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
		matConst.diff = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		matConst.spec = DirectX::XMFLOAT4(0.2f, 0.2f, 0.2f, 16.0f);

		AddStaticBind(std::make_unique<PSConstBuff<MaterialConstantPS>>(gfx, matConst, 1u));




		AddStaticBind(std::make_unique<SamplerState>(gfx));


		const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
		{
			{ "Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
			{"Size",0,DXGI_FORMAT_R32G32_FLOAT,0,12u,D3D11_INPUT_PER_VERTEX_DATA,0},
			//{"TexCoord",0,DXGI_FORMAT_R32G32_FLOAT,0,24u,D3D11_INPUT_PER_VERTEX_DATA,0},

		};

	
		AddStaticBind(std::make_unique<InputLayout>(gfx, ied, vsBlob));
		AddStaticBind(std::make_unique<PrimitiveTopology>(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST));
	}
	else
	{
		SetIndexBufferFromStatic();
	}
	AddStaticBind(std::make_unique<Texture>(gfx, TextureLoader(filePath)));
	AddBind(std::make_unique<TransformationBuffer>(gfx, *this, true));
}

void Tree::Update(float ft)
{
}

DirectX::XMMATRIX Tree::GetTransformation() const
{
	return DirectX::XMMatrixIdentity();
}
