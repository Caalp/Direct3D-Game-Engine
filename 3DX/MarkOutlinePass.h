#pragma once
#include "RenderQueuePass.h"


class MarkOutlinePass : public RenderQueuePass
{

public:
	MarkOutlinePass(Graphics& gfx, std::string passName);
	void Execute(Graphics& gfx) override;
	void Reset();

};