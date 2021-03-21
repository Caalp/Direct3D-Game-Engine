#include "Step.h"
#include "RenderQueuePass.h"
#include "Bindable.h"
#include "Drawable.h"
#include "RenderGraph.h"
#include <assert.h>

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
	if (targetPass)
	{
		targetPass->Accept(Job{ *this,d });
	}
	else
	{
		printf("TargetPass is not linked for drawable %s", d.GetName().c_str());
		assert(targetPass != NULL && "TargetPass is not linked for drawable");
	}
	
}

void Step::Link(RenderGraph& rg)
{
	// targetPass can be linked only once
	if (!targetPass)
	{
		targetPass = rg.GetRenderQueuePass(targetPassName);
		
		// targetPass may not be initialized if given RenderGraph doesn't have the targetPass
		// According to the result assign the linked's value
		linked = (targetPass) ? true : false;
	}
	else
	{
		printf("Trying to re-link already initialized targetPass %s", this->targetPassName.c_str());
		assert(targetPass == nullptr);
		
	}

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
