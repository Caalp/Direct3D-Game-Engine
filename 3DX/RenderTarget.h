#pragma once
#include "BufferResource.h"
#include "Bindable.h"


class DepthStencil;
// TO DO : set viewport after setting render target

class RenderTarget : public Bindable, public BufferResource
{
public:
	RenderTarget(Graphics& gfx, UINT width, UINT height);
	RenderTarget(Graphics& gfx, ID3D11Texture2D* texture);
	void BindAsBuffer(Graphics& gfx) override;
	void BindAsBuffer(Graphics& gfx, BufferResource* depth) override;
	// For view count new parameter can be added
	void BindAsBuffer(Graphics& gfx, DepthStencil* depth);
	void Clear(Graphics& gfx) override;
	void Clear(Graphics& gfx, const float color[4]);
	UINT GetWidth() const;
	UINT GetHeight() const;
	void Bind(Graphics& gfx);
protected:
	UINT width;
	UINT height;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTargetView;
};


class ShaderViewRenderTarget : public RenderTarget
{

public:
	ShaderViewRenderTarget(Graphics& gfx, UINT width, UINT Height, UINT slot);
	void BindAsBuffer(Graphics& gfx) override;
	
private:
	UINT slot;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> shaderResourceView;
};


class BackBuffer : public RenderTarget
{
public:

	BackBuffer(Graphics& gfx,ID3D11Texture2D* texture);
	void Bind(Graphics& gfx);
};