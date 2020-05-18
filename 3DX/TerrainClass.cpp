#include "TerrainClass.h"
#include "MatHelper.h"
#include "TextureLoader.h"
#include "Texture.h"
TerrainClass::TerrainClass()
{
}
TerrainClass::TerrainClass(Graphics& gfx, DirectX::XMFLOAT3 eyePos,UINT tW, UINT tH, float width, float height,bool tessellated)
{
	if (!tessellated)
	{
		if (!isStaticallyBinded())
		{
			terrainWidth = tW;;
			terrainHeight = tH;
			struct Vertex
			{
				DirectX::XMFLOAT3 pos;
				DirectX::XMFLOAT3 normal;
				DirectX::XMFLOAT2 texCoord;
			};

			UINT vertexCount = tW * tH;
			UINT triCount = (tW - 1) * (tH - 1) * 2;

			float halfWidth = 0.5f *width;
			float halfHeight = 0.5f * height;
			float dx = width / (tH - 1);
			float dz = height / (tW - 1);

			float du = 1.0f / (tH - 1);
			float dv = 1.0f / (tW - 1);
			std::vector<DirectX::XMFLOAT3> v;
			std::vector<DirectX::XMFLOAT2> tex;
			std::vector<Vertex> vertexData;
			v.resize(vertexCount);
			tex.resize(vertexCount);
			TextureLoader ld("Textures\\grass.dds");
			std::vector<WORD> indexB;

			for (int j = 0; j < tH; j++)
			{
				float z = halfHeight - j * dz;
				for (int i = 0; i < tW; i++)
				{
					float x = -halfWidth + i * dx;
					v[j*tW + i] = DirectX::XMFLOAT3(x, 0.0f, z);
					tex[j*tW + i] = DirectX::XMFLOAT2(5 * i*du, 5 * j*dv);

				}
			}

			indexB.resize(triCount * 3);
			UINT k = 0;

			for (UINT i = 0; i < tW - 1; ++i)
			{
				for (UINT j = 0; j < tH - 1; ++j)
				{
					indexB[k] = i * tH + j;
					indexB[k + 1] = i * tH + j + 1;
					indexB[k + 2] = (i + 1)* tH + j;
					indexB[k + 3] = (i + 1) * tH + j;
					indexB[k + 4] = i * tH + j + 1;
					indexB[k + 5] = (i + 1) * tH + j + 1;
					k += 6;
				}
			}
			vertexData.resize(v.size());

			auto getHeight = [](float x, float z)  -> float
			{
				return 0.1f*(z*sinf(0.1f*x) + x * cosf(0.1f*z));
			};
			auto getHillNormal = [](float x, float z)
			{
				// n = (-df/dx, 1, -df/dz)
				DirectX::XMFLOAT3 n(
					-0.03f*z*cosf(0.1f*x) - 0.3f*cosf(0.1f*z),
					1.0f,
					-0.3f*sinf(0.1f*x) + 0.03f*x*sinf(0.1f*z));

				DirectX::XMVECTOR unitNormal = DirectX::XMVector3Normalize(XMLoadFloat3(&n));
				XMStoreFloat3(&n, unitNormal);

				return n;
			};


			for (size_t i = 0; i < v.size(); i++)
			{
				DirectX::XMFLOAT3 p = v[i];

				p.y = GetHillHeight(p.x, p.z);

				vertexData[i].pos = p;

				vertexData[i].normal = getHillNormal(p.x, p.z);
				vertexData[i].texCoord = tex[i];

			}
			AddStaticBind(std::make_unique<VertexBuffer>(gfx, vertexData));
			AddStaticBind(std::make_unique<PixelShader>(gfx, L"PhongLightingPS.cso"));
			//AddStaticBind(std::make_unique<BlendState>(gfx));
			auto vs = std::make_unique<VertexShader>(gfx, L"TexPhongVS.cso");
			auto vsBlob = vs->GetVBlob();
			AddStaticBind(std::move(vs));
			AddStaticBind(std::make_unique<IndexBuff>(gfx, indexB));
			struct MaterialConstantPS
			{

				DirectX::XMFLOAT4 amb;
				DirectX::XMFLOAT4 diff;
				DirectX::XMFLOAT4 spec;

			}matConst;

			matConst.amb = DirectX::XMFLOAT4(0.48f, 0.77f, 0.46f, 1.0f);
			matConst.diff = DirectX::XMFLOAT4(0.48f, 0.77f, 0.46f, 1.0f);
			matConst.spec = DirectX::XMFLOAT4(0.02f, 0.02f, 0.2f, 16.0f);

			AddStaticBind(std::make_unique<PSConstBuff<MaterialConstantPS>>(gfx, matConst, 1u));

			AddStaticBind(std::make_unique<Texture>(gfx, ld));

			AddStaticBind(std::make_unique<SamplerState>(gfx));

			const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
			{
				{ "Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
				{"Normal",0,DXGI_FORMAT_R32G32B32_FLOAT,0,12u,D3D11_INPUT_PER_VERTEX_DATA,0},
				{"TexCoord",0,DXGI_FORMAT_R32G32_FLOAT,0,24u,D3D11_INPUT_PER_VERTEX_DATA,0},

			};

			//AddStaticBind(std::make_unique<RasterizerState>(gfx));
			AddStaticBind(std::make_unique<InputLayout>(gfx, ied, vsBlob));
			AddStaticBind(std::make_unique<PrimitiveTopology>(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));


		}
		else
		{
			SetIndexBufferFromStatic();
		}
	}
	else
	{
		
		std::vector<DirectX::XMFLOAT3> vertices =
		{
			{-10.0f, 0.0f, +10.0f},
			{+10.0f, 0.0f, +10.0f},
			{-10.0f, 0.0f, -10.0f},
			{+10.0f, 0.0f, -10.0f}
		};
		AddStaticBind(std::make_unique<VertexBuffer>(gfx,vertices));
		AddStaticBind(std::make_unique<PixelShader>(gfx, L"PSBasicTessellation.cso"));
		auto vs = std::make_unique<VertexShader>(gfx, L"VSBasicTessellation.cso");
		auto vsBlob = vs->GetVBlob();
		AddStaticBind(std::move(vs));
		AddStaticBind(std::make_unique<HullShader>(gfx, L"HSBasicTessellation.cso"));
		AddStaticBind(std::make_unique<DomainShader>(gfx, L"DSBasicTessellation.cso"));
		const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
		{
			{ "Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
		};

		AddStaticBind(std::make_unique<InputLayout>(gfx, ied, vsBlob));
		AddStaticBind(std::make_unique<PrimitiveTopology>(D3D11_PRIMITIVE_TOPOLOGY_4_CONTROL_POINT_PATCHLIST));
	}
	 AddBind(std::make_unique<TransformationBuffer>(gfx, *this));
}

DirectX::XMMATRIX TerrainClass::GetTransformation() const
{
	return DirectX::XMMatrixIdentity();
}







