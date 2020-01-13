#pragma once
#include "DrawableBase.h"
#include "ConstBuffs.h"
#include "Camera.h"
class TransformationBuffer : public Bindables
{
	
public:
	TransformationBuffer(Graphics& gfx, const DrawableBase& parent);
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
	const DrawableBase& parent;
	
};