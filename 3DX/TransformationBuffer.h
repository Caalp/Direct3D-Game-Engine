#pragma once

#include "ConstBuffs.h"
#include "Camera.h"
class Drawable;
class TransformationBuffer : public Bindable
{
	
public:
	
	TransformationBuffer(Graphics& gfx, const Drawable & parent, bool texused = false);
	void UpdateBufferData(Graphics& gfx);
	void Bind(Graphics& gfx) override;

private:
	
	struct TransformBuffer
	{
		DirectX::XMMATRIX world;
		DirectX::XMMATRIX worldviewProj;
		DirectX::XMMATRIX texTransform;
		DirectX::XMFLOAT3 eyePos;
	};
	
protected:
	TransformBuffer _TransformBuffer;
	
	mutable std::unique_ptr<VSConstBuff<TransformBuffer>> m_TransformBuffer;
	const Drawable& parent;
	bool texUsed = false;
};