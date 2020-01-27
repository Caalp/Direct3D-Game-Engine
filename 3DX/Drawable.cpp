#include "Drawable.h"

void Drawable::Draw(Graphics & gfx)
{
	for (auto& b : bindables)
	{
		
		if (typeid(*b) == typeid(IndexBuff))
		{
			pIndexBuffer = dynamic_cast<IndexBuff*>(b.get());
		}
		b->Bind(gfx);
	}
	for (auto& b : staticBindables)
	{
		if (typeid(*b) == typeid(IndexBuff))
		{
			pIndexBuffer = dynamic_cast<IndexBuff*>(b.get());
		}
		b->Bind(gfx);
	}

	gfx.DrawIndexed(pIndexBuffer->GetIndexCount());
}

void Drawable::AddIndexBuffer(std::shared_ptr<class IndexBuff> indexBuffer)
{
	pIndexBuffer = indexBuffer.get();
}

void Drawable::SetIndexBufferFromStatic()
{
	for (auto& elem : staticBindables)
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
	if (staticBindables.empty())
	{
		return false;
	}
	return true;
}

void Drawable::AddBind(std::unique_ptr<Bindables> binds)
{
	bindables.push_back(std::move(binds));
}

void Drawable::AddStaticBind(std::unique_ptr<Bindables> sBinds)
{
	staticBindables.push_back(std::move(sBinds));
}

//std::vector<std::unique_ptr<Bindables>> Drawable::staticBindables;