#pragma once
#include "Graphics.h"
#include "Camera.h"



class Bindable
{
	friend class DrawableBase;
public:
	virtual void Bind(Graphics& gfx) = 0;
	virtual void Bind(Graphics& gfx, UINT, UINT) {};
	
	virtual ~Bindable() = default;

protected:
	static ID3D11Device* GetDevice(Graphics& gfx);
	static ID3D11DeviceContext* GetContext(Graphics& gfx);
	static ID3D11RenderTargetView* GetTarget(Graphics& gfx);
};