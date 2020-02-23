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
	
	
	//
	//if (blendOn)
	//{
	//	//pBlendState->ResetBlendState(gfx);
	//	pBlendState->Bind(gfx);
	//	blendOn = false;
	//}
	gfx.DrawIndexed(pIndexBuffer->GetIndexCount());
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


void Drawable::AddBind(std::unique_ptr<Bindable> binds)
{
	Bindables.push_back(std::move(binds));
}

void Drawable::AddStaticBind(std::unique_ptr<Bindable> sBinds)
{
	staticBindable.push_back(std::move(sBinds));
}

//std::vector<std::unique_ptr<Bindable>> Drawable::staticBindable;