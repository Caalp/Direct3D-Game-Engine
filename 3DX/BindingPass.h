#pragma once
#include "Pass.h"
#include "Bindable.h"
#include "RenderTarget.h"
#include "DepthStencil.h"



class BindingPass : public Pass
{
	
public:
	
	BindingPass(std::string passName);
	void AddBind(std::unique_ptr<Bindable> bind);
	void BindAll(Graphics& gfx);
protected:
	std::shared_ptr<RenderTarget> renderTarget;
	std::shared_ptr<DepthStencil> depthStencil;
	
private:
	void BindBufferResources(Graphics& gfx);
private:

	std::vector<std::unique_ptr<Bindable>> binds;

};