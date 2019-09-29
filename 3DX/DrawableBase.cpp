#include "DrawableBase.h"

void DrawableBase::AddBind(std::unique_ptr<Bindables> binds)
{
	bindables.push_back(std::move(binds));
}
