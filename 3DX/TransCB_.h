#pragma once
#include "DrawableBase.h"
#include "ConstBuffs.h"
#include "Camera.h"
class TransCB_ : public Bindables
{
	
public:
	TransCB_(Graphics& gfx, const DrawableBase& parent);
	void Bind(Graphics& gfx) override;
	
protected:
	static std::unique_ptr<VSConstBuff<DirectX::XMMATRIX>> TransMatrix_;
	const DrawableBase& parent;
	
};