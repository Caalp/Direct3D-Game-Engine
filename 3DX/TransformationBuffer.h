#pragma once

#include "ConstBuffs.h"


struct TransformBuffer
{
	DirectX::XMMATRIX world;
	DirectX::XMMATRIX worldInverseTranspose;
	DirectX::XMMATRIX worldviewProj;
	DirectX::XMFLOAT3 eyePos;
	float padding;
};
class TransformationBuffer : public Bindable
{

public:


	//TransformationBuffer(Graphics& gfx);
	TransformationBuffer(std::shared_ptr<VSConstBuff<TransformBuffer>> tbuff);
	
	/// <summary>
	/// Update buffer data with UpdateBufferData and Bind Buffer
	/// </summary>
	/// <param name="gfx"></param>
	void Bind(Graphics& gfx) override;

private:

	/// <summary>
	/// Update buffer data with data from Transformation Component
	/// </summary>
	/// <param name="gfx"></param>
	void UpdateBufferData(Graphics& gfx);

	/// <summary>
	/// Transformation Buffer structure (Created as D3D11_USAGE_DYNAMIC)
	/// </summary>
	
	
private:
	//std::shared_ptr<TransformBuffer> m_BufferStruct; 
	std::weak_ptr<VSConstBuff<TransformBuffer>> m_TBuffer;

	
};