#pragma once
#include "Graphics.h"
#include "Camera.h"
#include "GraphicsResources.h"

class Bindable
{
	
public:
	virtual void Bind(Graphics& gfx) = 0;
	virtual void Bind(Graphics& gfx, UINT, UINT) {};
	
	virtual ~Bindable() = default;

protected:

	static const std::shared_ptr<RenderTarget>& GetTarget(Graphics& gfx);
};