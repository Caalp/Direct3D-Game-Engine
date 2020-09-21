#pragma once
#include "RenderQueuePass.h"

class DefaultPass : public RenderQueuePass
{
public:
	DefaultPass(Graphics& gfx,std::string passName);
	void Execute(Graphics& gfx);
	void Reset();
};