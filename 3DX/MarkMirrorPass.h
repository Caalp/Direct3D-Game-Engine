#pragma once
#include "RenderQueuePass.h"


class MarkMirrorPass : public RenderQueuePass
{
public:
	MarkMirrorPass(Graphics& gfx, std::string passName);
	void Execute(Graphics& gfx) override;
	void Reset();


};