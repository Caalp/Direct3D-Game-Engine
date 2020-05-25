#pragma once
#include "Bindables.h"
#include <vector>
#include <memory>
#include <string>
class Step
{
public:
	Step(const std::string ID);
	void AddBind(std::shared_ptr<Bindables> bindable);
	void Bind(Graphics& gfx);
private:
	std::string stepID;
	std::vector<std::shared_ptr<Bindables>> bindables;

};