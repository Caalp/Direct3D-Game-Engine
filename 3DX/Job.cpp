#include "Job.h"
#include "DrawCallDispatch.h"
#include "Step.h"
#include "Renderable.h"


Job::Job(const Step& s, const Renderable& d) : m_step(s), m_renderable(d)
{
}


void Job::Execute(Graphics& gfx)
{
	
	m_renderable.Bind();
	m_step.Bind();
	m_step.Draw();
}
