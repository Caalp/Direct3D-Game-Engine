#include "Bezier.h"

Bezier::Bezier(Graphics & gfx)
{
	if (!isStaticallyBinded())
	{
		std::vector<DirectX::XMFLOAT3> vertices =
		{

			{-10.0f, -10.0f, +15.0f},
			{-5.0f,  0.0f, +15.0f},
			{+5.0f,  0.0f, +15.0f},
			{+10.0f, 0.0f, +15.0f},


			{-15.0f, 0.0f, +5.0f},
			{-5.0f,  0.0f, +5.0f},
			{+5.0f,  20.0f, +5.0f},
			{+15.0f, 0.0f, +5.0f},


			{-15.0f, 0.0f, -5.0f},
			{-5.0f,  0.0f, -5.0f},
			{+5.0f,  0.0f, -5.0f},
			{+15.0f, 0.0f, -5.0f},


			{-10.0f, 10.0f, -15.0f},
			{-5.0f,  0.0f, -15.0f},
			{+5.0f,  0.0f, -15.0f},
			{+25.0f, 10.0f, -15.0f}
		};

		AddStaticBind(std::make_unique<VertexBuffer>(gfx, vertices));
		AddStaticBind(std::make_unique<PixelShader>(gfx, L"PSBezierTessellation.cso"));
		auto vs = std::make_unique<VertexShader>(gfx, L"VSBezierTessellation.cso");
		auto vsBlob = vs->GetVBlob();
		AddStaticBind(std::move(vs));
		AddStaticBind(std::make_unique<HullShader>(gfx, L"HSBezierTessellation.cso"));
		AddStaticBind(std::make_unique<DomainShader>(gfx, L"DSBezierTessellation.cso"));
		const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
		{
			{ "Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
		};

		AddStaticBind(std::make_unique<InputLayout>(gfx, ied, vsBlob));
		AddStaticBind(std::make_unique<PrimitiveTopology>(D3D11_PRIMITIVE_TOPOLOGY_16_CONTROL_POINT_PATCHLIST));
	
		AddBind(std::make_unique<TransformationBuffer>(gfx, *this));
	}

}

void Bezier::Update(float dt)
{
}
