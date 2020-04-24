#include "Sky.h"
#include "GeometryGenerator.h"

Sky::Sky(Graphics & gfx, const char * filePath, float skyRadius)
{
	// Create sphere of off the GeometryGenerator class to use 
	// to map the texture as sky
	GeometryGenerator sphere;
	sphere.GenerateSphere(gfx, filePath, skyRadius, 30, 30);
	int verticesSize = sphere.GetMeshData()->vertexData.size();
	vertices.resize(verticesSize);

	for (int i = 0; i < verticesSize; i++)
	{
		vertices[i] = sphere.GetMeshData()->vertexData[i].Pos;
	}
	
	if (!isStaticallyBinded())
	{
		//SetBlendState(true);
		//AddStaticBind(std::make_unique<BlendState>(gfx));
		AddBind(std::make_unique<VertexBuffer>(gfx, sphere.GetMeshData()->vertexData));
		//AddStaticBind(std::make_unique<PixelShader>(gfx, L"ConstantColorPS.cso"));
		AddStaticBind(std::make_unique<PixelShader>(gfx, L"PSCubeMapping.cso"));
		//AddStaticBind(std::make_unique<GeometryShader>(gfx, L"GS_Subdivide.cso"));
		auto vs = std::make_unique<VertexShader>(gfx, L"VSCubeMapping.cso");
		auto vsBlob = vs->GetVBlob();
		AddStaticBind(std::move(vs));
		AddStaticBind(std::make_unique<IndexBuff>(gfx, const_cast<std::vector<WORD>&>(sphere.GetMeshData()->indices)));
		//TextureLoader texLoader(filePath.c_str());


		/*struct MaterialConstantPS
		{

			DirectX::XMFLOAT4 amb;
			DirectX::XMFLOAT4 diff;
			DirectX::XMFLOAT4 spec;

		}matConst;

		matConst.amb = DirectX::XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
		matConst.diff = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		matConst.spec = DirectX::XMFLOAT4(0.8f, 0.8f, 0.8f, 32.0f);

		AddStaticBind(std::make_unique<PSConstBuff<MaterialConstantPS>>(gfx, matConst, 1u));
*/



		AddStaticBind(std::make_unique<SamplerState>(gfx));


		const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
		{
			{ "Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
			
		};

		//AddStaticBind(std::make_unique<RasterizerState>(gfx));
		AddStaticBind(std::make_unique<InputLayout>(gfx, ied, vsBlob));
		AddStaticBind(std::make_unique<PrimitiveTopology>(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
	}
	else
	{
		SetIndexBufferFromStatic();
	}
	AddStaticBind(std::make_unique<Texture>(gfx, filePath));
	AddBind(std::make_unique<TransformationBuffer>(gfx, *this, true));
}

void Sky::Update(float ft)
{
}

DirectX::XMMATRIX Sky::GetTransformation() const
{
	return DirectX::XMMatrixIdentity();
}

DirectX::XMMATRIX Sky::GetTransformation(Graphics & gfx) const
{
	DirectX::XMFLOAT3 camPos = gfx.GetCameraPos();
	return DirectX::XMMatrixTranslation(camPos.x,camPos.y,camPos.z);
}
