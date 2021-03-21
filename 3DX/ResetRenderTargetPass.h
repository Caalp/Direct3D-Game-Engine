#pragma once
#include "BindingPass.h"
#include "RenderGraph.h"



class ResetRenderTargetPass : public BindingPass
{
public:

	ResetRenderTargetPass(RenderGraph& rg,std::string passName);
	void Execute(Graphics& gfx) override;
	void Reset() override;
private:
	RenderGraph& rg;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> shaderResourceView;
};