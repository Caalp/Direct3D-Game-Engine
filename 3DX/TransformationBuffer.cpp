#include "TransformationBuffer.h"
#include "Drawable.h"
#include "Scene.h"

TransformationBuffer::TransformationBuffer(Graphics & gfx, const uint32_t& enttID):
	mEnttID(std::move(enttID))
	
		
{
	if (!m_TransformBuffer)
	{
		m_TransformBuffer = std::make_unique<VSConstBuff<TransformBuffer>>(gfx);
	}
	
	
}


void TransformationBuffer::UpdateBufferData(Graphics& gfx)
{
	
	Transformation* transform = nullptr;
	auto view = (Scene::reg).view<Transformation>();
	for (const entt::entity& e : view)
	{
		if ((uint32_t)e == mEnttID)
		{
			transform = &view.get<Transformation>(e);
		}
		 
	}
	_TransformBuffer =
	{

		{DirectX::XMMatrixTranspose(transform->transform)},
		{transform->GetInverseTransform()},
		{DirectX::XMMatrixTranspose(transform->transform*gfx.GetCamera())},
		{gfx.GetCameraPos()},

	};
}


void TransformationBuffer::Bind(Graphics & gfx)
{
	
	
	UpdateBufferData(gfx);
	m_TransformBuffer->Update(gfx,_TransformBuffer);
	
	m_TransformBuffer->Bind(gfx,0u,1u);
	
}


