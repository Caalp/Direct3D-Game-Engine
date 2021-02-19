#pragma once
#include <d3d11.h>

class Graphics;

class BufferResource
{

public:
	virtual ~BufferResource() = default;
	virtual void BindAsBuffer(Graphics& gfx) = 0;
	virtual void BindAsBuffer(Graphics& gfx, BufferResource* depth) = 0;
	virtual void Clear(Graphics& gfx) = 0;
	virtual void GetResource(ID3D11Resource** resource) = 0;
};