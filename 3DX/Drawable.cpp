#include "Drawable.h"

void Drawable::SetBlendState(bool state)
{
	blendOn = state;
}

void Drawable::Draw(Graphics & gfx)
{



	for (auto& b : Bindables)
	{

		if (typeid(*b) == typeid(IndexBuff))
		{
			pIndexBuffer = dynamic_cast<IndexBuff*>(b.get());
		}
		if (typeid(*b) == typeid(BlendState))
		{
			pBlendState = dynamic_cast<BlendState*>(b.get());

		}
		b->Bind(gfx);
	}
	for (auto& b : staticBindable)
	{
		if (typeid(*b) == typeid(IndexBuff))
		{
			pIndexBuffer = dynamic_cast<IndexBuff*>(b.get());
		}
		if (typeid(*b) == typeid(BlendState))
		{
			pBlendState = dynamic_cast<BlendState*>(b.get());

		}
		b->Bind(gfx);
	}
	while (!renderStates.empty())
	{
		renderStates.top()->Bind(gfx);
		renderStates.pop();
	}

	gfx.Draw(16, 0);
	//
	//if (blendOn)
	//{
	//	//pBlendState->ResetBlendState(gfx);
	//	pBlendState->Bind(gfx);
	//	blendOn = false;
	//}
	// Temporary work around for tree drawing
	/*if (pIndexBuffer == nullptr)
	{
		gfx.DrawVertexed(3, 0);
	}
	else
	{
		gfx.DrawIndexed(pIndexBuffer->GetIndexCount());
	}*/
}

void Drawable::AddIndexBuffer(std::shared_ptr<class IndexBuff> indexBuffer)
{
	pIndexBuffer = indexBuffer.get();
}

void Drawable::SetIndexBufferFromStatic()
{
	for (auto& elem : staticBindable)
	{
		if (typeid(*elem) == typeid(IndexBuff))
		{
			pIndexBuffer = dynamic_cast<IndexBuff*>(elem.get());
			return;
		}
	}
}

bool Drawable::isStaticallyBinded() const
{
	if (staticBindable.empty())
	{
		return false;
	}
	return true;
}

void Drawable::SetRS(Graphics & gfx, RasterizerState::RasterizerType rType)
{
	renderStates.push(std::make_unique<RasterizerState>(gfx, rType));
}

void Drawable::SetBS(Graphics & gfx, BlendState::BlendType bType)
{
	renderStates.push(std::make_unique<BlendState>(gfx, true, bType));
}

void Drawable::SetDSS(Graphics & gfx, DSS::DSSType dType)
{
	renderStates.push(std::make_unique<DSS>(gfx, dType));
}


void Drawable::AddBind(std::unique_ptr<Bindable> binds)
{
	Bindables.push_back(std::move(binds));
}

void Drawable::AddStaticBind(std::unique_ptr<Bindable> sBinds)
{
	staticBindable.push_back(std::move(sBinds));
}

//std::vector<std::unique_ptr<Bindable>> Drawable::staticBindable;