#include <typeinfo>
#include "RenderGraph.h"
#include "RenderQueuePass.h"

RenderGraph::RenderGraph(Graphics& gfx) : backBuffer(gfx.GetTarget()), depthBuffer(std::make_shared<OutputOnlyDepthBuffer>(gfx))
{
	AddGlobalSink(DirectBufferSink<RenderTarget>::Make("backbuffer", backBuffer));
	AddGlobalSource(DirectBufferSource<RenderTarget>::Make("backbuffer", backBuffer));

	AddGlobalSource(DirectBufferSource<DepthStencil>::Make("depthbuffer", depthBuffer));
	AddGlobalSink(DirectBufferSink<DepthStencil>::Make("depthbuffer", depthBuffer));
}

RenderQueuePass* RenderGraph::GetRenderQueuePass(const std::string& techName)
{
	try
	{
		for (const auto& p : passes)
		{
			if (p->GetPassName() == techName)
			{
				return dynamic_cast<RenderQueuePass*>(p.get());
			}
		}
	}
	catch (std::bad_cast& e)
	{
		throw(e.what());
	}
	return nullptr;
}

void RenderGraph::AddGlobalSource(std::unique_ptr<Source> source)
{
	globalSources.emplace_back(std::move(source));
}

void RenderGraph::AddGlobalSink(std::unique_ptr<Sink> sink)
{
	globalSinks.emplace_back(std::move(sink));
}

const std::unique_ptr<Pass>& RenderGraph::GetPassByName(std::string passName) const
{
	for (auto& e : passes)
	{
		if (e->GetPassName() == passName)
			return e;
	}
	return nullptr;
}

void RenderGraph::AppendPass(std::unique_ptr<Pass> pass)
{
	// auto& sink = pass->GetSinks();
	auto dispatchName = [=](std::string name)
	{
		std::string* a = new std::string[2];
		int i = 0;
		for (const auto& elem : name)
		{
			if (elem != '.' && i < 2)
			{
				a[i] += elem;
			}
			else
			{
				i++;
			}
		}
		return a;
	};
	// GetSink here return vector of unique_ptr of sinks
	std::string* dissolvedName = nullptr;
	for (const auto& si : pass->GetSinks())
	{
		dissolvedName = dispatchName(si->GetTargetName());
		std::string b = dissolvedName[1];
		if (dissolvedName[0] == "$")
		{
			// Get Sink by name(from global) and init our sink with it
			for (auto& elem : globalSources)
			{
				if (dissolvedName[1] == elem->GetName())
				{
					si->Bind(*elem);
					break;
				}
			}
		}
		else
		{
			// Figure out how to bind sink from already binded ones
			for (const auto& p : passes)
			{
				if (p->GetPassName() == dissolvedName[0])
				{

					// Get the the source which has the same name from passes's sources
					Source& s = p->GetSource(dissolvedName[1]);
					si->Bind(s);
					break;
				}
			}
		}
	}
	if (!dissolvedName)
		delete dissolvedName;
	passes.push_back(std::move(pass));
}

void RenderGraph::Execute(Graphics& gfx)
{
	for (const auto& pass : passes)
	{
		pass->Execute(gfx);
	}
}

void RenderGraph::Reset()
{
	for (const auto& p : passes)
	{
		p->Reset();
	}
}