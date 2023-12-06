#include "AnimatedCharacter.h"
#include "Entity.h"
#include "SceneRenderer.h"
#include "Channels.h"
#include "Model.h"
#include <utility>
#include <fstream>
#include <iostream>
#include "Technique.h"

AnimatedCharacter::AnimatedCharacter(Graphics& gfx, const std::string& filename, const std::string& modelName) 
	: m_cbBoneTransforms(gfx, m_finalTransforms.finalTransforms, m_finalTransforms.finalTransforms.size(), 2u)
{
	up_model = std::make_unique<Model>(gfx, filename);
	for (auto& e : up_model->pMesh)
	{
		printf("Mesh %s initialized\n", e.GetName().c_str());
		Technique object(e.GetName(), channel1::defaultChannel, true);
		Step s1{ "default" };
		s1.AddBind(std::make_shared<PixelShader>(gfx, "PS_TextureArrayMapping.cso"));
		auto vs = std::make_shared<VertexShader>(gfx, "VS_AnimatedCharacter.cso");
		auto vsBlob = vs->GetVBlob();
		s1.AddBind(std::move(vs));
		const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
		{
			{ "Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
			//{ "Normal",0,DXGI_FORMAT_R32G32B32_FLOAT,0,12u,D3D11_INPUT_PER_VERTEX_DATA,0 },
			{ "TexCoord",0,DXGI_FORMAT_R32G32B32_FLOAT,0,12u,D3D11_INPUT_PER_VERTEX_DATA,0 },
			{ "Weight",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,24u,D3D11_INPUT_PER_VERTEX_DATA,0 },
			{ "BoneIndices",0,DXGI_FORMAT_R8G8B8A8_UINT,0,40u,D3D11_INPUT_PER_VERTEX_DATA,0 },
		};
		s1.AddBind(std::make_shared<InputLayout>(gfx, ied, vsBlob));
		int i = 0;
		for (const auto& elem : e.textures)
		{
			s1.AddBind(std::make_shared<Texture>(gfx, elem.path.c_str(), i));
			i++;
		}
		s1.AddBind(std::make_shared<SamplerState>(gfx));
		Entity* entt = e.db.GetScene().CreateEntity(&e.db);
		//auto tt = up_model.get()->nodes["body"]->toRootTransform;
		//entt->AddComponent<Transformation>(tt* DirectX::XMMatrixScaling(10.5f, 10.5f, 10.5f) * DirectX::XMMatrixTranslation(0.0f, 0.0f, -15.0f));
		entt->AddComponent<Transformation>(DirectX::XMMatrixScaling(0.5f, 0.5f, 0.5f) * DirectX::XMMatrixTranslation(0.0f, -2.0f, -15.0f));
		uint32_t mID = std::move(entt->GetID());

		s1.AddBind(std::make_shared<TransformationBuffer>(gfx, mID));
		s1.AddBind(std::make_shared<DrawIndexed>(e.indices.size(), 0, 0));
		object.AddStep(s1);
		e.InitDrawable(gfx, object, e.GetName(), mID);
	}
}

void AnimatedCharacter::GetFinalTransforms(std::string clipName, float timePos)
{
	auto animClip = up_model.get()->anims[clipName];
	DirectX::XMMATRIX XM = DirectX::XMMatrixIdentity();
	//double possibleFPS = 1 / timePos;
	//auto durationInSec = (animClip.duration / animClip.ticksPerSec);
	//double fTime = 1 / animClip.ticksPerSec;
	dt += timePos;
	//float timeStep = animClip.ticksPerSec*timePos;
	// Loop animation
	if (dt * 30 > (float)animClip.duration)
		dt = 0.0f;
	up_model.get()->GetFinalTransforms(clipName, dt * 30, up_model.get()->GetRootNode().get(), XM);
	std::map<int, BoneData> bd = up_model.get()->GetBones();
	//m_finalTransforms.finalTransforms.resize(bd.size());
	//std::copy(up_model.get()->finalTransforms.begin(), up_model.get()->finalTransforms.end(), m_finalTransforms.finalTransforms);
	//m_finalTransforms.finalTransforms = up_model.get()->finalTransforms;
	for (size_t i = 0; i < bd.size(); i++)
	{
		m_finalTransforms.finalTransforms[i] = DirectX::XMMatrixTranspose(bd[i].finalTransform);
	}
}

void AnimatedCharacter::LinkTechnique(RenderGraph& rg)
{
	for (auto& elem : up_model.get()->pMesh)
	{
		elem.LinkTechnique(rg);
	}
}

void AnimatedCharacter::Submit(size_t channel)
{
	for (auto& elem : up_model.get()->pMesh)
	{
		elem.Submit(channel);
	}
}