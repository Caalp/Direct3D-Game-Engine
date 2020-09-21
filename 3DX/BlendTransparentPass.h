#pragma once
#include "RenderQueuePass.h"


class BlendTransparentPass : public RenderQueuePass
{
public:
	BlendTransparentPass(Graphics& gfx, std::string passName);
	void Execute(Graphics& gfx) override;
	void Reset();


};