#pragma once
#include "BufferResource.h"
#include "DSS.h"
#include "Drawable.h"

// New child classes can be created like RenderTarget example
class DepthStencil : public Bindable, public BufferResource
{
	friend class RenderTarget;
public:
	DepthStencil(Graphics& gfx);
	DepthStencil(Graphics& gfx,UINT width,UINT height);
	DepthStencil(Graphics& gfx, UINT width, UINT height,UINT state);
	void GetResource(ID3D11Resource** resource) override { this->shaderResourceView.Get()->GetResource(resource); }
	DepthStencil(Graphics& gfx, ID3D11Texture2D* tex, UINT state);
	void BindAsBuffer(Graphics& gfx) override;
	void BindAsBuffer(Graphics& gfx, BufferResource* depth) override;
	void Clear(Graphics& gfx) override;

public:
	UINT width;
	UINT height;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depthStencilView;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> shaderResourceView;

};

class OutputOnlyDepthBuffer : public DepthStencil
{
public:
	OutputOnlyDepthBuffer(Graphics& gfx);
	OutputOnlyDepthBuffer(Graphics& gfx, UINT width, UINT height);
	void Bind(Graphics& gfx) override;
};


class ShaderResourceDS : public DepthStencil
{
/// <summary>
/// Depth Buffer which can be binded as shader resource later.
/// </summary>
public:
	ShaderResourceDS(Graphics& gfx);
	ShaderResourceDS(Graphics& gfx, UINT width, UINT height);
	void Bind(Graphics& gfx) override;
};