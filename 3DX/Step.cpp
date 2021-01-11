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
	OutputDebugString(typeid(bindable.get()).name());
		
	bindables.push_back(std::move(bindable));
}

void Step::AddBind(const std::shared_ptr<IBackendDispatch>& drawFunc)
{
	mDrawFunc.push_back(drawFunc);
}

void Step::Submit(Drawable& d)
{
	targetPass->Accept(Job{ *this,d });
}

void Step::Link(RenderGraph& rg)
{
	// Check if targetPass is already linked
	//assert(targetPass == nullptr);
	// Get the renderQueuePass from argument RenderQueue
	if (!targetPass)
	{
		targetPass = rg.GetRenderQueuePass(targetPassName);
	}
	/*if (!targetPass)
	{
		printf("[ERROR]-Attempt linking against target pass %s failed!\n", targetPassName.c_str());
	}*/
	
	
}

void Step::Bind(Graphics & gfx) const 
{
	//OutputDebugString(typeid(mDrawFunc.get()).name());
	//DrawExample* dw = dynamic_cast<DrawExample*>(mDrawFunc.get());
	for (auto& elem : bindables)
	{
		elem->Bind(gfx);
	}
}


void Step::Draw(Graphics& gfx) const 
{
	for (auto elem : mDrawFunc)
	{
		elem->Draw(gfx);
	}
	
}


const std::string& Step::GetTargetPassName() const
{
	return targetPassName;
}

bool Step::isLinked() const
{
	return linked;
}
