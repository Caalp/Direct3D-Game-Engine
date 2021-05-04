#include "Job.h"
#include "Drawable.h"
#include "DrawCallDispatch.h"
#include "Step.h"
#include "Components.h"


Job::Job(const Step & s, const Renderable & d) : step(&s), m_Renderable(&d)
{
}

void Job::Execute(Graphics& gfx)
{
	
	m_Renderable->Bind(gfx);
	step->Bind(gfx);
	step->Draw(gfx);
	//gfx.DrawIndexed(drawable.GetIndexCount());
}

