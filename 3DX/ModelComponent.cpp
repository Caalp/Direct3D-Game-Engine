#include "ModelComponent.h"
#include "PixelShader.h"
#include "VertexShader.h"
#include "InputLayout.h"
#include "Texture.h"
#include "SamplerState.h"
#include "ModelResource.h"
#include "ResourceManager.h"
#include "Channels.h"

ModelComponent::ModelComponent(Ref<ModelResource>& modelRes) : m_modelResource(modelRes)
{




	// Set dummy technique
	for (auto m : m_modelResource->GetMeshes())
	{
		Technique boxDefault("TestGraph", "boxDefault", channel1::defaultChannel, true);
		{
			{

				Step s1{ "default" };


				s1.AddBind(std::make_shared<PixelShader>("ColorBlenderPS.cso"));
				auto vs = std::make_shared<VertexShader>("ColorBlenderVS.cso");
				auto vsBlob = vs->GetVBlob();
				s1.AddBind(std::move(vs));
				const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
				{
					{ "Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 }
					//{ "TexCoord",0,DXGI_FORMAT_R32G32_FLOAT,0,12u,D3D11_INPUT_PER_VERTEX_DATA,0 }
				};

				s1.AddBind(std::make_shared<InputLayout>(ied, vsBlob));




				//s1.AddBind(std::make_shared<SamplerState>());
				//s1.AddBind(std::make_shared<Texture>("../Textures/WoodCrate01.dds"));

				s1.AddBind(std::make_shared<DrawIndexed>(0,m.get()->second.GetIndexCount()));
				//s1.AddBind(std::make_shared<TransformationBuffer>();

				boxDefault.AddStep(s1);
			}
		}
		m.get()->second.AppendTechnique(boxDefault);
	}

	// Dummy technique here

	
	//this->AppendTechnique(boxDefault);

}
