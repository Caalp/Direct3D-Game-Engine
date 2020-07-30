#include "RenderQueuePass.h"

void RenderQueuePass::Accept(Job job)
{
	jobs.push_back(job);
}

void RenderQueuePass::Execute(Graphics& gfx)
{
	BindAll(gfx);
	for (auto& job : jobs)
	{
		job.Execute(gfx);
	}
}

void RenderQueuePass::Reset()
{
	jobs.clear();
}
