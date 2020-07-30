#pragma once
#include <string>
#include "Step.h"

class RenderGraph;

class Technique
{
public:
	Technique(std::string techName, bool status = true);
	
	Technique(std::string techName, size_t techChannel, bool status = true);
	void Link(RenderGraph& rg);
	void Submit(Drawable& d, size_t channel);
	void AddStep(Step& step);
	

private:
	bool isActive = true;
	std::string techniqueName;
	unsigned int techniqueChannel;
	std::vector<Step> steps;
	
};

