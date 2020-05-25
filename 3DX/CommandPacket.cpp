
#include "Drawable.h"

CommandPacket::CommandPacket(Drawable * drawable)
{
	//assert(drawable, "Drawable is not initialized");
	pDrawable = drawable;
}

void CommandPacket::PushStep(const Step & step)
{
	steps.push_back(std::move(step));
}

void CommandPacket::Bind(Graphics& gfx)
{
	pDrawable->Bind(gfx);
	for (auto& elem : steps)
	{
		elem.Bind(gfx);
	}
	gfx.DrawIndexed(pDrawable->GetIndexCount());

}
