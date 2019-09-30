#include "DrawableBase.h"

void DrawableBase::Draw(Graphics & gfx)
{
	for (auto& b : bindables)
	{
		b->Bind(gfx);
	}
	for (auto& b : GetStaticBindables())
	{
		b->Bind(gfx);
	}
	
	gfx.DrawIndexed(36u);
}

void DrawableBase::AddBind(std::unique_ptr<Bindables> binds)
{
	bindables.push_back(std::move(binds));
}
