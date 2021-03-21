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
	void Deactivate();
	void SetTechID(uint32_t id);
	uint32_t GetTechID() const;
	void AddStep(Step& step);
	std::string GetName() const;

private:
	bool isActive = true;
	uint32_t techID;
	std::string techniqueName;
	unsigned int techniqueChannel;
	std::vector<Step> steps;
	
};

