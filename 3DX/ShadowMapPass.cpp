#include "ShadowMapPass.h"

ShadowMapPass::ShadowMapPass(Graphics& gfx, std::string passName) : RenderQueuePass(std::move(passName))
{
	// RegisterSink  to the render target and depth buffer
	RegisterSink(std::make_unique<DirectBufferSink<DepthStencil>>("depthstencil", depthStencil));
	RegisterSink(std::make_unique<DirectBufferSink<RenderTarget>>("rendertarget", renderTarget));
	RegisterSink(std::make_unique<DirectBufferSink<ShaderResourceDS>>("ShaderResourceDS", m_shadowMap));
}

void ShadowMapPass::Execute(Graphics& gfx)
{				
}

void ShadowMapPass::Reset()
{
}

void ShadowMapPass::BindShadowMap(Graphics& gfx)
{
	// Set some states to draw shadow map onto screen
	{
			
		

			//AddBind(std::make_shared<DrawIndexed>(0, indexBuffer.get()->GetIndexCount()));
			std::make_shared<SamplerState>(gfx).get()->Bind(gfx);
			std::make_shared<Texture>(gfx, m_shadowMap.get()->shaderResourceView).get()->Bind(gfx);
			std::make_shared<PixelShader>(gfx, "PS_Textured.cso").get()->Bind(gfx);
			auto vs = std::make_shared<VertexShader>(gfx, "ColorBlenderVS.cso");
			auto vsBlob = vs->GetVBlob();
			std::move(vs).get()->Bind(gfx);
			//const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
			//{
			//	{ "Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
			//	//{ "TexCoord",0,DXGI_FORMAT_R32G32_FLOAT,0,12u,D3D11_INPUT_PER_VERTEX_DATA,0 }
			//};

			//std::make_shared<InputLayout>(gfx, ied, vsBlob).get()->Bind(gfx);



			//Entity* entt = GetScene().CreateEntity(this);
			//entt->AddComponent<Transformation>(DirectX::XMMatrixScaling(1.1f, 1.1f, 1.1f) * DirectX::XMMatrixTranslation(posX, posY, posZ));
			//mID2 = std::move(entt->GetID());

			//s2.AddBind(std::make_shared<TransformationBuffer>(gfx, mID2));

			//textured_object.AddStep(s2);
		

	}
}
