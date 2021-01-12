#pragma once
#include <memory>
#include <string>


#include "Model.h"

//class Model;
class Graphics;
struct boneTransforms
{
	boneTransforms()
	{
	
		finalTransforms.resize(96);
	}
	std::vector<DirectX::XMMATRIX> finalTransforms;
	
};
class AnimatedCharacter
{

public:
	AnimatedCharacter(Graphics& gfx, const std::string& filename, const std::string& modelName);
	void GetFinalTransforms(std::string clipName, float timePos);
	void LinkTechnique(RenderGraph& rg);
	void Submit(size_t channel);

	//void GetFinalTransforms(std::string clipName, float timePos, std::vector<DirectX::XMFLOAT4X4>& finalTransforms);
	void Update(Graphics& gfx)
	{
		m_cbBoneTransforms.Update(gfx, m_finalTransforms.finalTransforms, m_finalTransforms.finalTransforms.size());
		m_cbBoneTransforms.Bind(gfx,2u,1u);
	}
	void UpdateXM()
	{
	/*	for (auto& elem : up_model.get()->pMesh)
		{

		}*/
		/*Transformation* transform = nullptr;
		auto view = (Scene::reg).view<Transformation>();
		for (const entt::entity& e : view)
		{
			if ((uint32_t)e == up_model.get()->pMesh[2].db.GetID())
			{
				transform = &view.get<Transformation>(e);
				transform->transform = (up_model.get()->nodes["helmet"]->toRootTransform * DirectX::XMMatrixScaling(10.5f, 10.5f, 10.5f));
			}
			else if ((uint32_t)e == up_model.get()->pMesh[0].db.GetID())
			{
				transform = &view.get<Transformation>(e);
				transform->transform = (up_model.get()->nodes["body"]->toRootTransform * DirectX::XMMatrixScaling(10.5f, 10.5f, 10.5f));
			}
			else if ((uint32_t)e == up_model.get()->pMesh[3].db.GetID())
			{
				transform = &view.get<Transformation>(e);
				transform->transform = (up_model.get()->nodes["PulseRifle"]->toRootTransform * DirectX::XMMatrixScaling(10.5f, 10.5f, 10.5f));
			}
			else if ((uint32_t)e == up_model.get()->pMesh[1].db.GetID())
			{
				transform = &view.get<Transformation>(e);
				transform->transform = ( DirectX::XMMatrixScaling(10.5f, 10.5f, 10.5f));
			}

		}*/

		
		
	}

private:
	float dt = 0.0f;
	float animTimer = 0.0f;
	
	std::unique_ptr<Model> up_model;
	boneTransforms m_finalTransforms;
	mutable VSConstBuff<std::vector<DirectX::XMMATRIX>> m_cbBoneTransforms;

};