#pragma once
#include "Bindable.h"
#include <vector>
#include <memory>
#include <string>
class Step
{
public:
	Step(const std::string ID);
	void AddBind(std::shared_ptr<Bindable> bindable);
	void Bind(Graphics& gfx);
private:
	std::string stepID;
	std::vector<std::shared_ptr<Bindable>> bindables;

};