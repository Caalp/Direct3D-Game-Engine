#pragma once
#include "RenderQueuePass.h"

class SkyBoxPass :public RenderQueuePass
{
public:
	SkyBoxPass(Graphics& gfx, std::string passName);
	void Execute(Graphics& gfx) override;
	void Reset();
};