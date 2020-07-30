#pragma once
#include "Graphics.h"
#include "Camera.h"


class Bindable
{
	
public:
	virtual void Bind(Graphics& gfx) = 0;
	virtual void Bind(Graphics& gfx, UINT, UINT) {};
	
	virtual ~Bindable() = default;

protected:
	static ID3D11Device* GetDevice(Graphics& gfx);
	static ID3D11DeviceContext* GetContext(Graphics& gfx);
	static const std::shared_ptr<RenderTarget>& GetTarget(Graphics& gfx);
};