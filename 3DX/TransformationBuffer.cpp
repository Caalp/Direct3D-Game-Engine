#include "TransformationBuffer.h"
#include "Drawable.h"


TransformationBuffer::TransformationBuffer(Graphics & gfx, const Drawable & parent, bool texused):
	parent(parent),texUsed(texused)
		
{
	if (!m_TransformBuffer)
	{
		m_TransformBuffer = std::make_unique<VSConstBuff<TransformBuffer>>(gfx);
	}
	
	
	
}

void TransformationBuffer::UpdateBufferData(Graphics& gfx)
{
	if (!texUsed)
	{

		_TransformBuffer =
		{

			{DirectX::XMMatrixTranspose(parent.GetTransformation(gfx))},
			{DirectX::XMMatrixTranspose(parent.GetTransformation(gfx)*gfx.GetCamera())},
			{ DirectX::XMMatrixIdentity() },
			{gfx.GetCameraPos()},

		};
	}
	else
	{
		_TransformBuffer =
		{

			{DirectX::XMMatrixTranspose(parent.GetTransformation(gfx))},
			{DirectX::XMMatrixTranspose(parent.GetTransformation(gfx)*gfx.GetCamera())},
			{DirectX::XMMatrixTranspose(parent.GetTexTransformXM())},
			{gfx.GetCameraPos()},

		};
	}
}


void TransformationBuffer::Bind(Graphics & gfx)
{
	
	UpdateBufferData(gfx);
	m_TransformBuffer->Update(gfx, _TransformBuffer);
	m_TransformBuffer->Bind(gfx, 0u, 1u);
}


