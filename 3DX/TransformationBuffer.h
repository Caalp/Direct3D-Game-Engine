#pragma once

#include "ConstBuffs.h"
#include "Camera.h"

class Drawable;
class TransformationBuffer : public Bindable
{

public:

	TransformationBuffer(Graphics& gfx, const uint32_t& enttID);
	void UpdateBufferData(Graphics& gfx);
	void Bind(Graphics& gfx) override;

private:
	struct TransformBuffer
	{
		DirectX::XMMATRIX world;
		DirectX::XMMATRIX worldviewProj;
		DirectX::XMFLOAT3 eyePos;
		float padding;
	};
	
protected:
	TransformBuffer _TransformBuffer; 
	mutable std::unique_ptr<VSConstBuff<TransformBuffer>> m_TransformBuffer;
	//const Drawable& parent;
	const uint32_t mEnttID;
	
};