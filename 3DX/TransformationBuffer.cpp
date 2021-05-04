#include "TransformationBuffer.h"
#include "Drawable.h"
#include "Scene.h"
#include "ECSFactory.h"

//TransformationBuffer::TransformationBuffer(Graphics& gfx)
//{
//
//	//if (!m_TBuffer)
//	//{
//	//	m_TBuffer = std::make_shared<VSConstBuff<TransformBuffer>>(gfx);
//	//}
//
//}

TransformationBuffer::TransformationBuffer(std::shared_ptr<VSConstBuff<TransformBuffer>> tbuff)
{
	m_TBuffer = tbuff;
}


void TransformationBuffer::UpdateBufferData(Graphics& gfx)
{
	//const auto& m_TransformComponent = ECSFactory::GetECSFactory().GetRegistry().view<TransformationComponent>().get((entt::entity)m_ID);

	//m_BufferStruct =
	//{

	//	{DirectX::XMMatrixTranspose(m_TransformComponent.GetMatrix())},
	//	{m_TransformComponent.GetInverseTransform()},
	//	{DirectX::XMMatrixTranspose(m_TransformComponent.GetMatrix() * gfx.GetCamera())},
	//	{gfx.GetCameraPos()},

	//};
}


void TransformationBuffer::Bind(Graphics & gfx)
{
	
	
	////UpdateBufferData(gfx);

	//	m_TBuffer->Update(gfx, *m_BufferStruct);
	if (auto pref = m_TBuffer.lock())
	{
		pref->Bind(gfx, 0u, 1u);
	}
		

	
}


