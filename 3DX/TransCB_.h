#pragma once
#include "DrawableBase.h"
#include "ConstBuffs.h"
class TransCB_ : public Bindables
{
	
public:
	TransCB_(Graphics& gfx, const DrawableBase& db);
	void Bind(Graphics& gfx);
protected:
	std::unique_ptr<VSConstBuff<DirectX::XMMATRIX>> viewMatrix_;
	std::unique_ptr<VSConstBuff<DirectX::XMMATRIX>> projMatrix_;
	std::unique_ptr<VSConstBuff<DirectX::XMMATRIX>> WorldMatrix_;

};