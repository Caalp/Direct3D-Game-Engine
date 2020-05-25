#pragma once
#include "Step.h"
#include <vector>

class Drawable;

class CommandPacket
{
	
public:
	
	CommandPacket(Drawable* drawable);
	void PushStep(const Step& step);
	void Bind(Graphics& gfx);

private:
	class Drawable* pDrawable;
	std::vector<Step> steps;
};