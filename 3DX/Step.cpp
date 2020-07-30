#include "Step.h"
#include "RenderQueuePass.h"
#include "Bindable.h"
#include "Drawable.h"
#include "RenderGraph.h"

Step::Step(std::string ID) : targetPassName(std::move(ID))
{
	
}

void Step::AddBind(std::shared_ptr<Bindable> bindable)
{
	bindables.push_back(std::move(bindable));
}

void Step::Submit(Drawable& d)
{
	targetPass->Accept(Job{ *this,d });
}

void Step::Link(RenderGraph& rg)
{
	// Check if targetPass is already linked
	assert(targetPass == nullptr);
	// Get the renderQueuePass from argument RenderQueue
	targetPass = &rg.GetRenderQueuePass(targetPassName);
}

void Step::Bind(Graphics & gfx) const 
{
	for (auto& elem : bindables)
	{
		elem->Bind(gfx);
	}
}


const std::string& Step::GetTargetPassName() const
{
	return targetPassName;
}
