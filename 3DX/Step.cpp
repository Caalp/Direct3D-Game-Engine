#include "Step.h"

Step::Step(const std::string ID)
{
	stepID = ID;
}

void Step::AddBind(std::shared_ptr<Bindable> bindable)
{
	bindables.push_back(std::move(bindable));
}

void Step::Bind(Graphics & gfx)
{
	for (auto& elem : bindables)
	{
		elem->Bind(gfx);
	}
}

