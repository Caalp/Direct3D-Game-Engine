#include "TransformationBuffer.h"
#include "Drawable.h"


TransformationBuffer::TransformationBuffer(Graphics & gfx, const Drawable & parent):
	parent(parent)
	
		
{
	if (!m_TransformBuffer)
	{
		m_TransformBuffer = std::make_unique<VSConstBuff<TransformBuffer>>(gfx);
	}
	
	
}

void TransformationBuffer::UpdateBufferData(Graphics& gfx)
{
	_TransformBuffer =
	{
		
		{DirectX::XMMatrixTranspose(parent.GetTransformation())},
		{DirectX::XMMatrixTranspose(parent.GetTransformation()*gfx.GetCamera())},
		{gfx.GetCameraPos()},

	};
}


void TransformationBuffer::Bind(Graphics & gfx)
{
	
	
	UpdateBufferData(gfx);
	m_TransformBuffer->Update(gfx,_TransformBuffer);
	
	m_TransformBuffer->Bind(gfx,0u,1u);
	
}


