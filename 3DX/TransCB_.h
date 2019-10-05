#pragma once
#include "DrawableBase.h"
#include "ConstBuffs.h"
#include "Camera.h"
class TransCB_ : public Bindables
{
	
public:
	//TransCB_(Graphics& gfx);
	TransCB_(Graphics& gfx, const DrawableBase& parent);
	void Bind(Graphics& gfx) override;
	
	void SetviewM_(Graphics& gfx,DirectX::XMMATRIX vm);
	/*void SetprojM_(Graphics& gfx,DirectX::XMMATRIX pm);
	void SetworldM_(Graphics& gfx,DirectX::XMMATRIX wm);*/
protected:
	//const DrawableBase& db0;
	static std::unique_ptr<VSConstBuff<DirectX::XMMATRIX>> projMatrix_;
	static std::unique_ptr<VSConstBuff<DirectX::XMMATRIX>> viewMatrix_;
	static std::unique_ptr<VSConstBuff<DirectX::XMMATRIX>> worldMatrix_;
	//static std::unique_ptr<VSConstBuff<DirectX::XMMATRIX>> pVcbuf;
	const DrawableBase& parent;
	
};